#!/usr/bin/env python3
"""Generate detailed map layouts for all Snow locations.
Each map designed from v17 spec descriptions with correct geography,
buildings, terrain features, and item placement areas.

Boralyss flows NORTH to SOUTH: snowy north → tropical south.
Dawnflake Town is northernmost. Player exits south."""

import json, struct, math, random
from pathlib import Path

random.seed(2026)
REPO = Path(__file__).resolve().parent.parent.parent

# ═══ METATILE ENCODING ═══
def T(meta, col=0, elv=3):
    return meta | (col << 10) | (elv << 12)

# Ground (elev 3, passable)
GR  = T(0x001)  # Short grass ground
GR2 = T(0x004)  # Alt ground
TG  = T(0x00D)  # Tall grass (ENCOUNTERS)
LG  = T(0x015)  # Long grass (ENCOUNTERS)

# Path system (elev 3)
PC  = T(0x1D9)  # Path center
PL  = T(0x1D8)  # Path left edge
PR  = T(0x1DA)  # Path right edge
PT  = T(0x1D1)  # Path top edge
PB  = T(0x1E1)  # Path bottom edge
PTL = T(0x1D0)  # Corner top-left
PTR = T(0x1D2)  # Corner top-right
PBL = T(0x1E0)  # Corner bottom-left
PBR = T(0x1E2)  # Corner bottom-right

# Trees (2x2 blocks, impassable)
TTL = T(0x1D4, 1, 0); TTR = T(0x1D5, 1, 0)
TBL = T(0x1DC, 1, 0); TBR = T(0x1DD, 1, 0)
# Tall grass under trees
TGL = T(0x1C6); TGR = T(0x1C7)
# Grass-tree edge
GTL = T(0x1CE); GTR = T(0x1CF)

# Cliffs/rocks (impassable)
CLD = T(0x075, 1, 0)  # Dark cliff
CLM = T(0x073, 1, 0)  # Medium cliff
CLL = T(0x071, 1, 0)  # Light cliff
RKG = T(0x079, 1, 0)  # Rock wall grass base
RKR = T(0x07C, 1, 0)  # Rock wall rock base
LDG = T(0x089, 1, 0)  # Ledge

# Water (elev 1)
WTR = T(0x170, elv=1)  # Calm water
WTE = T(0x171, elv=1)  # Water edge

# Cave (secondary tileset)
CFL = T(0x201)          # Cave floor
CF2 = T(0x211)          # Cave floor 2
CWL = T(0x211, 1, 0)   # Cave wall
CW2 = T(0x219, 1, 0)   # Cave wall 2
CW3 = T(0x209, 1, 0)   # Cave wall 3

# Buildings (Petalburg secondary tileset)
POKECENTER = [
    [T(0x26C), T(0x26D), T(0x26D), T(0x26E)],
    [T(0x274,1,0), T(0x275,1,0), T(0x275,1,0), T(0x276,1,0)],
    [T(0x27C,1,0), T(0x27F,1,0), T(0x27D,1,0), T(0x27E,1,0)],
    [T(0x284,1,0), T(0x287,1,0), T(0x28F,1,0), T(0x286,1,0)],
]
MART = [
    [T(0x230,1,0), T(0x231,1,0), T(0x232,1,0), T(0x233,1,0)],
    [T(0x238,1,0), T(0x239,1,0), T(0x23A,1,0), T(0x23B,1,0)],
    [T(0x260,1,0), T(0x241,1,0), T(0x242,1,0), T(0x243,1,0)],
]
HOUSE = [
    [T(0x248), T(0x249), T(0x282), T(0x283)],
    [T(0x250,1,0), T(0x251,1,0), T(0x252,1,0), T(0x253,1,0)],
    [T(0x258,1,0), T(0x259,1,0), T(0x25A,1,0), T(0x25B,1,0)],
    [T(0x260,1,0), T(0x261,1,0), T(0x262,1,0), T(0x263,1,0)],
]


