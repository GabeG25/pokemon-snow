-- snow_smoke_state.lua
-- Pokemon Snow runtime state dumper for mGBA.
--
-- Reads SaveBlock1 every FRAME_INTERVAL frames and appends a JSON line to
-- LOG_PATH so a human or AI agent can verify the player's path/state through
-- the intro sequence (and later, any scripted scenario) without having to
-- watch the screen frame-by-frame.
--
-- Verification anchors (DO NOT EDIT without re-verifying):
--   gSaveBlock1Ptr IWRAM addr 0x030051D0   pokeemerald.map:5592
--   SaveBlock1.flags offset 0x1270         FlagGet literal pool @ 0x8119fb4
--   SaveBlock1.vars offset 0x13B8          GetVarPointer literal pool: 0xffffc9dc
--                                          (id - 0x3624) << 1 yields offset
--                                          NB: global.h /*0x139C*/ comment is
--                                          STALE under the project's expanded
--                                          NUM_FLAG_BYTES; trust the ELF.
--   FLAG_SNOW_GOT_CANDY_BOX = 0x20         include/constants/flags.h:55
--   FLAG_SNOW_INTRO_MOM_CUTSCENE_DONE 0x44 include/constants/flags.h:91
--   VAR_SNOW_INTRO_STATE = 0x404E          include/constants/vars.h:100
--
-- Load via mGBA: Tools -> Scripting -> Load script... and pick this file.
-- Output appears in /tmp/snow-smoke.log AND mGBA's scripting console.

local LOG_PATH = "/tmp/snow-smoke.log"
local FRAME_INTERVAL = 30  -- ~half a second at 60fps

local SB1_PTR_ADDR   = 0x030051D0  -- IWRAM symbol gSaveBlock1Ptr (4 bytes)

local OFF_POS_X      = 0x00    -- u16
local OFF_POS_Y      = 0x02    -- u16
local OFF_LOC_GROUP  = 0x04    -- s8
local OFF_LOC_NUM    = 0x05    -- s8
local OFF_LOC_WARPID = 0x06    -- s8
local OFF_FLAGS      = 0x1270  -- u8 array (NUM_FLAG_BYTES bytes), per FlagGet pool
local OFF_VARS       = 0x13B8  -- u16 array, per GetVarPointer pool (NOT 0x139C)

local FLAG_SNOW_GOT_CANDY_BOX           = 0x20
local FLAG_SNOW_INTRO_MOM_CUTSCENE_DONE = 0x44
local VAR_SNOW_INTRO_STATE              = 0x404E
local VARS_START                        = 0x4000

local frame_count = 0
local log_file = nil
local last_line = nil

local function read_flag(sb1, flag_id)
  local byte = emu:read8(sb1 + OFF_FLAGS + (flag_id // 8))
  return ((byte >> (flag_id & 7)) & 1) == 1
end

local function read_var(sb1, var_id)
  return emu:read16(sb1 + OFF_VARS + ((var_id - VARS_START) * 2))
end

local function dump_state()
  local sb1 = emu:read32(SB1_PTR_ADDR)
  if sb1 == 0 then return end  -- pre-NewGame; SaveBlock1 not allocated yet

  local px        = emu:read16(sb1 + OFF_POS_X)
  local py        = emu:read16(sb1 + OFF_POS_Y)
  local map_group = emu:read8(sb1 + OFF_LOC_GROUP)
  local map_num   = emu:read8(sb1 + OFF_LOC_NUM)
  local warp_id   = emu:read8(sb1 + OFF_LOC_WARPID)
  local intro     = read_var(sb1, VAR_SNOW_INTRO_STATE)
  local candy     = read_flag(sb1, FLAG_SNOW_GOT_CANDY_BOX)
  local mom_done  = read_flag(sb1, FLAG_SNOW_INTRO_MOM_CUTSCENE_DONE)

  local line = string.format(
    '{"frame":%d,"sb1":"0x%08x","x":%d,"y":%d,"map":"%d.%d","warp":%d,"intro_state":%d,"got_candy":%s,"mom_done":%s}',
    frame_count, sb1, px, py, map_group, map_num, warp_id, intro,
    tostring(candy), tostring(mom_done))

  -- Suppress duplicate consecutive lines so the log captures CHANGES, not noise
  if line ~= last_line then
    if log_file then
      log_file:write(line .. "\n")
      log_file:flush()
    end
    console:log(line)
    last_line = line
  end
end

local function open_log()
  log_file = io.open(LOG_PATH, "w")
  if log_file then
    log_file:write("# snow_smoke_state.lua started\n")
    log_file:flush()
    console:log("[snow-smoke] log opened at " .. LOG_PATH)
  else
    console:error("[snow-smoke] FAILED to open log at " .. LOG_PATH)
  end
end

callbacks:add("frame", function()
  frame_count = frame_count + 1
  if (frame_count % FRAME_INTERVAL) == 0 then
    dump_state()
  end
end)

open_log()
console:log("[snow-smoke] script loaded; sampling every " .. FRAME_INTERVAL .. " frames")
