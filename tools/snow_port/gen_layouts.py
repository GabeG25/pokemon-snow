#!/usr/bin/env python3
"""Detailed layouts for all Snow locations from CEO synopses + v17 spec.

Key design rules:
- Towns: 1-2 small intentional grass patches only (NOT wall-to-wall)
- Routes: sparse varied grass patches with some MANDATORY sections on path
- R1: mandatory grass area for Autumn catching tutorial
- Dawnflake: grass in far corners, player can't enter without Pokémon
- Powderpath: fenced grass with tree-border + single gate opening
- Pinegrove: CRATER design with slopes leading down to center PokéCenter
- Ironfrost: mining/industrial (rock formations, constructions)
- Dreamurs: fairy/dreamy vibe
- Iceharbor: medium port, cargo bays, half-frozen water
- Dragonforge: LARGEST city, Facility Alpha visible, decorative buildings
- Solace: rural agricultural, monuments, hidden Anti-Veil base
- Pyrespire: 2nd largest, Facility Beta, tropical vibe
- Move Tutors per v17 §15: Icespire/Ironfrost/Iceharbor/Dragonforge/Pyrespire
"""

import json, struct, math, random
from pathlib import Path

random.seed(2026)
REPO = Path(__file__).resolve().parent.parent.parent

def T(meta, col=0, elv=3):
    return meta | (col << 10) | (elv << 12)

# Ground tiles
GR  = T(0x001); GR2 = T(0x004)
TG  = T(0x00D); LG  = T(0x015)
# Path tiles
PC  = T(0x1D9); PL = T(0x1D8); PR = T(0x1DA)
PT  = T(0x1D1); PB = T(0x1E1)
# Trees (impassable)
TTL = T(0x1D4,1,0); TTR = T(0x1D5,1,0)
TBL = T(0x1DC,1,0); TBR = T(0x1DD,1,0)
# Cliffs (impassable)
CLD = T(0x075,1,0); CLM = T(0x073,1,0); CLL = T(0x071,1,0)
RKG = T(0x079,1,0); RKR = T(0x07C,1,0)
# Water
WTR = T(0x170,elv=1)
# Slope (for crater descent — animated muddy slope)
SLP = T(0x0E8)  # Passable slope tile
# Cave
CFL = T(0x201); CF2 = T(0x211)
CWL = T(0x211,1,0); CW2 = T(0x219,1,0); CW3 = T(0x209,1,0)