class M:
    """Map grid with helper methods."""
    def __init__(s, w, h, fill=GR):
        s.w, s.h = w, h
        s.g = [[fill]*w for _ in range(h)]
    def s(s, x, y, t):
        if 0<=x<s.w and 0<=y<s.h: s.g[y][x]=t
    def r(s, x, y):
        return s.g[y][x] if 0<=x<s.w and 0<=y<s.h else 0
    def rect(s, x1, y1, x2, y2, t):
        for y in range(max(0,y1),min(s.h,y2+1)):
            for x in range(max(0,x1),min(s.w,x2+1)): s.g[y][x]=t
    def bld(s, x, y, p):
        for dy,row in enumerate(p):
            for dx,t in enumerate(row): s.s(x+dx,y+dy,t)
    def tree(s, x, y):
        s.s(x,y,TTL); s.s(x+1,y,TTR); s.s(x,y+1,TBL); s.s(x+1,y+1,TBR)
    def trees(s, t=2):
        for y in range(0,s.h,2):
            for x in range(0,s.w,2):
                b = x<t*2 or x>=s.w-t*2 or y<t*2 or y>=s.h-t*2
                if b: s.tree(x,y)
    def path_v(s, x, y1, y2, w=3):
        for y in range(min(y1,y2),max(y1,y2)+1):
            for dx in range(-(w//2),w//2+1): s.s(x+dx,y,PC)
    def path_h(s, y, x1, x2, w=3):
        for x in range(min(x1,x2),max(x1,x2)+1):
            for dy in range(-(w//2),w//2+1): s.s(x,y+dy,PC)
    def wind_v(s, cx, y1, y2, w=3, amp=3, per=10):
        for y in range(min(y1,y2),max(y1,y2)+1):
            off=int(amp*math.sin(y*2*math.pi/per))
            for dx in range(-(w//2),w//2+1): s.s(cx+off+dx,y,PC)
    def grass_o(s, cx, cy, rx, ry):
        for y in range(s.h):
            for x in range(s.w):
                if ((x-cx)/max(rx,1))**2+((y-cy)/max(ry,1))**2<=1:
                    if s.r(x,y) in (GR,GR2): s.s(x,y,TG)
    def scat_trees(s, x1, y1, x2, y2, d=0.08):
        for y in range(y1,y2-1,2):
            for x in range(x1,x2-1,2):
                if random.random()<d:
                    if all(s.r(x+a,y+b) in (TG,GR,LG) for a in range(2) for b in range(2)):
                        s.tree(x,y)
    def ent_s(s, cx, w=5):
        for x in range(cx-w//2,cx+w//2+1):
            for y in range(s.h-4,s.h): s.s(x,y,GR)
    def ent_n(s, cx, w=5):
        for x in range(cx-w//2,cx+w//2+1):
            for y in range(4): s.s(x,y,GR)
    def ent_e(s, cy, w=3):
        for y in range(cy-w//2,cy+w//2+1):
            for x in range(s.w-4,s.w): s.s(x,y,GR)
    def ent_w(s, cy, w=3):
        for y in range(cy-w//2,cy+w//2+1):
            for x in range(4): s.s(x,y,GR)
    def clearing(s, cx, cy, rw=3, rh=1):
        s.rect(cx-rw,cy-rh,cx+rw,cy+rh,GR)
    def item_spot(s, x, y):
        """Mark a visible item ball location."""
        s.s(x,y,GR)
    def to_bytes(s):
        o=bytearray()
        for row in s.g:
            for t in row: o+=struct.pack("<H",t)
        return bytes(o)


# ═══════════════════════════════════════════════════
# ACT 1 — HEAVY SNOW ZONE (Northernmost)
# ═══════════════════════════════════════════════════

def dawnflake_town():
    """Northernmost town. 3 houses + Evergreen Lab. Exits SOUTH. Cozy."""
    w,h = 30,26
    m = M(w,h,GR)
    m.trees(2)
    cx = w//2
    # Main path N-S (player walks south to leave)
    m.path_v(cx, 4, h-1, 3)
    # East-west residential path (upper third)
    m.path_h(9, 5, w-6, 3)
    # Player's house (northwest) — mom heals, Candy Box under bed
    m.bld(5, 4, HOUSE)
    m.path_v(7, 8, 9)
    # Asher's house (north center)
    m.bld(cx-2, 4, HOUSE)
    m.path_v(cx, 8, 9)
    # Autumn's house (northeast)
    m.bld(w-9, 4, HOUSE)
    m.path_v(w-7, 8, 9)
    # Prof. Evergreen's Lab (south-center, larger — PokéCenter model as lab)
    m.bld(cx-2, h-10, POKECENTER)
    m.path_v(cx, h-10, h-6)
    m.path_h(h-6, cx-2, cx+2, 3)
    # Encounter grass patches (south and east)
    m.grass_o(7, h-5, 3, 2)
    m.grass_o(w-8, h-5, 3, 2)
    m.grass_o(w-7, 14, 2, 3)
    # South exit to R1
    m.ent_s(cx)
    return m,w,h

def route1():
    """Powderpath Trail. First route. Gentle snowy path south. 3 trainers."""
    w,h = 24,42
    m = M(w,h,CLM)
    m.rect(4,2,w-5,h-3,TG)
    cx = w//2
    # Winding path south through snow
    m.wind_v(cx, 0, h-1, 3, amp=3, per=12)
    # Trainer clearings (3 trainers evenly spaced)
    m.clearing(cx+1, 10, 3, 2)   # Noel (Youngster)
    m.clearing(cx-1, 22, 3, 2)   # Elise (Lass)
    m.clearing(cx+2, 33, 3, 2)   # Kai (Hiker)
    # Scattered trees along edges
    m.scat_trees(4,2,cx-3,h-3, 0.08)
    m.scat_trees(cx+3,2,w-5,h-3, 0.08)
    # F2 Autumn #1 area near south exit
    m.clearing(cx, h-7, 4, 2)
    m.ent_n(cx); m.ent_s(cx)
    return m,w,h

def powderpath_village():
    """Small hamlet between R1 and R2. Vanillite vendor. Rest stop."""
    w,h = 26,20
    m = M(w,h,GR)
    m.trees(2)
    cx = w//2
    m.path_v(cx, 0, h-1, 3)
    m.path_h(h//2, 5, w-6, 3)
    # PokéCenter (west side)
    m.bld(5, 4, POKECENTER)
    m.path_v(7, 8, h//2)
    # Mart (east side)
    m.bld(w-9, 5, MART)
    m.path_v(w-7, 8, h//2)
    # Vanillite vendor stand (small house, south-east)
    m.bld(w-9, h-8, HOUSE)
    m.path_v(w-7, h//2, h-8)
    # Grass patches
    m.grass_o(7, h-5, 3, 2)
    m.grass_o(cx, h-4, 2, 2)
    m.ent_n(cx); m.ent_s(cx)
    return m,w,h

def route2():
    """Icespire Pass. Mountain climb, rocky narrows. 4 trainers. TM2 Hone Claws."""
    w,h = 24,38
    m = M(w,h,CLD)
    # Narrow mountain pass carved from dark rock
    m.rect(5,2,w-6,h-3,TG)
    cx = w//2
    # Winding path up the mountain (tighter amplitude)
    m.wind_v(cx, 0, h-1, 3, amp=2, per=8)
    # Rocky outcrops narrowing the path
    m.rect(5,8,9,11,CLM)    # West outcrop
    m.rect(w-10,16,w-6,19,CLM)  # East outcrop
    m.rect(5,24,9,27,CLM)   # Another west outcrop
    # Trainer clearings (4 trainers)
    m.clearing(cx, 7, 3, 1)    # Brett
    m.clearing(cx+1, 15, 3, 1) # Finn
    m.clearing(cx-1, 23, 3, 1) # Mila
    m.clearing(cx, 31, 3, 1)   # Gus
    # TM2 Hone Claws pickup spot
    m.item_spot(cx+4, 20)
    m.scat_trees(5,2,w-6,h-3, 0.04)
    m.ent_n(cx); m.ent_s(cx)
    return m,w,h

def icespire_town():
    """Mountain base town. Gym 1 (Silvan, Ice). PokéCenter + Gym + houses."""
    w,h = 32,26
    m = M(w,h,GR)
    m.trees(2)
    cx = w//2
    m.path_v(cx, 0, h-1, 3)
    m.path_h(h//2, 5, w-6, 3)
    # PokéCenter (northwest)
    m.bld(5, 4, POKECENTER)
    m.path_v(7, 8, h//2)
    # Gym 1 building (northeast — Mart model as gym)
    m.bld(w-9, 4, MART)
    m.path_v(w-7, 7, h//2)
    # Mart (southwest)
    m.bld(5, h-7, MART)
    m.path_v(7, h//2, h-7)
    # House (southeast — Wide Lens NPC)
    m.bld(w-9, h-8, HOUSE)
    m.path_v(w-7, h//2, h-8)
    # Grass encounters
    m.grass_o(cx+5, 8, 2, 3)
    m.grass_o(cx-4, h-5, 3, 2)
    m.ent_n(cx); m.ent_s(cx)
    return m,w,h

def route3():
    """Pinehurst Woods. Dense forest gauntlet. 5 trainers. East branch to R4.
    Veil Grunt at south exit. TM5 Protect + Bright Powder."""
    w,h = 30,48
    m = M(w,h,TTL)
    # Fill with tree canopy
    for y in range(0,h,2):
        for x in range(0,w,2): m.tree(x,y)
    # Carve forest interior
    m.rect(4,2,w-5,h-3,TG)
    cx = w//2
    # Winding forest path
    m.wind_v(cx, 0, h-1, 3, amp=4, per=10)
    # Dense scattered trees inside forest
    m.scat_trees(4,2,w-5,h-3, 0.15)
    # Trainer clearings (4 normal + 1 Veil Grunt at south)
    m.clearing(cx+2, 8, 3, 2)    # Tate (Youngster)
    m.clearing(cx-2, 16, 3, 2)   # Liam (Bug Catcher)
    m.clearing(cx+1, 24, 3, 2)   # Faye (Lass)
    m.clearing(cx-1, 32, 3, 2)   # Rowan (Bug Catcher)
    m.clearing(cx, h-7, 4, 2)    # Veil Grunt blocks south exit
    # East branch to R4 (side path)
    m.path_h(h//3, cx, w-1, 3)
    m.ent_e(h//3, 3)
    # TM5 Protect pickup
    m.item_spot(cx-5, 20)
    # Bright Powder hidden
    m.item_spot(8, 28)
    m.ent_n(cx); m.ent_s(cx)
    return m,w,h

def route4():
    """Timber Creek. Optional, no trainers. Creek feature. TM6 Toxic hidden."""
    w,h = 24,24
    m = M(w,h,GR)
    m.trees(2)
    m.rect(4,4,w-5,h-5,TG)
    cx = w//2
    # Meandering creek through the area
    for y in range(2,h-2):
        wx = cx+3 + int(2*math.sin(y*0.5))
        m.s(wx,y,WTR); m.s(wx+1,y,WTR)
    # Path alongside creek
    m.path_v(cx-1, 2, h-3, 3)
    # TM6 Toxic hidden spot
    m.item_spot(cx-4, h//2)
    m.scat_trees(4,4,cx-3,h-5, 0.1)
    # West entrance only (connects to R3)
    m.ent_w(h//2, 3)
    return m,w,h

def pinegrove_city():
    """Forest town. Gym 2 (Cedar, Grass). PokéCenter + Mart + Gym. First fishing."""
    w,h = 30,24
    m = M(w,h,GR)
    m.trees(2)
    cx = w//2
    m.path_v(cx, 0, h-1, 3)
    m.path_h(h//2, 5, w-6, 3)
    # PokéCenter (northwest)
    m.bld(5, 4, POKECENTER)
    m.path_v(7, 8, h//2)
    # Gym 2 (northeast)
    m.bld(w-9, 4, MART)
    m.path_v(w-7, 7, h//2)
    # Mart (southwest)
    m.bld(5, h-8, MART)
    m.path_v(7, h//2, h-8)
    # House — fishing rod NPC / Toxic Orb NPC (southeast)
    m.bld(w-9, h-8, HOUSE)
    m.path_v(w-7, h//2, h-8)
    # Fishing pond (south center)
    m.rect(cx-3, h-7, cx+3, h-4, WTR)
    # Grass
    m.grass_o(cx, 7, 2, 2)
    m.ent_n(cx); m.ent_s(cx)
    return m,w,h

def route5():
    """Ironfrost Cave. Gauntlet cave. 2 trainers + 4 Veil Grunts + Crash boss.
    TM9 Brick Break + Light Clay. Mining/industrial cave."""
    w,h = 28,40
    m = M(w,h,CWL)
    # Carve main cavern
    m.rect(4,2,w-5,h-3,CFL)
    cx = w//2
    # Central corridor
    m.path_v(cx, 0, h-1, 3)
    # Rock pillars creating rooms/corridors
    m.rect(4,6,8,9,CW2)     # West pillar 1
    m.rect(w-9,12,w-5,15,CW2)  # East pillar 2
    m.rect(4,18,8,21,CW2)   # West pillar 3
    m.rect(w-9,24,w-5,27,CW2)  # East pillar 4
    # Side rooms/alcoves
    m.rect(4,10,8,12,CF2)   # West alcove
    m.rect(w-9,7,w-5,9,CF2) # East alcove
    m.rect(4,28,8,30,CF2)   # Mining alcove
    # Trainer/grunt clearings (6 encounters)
    m.clearing(cx, 5, 3, 1)    # Knox (Hiker)
    m.clearing(cx, 11, 3, 1)   # Lina (Scientist)
    m.clearing(cx, 17, 3, 1)   # Veil Grunt 1
    m.clearing(cx, 23, 3, 1)   # Veil Grunt 2
    m.clearing(cx, 29, 3, 1)   # Veil Grunts 3+4 (tag double)
    m.clearing(cx, h-6, 4, 2)  # F7 Crash boss area (wider)
    # TM9 Brick Break
    m.item_spot(6, 15)
    # Light Clay hidden
    m.item_spot(w-7, 20)
    m.ent_n(cx); m.ent_s(cx)
    return m,w,h

def ironfrost_city():
    """Industrial town. Gym 3 (Copper, Steel). Fossil Museum. Cave B1 entrance west."""
    w,h = 34,26
    m = M(w,h,GR)
    m.trees(2)
    cx = w//2
    m.path_v(cx, 0, h-1, 3)
    m.path_h(h//2, 5, w-6, 3)
    # PokéCenter (north-center-left)
    m.bld(6, 4, POKECENTER)
    m.path_v(8, 8, h//2)
    # Gym 3 (north-center-right)
    m.bld(cx+2, 4, MART)
    m.path_v(cx+4, 7, h//2)
    # Mart (south-west)
    m.bld(6, h-7, MART)
    m.path_v(8, h//2, h-7)
    # Fossil Museum (south-east, larger — PokéCenter model)
    m.bld(w-10, h-8, POKECENTER)
    m.path_v(w-8, h//2, h-8)
    # HM Strength NPC house
    m.bld(w-10, 4, HOUSE)
    m.path_v(w-8, 8, h//2)
    # Grass
    m.grass_o(cx, h-4, 3, 2)
    # West exit to Ironfrost Cave B1 (postgame)
    m.ent_w(h//2, 3)
    m.ent_n(cx); m.ent_s(cx)
    return m,w,h


# ═══════════════════════════════════════════════════
# ACT 2 — TRANSITIONAL ZONE
# ═══════════════════════════════════════════════════

def route6():
    """Glacier Lake. Central frozen lake with ring path. Ice puzzle area.
    TM13 Ice Beam puzzle reward. Surf-gated Razor Claw. 8 trainers."""
    w,h = 32,42
    m = M(w,h,CLM)
    m.rect(4,2,w-5,h-3,TG)
    cx,cy = w//2, h//2
    # Central frozen lake
    for y in range(h):
        for x in range(w):
            if (x-cx)**2+(y-cy)**2 <= 49: m.s(x,y,WTR)
    # Ring path around lake
    for a in range(360):
        r=math.radians(a)
        for rad in range(8,10):
            px,py = int(cx+rad*math.cos(r)), int(cy+rad*math.sin(r))
            m.s(px,py,PC)
    # Main N-S path on west side
    m.path_v(cx-9, 0, h-1, 3)
    # Connect main path to ring (east-west connectors)
    m.path_h(cy-5, cx-9, cx-7, 3)
    m.path_h(cy+5, cx-9, cx-7, 3)
    # Ice puzzle area (northeast, elevated)
    m.rect(cx+8, 4, w-5, 12, GR)
    m.rect(cx+9, 5, w-6, 11, CLL)  # Ice puzzle tiles
    m.item_spot(w-7, 8)  # TM13 Ice Beam reward
    m.path_h(8, cx+5, cx+8, 3)  # Path to puzzle
    # Surf-gated area (southeast)
    m.rect(cx+6, cy+8, w-5, h-5, WTR)
    m.item_spot(w-7, cy+10)  # Razor Claw (Surf-gated)
    # Zoom Lens ground pickup
    m.item_spot(cx-6, cy-3)
    # Trainer clearings around the lake
    for i,a in enumerate(range(0,360,45)):
        r=math.radians(a)
        tx,ty = int(cx+10*math.cos(r)), int(cy+10*math.sin(r))
        m.clearing(tx,ty,2,1)
    m.scat_trees(4,2,cx-10,h-3, 0.06)
    m.ent_n(cx-9); m.ent_s(cx-9)
    return m,w,h

def frostbreak_lodge():
    """Mountain rest stop. Specialty shop. Yanma gift. Shell Bell NPC."""
    w,h = 22,18
    m = M(w,h,GR)
    m.trees(2)
    cx = w//2
    m.path_v(cx, 0, h-1, 3)
    # Lodge building (center — larger, using PokéCenter model)
    m.bld(cx-2, 4, POKECENTER)
    m.path_v(cx, 8, h//2)
    # Small house (Shell Bell NPC)
    m.bld(5, h-8, HOUSE)
    m.path_h(h//2, 5, cx, 3)
    m.grass_o(w-7, h-5, 2, 2)
    m.ent_n(cx); m.ent_s(cx)
    return m,w,h

def route7():
    """Galetop Plateau. Elevated, breezy. 5 trainers. Berry bushes.
    F10 Autumn #3. Postgame F29 Crash #3. 9 hidden berries."""
    w,h = 28,40
    m = M(w,h,CLM)
    m.rect(4,2,w-5,h-3,TG)
    cx = w//2
    m.wind_v(cx, 0, h-1, 3, amp=4, per=11)
    # Trainer clearings
    for i,(dy,dx) in enumerate([(8,1),(16,-2),(24,0),(30,2),(36,-1)]):
        m.clearing(cx+dx, dy, 3, 2)
    # Berry bush area (west side, marked with ground tiles)
    m.rect(5, 14, 9, 20, GR)
    for y in range(15,20,2):
        for x in range(6,9,2): m.item_spot(x,y)  # 9 berry spots
    # F10 Autumn battle area
    m.clearing(cx, h-8, 4, 2)
    # Postgame F29 Crash area
    m.clearing(5, 8, 3, 2)
    m.scat_trees(4,2,w-5,h-3, 0.06)
    m.ent_n(cx); m.ent_s(cx)
    return m,w,h

def route8():
    """Dreamurs Valley. Valley with water. 6 trainers. TM17 Will-O-Wisp hidden."""
    w,h = 28,40
    m = M(w,h,CLM)
    m.rect(4,2,w-5,h-3,TG)
    cx = w//2
    m.wind_v(cx, 0, h-1, 3, amp=3, per=9)
    # Valley stream running east side
    for y in range(6,h-6):
        wx = cx+6+int(2*math.sin(y*0.3))
        m.s(wx,y,WTR); m.s(wx+1,y,WTR)
    # Trainer clearings
    sp = (h-10)//6
    for i in range(6):
        ty = 5+i*sp
        m.clearing(cx+int(2*math.sin(ty*0.7)), ty, 3, 1)
    # TM17 Will-O-Wisp hidden (off main path)
    m.item_spot(7, h//2+3)
    m.scat_trees(4,2,cx-3,h-3, 0.06)
    m.ent_n(cx); m.ent_s(cx)
    return m,w,h

def dreamurs_town():
    """Fairy-themed town. Gym 4 (Fran, Fairy). Daycare. Deino egg."""
    w,h = 28,22
    m = M(w,h,GR)
    m.trees(2)
    cx = w//2
    m.path_v(cx, 0, h-1, 3)
    m.path_h(h//2, 5, w-6, 3)
    # PokéCenter (northwest)
    m.bld(5, 4, POKECENTER)
    m.path_v(7, 8, h//2)
    # Gym 4 (northeast)
    m.bld(w-9, 4, MART)
    m.path_v(w-7, 7, h//2)
    # Daycare (south-west — larger building)
    m.bld(5, h-8, POKECENTER)
    m.path_v(7, h//2, h-8)
    # House (Move Relearner, south-east)
    m.bld(w-9, h-8, HOUSE)
    m.path_v(w-7, h//2, h-8)
    m.grass_o(cx, h-4, 2, 2)
    m.ent_n(cx)
    # East exit to R9 (coastal)
    m.ent_e(h//2, 3)
    return m,w,h

def route9():
    """Iceharbor Bay. Eastern coast. 8 trainers (2 Surf-gated). Fishing.
    TM19 Shadow Ball."""
    w,h = 30,36
    m = M(w,h,CLM)
    # Land on west, water on east (coastal)
    split = w*3//5
    m.rect(4,2,split-1,h-3,TG)
    m.rect(split,2,w-3,h-3,WTR)
    # Shore path
    m.path_v(split-3, 0, h-1, 3)
    # Irregular shoreline
    for y in range(2,h-2):
        off = int(1.5*math.sin(y*0.4))
        m.s(split+off,y,GR); m.s(split+off-1,y,GR)
    # Trainer clearings along shore (6 main)
    sp = (h-10)//6
    for i in range(6):
        ty = 5+i*sp
        m.clearing(split-5, ty, 3, 1)
    # 2 Surf-gated swimmers (in water, east side)
    m.clearing(w-8, h//3, 2, 1)    # Surf swimmer 1
    m.clearing(w-8, 2*h//3, 2, 1)  # Surf swimmer 2
    # TM19 Shadow Ball
    m.item_spot(8, h//2)
    m.scat_trees(4,2,split-5,h-3, 0.06)
    # West entrance (from Dreamurs), east leads to Iceharbor
    m.ent_w(h//2, 3)
    m.ent_e(h//2, 3)
    return m,w,h

def iceharbor_city():
    """Harbor city. Gym 5 (Marina, Water). Facility Delta. Surf to DI."""
    w,h = 32,24
    m = M(w,h,GR)
    m.trees(2)
    cx = w//2
    m.path_v(cx, 4, h-1, 3)
    m.path_h(h//2, 5, w-6, 3)
    # Harbor water (east side)
    m.rect(w-8, 4, w-5, h-5, WTR)
    # PokéCenter (northwest)
    m.bld(5, 4, POKECENTER)
    m.path_v(7, 8, h//2)
    # Gym 5 (center-north)
    m.bld(cx-2, 4, MART)
    m.path_v(cx, 7, h//2)
    # Mart (southwest)
    m.bld(5, h-7, MART)
    m.path_v(7, h//2, h-7)
    # Facility Delta entrance (south-east)
    m.bld(w-12, h-8, POKECENTER)
    m.path_h(h//2, cx, w-10, 3)
    # Black Sludge NPC house
    m.bld(cx+4, 4, HOUSE)
    # Surf access east to Driftrock Isle
    m.ent_e(h//2, 3)
    # West entrance from R9, south to R10
    m.ent_w(h//2, 3)
    m.ent_s(cx)
    return m,w,h

def driftrock_isle():
    """Optional island east of Iceharbor via Surf. 5 trainers. King's Rock.
    Larvitar/Lapras rare encounters."""
    w,h = 26,28
    m = M(w,h,WTR)  # Surrounded by water
    # Island landmass in center
    for y in range(h):
        for x in range(w):
            if (x-w//2)**2+(y-h//2)**2 <= 100:
                m.s(x,y,TG)
    cx,cy = w//2, h//2
    # Central path
    m.path_v(cx, cy-7, cy+7, 3)
    m.path_h(cy, cx-6, cx+6, 3)
    # Trainer clearings (4 swimmers in water, 1 Ranger on island)
    m.clearing(6, 6, 2, 1)     # Swimmer 1
    m.clearing(w-7, 6, 2, 1)   # Swimmer 2
    m.clearing(6, h-7, 2, 1)   # Swimmer 3
    m.clearing(w-7, h-7, 2, 1) # Swimmer 4
    m.clearing(cx, cy, 3, 2)   # Ranger Heath (center)
    # Items
    m.item_spot(cx+3, cy-3)  # King's Rock
    m.item_spot(cx-4, cy+2)  # TM22 Bulk Up
    m.scat_trees(cx-5,cy-5,cx+5,cy+5, 0.08)
    # West exit (Surf back to Iceharbor)
    m.ent_w(cy, 3)
    return m,w,h

def route10():
    """Snowburn Path. Fire/ice dual cave. 8-trainer GAUNTLET (longest).
    TM24 Overheat + Rocky Helmet + Flame Orb."""
    w,h = 28,42
    m = M(w,h,CWL)
    m.rect(4,2,w-5,h-3,CFL)
    cx = w//2
    m.path_v(cx, 0, h-1, 3)
    # Rock pillars alternating sides (creates corridor feel)
    for i in range(6):
        py = 5+i*6
        if i%2==0:
            m.rect(4,py,8,py+2,CW2)
        else:
            m.rect(w-9,py,w-5,py+2,CW2)
    # Side rooms (fire/ice themed areas)
    m.rect(4, h//4, 8, h//4+3, CF2)     # Ice alcove
    m.rect(w-9, h//2, w-5, h//2+3, CF2) # Fire alcove
    m.rect(4, 3*h//4, 8, 3*h//4+3, CF2)
    # 8 trainer clearings (gauntlet)
    sp = (h-10)//8
    for i in range(8):
        ty = 4+i*sp
        m.clearing(cx, ty, 3, 1)
    # Items
    m.item_spot(6, h//4+1)    # Rocky Helmet
    m.item_spot(w-7, h//2+1)  # Flame Orb
    m.item_spot(cx+4, h-8)    # TM24 Overheat
    m.ent_n(cx); m.ent_s(cx)
    return m,w,h

def route11():
    """Brightbloom Meadow. Beautiful flower meadow. 6 trainers. Last 0-EV route.
    TM25 U-turn + TM26 Volt Switch. Expert Belt."""
    w,h = 30,40
    m = M(w,h,CLM)
    m.rect(4,2,w-5,h-3,TG)
    cx = w//2
    m.wind_v(cx, 0, h-1, 3, amp=5, per=12)
    # Flower patches (using long grass for variety)
    m.rect(6,8,10,12,LG)
    m.rect(w-11,16,w-7,20,LG)
    m.rect(7,26,11,30,LG)
    m.rect(w-11,32,w-7,36,LG)
    # Trainer clearings
    sp = (h-10)//6
    for i in range(6):
        ty = 5+i*sp
        off = int(4*math.sin(ty*0.5))
        m.clearing(cx+off, ty, 3, 2)
    # F14 Asher #4 area near south
    m.clearing(cx, h-8, 4, 2)
    # Items
    m.item_spot(cx-6, 14)  # TM25 U-turn
    m.item_spot(w-8, 24)   # TM26 Volt Switch hidden
    m.item_spot(8, h-10)   # Expert Belt
    m.scat_trees(4,2,w-5,h-3, 0.04)
    m.ent_n(cx); m.ent_s(cx)
    return m,w,h

def dragonforge_city():
    """Tech hub. Gym 6 (Priyo, Dragon). Department Store. THE REVEAL.
    Porygon gift Lv30. Largest city."""
    w,h = 36,28
    m = M(w,h,GR)
    m.trees(2)
    cx = w//2
    m.path_v(cx, 0, h-1, 3)
    m.path_h(h//3, 5, w-6, 3)
    m.path_h(2*h//3, 5, w-6, 3)
    # PokéCenter (northwest)
    m.bld(5, 4, POKECENTER)
    m.path_v(7, 8, h//3)
    # Gym 6 (north-center-right)
    m.bld(cx+4, 4, MART)
    m.path_v(cx+6, 7, h//3)
    # Mart (west)
    m.bld(5, h//3+2, MART)
    m.path_v(7, h//3, h//3+5)
    # Department Store (east side — LARGE, two buildings)
    m.bld(w-10, 4, POKECENTER)  # Main dept store
    m.bld(w-10, 9, HOUSE)       # Dept store annex
    m.path_v(w-8, 8, h//3)
    # Porygon house (south-west)
    m.bld(5, h-8, HOUSE)
    m.path_v(7, 2*h//3, h-8)
    # House (south-east, NPC area)
    m.bld(w-10, h-8, HOUSE)
    m.path_v(w-8, 2*h//3, h-8)
    # HM2 Fly NPC area
    m.bld(cx-2, h-8, HOUSE)
    m.path_v(cx, 2*h//3, h-8)
    m.ent_n(cx); m.ent_s(cx)
    return m,w,h


# ═══════════════════════════════════════════════════
# ACT 3 — TROPICAL/VOLCANIC ZONE
# ═══════════════════════════════════════════════════

def route12():
    """Memoria Passage. Ghost cave. Spiritomb side passage. First full-EV route.
    7 trainers. TM35 Psychic. Reaper Cloth."""
    w,h = 28,40
    m = M(w,h,CWL)
    m.rect(4,2,w-5,h-3,CFL)
    cx = w//2
    m.path_v(cx, 0, h-1, 3)
    # Cave rooms
    m.rect(4,8,9,14,CF2)     # West chamber
    m.rect(w-10,18,w-5,24,CF2)  # East chamber
    # Spiritomb side passage (west dead-end)
    m.rect(4,h//2-2,10,h//2+2,CF2)
    m.item_spot(5, h//2)  # Spiritomb static location
    # Rock pillars
    m.rect(4,16,7,17,CW2)
    m.rect(w-8,10,w-5,11,CW2)
    m.rect(4,28,7,29,CW2)
    # Trainer clearings (7 trainers in 6 encounters, tag double at end)
    for i,(ty,dx) in enumerate([(6,0),(12,2),(18,-2),(24,1),(30,-1),(36,0)]):
        rw = 4 if i==5 else 3  # Wider for tag double
        m.clearing(cx+dx, ty, rw, 1)
    # Items
    m.item_spot(cx+5, 20)  # TM35 Psychic
    m.item_spot(7, 26)     # Reaper Cloth hidden
    m.ent_n(cx); m.ent_s(cx)
    return m,w,h

def solace_town():
    """Desert-like anti-Veil town. Gym 7 (Erin, Ground)."""
    w,h = 26,22
    m = M(w,h,GR)
    m.trees(2)
    cx = w//2
    m.path_v(cx, 0, h-1, 3)
    m.path_h(h//2, 5, w-6, 3)
    # PokéCenter
    m.bld(5, 4, POKECENTER)
    m.path_v(7, 8, h//2)
    # Gym 7
    m.bld(w-9, 4, MART)
    m.path_v(w-7, 7, h//2)
    # House (Dale NPC)
    m.bld(5, h-8, HOUSE)
    m.path_v(7, h//2, h-8)
    m.grass_o(w-7, h-5, 2, 2)
    m.grass_o(cx, h-4, 2, 2)
    m.ent_n(cx); m.ent_s(cx)
    return m,w,h

def route13():
    """Verdant Jungle. Dense tropical. 9-trainer GAUNTLET (continuous with R14).
    TM37 X-Scissor + TM38 Energy Ball. Scope Lens. Stream feature."""
    w,h = 32,50
    m = M(w,h,TTL)
    for y in range(0,h,2):
        for x in range(0,w,2): m.tree(x,y)
    m.rect(4,2,w-5,h-3,TG)
    cx = w//2
    m.wind_v(cx, 0, h-1, 3, amp=5, per=9)
    # Jungle stream (east side)
    for y in range(h//4, 3*h//4):
        wx = cx+7+int(2*math.sin(y*0.3))
        m.s(wx,y,WTR); m.s(wx+1,y,WTR)
    # 9 trainer clearings
    sp = (h-10)//9
    for i in range(9):
        ty = 4+i*sp
        off = int(4*math.sin(ty*0.6))
        m.clearing(cx+off, ty, 3, 1)
    # Items
    m.item_spot(cx-6, h//3)     # TM37 X-Scissor
    m.item_spot(cx+5, 2*h//3)   # TM38 Energy Ball
    m.item_spot(8, h//2)        # Scope Lens
    m.scat_trees(4,2,w-5,h-3, 0.18)
    m.ent_n(cx); m.ent_s(cx)
    return m,w,h

def route14():
    """Cinderstone Path. Volcanic ash. 9 trainers (continuous from R13).
    TM39 Rock Slide + TM40 Iron Head + TM41 Fire Blast. Magmarizer."""
    w,h = 30,42
    m = M(w,h,CLM)
    m.rect(4,2,w-5,h-3,TG)
    cx = w//2
    m.wind_v(cx, 0, h-1, 3, amp=3, per=7)
    # Volcanic rock formations
    m.rect(5,6,9,9,CLD)
    m.rect(w-10,14,w-6,17,CLD)
    m.rect(6,22,10,25,CLD)
    m.rect(w-10,30,w-6,33,CLD)
    # 9 trainer clearings (8 encounters, last is tag double)
    sp = (h-10)//8
    for i in range(8):
        ty = 4+i*sp
        rw = 4 if i==7 else 3
        m.clearing(cx+int(2*math.sin(ty*0.5)), ty, rw, 1)
    # Items
    m.item_spot(cx-5, 12)   # TM39 Rock Slide
    m.item_spot(w-8, 20)    # TM40 Iron Head hidden
    m.item_spot(cx+5, 28)   # TM41 Fire Blast
    m.item_spot(8, h-10)    # Magmarizer hidden
    m.scat_trees(4,2,w-5,h-3, 0.05)
    m.ent_n(cx)
    # West exit to R15 (volcanic lagoon)
    m.ent_w(h//2, 3)
    return m,w,h

def route15():
    """Pyrespire Lagoon. Volcanic lagoon. FORK structure at mid-route.
    F18 Autumn at fork. 9 trainers (3 Surf-gated). TM42 Solar Beam.
    5 Type Gems. North fork → Research Outpost. South → Pyrespire City."""
    w,h = 32,48
    m = M(w,h,CLM)
    m.rect(4,2,w-5,h-3,TG)
    cx = w//2
    # Main path from east entrance (R14) to fork mid-route
    m.path_h(6, 0, cx, 3)  # East entrance path
    m.path_v(cx, 6, h//2-2, 3)  # Path south to fork
    # === FORK at mid-point ===
    fork_y = h//2
    m.clearing(cx, fork_y-2, 5, 2)  # F18 Autumn battle area (at fork)
    # North fork (dead-end → Research Outpost)
    m.path_v(cx-6, fork_y-4, fork_y, 3)
    m.rect(cx-9, fork_y-8, cx-4, fork_y-4, GR)  # Outpost area
    m.bld(cx-9, fork_y-8, HOUSE)  # Research Outpost building
    # South fork (continues to Pyrespire City)
    m.path_v(cx, fork_y, h-1, 3)
    # Pre-fork trainers (2)
    m.clearing(cx-3, 10, 3, 1)  # Briney (Sailor)
    m.clearing(cx+2, 16, 3, 1)  # Ahab (Fisherman)
    # Post-fork trainers (4 main + 3 surf-gated)
    m.clearing(cx, fork_y+6, 3, 1)   # Cousteau
    m.clearing(cx-2, fork_y+12, 3, 1) # Hadley
    m.clearing(cx+1, fork_y+18, 3, 1) # Volt
    m.clearing(cx, h-8, 3, 1)         # Quint (mandatory gate)
    # Lagoon water (south-east)
    m.rect(cx+5, fork_y+4, w-5, h-5, WTR)
    # 3 Surf-gated swimmers in lagoon
    m.clearing(w-8, fork_y+8, 2, 1)
    m.clearing(w-10, fork_y+14, 2, 1)
    m.clearing(w-8, fork_y+20, 2, 1)
    # Items
    m.item_spot(cx+3, fork_y+10)  # TM42 Solar Beam
    # Type Gems scattered
    m.item_spot(6, 12)
    m.item_spot(w-8, fork_y-4)
    m.item_spot(8, fork_y+8)
    m.item_spot(cx-5, h-10)
    m.item_spot(6, h-6)
    m.scat_trees(4,2,cx-2,h-3, 0.06)
    # East entrance (from R14)
    m.ent_e(6, 3)
    m.ent_s(cx)
    return m,w,h

def pyrespire_city():
    """Volcanic coastal city. Gym 8 (Scorch, Fire). Facility Beta.
    Gen 5 Fossil Museum. Dragon Scale NPC."""
    w,h = 34,26
    m = M(w,h,GR)
    m.trees(2)
    cx = w//2
    m.path_v(cx, 0, h-1, 3)
    m.path_h(h//2, 5, w-6, 3)
    # PokéCenter (northwest)
    m.bld(5, 4, POKECENTER)
    m.path_v(7, 8, h//2)
    # Gym 8 (north-center)
    m.bld(cx+2, 4, MART)
    m.path_v(cx+4, 7, h//2)
    # Mart (west)
    m.bld(5, h-7, MART)
    m.path_v(7, h//2, h-7)
    # Facility Beta entrance (east)
    m.bld(w-10, 4, POKECENTER)
    m.path_v(w-8, 8, h//2)
    # Fossil Museum Gen 5 (south-east)
    m.bld(w-10, h-8, POKECENTER)
    m.path_v(w-8, h//2, h-8)
    # Dragon Scale NPC house
    m.bld(cx-6, h-8, HOUSE)
    m.path_v(cx-4, h//2, h-8)
    m.ent_n(cx); m.ent_s(cx)
    return m,w,h

def victory_road():
    """20-chamber cave gauntlet. 8 Ace Trainers. F30 Asher Final.
    Choice Band. PP Restore mid-sanctum."""
    w,h = 32,50
    m = M(w,h,CWL)
    m.rect(4,2,w-5,h-3,CFL)
    cx = w//2
    m.path_v(cx, 0, h-1, 3)
    # Chamber-like rooms with corridor bottlenecks
    for i in range(8):
        cy = 4 + i*5
        # Wide chamber
        m.rect(6,cy,w-7,cy+3,CF2)
        # Bottleneck between chambers
        if i < 7:
            m.rect(cx-2,cy+3,cx+2,cy+5,CFL)
    # Rock pillars in chambers
    for i in range(0,8,2):
        cy = 4+i*5
        m.rect(6,cy,9,cy+1,CW2)
        m.rect(w-10,cy+1,w-7,cy+2,CW2)
    # 8 trainer clearings (one per chamber)
    for i in range(8):
        cy = 5+i*5
        m.clearing(cx, cy, 3, 1)
    # F30 Asher Final chamber (south, larger)
    m.rect(6,h-8,w-7,h-4,CF2)
    m.clearing(cx, h-6, 4, 2)
    # Mid-sanctum PP restore (center)
    m.rect(cx-3,h//2-1,cx+3,h//2+1,CF2)
    # Choice Band
    m.item_spot(w-8, 22)
    m.ent_n(cx); m.ent_s(cx)
    return m,w,h

def pokemon_league():
    """E4 + Champion. Arena entrance."""
    w,h = 28,22
    m = M(w,h,GR)
    m.trees(2)
    cx = w//2
    m.path_v(cx, 0, h-1, 3)
    # League building (large, center)
    m.bld(cx-2, 4, POKECENTER)
    m.path_v(cx, 8, h//2)
    # PokéCenter (west)
    m.bld(5, 4, POKECENTER)
    m.path_h(8, 5, cx-2, 3)
    # Mart (east)
    m.bld(w-9, 5, MART)
    m.path_h(8, cx+2, w-9, 3)
    m.ent_n(cx)
    return m,w,h

def cave_b1():
    """Ironfrost Basement B1. Postgame cave. Leftovers + Assault Vest."""
    w,h = 28,28
    m = M(w,h,CWL)
    m.rect(4,2,w-5,h-3,CFL)
    cx = w//2
    m.path_v(cx, 0, h-1, 3)
    m.rect(4,h//3,9,h//3+4,CF2)
    m.rect(w-10,2*h//3,w-5,2*h//3+4,CF2)
    for i in range(3):
        py = 5+i*8
        if i%2==0: m.rect(4,py,7,py+1,CW2)
        else: m.rect(w-8,py,w-5,py+1,CW2)
    m.item_spot(6, h//3+2)    # Leftovers
    m.item_spot(w-7, h//3+2)  # Assault Vest
    m.ent_n(cx); m.ent_s(cx)
    return m,w,h

def cave_b2b3():
    """Ironfrost Basement B2-B3. Deep cave. Kyurem static Lv83. Choice Specs."""
    w,h = 30,34
    m = M(w,h,CWL)
    m.rect(4,2,w-5,h-3,CFL)
    cx = w//2
    m.path_v(cx, 0, h-1, 3)
    # Deeper, more open cave
    m.rect(6,4,w-7,h-5,CF2)
    # Kyurem chamber (south, large open area)
    m.rect(8,h-12,w-9,h-5,CFL)
    m.clearing(cx, h-8, 5, 3)  # Kyurem static position
    # Rock formations
    m.rect(4,8,8,10,CW2)
    m.rect(w-9,14,w-5,16,CW2)
    m.rect(4,20,8,22,CW2)
    # Choice Specs
    m.item_spot(w-8, 12)
    m.ent_n(cx)
    return m,w,h


# ═══════════════════════════════════════════════════
# BUILD ALL
# ═══════════════════════════════════════════════════

ALL = {
    "DawnflakeTown":      (dawnflake_town, "gTileset_Petalburg"),
    "SnowRoute1":         (route1, "gTileset_Petalburg"),
    "PowderpathVillage":  (powderpath_village, "gTileset_Petalburg"),
    "SnowRoute2":         (route2, "gTileset_Petalburg"),
    "IcespireTown":       (icespire_town, "gTileset_Petalburg"),
    "SnowRoute3":         (route3, "gTileset_Petalburg"),
    "SnowRoute4":         (route4, "gTileset_Petalburg"),
    "PinegroveCity":      (pinegrove_city, "gTileset_Petalburg"),
    "SnowRoute5":         (route5, "gTileset_Cave"),
    "IronfrostCity":      (ironfrost_city, "gTileset_Petalburg"),
    "SnowRoute6":         (route6, "gTileset_Petalburg"),
    "FrostbreakLodge":    (frostbreak_lodge, "gTileset_Petalburg"),
    "SnowRoute7":         (route7, "gTileset_Petalburg"),
    "SnowRoute8":         (route8, "gTileset_Petalburg"),
    "DreamursTown":       (dreamurs_town, "gTileset_Petalburg"),
    "SnowRoute9":         (route9, "gTileset_Petalburg"),
    "IceharborCity":      (iceharbor_city, "gTileset_Petalburg"),
    "DriftrockIsle":      (driftrock_isle, "gTileset_Petalburg"),
    "SnowRoute10":        (route10, "gTileset_Cave"),
    "SnowRoute11":        (route11, "gTileset_Petalburg"),
    "DragonforgeCity":    (dragonforge_city, "gTileset_Petalburg"),
    "SnowRoute12":        (route12, "gTileset_Cave"),
    "SolaceTown":         (solace_town, "gTileset_Petalburg"),
    "SnowRoute13":        (route13, "gTileset_Petalburg"),
    "SnowRoute14":        (route14, "gTileset_Petalburg"),
    "SnowRoute15":        (route15, "gTileset_Petalburg"),
    "PyrespireCity":      (pyrespire_city, "gTileset_Petalburg"),
    "SnowVictoryRoad":    (victory_road, "gTileset_Cave"),
    "PokemonLeague":      (pokemon_league, "gTileset_Petalburg"),
    "IronfrostCaveB1":    (cave_b1, "gTileset_Cave"),
    "IronfrostCaveB2B3":  (cave_b2b3, "gTileset_Cave"),
}
CAVES = {"SnowRoute5","SnowRoute10","SnowRoute12","SnowVictoryRoad","IronfrostCaveB1","IronfrostCaveB2B3"}

def main():
    with open(REPO/"data/layouts/layouts.json") as f: ld=json.load(f)
    for name,(gen,ts) in ALL.items():
        m,w,h = gen()
        lid = "LAYOUT_"+''.join(f'_{c}' if c.isupper() and i>0 and name[i-1].islower()
              else c for i,c in enumerate(name)).upper().replace('__','_')
        ldir = REPO/"data/layouts"/name; ldir.mkdir(parents=True,exist_ok=True)
        (ldir/"map.bin").write_bytes(m.to_bytes())
        bdr = [CWL]*4 if name in CAVES else [TTL,TTR,TBL,TBR]
        with open(ldir/"border.bin","wb") as f:
            for t in bdr: f.write(struct.pack("<H",t))
        ent = {"id":lid,"name":f"{name}_Layout","width":w,"height":h,
               "primary_tileset":"gTileset_General","secondary_tileset":ts,
               "border_filepath":f"data/layouts/{name}/border.bin",
               "blockdata_filepath":f"data/layouts/{name}/map.bin"}
        ex=[l for l in ld["layouts"] if l["id"]==lid]
        if ex: ld["layouts"][ld["layouts"].index(ex[0])]=ent
        else: ld["layouts"].append(ent)
        mjp=REPO/"data/maps"/name/"map.json"
        with open(mjp) as f: mj=json.load(f)
        mj["layout"]=lid
        with open(mjp,"w") as f: json.dump(mj,f,indent=2); f.write("\n")
        print(f"  {name:25s} {w:2d}x{h:2d}")
    seen={}
    for i,l in enumerate(ld["layouts"]): seen[l["id"]]=i
    ld["layouts"]=[ld["layouts"][i] for i in sorted(seen.values())]
    with open(REPO/"data/layouts/layouts.json","w") as f: json.dump(ld,f,indent=2); f.write("\n")
    print(f"\n{len(ALL)} layouts generated")

if __name__=="__main__": main()
