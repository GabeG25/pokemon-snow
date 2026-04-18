# Pokemon Snow Smoke-Test Harness

## Why this exists

Static analysis (audit_scripts.py + `make` success) catches *spelling* bugs (missing constants, dangling labels, charset issues, flag collisions). It does **not** catch *behavioral* bugs:

- Warp lands on the wrong tile / blocks re-exit
- ON_FRAME script never registered, cutscene doesn't auto-fire
- NPC sprite hidden behind wall / coord_event in unreachable position
- `goto_if_set` references the wrong flag
- Soft-locks where the script runs but the player can't move
- Map connections wired wrong, walking off the edge re-enters the same map

These are the entire content of the 2026-04-17 playtest bug list. Audit was clean while six intro events were unplayable.

This harness closes the loop by giving an AI agent (or human) machine-readable evidence of what actually happened in-game.

## What's here today (session 1)

`snow_smoke_state.lua` — minimal mGBA Lua script. Every 30 frames reads `gSaveBlock1Ptr -> {pos.x, pos.y, location.{mapGroup,mapNum,warpId}, FLAG_SNOW_GOT_CANDY_BOX, FLAG_SNOW_INTRO_MOM_CUTSCENE_DONE, VAR_SNOW_INTRO_STATE}` and appends a JSON line to `/tmp/snow-smoke.log`. Suppresses duplicate consecutive lines so the log shows state *transitions*.

## How to use it (today)

1. **Install mGBA** if not present: `sudo apt install -y mgba-qt` (Ubuntu 24.04 ships 0.10.2, has Lua 5.4 built in).
2. **Open the ROM** in mGBA: File → Load ROM → `~/pokemon-snow/pokeemerald.gba`.
3. **Load the script**: Tools → Scripting → Load script → `dev_scripts/smoke/snow_smoke_state.lua`. The scripting console should print `[snow-smoke] script loaded; sampling every 30 frames`.
4. **Play the intro**: New game → name → bedroom wake-up → press A on candy box → leave bedroom → walk down to mom → leave house. The script writes to `/tmp/snow-smoke.log`.
5. **Read the log** to verify state changes happened where they should:
   ```
   tail -f /tmp/snow-smoke.log
   ```

Expected progression on a working build:
- Bedroom wake-up: `intro_state=0`, `got_candy=false`, `mom_done=false`
- After A on candy box: `got_candy=true`
- After mom downstairs cutscene: `mom_done=true`, `intro_state=2`
- After leaving house: `map` changes from `(MAP_PLAYERS_HOUSE_1F)` → `(MAP_DAWNFLAKE_TOWN)` and `pos` resets

If any of those don't transition: you've found a bug that audit can't see.

## Roadmap

### Session 2 — Add input automation
- Python driver invoking `mgba-rom-test` headlessly (or mGBA-http sidecar)
- Scripted button sequences for the intro (savestate-anchored)
- Screenshot capture at each named checkpoint, written to `/tmp/snow-smoke-frames/`
- AI agent views screenshots multimodally and asserts visual expectations

### Session 3 — Codify the intro scenario
- Single Python file `scenarios/intro.py` with named checkpoints + state assertions:
  - `assert state.var('VAR_SNOW_INTRO_STATE') == 1 after press('A', frames=120)` at the bedroom
  - `assert state.flag('FLAG_SNOW_GOT_CANDY_BOX') == True after walk_to(5, 4)`
  - `assert state.map() == (DAWNFLAKE_TOWN_PLAYERS_HOUSE_1F) after exit_warp()`
- Pass/fail per checkpoint. CI-friendly exit code.

### Session 4+ — Per-feature scenarios
Every new content session (gym, rival fight, hidden item, new map) adds a scenario file before declaring "done." No commit ships gameplay flow without a scenario verifying it.

## Why this approach over alternatives

- **vs. CEO playtest only**: doesn't scale; CEO can't catch silent flag-collision bugs by feel; CEO time is precious.
- **vs. full agentic Claude-plays-Pokemon loop**: overkill for bug detection; scripted scenarios + assertions hit ~90% of warp/event/flag bugs at a fraction of the LLM-tokens-per-bug cost.
- **vs. extending in-ROM `make check` test runner**: that suite is for battle/script-interpreter unit tests. Driving the overworld from inside the ROM would require building a synthetic input layer; far more invasive than scripting an emulator from outside.

## Conventions

- All scenarios live under `dev_scripts/smoke/scenarios/`
- All log output goes under `/tmp/snow-smoke*` (gitignored, ephemeral)
- Lua / Python scripts grep-verify constant names against `include/constants/` headers at startup so a renamed flag fails loudly instead of silently reading the wrong byte
- Every memory address / offset has a verification anchor comment pointing to the source file and line