# Buildings (Petalburg secondary)
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
    def __init__(s,w,h,fill=GR):
        s.w,s.h=w,h; s.g=[[fill]*w for _ in range(h)]
    def set(s,x,y,t):
        if 0<=x<s.w and 0<=y<s.h: s.g[y][x]=t
    def get(s,x,y):
        return s.g[y][x] if 0<=x<s.w and 0<=y<s.h else 0
    def rect(s,x1,y1,x2,y2,t):
        for y in range(max(0,y1),min(s.h,y2+1)):
            for x in range(max(0,x1),min(s.w,x2+1)): s.g[y][x]=t
    def bld(s,x,y,p):
        for dy,row in enumerate(p):
            for dx,t in enumerate(row): s.set(x+dx,y+dy,t)
    def tree(s,x,y):
        s.set(x,y,TTL); s.set(x+1,y,TTR); s.set(x,y+1,TBL); s.set(x+1,y+1,TBR)
    def border(s,t=2):
        """Tree border around map."""
        for y in range(0,s.h,2):
            for x in range(0,s.w,2):
                if x<t*2 or x>=s.w-t*2 or y<t*2 or y>=s.h-t*2:
                    s.tree(x,y)
    def path_v(s,cx,y1,y2,w=3):
        for y in range(min(y1,y2),max(y1,y2)+1):
            for dx in range(-(w//2),w//2+1): s.set(cx+dx,y,PC)
    def path_h(s,cy,x1,x2,w=3):
        for x in range(min(x1,x2),max(x1,x2)+1):
            for dy in range(-(w//2),w//2+1): s.set(x,cy+dy,PC)
    def wind_v(s,cx,y1,y2,w=3,amp=3,per=10):
        for y in range(min(y1,y2),max(y1,y2)+1):
            off=int(amp*math.sin(y*2*math.pi/per))
            for dx in range(-(w//2),w//2+1): s.set(cx+off+dx,y,PC)
    def grass_patch(s,cx,cy,rx,ry=None):
        """Small patch of tall grass (sparse)."""
        if ry is None: ry=rx
        for y in range(max(0,cy-ry),min(s.h,cy+ry+1)):
            for x in range(max(0,cx-rx),min(s.w,cx+rx+1)):
                if ((x-cx)/max(rx,1))**2+((y-cy)/max(ry,1))**2<=1:
                    if s.get(x,y) in (GR,GR2): s.set(x,y,TG)
    def clearing(s,cx,cy,rw=3,rh=1):
        s.rect(cx-rw,cy-rh,cx+rw,cy+rh,GR)
    def item(s,x,y):
        s.set(x,y,GR)
    def fence_grass(s,cx,cy,rx,ry,gate_side='south'):
        """Small grass area enclosed by trees, with gate opening."""
        # Grass interior
        s.rect(cx-rx,cy-ry,cx+rx,cy+ry,TG)
        # Tree perimeter
        for x in range(cx-rx-1,cx+rx+2,2):
            s.tree(x,cy-ry-1)
            s.tree(x,cy+ry)
        for y in range(cy-ry-1,cy+ry+1,2):
            s.tree(cx-rx-1,y)
            s.tree(cx+rx+1,y)
        # Gate opening
        if gate_side=='south':
            s.set(cx,cy+ry+1,GR); s.set(cx,cy+ry+2,GR)
        elif gate_side=='north':
            s.set(cx,cy-ry-1,GR); s.set(cx,cy-ry-2,GR)
        elif gate_side=='west':
            s.set(cx-rx-1,cy,GR); s.set(cx-rx-2,cy,GR)
        elif gate_side=='east':
            s.set(cx+rx+1,cy,GR); s.set(cx+rx+2,cy,GR)
    def ent_s(s,cx,w=5):
        for x in range(cx-w//2,cx+w//2+1):
            for y in range(s.h-4,s.h): s.set(x,y,GR)
    def ent_n(s,cx,w=5):
        for x in range(cx-w//2,cx+w//2+1):
            for y in range(4): s.set(x,y,GR)
    def ent_e(s,cy,w=3):
        for y in range(cy-w//2,cy+w//2+1):
            for x in range(s.w-4,s.w): s.set(x,y,GR)
    def ent_w(s,cy,w=3):
        for y in range(cy-w//2,cy+w//2+1):
            for x in range(4): s.set(x,y,GR)
    def to_bytes(s):
        o=bytearray()
        for row in s.g:
            for t in row: o+=struct.pack("<H",t)
        return bytes(o)


# ═══════════════════════════════════════════════════════════
# ACT 1 — HEAVY SNOW ZONE
# ═══════════════════════════════════════════════════════════

def dawnflake_town():
    """Quaint starting town. 3 houses (Player/Asher/Autumn) + Prof. Evergreen's Lab.
    2 small grass patches in far corners (prompts player to catch Pokémon first).
    No PokéCenter/Mart — it's just a tiny hamlet."""
    w,h = 32,26
    m = M(w,h,GR)
    m.border(2)
    cx = w//2
    # Main south exit path (vertical)
    m.path_v(cx, 4, h-1, 3)
    # Upper residential cross path
    m.path_h(7, 6, w-7, 3)
    # Player's house (northwest)
    m.bld(5, 3, HOUSE)
    m.path_v(7, 7, 8)
    # Asher's house (north center-left)
    m.bld(cx-5, 3, HOUSE)
    m.path_v(cx-3, 7, 8)
    # Autumn's house (north center-right)
    m.bld(cx+2, 3, HOUSE)
    m.path_v(cx+4, 7, 8)
    # Prof. Evergreen's Lab (large, south-center — where player gets starter)
    m.bld(cx-2, h-11, POKECENTER)
    m.path_v(cx, h-7, h-6)
    # Lower path to lab
    m.path_h(h-6, cx-2, cx+2, 3)
    # 2 small grass patches in FAR corners (player can't enter without Pokémon)
    m.grass_patch(4, h-6, 2, 1)      # Southwest corner patch (tiny)
    m.grass_patch(w-5, h-6, 2, 1)    # Southeast corner patch (tiny)
    # South exit
    m.ent_s(cx)
    return m,w,h

def route1():
    """Powderpath Trail. First route. MANDATORY grass for Autumn catching tutorial.
    3 trainers: Noel, Elise, Kai. Autumn F2 at south end."""
    w,h = 24,42
    m = M(w,h,CLM)
    m.rect(3,2,w-4,h-3,GR)  # Walkable grass (NOT tall grass) — sparse placement
    cx = w//2
    # Winding path through the route
    m.wind_v(cx, 0, h-1, 3, amp=2, per=14)
    # MANDATORY grass section — Autumn catching tutorial
    # Player MUST walk through this grass to continue south
    m.rect(cx-2, 6, cx+2, 10, TG)   # Wide mandatory grass across path
    # Autumn tutorial NPC spot (north edge of mandatory grass)
    m.item(cx, 5)
    # Additional sprinkled grass patches (optional encounters)
    m.grass_patch(5, 15, 2, 2)
    m.grass_patch(w-6, 18, 2, 1)
    m.grass_patch(6, 24, 1, 2)
    m.grass_patch(w-7, 27, 2, 2)
    m.grass_patch(4, 32, 1, 1)
    m.grass_patch(w-5, 34, 2, 1)
    # Trainer clearings along path
    m.clearing(cx-1, 14, 3, 1)   # Noel (Youngster)
    m.clearing(cx+1, 22, 3, 1)   # Elise (Lass)
    m.clearing(cx-1, 31, 3, 1)   # Kai (Hiker)
    # F2 Autumn #1 battle area near south exit
    m.clearing(cx, h-7, 4, 2)
    # Scattered single trees
    for (x,y) in [(5,4),(w-6,7),(4,19),(w-5,21),(5,28),(w-6,36)]:
        m.tree(x,y)
    m.ent_n(cx); m.ent_s(cx)
    return m,w,h

def powderpath_village():
    """Quaint northern village. PokéCenter + Mart + 4-5 NPC houses.
    Small fenced grass with gate. Intro to PC/Mart."""
    w,h = 28,22
    m = M(w,h,GR)
    m.border(2)
    cx = w//2
    m.path_v(cx, 0, h-1, 3)
    m.path_h(h//2-1, 4, w-5, 3)
    # PokéCenter (northwest)
    m.bld(4, 4, POKECENTER)
    m.path_v(6, 8, h//2-1)
    # Mart (northeast)
    m.bld(w-8, 4, MART)
    m.path_v(w-6, 7, h//2-1)
    # NPC House 1 (west)
    m.bld(4, h-8, HOUSE)
    m.path_v(6, h//2-1, h-8)
    # NPC House 2 (east)
    m.bld(w-8, h-8, HOUSE)
    m.path_v(w-6, h//2-1, h-8)
    # NPC House 3 (south-center-left — Vanillite vendor)
    m.bld(cx-6, h-8, HOUSE)
    m.path_v(cx-4, h//2-1, h-8)
    # NPC House 4 (south-center-right)
    m.bld(cx+2, h-8, HOUSE)
    m.path_v(cx+4, h//2-1, h-8)
    # Fenced grass patch (upper center, between houses)
    m.fence_grass(cx, 7, 2, 1, gate_side='south')
    m.ent_n(cx); m.ent_s(cx)
    return m,w,h

def route2():
    """Icespire Pass. Mountain climb. 4 trainers. TM2 Hone Claws.
    Sparse grass patches along path."""
    w,h = 24,38
    m = M(w,h,CLD)
    m.rect(4,2,w-5,h-3,GR)
    cx = w//2
    m.wind_v(cx, 0, h-1, 3, amp=2, per=8)
    # Rocky outcrops narrowing the pass
    m.rect(4,9,8,12,CLM)
    m.rect(w-9,17,w-5,20,CLM)
    m.rect(4,25,8,28,CLM)
    # Sparse grass patches (not everywhere)
    m.grass_patch(6, 5, 2, 1)
    m.grass_patch(w-7, 13, 1, 2)
    m.grass_patch(5, 21, 2, 1)
    m.grass_patch(w-6, 30, 2, 1)
    m.grass_patch(6, 34, 1, 1)
    # Trainer clearings
    m.clearing(cx, 7, 3, 1)     # Brett
    m.clearing(cx+1, 15, 3, 1)  # Finn
    m.clearing(cx-1, 23, 3, 1)  # Mila
    m.clearing(cx, 31, 3, 1)    # Gus
    # TM2 Hone Claws
    m.item(cx+4, 20)
    m.ent_n(cx); m.ent_s(cx)
    return m,w,h

def icespire_town():
    """First real explorable town. Gym 1 + Ice Cream Stand + PC + Mart + 6 NPC houses.
    Roughneck Move Tutor. Pro-Veil winter culture town."""
    w,h = 36,28
    m = M(w,h,GR)
    m.border(2)
    cx = w//2
    m.path_v(cx, 0, h-1, 3)
    m.path_h(8, 5, w-6, 3)
    m.path_h(h-8, 5, w-6, 3)
    # Gym 1 (north-center, prominent)
    m.bld(cx-2, 3, MART)
    m.path_v(cx, 6, 8)
    # PokéCenter (northwest)
    m.bld(5, 3, POKECENTER)
    m.path_v(7, 7, 8)
    # Mart (northeast)
    m.bld(w-9, 3, MART)
    m.path_v(w-7, 6, 8)
    # Ice Cream Stand (center, small — HOUSE as placeholder)
    m.bld(cx-2, h//2-1, HOUSE)
    m.path_v(cx, h//2+3, h-8)
    # NPC House 1 — Roughneck Move Tutor (south-west)
    m.bld(5, h-7, HOUSE)
    m.path_v(7, h-8, h-3)
    # NPC House 2 (south, Wide Lens NPC)
    m.bld(cx-8, h-7, HOUSE)
    m.path_v(cx-6, h-8, h-3)
    # NPC House 3 (south-center)
    m.bld(cx+2, h-7, HOUSE)
    m.path_v(cx+4, h-8, h-3)
    # NPC House 4 (southeast)
    m.bld(w-9, h-7, HOUSE)
    m.path_v(w-7, h-8, h-3)
    # NPC House 5 (west-mid)
    m.bld(5, h//2-1, HOUSE)
    m.path_h(h//2, 8, cx-2, 3)
    # NPC House 6 (east-mid)
    m.bld(w-9, h//2-1, HOUSE)
    m.path_h(h//2, cx+2, w-9, 3)
    # 1 small grass patch (southwest corner)
    m.grass_patch(4, h-4, 1, 1)
    m.ent_n(cx); m.ent_s(cx)
    return m,w,h

def route3():
    """Pinehurst Woods. Forest gauntlet. 5 trainers (4 + Veil grunt).
    East branch to R4. Sparse grass, TM5 Protect, Bright Powder."""
    w,h = 30,48
    m = M(w,h,TTL)
    for y in range(0,h,2):
        for x in range(0,w,2): m.tree(x,y)
    m.rect(4,2,w-5,h-3,GR)
    cx = w//2
    m.wind_v(cx, 0, h-1, 3, amp=3, per=10)
    # Sparse grass patches throughout forest
    m.grass_patch(6, 6, 2, 1)
    m.grass_patch(w-7, 10, 2, 2)
    m.grass_patch(6, 18, 1, 2)
    m.grass_patch(w-6, 22, 2, 1)
    m.grass_patch(5, 28, 2, 1)
    m.grass_patch(w-7, 34, 2, 2)
    m.grass_patch(8, 40, 1, 1)
    # Trainer clearings
    m.clearing(cx+1, 8, 3, 1)
    m.clearing(cx-2, 16, 3, 1)
    m.clearing(cx+1, 24, 3, 1)
    m.clearing(cx-1, 32, 3, 1)
    m.clearing(cx, h-7, 4, 2)  # Veil grunt (south exit block)
    # East branch to R4
    m.path_h(h//3, cx, w-1, 3)
    m.ent_e(h//3, 3)
    # Items
    m.item(cx-5, 20)  # TM5 Protect
    m.item(8, 28)     # Bright Powder
    # Scattered trees in grass areas
    for (x,y) in [(8,5),(w-9,11),(7,17),(w-8,25),(6,33),(w-9,39)]:
        m.tree(x,y)
    m.ent_n(cx); m.ent_s(cx)
    return m,w,h

def route4():
    """Timber Creek. Optional, no trainers. Creek + sparse grass. TM6 Toxic hidden."""
    w,h = 26,24
    m = M(w,h,GR)
    m.border(2)
    cx = w//2
    # Creek runs through
    for y in range(2,h-2):
        wx = cx+3+int(2*math.sin(y*0.5))
        m.set(wx,y,WTR); m.set(wx+1,y,WTR)
    m.path_v(cx-1, 2, h-3, 3)
    # Sparse grass patches
    m.grass_patch(5, 5, 2, 2)
    m.grass_patch(5, 12, 2, 1)
    m.grass_patch(6, 18, 1, 2)
    m.grass_patch(w-8, 7, 1, 1)
    # Item: TM6 Toxic hidden
    m.item(cx-4, h//2)
    # Scattered trees
    for (x,y) in [(7,4),(4,9),(7,15),(4,20)]:
        m.tree(x,y)
    # West entrance (connects to R3)
    m.ent_w(h//2, 3)
    return m,w,h

def pinegrove_city():
    """CRATER CITY (Celestic-style). Stairs descend to center PokéCenter.
    Gym 2 + Mart + 7 NPC houses + Move Relearner. Small ponds for fishing/surf."""
    w,h = 34,30
    m = M(w,h,GR)
    m.border(2)
    cx,cy = w//2, h//2
    # Crater rim (cliff walls ringing the city)
    for y in range(3,h-3):
        for x in range(3,w-3):
            # Outer ring is higher ground (cliffs)
            dist = max(abs(x-cx), abs(y-cy))
            if dist >= 9:
                m.set(x,y,CLM)
    # Slope tiles descending into crater (muddy slopes = visual slope)
    # North slope
    for x in range(cx-2,cx+3):
        m.set(x,5,SLP); m.set(x,6,SLP)
    # South slope
    for x in range(cx-2,cx+3):
        m.set(x,h-7,SLP); m.set(x,h-6,SLP)
    # East slope
    for y in range(cy-2,cy+3):
        m.set(w-7,y,SLP); m.set(w-6,y,SLP)
    # West slope
    for y in range(cy-2,cy+3):
        m.set(5,y,SLP); m.set(6,y,SLP)
    # Paths around the crater rim (upper level)
    # Upper plaza (outside the crater)
    # Inner crater floor (walkable grass)
    m.rect(cx-7,cy-6,cx+7,cy+6,GR)
    # Central PokéCenter (at bottom of crater)
    m.bld(cx-2,cy-2,POKECENTER)
    # Paths from slopes to center PC
    m.path_v(cx, 7, cy-2)
    m.path_v(cx, cy+2, h-7)
    m.path_h(cy, 7, cx-2)
    m.path_h(cy, cx+2, w-7)
    # Gym 2 (upper-north, outside crater)
    m.bld(cx-2, 3, MART)
    m.path_v(cx, 6, 7)
    # Mart (upper-west)
    m.bld(5, 3, MART)
    m.path_h(5, 8, cx-2, 3)
    # NPC Houses around rim (7 houses)
    m.bld(w-9, 3, HOUSE)    # 1: northeast rim
    m.path_h(5, cx+2, w-9, 3)
    m.bld(3, cy-2, HOUSE)    # 2: west rim — Move Relearner
    m.bld(w-5, cy-2, HOUSE)  # 3: east rim
    m.bld(5, h-7, HOUSE)     # 4: southwest rim
    m.bld(w-9, h-7, HOUSE)   # 5: southeast rim
    m.bld(cx-6, h-7, HOUSE)  # 6: south-center-left
    m.bld(cx+2, h-7, HOUSE)  # 7: south-center-right
    # Small fishing ponds (south side of rim area)
    m.rect(cx-4,h-5,cx-2,h-4,WTR)
    m.rect(cx+2,h-5,cx+4,h-4,WTR)
    # 1 small grass patch on crater floor
    m.grass_patch(cx-5, cy+2, 1, 1)
    m.ent_n(cx); m.ent_s(cx)
    return m,w,h

def route5():
    """Ironfrost Cave. Gauntlet. 2 trainers + 4 grunts + Crash boss.
    TM9 + Light Clay. Sparse encounter areas."""
    w,h = 28,42
    m = M(w,h,CWL)
    m.rect(4,2,w-5,h-3,CFL)
    cx = w//2
    m.path_v(cx, 0, h-1, 3)
    # Rock pillars
    m.rect(4,7,8,10,CW2)
    m.rect(w-9,13,w-5,16,CW2)
    m.rect(4,19,8,22,CW2)
    m.rect(w-9,25,w-5,28,CW2)
    # Side alcoves
    m.rect(4,11,8,13,CF2)
    m.rect(w-9,8,w-5,10,CF2)
    m.rect(4,29,8,31,CF2)
    # Trainer/grunt clearings
    m.clearing(cx, 5, 3, 1)    # Knox
    m.clearing(cx, 11, 3, 1)   # Lina
    m.clearing(cx, 17, 3, 1)   # Grunt 1
    m.clearing(cx, 23, 3, 1)   # Grunt 2
    m.clearing(cx, 29, 3, 1)   # Grunts 3+4 tag
    m.clearing(cx, h-7, 4, 2)  # Crash boss
    # Items
    m.item(6, 15)
    m.item(w-7, 21)
    m.ent_n(cx); m.ent_s(cx)
    return m,w,h

def ironfrost_city():
    """Oreburgh-style mining/industrial. Winter-themed. Heavy mining equipment (rocks).
    Gym 3 + PC + Mart + Fossil Revival + Fossil Gift NPC + 7 houses + Geologist Tutor."""
    w,h = 38,28
    m = M(w,h,GR)
    m.border(2)
    cx = w//2
    m.path_v(cx, 0, h-1, 3)
    m.path_h(9, 4, w-5, 3)
    m.path_h(h-9, 4, w-5, 3)
    # Mining/construction rock formations (decorative)
    m.rect(3, h//2-1, 6, h//2+1, CLD)   # West mine pit
    m.rect(w-6, h//2-1, w-3, h//2+1, CLM) # East mine pit
    m.rect(cx-8, 12, cx-5, 14, CLM)      # Center construction
    m.rect(cx+5, 14, cx+8, 16, CLD)      # Another pile
    # Gym 3 (north-center, prominent)
    m.bld(cx-2, 3, MART)
    m.path_v(cx, 6, 9)
    # PokéCenter (northwest)
    m.bld(5, 3, POKECENTER)
    m.path_v(7, 7, 9)
    # Mart (northeast)
    m.bld(w-9, 3, MART)
    m.path_v(w-7, 6, 9)
    # Fossil Revival Lab (west-mid, large — POKECENTER model)
    m.bld(5, h//2-2, POKECENTER)
    m.path_v(7, h//2+2, h-9)
    # NPC House 1: Fossil Gift man (east-mid)
    m.bld(w-9, h//2-2, HOUSE)
    m.path_v(w-7, h//2+2, h-9)
    # NPC House 2: Geologist Tutor (south-west)
    m.bld(5, h-8, HOUSE)
    m.path_v(7, h-8, h-3)
    # NPC House 3 (south-center-left)
    m.bld(cx-8, h-8, HOUSE)
    m.path_v(cx-6, h-8, h-3)
    # NPC House 4 (south-center)
    m.bld(cx-2, h-8, HOUSE)
    m.path_v(cx, h-8, h-3)
    # NPC House 5 (south-center-right)
    m.bld(cx+2, h-8, HOUSE)
    m.path_v(cx+4, h-8, h-3)
    # NPC House 6 (southeast)
    m.bld(w-9, h-8, HOUSE)
    m.path_v(w-7, h-8, h-3)
    # NPC House 7 (west high)
    m.bld(cx-8, 3, HOUSE)
    m.path_v(cx-6, 7, 9)
    # 1 small grass patch
    m.grass_patch(w-5, h-4, 1, 1)
    # West exit to Ironfrost Cave B1
    m.ent_w(h//2, 3)
    m.ent_n(cx); m.ent_s(cx)
    return m,w,h


# ═══════════════════════════════════════════════════════════
# ACT 2 — TRANSITIONAL ZONE
# ═══════════════════════════════════════════════════════════

def route6():
    """Glacier Lake. Central frozen lake, ring path. Ice puzzle area, Surf-gated."""
    w,h = 34,42
    m = M(w,h,CLM)
    m.rect(4,2,w-5,h-3,GR)
    cx,cy = w//2, h//2
    # Central frozen lake
    for y in range(h):
        for x in range(w):
            if (x-cx)**2+(y-cy)**2 <= 49: m.set(x,y,WTR)
    # Ring path around lake
    for a in range(0,360,2):
        r=math.radians(a)
        for rad in range(8,10):
            px,py=int(cx+rad*math.cos(r)),int(cy+rad*math.sin(r))
            m.set(px,py,PC)
    # Main path west side
    m.path_v(cx-10, 0, h-1, 3)
    m.path_h(cy, cx-10, cx-8, 3)
    # Ice puzzle area (NE, elevated plateau with TM13)
    m.rect(cx+8, 4, w-5, 12, GR)
    m.rect(cx+9, 5, w-6, 11, CLL)  # Ice tiles
    m.item(w-7, 8)  # TM13 Ice Beam
    # Surf-gated area (SE with Razor Claw)
    m.rect(cx+6, cy+8, w-5, h-5, WTR)
    m.item(w-7, cy+12)  # Razor Claw
    # Trainer clearings around lake
    for a in range(0,360,45):
        r=math.radians(a)
        tx,ty=int(cx+11*math.cos(r)),int(cy+11*math.sin(r))
        m.clearing(tx,ty,2,1)
    # Sparse grass patches
    m.grass_patch(6, 6, 2, 1)
    m.grass_patch(6, h-7, 2, 1)
    m.grass_patch(cx-3, 4, 1, 1)
    m.grass_patch(cx+3, h-5, 2, 1)
    # Zoom Lens
    m.item(cx-7, cy-4)
    m.ent_n(cx-10); m.ent_s(cx-10)
    return m,w,h

def frostbreak_lodge():
    """Small mountain rest stop. Large lodge (specialty shop). Shell Bell NPC. Yanma gift."""
    w,h = 22,18
    m = M(w,h,GR)
    m.border(2)
    cx = w//2
    m.path_v(cx, 0, h-1, 3)
    # Main Lodge (center — large POKECENTER model)
    m.bld(cx-2, 4, POKECENTER)
    m.path_v(cx, 8, h-4)
    # Small house (Shell Bell NPC)
    m.bld(5, h-8, HOUSE)
    m.path_h(h-7, 7, cx-2, 3)
    # NPC House (Yanma gift)
    m.bld(w-8, h-8, HOUSE)
    m.path_h(h-7, cx+2, w-8, 3)
    m.ent_n(cx); m.ent_s(cx)
    return m,w,h

def route7():
    """Galetop Plateau. 5 trainers. 9 hidden berries. F10 Autumn."""
    w,h = 28,40
    m = M(w,h,CLM)
    m.rect(4,2,w-5,h-3,GR)
    cx = w//2
    m.wind_v(cx, 0, h-1, 3, amp=4, per=11)
    # Berry bush area (west side)
    m.rect(5, 14, 9, 22, GR)
    for y in (15,17,19,21):
        for x in (6,8): m.item(x,y)
    # Trainer clearings
    for (dy,dx) in [(8,1),(16,-2),(24,0),(30,2),(36,-1)]:
        m.clearing(cx+dx, dy, 3, 1)
    # F10 Autumn area (south)
    m.clearing(cx, h-8, 4, 2)
    # Postgame F29 Crash area (north)
    m.clearing(5, 8, 3, 1)
    # Sparse grass patches
    m.grass_patch(w-7, 10, 2, 1)
    m.grass_patch(w-8, 20, 1, 2)
    m.grass_patch(w-6, 32, 2, 1)
    m.ent_n(cx); m.ent_s(cx)
    return m,w,h

def route8():
    """Dreamurs Valley. Misty Terrain valley with stream. 6 trainers."""
    w,h = 28,38
    m = M(w,h,CLM)
    m.rect(4,2,w-5,h-3,GR)
    cx = w//2
    m.wind_v(cx, 0, h-1, 3, amp=3, per=9)
    # Valley stream (east side)
    for y in range(5,h-5):
        wx = cx+6+int(2*math.sin(y*0.3))
        m.set(wx,y,WTR); m.set(wx+1,y,WTR)
    # Trainer clearings
    for i in range(6):
        ty = 5+i*((h-10)//6)
        m.clearing(cx+int(2*math.sin(ty*0.7)), ty, 3, 1)
    # TM17 Will-O-Wisp hidden
    m.item(7, h//2+3)
    # Sparse grass
    m.grass_patch(6, 8, 2, 1)
    m.grass_patch(6, 18, 1, 2)
    m.grass_patch(6, 28, 2, 1)
    m.grass_patch(cx-4, 14, 1, 1)
    m.ent_n(cx); m.ent_s(cx)
    return m,w,h

def dreamurs_town():
    """Mystical, dreamy, welcoming. Gym 4 + PC + Mart + Daycare + 5 NPC houses."""
    w,h = 30,22
    m = M(w,h,GR)
    m.border(2)
    cx = w//2
    m.path_v(cx, 0, h-1, 3)
    m.path_h(8, 5, w-6, 3)
    m.path_h(h-8, 5, w-6, 3)
    # Gym 4 (north-center)
    m.bld(cx-2, 3, MART)
    m.path_v(cx, 6, 8)
    # PokéCenter (northwest)
    m.bld(5, 3, POKECENTER)
    m.path_v(7, 7, 8)
    # Mart (northeast)
    m.bld(w-9, 3, MART)
    m.path_v(w-7, 6, 8)
    # Daycare (southwest — large building)
    m.bld(5, h-8, POKECENTER)
    m.path_v(7, h-8, h-3)
    # NPC Houses
    m.bld(w-9, h-8, HOUSE)     # Move Relearner (south-east)
    m.path_v(w-7, h-8, h-3)
    m.bld(cx-6, h-8, HOUSE)    # NPC
    m.path_v(cx-4, h-8, h-3)
    m.bld(cx+2, h-8, HOUSE)    # NPC
    m.path_v(cx+4, h-8, h-3)
    m.bld(cx-8, 3, HOUSE)      # NPC
    m.path_v(cx-6, 6, 8)
    m.bld(cx+4, 3, HOUSE)      # NPC
    m.path_v(cx+6, 6, 8)
    # 1 grass patch
    m.grass_patch(4, h-4, 1, 1)
    m.ent_n(cx)
    m.ent_e(h//2, 3)
    return m,w,h

def route9():
    """Iceharbor Bay. Eastern coast — half-frozen ocean. 8 trainers (2 Surf-gated)."""
    w,h = 34,34
    m = M(w,h,CLM)
    split = w*3//5
    m.rect(4,2,split-1,h-3,GR)
    m.rect(split,2,w-3,h-3,WTR)
    # Partially frozen ice tiles in water (CLL for icy look)
    for (x,y) in [(split+3,5),(split+5,10),(split+2,15),(split+6,20),(split+4,25),(split+7,12)]:
        if 0<=x<w and 0<=y<h: m.set(x,y,CLL)
    m.path_v(split-3, 0, h-1, 3)
    # Irregular shoreline
    for y in range(2,h-2):
        off = int(1.5*math.sin(y*0.4))
        m.set(split+off,y,GR); m.set(split+off-1,y,GR)
    # Trainer clearings (6 main)
    for i in range(6):
        ty = 5+i*((h-10)//6)
        m.clearing(split-5, ty, 3, 1)
    # 2 Surf-gated swimmers
    m.clearing(w-8, h//3, 2, 1)
    m.clearing(w-8, 2*h//3, 2, 1)
    # TM19 Shadow Ball
    m.item(8, h//2)
    # Sparse grass
    m.grass_patch(7, 7, 2, 1)
    m.grass_patch(9, 18, 1, 2)
    m.grass_patch(6, 28, 2, 1)
    m.ent_w(h//2, 3); m.ent_e(h//2, 3)
    return m,w,h

def iceharbor_city():
    """Medium port city. Half-frozen harbor. PC + Mart + Gym 5 + Facility Delta +
    cargo bays/warehouses + Sailor Tutor + 8 houses."""
    w,h = 38,28
    m = M(w,h,GR)
    m.border(2)
    cx = w//2
    m.path_v(cx, 4, h-1, 3)
    m.path_h(9, 5, w-6, 3)
    m.path_h(h-9, 5, w-6, 3)
    # Harbor water (east side) — half frozen
    m.rect(w-10, 4, w-4, h-5, WTR)
    # Ice chunks in harbor
    for (x,y) in [(w-8,6),(w-6,10),(w-9,14),(w-5,18),(w-7,22)]:
        m.set(x,y,CLL)
    # Gym 5 (north-center)
    m.bld(cx-2, 3, MART)
    m.path_v(cx, 6, 9)
    # PokéCenter (northwest)
    m.bld(5, 3, POKECENTER)
    m.path_v(7, 7, 9)
    # Mart (north — west of center)
    m.bld(cx-8, 3, MART)
    m.path_v(cx-6, 6, 9)
    # Facility Delta (south-west — large POKECENTER model)
    m.bld(5, h-9, POKECENTER)
    m.path_v(7, h-9, h-4)
    # Cargo warehouse 1 (south — HOUSE as large cargo building)
    m.bld(cx-7, h-9, HOUSE)
    m.path_v(cx-5, h-9, h-4)
    # Cargo warehouse 2 (south-center — Sailor Tutor)
    m.bld(cx-1, h-9, HOUSE)
    m.path_v(cx+1, h-9, h-4)
    # NPC Houses 1-4
    m.bld(cx-14, 3, HOUSE)
    m.path_v(cx-12, 6, 9)
    m.bld(5, h//2-1, HOUSE)
    m.path_h(h//2+1, 8, cx-2, 3)
    m.bld(cx-14, h-9, HOUSE)
    m.path_v(cx-12, h-9, h-4)
    # House: Black Sludge NPC
    m.bld(cx+3, h//2-1, HOUSE)
    m.path_h(h//2+1, cx+5, w-11, 3)
    # East: Surf access to Driftrock Isle
    m.ent_e(h//2, 3)
    m.ent_w(h//2, 3)
    m.ent_s(cx)
    return m,w,h

def driftrock_isle():
    """Surf-accessible island. 5 trainers. King's Rock, TM22 Bulk Up."""
    w,h = 26,28
    m = M(w,h,WTR)
    cx,cy = w//2, h//2
    # Island landmass
    for y in range(h):
        for x in range(w):
            if (x-cx)**2+(y-cy)**2 <= 100: m.set(x,y,GR)
    m.path_v(cx, cy-7, cy+7, 3)
    m.path_h(cy, cx-6, cx+6, 3)
    # Trainer spots
    m.clearing(6, 6, 2, 1)
    m.clearing(w-7, 6, 2, 1)
    m.clearing(6, h-7, 2, 1)
    m.clearing(w-7, h-7, 2, 1)
    m.clearing(cx, cy, 3, 2)  # Ranger Heath
    # Items
    m.item(cx+3, cy-3)
    m.item(cx-4, cy+2)
    # Sparse grass
    m.grass_patch(cx-4, cy-4, 1, 1)
    m.grass_patch(cx+4, cy+4, 2, 1)
    m.ent_w(cy, 3)
    return m,w,h

def route10():
    """Snowburn Path. Fire/ice dual cave. 8-trainer gauntlet. Longest."""
    w,h = 28,42
    m = M(w,h,CWL)
    m.rect(4,2,w-5,h-3,CFL)
    cx = w//2
    m.path_v(cx, 0, h-1, 3)
    # Alternating pillars
    for i in range(6):
        py = 5+i*6
        if i%2==0: m.rect(4,py,8,py+2,CW2)
        else: m.rect(w-9,py,w-5,py+2,CW2)
    # Side rooms
    m.rect(4, h//4, 8, h//4+3, CF2)
    m.rect(w-9, h//2, w-5, h//2+3, CF2)
    m.rect(4, 3*h//4, 8, 3*h//4+3, CF2)
    # 8 trainer clearings
    for i in range(8):
        ty = 4+i*((h-10)//8)
        m.clearing(cx, ty, 3, 1)
    # Items
    m.item(6, h//4+1)
    m.item(w-7, h//2+1)
    m.item(cx+4, h-8)
    m.ent_n(cx); m.ent_s(cx)
    return m,w,h

def route11():
    """Brightbloom Meadow. Flower meadow. 6 trainers. Last 0-EV route."""
    w,h = 30,38
    m = M(w,h,CLM)
    m.rect(4,2,w-5,h-3,GR)
    cx = w//2
    m.wind_v(cx, 0, h-1, 3, amp=5, per=12)
    # Flower patches
    m.rect(6,8,9,11,LG)
    m.rect(w-10,16,w-7,19,LG)
    m.rect(7,26,10,29,LG)
    # Trainer clearings
    for i in range(6):
        ty = 5+i*((h-10)//6)
        off = int(4*math.sin(ty*0.5))
        m.clearing(cx+off, ty, 3, 1)
    # F14 Asher
    m.clearing(cx, h-8, 4, 2)
    # Items
    m.item(cx-6, 14)
    m.item(w-8, 24)
    m.item(8, h-10)
    # Sparse grass patches
    m.grass_patch(6, 6, 1, 1)
    m.grass_patch(w-6, 12, 2, 1)
    m.grass_patch(8, 22, 1, 2)
    m.ent_n(cx); m.ent_s(cx)
    return m,w,h

def dragonforge_city():
    """LARGEST CITY. Team Veil HQ Facility Alpha (visible, locked pre-Gym 8).
    Gym 6 + PC (with Professor's Aide Tutor) + Department Store + 10+ houses + decorative buildings."""
    w,h = 42,32
    m = M(w,h,GR)
    m.border(2)
    cx = w//2
    # Main N-S path
    m.path_v(cx, 0, h-1, 3)
    # Multiple cross paths for large city
    m.path_h(6, 4, w-5, 3)
    m.path_h(h//2, 4, w-5, 3)
    m.path_h(h-7, 4, w-5, 3)
    # Facility Alpha (northeast — LARGE, uses multiple buildings combined)
    m.bld(w-10, 3, POKECENTER)   # Main facility
    m.bld(w-10, 8, HOUSE)         # Facility annex
    m.path_v(w-8, 7, h//2)
    # Gym 6 (north-center)
    m.bld(cx-2, 3, MART)
    m.path_v(cx, 6, 6)
    # PokéCenter (northwest) — Professor's Aide tutor inside
    m.bld(4, 3, POKECENTER)
    m.path_v(6, 7, 6)
    # Department Store (east, LARGE — 2 buildings stacked)
    m.bld(w-10, h//2-2, POKECENTER)  # Main dept store
    m.bld(w-10, h//2+3, HOUSE)       # Annex
    m.path_v(w-8, h//2-2, h//2)
    # Mart (west-mid)
    m.bld(4, h//2-2, MART)
    m.path_h(h//2, 8, cx-2, 3)
    # 10 enterable NPC houses spread across the large city
    # North row
    m.bld(cx-10, 3, HOUSE); m.path_v(cx-8, 6, 6)
    m.bld(cx+4, 3, HOUSE); m.path_v(cx+6, 6, 6)
    # Mid row west
    m.bld(11, h//2-2, HOUSE); m.path_v(13, h//2, h//2+1)
    # Mid row center
    m.bld(cx-6, h//2-2, HOUSE); m.path_v(cx-4, h//2, h//2+1)
    m.bld(cx+2, h//2-2, HOUSE); m.path_v(cx+4, h//2, h//2+1)
    # South row
    m.bld(4, h-8, HOUSE); m.path_v(6, h-8, h-6)
    m.bld(11, h-8, HOUSE); m.path_v(13, h-8, h-6)
    m.bld(cx-5, h-8, HOUSE); m.path_v(cx-3, h-8, h-6)
    m.bld(cx+3, h-8, HOUSE); m.path_v(cx+5, h-8, h-6)
    m.bld(w-10, h-8, HOUSE); m.path_v(w-8, h-8, h-6)
    # Decorative (non-enterable) large buildings — visual scale
    # Use POKECENTER patterns as decoration for tall skyscraper feel
    m.bld(18, 3, POKECENTER)          # Tall building 1
    m.bld(cx-13, h//2+4, POKECENTER)  # Tall building 2
    m.bld(28, h//2+4, POKECENTER)     # Tall building 3
    m.ent_n(cx); m.ent_s(cx)
    return m,w,h


# ═══════════════════════════════════════════════════════════
# ACT 3 — TROPICAL/VOLCANIC ZONE
# ═══════════════════════════════════════════════════════════

def route12():
    """Memoria Passage. Ghost cave. Spiritomb side passage. 7 trainers. First full-EV."""
    w,h = 28,40
    m = M(w,h,CWL)
    m.rect(4,2,w-5,h-3,CFL)
    cx = w//2
    m.path_v(cx, 0, h-1, 3)
    # Cave rooms
    m.rect(4,8,9,14,CF2)
    m.rect(w-10,18,w-5,24,CF2)
    # Spiritomb side passage (west dead-end)
    m.rect(4,h//2-2,10,h//2+2,CF2)
    m.item(5, h//2)
    # Rock pillars
    m.rect(4,16,7,17,CW2)
    m.rect(w-8,10,w-5,11,CW2)
    m.rect(4,28,7,29,CW2)
    # Trainer clearings
    for i,(ty,dx) in enumerate([(6,0),(12,2),(18,-2),(24,1),(30,-1),(36,0)]):
        rw = 4 if i==5 else 3
        m.clearing(cx+dx, ty, rw, 1)
    m.item(cx+5, 20)
    m.item(7, 26)
    m.ent_n(cx); m.ent_s(cx)
    return m,w,h

def solace_town():
    """Rural agricultural town. Kyurem relics. Gym 7 + PC + Mart + 5 houses +
    secret Anti-Veil hideout."""
    w,h = 28,22
    m = M(w,h,GR)
    m.border(2)
    cx = w//2
    m.path_v(cx, 0, h-1, 3)
    m.path_h(h//2, 5, w-6, 3)
    # PokéCenter (northwest)
    m.bld(5, 3, POKECENTER)
    m.path_v(7, 7, h//2)
    # Gym 7 (northeast)
    m.bld(w-9, 3, MART)
    m.path_v(w-7, 6, h//2)
    # Mart (north-center)
    m.bld(cx-2, 3, MART)
    m.path_v(cx, 6, h//2)
    # Kyurem relic monument (center — using HOUSE as a stone monument)
    m.bld(cx-2, h//2+1, HOUSE)
    # NPC Houses
    m.bld(5, h-8, HOUSE)       # Dale NPC
    m.bld(cx-8, h-8, HOUSE)
    m.bld(w-9, h-8, HOUSE)
    m.bld(cx+4, h-8, HOUSE)
    m.bld(cx-13, h//2-1, HOUSE)  # Secret Anti-Veil hideout (looks like normal house)
    # 1 small grass patch
    m.grass_patch(w-5, h-4, 1, 1)
    m.ent_n(cx); m.ent_s(cx)
    return m,w,h

def route13():
    """Verdant Jungle. Dense tropical. 9-trainer gauntlet (continues to R14)."""
    w,h = 32,50
    m = M(w,h,TTL)
    for y in range(0,h,2):
        for x in range(0,w,2): m.tree(x,y)
    m.rect(4,2,w-5,h-3,GR)
    cx = w//2
    m.wind_v(cx, 0, h-1, 3, amp=5, per=9)
    # Jungle stream (east side)
    for y in range(h//4, 3*h//4):
        wx = cx+7+int(2*math.sin(y*0.3))
        m.set(wx,y,WTR); m.set(wx+1,y,WTR)
    # 9 trainer clearings
    for i in range(9):
        ty = 4+i*((h-10)//9)
        off = int(4*math.sin(ty*0.6))
        m.clearing(cx+off, ty, 3, 1)
    # Items
    m.item(cx-6, h//3)
    m.item(cx+5, 2*h//3)
    m.item(8, h//2)
    # Sparse grass
    m.grass_patch(6, 8, 2, 1)
    m.grass_patch(w-7, 20, 1, 2)
    m.grass_patch(7, 35, 2, 1)
    m.ent_n(cx); m.ent_s(cx)
    return m,w,h

def route14():
    """Cinderstone Path. Volcanic ash. 9 trainers (continues from R13)."""
    w,h = 30,42
    m = M(w,h,CLM)
    m.rect(4,2,w-5,h-3,GR)
    cx = w//2
    m.wind_v(cx, 0, h-1, 3, amp=3, per=7)
    # Volcanic rock formations
    m.rect(5,6,9,9,CLD)
    m.rect(w-10,14,w-6,17,CLD)
    m.rect(6,22,10,25,CLD)
    m.rect(w-10,30,w-6,33,CLD)
    # 9 trainer clearings (8 encounters)
    for i in range(8):
        ty = 4+i*((h-10)//8)
        rw = 4 if i==7 else 3
        m.clearing(cx+int(2*math.sin(ty*0.5)), ty, rw, 1)
    # Items
    m.item(cx-5, 12)
    m.item(w-8, 20)
    m.item(cx+5, 28)
    m.item(8, h-10)
    # Sparse grass
    m.grass_patch(w-7, 10, 1, 1)
    m.grass_patch(6, 18, 2, 1)
    m.grass_patch(w-6, 35, 1, 2)
    m.ent_n(cx); m.ent_w(h//2, 3)
    return m,w,h

def route15():
    """Pyrespire Lagoon. FORK structure. F18 Autumn at fork. 9 trainers (3 Surf-gated)."""
    w,h = 32,48
    m = M(w,h,CLM)
    m.rect(4,2,w-5,h-3,GR)
    cx = w//2
    # East entrance path from R14
    m.path_h(6, 0, cx, 3)
    # Path south to fork
    m.path_v(cx, 6, h//2-2, 3)
    # Fork junction
    fy = h//2
    m.clearing(cx, fy-2, 5, 2)  # F18 Autumn battle area
    # North fork to Research Outpost
    m.path_v(cx-6, fy-4, fy, 3)
    m.rect(cx-9, fy-8, cx-4, fy-4, GR)
    m.bld(cx-9, fy-8, HOUSE)  # Research Outpost
    # South fork to Pyrespire City
    m.path_v(cx, fy, h-1, 3)
    # Pre-fork trainers
    m.clearing(cx-3, 10, 3, 1)
    m.clearing(cx+2, 16, 3, 1)
    # Post-fork trainers
    m.clearing(cx, fy+6, 3, 1)
    m.clearing(cx-2, fy+12, 3, 1)
    m.clearing(cx+1, fy+18, 3, 1)
    m.clearing(cx, h-8, 3, 1)  # Quint (mandatory gate)
    # Lagoon water
    m.rect(cx+5, fy+4, w-5, h-5, WTR)
    # Surf swimmers
    m.clearing(w-8, fy+8, 2, 1)
    m.clearing(w-10, fy+14, 2, 1)
    m.clearing(w-8, fy+20, 2, 1)
    # Items
    m.item(cx+3, fy+10)
    for (x,y) in [(6,12),(w-8,fy-4),(8,fy+8),(cx-5,h-10),(6,h-6)]:
        m.item(x,y)
    # Sparse grass
    m.grass_patch(7, 20, 2, 1)
    m.grass_patch(8, 35, 1, 2)
    m.ent_e(6, 3); m.ent_s(cx)
    return m,w,h

def pyrespire_city():
    """Second-largest city. Tropical vibe. Facility Beta. Gym 8 + PC + Mart +
    Fossil Museum + Volcano Hermit Tutor + 9 houses + decorative buildings."""
    w,h = 38,30
    m = M(w,h,GR)
    m.border(2)
    cx = w//2
    m.path_v(cx, 0, h-1, 3)
    m.path_h(6, 4, w-5, 3)
    m.path_h(h//2, 4, w-5, 3)
    m.path_h(h-7, 4, w-5, 3)
    # Facility Beta (east — LARGE)
    m.bld(w-10, 3, POKECENTER)
    m.bld(w-10, 8, HOUSE)
    m.path_v(w-8, 7, h//2)
    # Gym 8 (north-center)
    m.bld(cx-2, 3, MART)
    m.path_v(cx, 6, 6)
    # PokéCenter (northwest)
    m.bld(4, 3, POKECENTER)
    m.path_v(6, 7, 6)
    # Mart (north-center-west)
    m.bld(cx-9, 3, MART)
    m.path_v(cx-7, 6, 6)
    # Fossil Museum (south-east)
    m.bld(w-10, h-9, POKECENTER)
    m.path_v(w-8, h-9, h-4)
    # 9 enterable NPC houses
    m.bld(11, 3, HOUSE); m.path_v(13, 6, 6)
    m.bld(4, h//2-2, HOUSE); m.path_h(h//2, 8, cx-2, 3)
    m.bld(cx-9, h//2-2, HOUSE)
    m.bld(cx+3, h//2-2, HOUSE)  # Volcano Hermit Tutor
    m.bld(cx+10, h//2-2, HOUSE)
    m.bld(4, h-9, HOUSE); m.path_v(6, h-9, h-4)
    m.bld(cx-9, h-9, HOUSE); m.path_v(cx-7, h-9, h-4)
    m.bld(cx-2, h-9, HOUSE); m.path_v(cx, h-9, h-4)
    m.bld(cx+4, h-9, HOUSE); m.path_v(cx+6, h-9, h-4)
    # Decorative large buildings (tropical resort feel)
    m.bld(18, 3, POKECENTER)
    m.bld(cx-14, h-9, POKECENTER)
    m.ent_n(cx); m.ent_s(cx)
    return m,w,h

def victory_road():
    """Volcano interior labyrinth. 8 Ace Trainers in chambers. F30 Asher final."""
    w,h = 32,50
    m = M(w,h,CWL)
    m.rect(4,2,w-5,h-3,CFL)
    cx = w//2
    m.path_v(cx, 0, h-1, 3)
    # Chamber rooms
    for i in range(8):
        cy = 4 + i*5
        m.rect(6,cy,w-7,cy+3,CF2)
        if i < 7:
            m.rect(cx-2,cy+3,cx+2,cy+5,CFL)
    # Pillars
    for i in range(0,8,2):
        cy = 4+i*5
        m.rect(6,cy,9,cy+1,CW2)
        m.rect(w-10,cy+1,w-7,cy+2,CW2)
    # Trainer clearings
    for i in range(8):
        m.clearing(cx, 5+i*5, 3, 1)
    # F30 Asher final chamber
    m.rect(6,h-8,w-7,h-4,CF2)
    m.clearing(cx, h-6, 4, 2)
    # Mid-sanctum PP restore
    m.rect(cx-3,h//2-1,cx+3,h//2+1,CF2)
    # Choice Band
    m.item(w-8, 22)
    m.ent_n(cx); m.ent_s(cx)
    return m,w,h

def pokemon_league():
    """League Lobby (PC + Mart separate from recovery room). Arena entrance."""
    w,h = 28,22
    m = M(w,h,GR)
    m.border(2)
    cx = w//2
    m.path_v(cx, 0, h-1, 3)
    # Arena entrance (center — large)
    m.bld(cx-2, 4, POKECENTER)
    m.path_v(cx, 8, h//2)
    # PokéCenter (west — Lobby)
    m.bld(5, 4, POKECENTER)
    m.path_h(8, 5, cx-2, 3)
    # Mart (east — Lobby)
    m.bld(w-9, 5, MART)
    m.path_h(8, cx+2, w-9, 3)
    # NPC houses (waiting area)
    m.bld(5, h-8, HOUSE)
    m.bld(w-9, h-8, HOUSE)
    m.ent_n(cx)
    return m,w,h

def cave_b1():
    """Ironfrost B1. Leftovers + Assault Vest postgame items."""
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
    m.item(6, h//3+2)
    m.item(w-7, h//3+2)
    m.ent_n(cx); m.ent_s(cx)
    return m,w,h

def cave_b2b3():
    """Ironfrost B2-B3. Kyurem static + Choice Specs."""
    w,h = 30,34
    m = M(w,h,CWL)
    m.rect(4,2,w-5,h-3,CFL)
    cx = w//2
    m.path_v(cx, 0, h-1, 3)
    m.rect(6,4,w-7,h-5,CF2)
    m.rect(8,h-12,w-9,h-5,CFL)
    m.clearing(cx, h-8, 5, 3)
    m.rect(4,8,8,10,CW2)
    m.rect(w-9,14,w-5,16,CW2)
    m.rect(4,20,8,22,CW2)
    m.item(w-8, 12)
    m.ent_n(cx)
    return m,w,h


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
