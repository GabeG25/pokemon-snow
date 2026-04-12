#!/usr/bin/env python3
"""Generate detailed map layouts for all Snow locations.
Uses proper metatile encoding with correct elevation, collision,
tree borders, buildings, and path systems from vanilla patterns."""

import json, struct, math, random
from pathlib import Path

random.seed(2026)
REPO = Path(__file__).resolve().parent.parent.parent

# ═══════════════════════════════════════════════════
# METATILE ENCODING
# Format: metatile_id | (collision << 10) | (elevation << 12)
# ═══════════════════════════════════════════════════
def T(meta, col=0, elv=3):
    return meta | (col << 10) | (elv << 12)

# ═══ PRIMARY TILESET (General) — works with all secondary tilesets ═══

# Ground tiles (elevation 3, passable)
GRASS        = T(0x001)  # Short grass, walkable, no encounters
GRASS2       = T(0x004)  # Alternative ground
TALL_GRASS   = T(0x00D)  # Encounter grass!
LONG_GRASS   = T(0x015)  # Long encounter grass
SIGN         = T(0x003)  # Sign/decoration tile

# Path system (elevation 3, passable) — forms connected walkways
PATH_TL      = T(0x1D0)  # Path top-left corner
PATH_T       = T(0x1D1)  # Path top edge
PATH_TR      = T(0x1D2)  # Path top-right corner
PATH_L       = T(0x1D8)  # Path left edge
PATH_C       = T(0x1D9)  # Path center (main walkable)
PATH_R       = T(0x1DA)  # Path right edge
PATH_BL      = T(0x1E0)  # Path bottom-left corner
PATH_B       = T(0x1E1)  # Path bottom edge
PATH_BR      = T(0x1E2)  # Path bottom-right corner

# Tree tiles (2x2 blocks, impassable, elevation 0)
TREE_TL      = T(0x1D4, col=1, elv=0)  # Tree top-left
TREE_TR      = T(0x1D5, col=1, elv=0)  # Tree top-right
TREE_BL      = T(0x1DC, col=1, elv=0)  # Tree bottom-left
TREE_BR      = T(0x1DD, col=1, elv=0)  # Tree bottom-right
# Tree edge variants
TREE_ETL     = T(0x1E4, col=1, elv=0)  # Edge top-left
TREE_ETR     = T(0x1E5, col=1, elv=0)  # Edge top-right
TREE_EBL     = T(0x1E6, col=1, elv=0)  # Edge bottom-left corner
TREE_EBR     = T(0x1E7, col=1, elv=0)  # Edge bottom-right corner
TREE_EDL     = T(0x1D6, col=1, elv=0)  # Edge down-left
TREE_EDR     = T(0x1D7, col=1, elv=0)  # Edge down-right
# Tall grass + tree combo
TGRASS_TL    = T(0x1C6)  # Tall grass under tree left
TGRASS_TR    = T(0x1C7)  # Tall grass under tree right
# Grass-tree transitions
GTREE_L      = T(0x1CE)  # Grass-tree left transition
GTREE_R      = T(0x1CF)  # Grass-tree right transition

# Water (elevation 1, passable/surfable)
WATER        = T(0x170, elv=1)
WATER_EDGE   = T(0x171, elv=1)

# Rock/cliff (impassable)
ROCK_GR      = T(0x079, col=1, elv=0)  # Rock wall grass base
ROCK_RK      = T(0x07C, col=1, elv=0)  # Rock wall rock base
CLIFF_DK     = T(0x075, col=1, elv=0)  # Dark cliff
CLIFF_MD     = T(0x073, col=1, elv=0)  # Medium cliff
CLIFF_LT     = T(0x071, col=1, elv=0)  # Light cliff
LEDGE_T      = T(0x089, col=1, elv=0)  # Ledge top

# Cave tiles (secondary tileset: gTileset_Cave)
CAVE_FL      = T(0x201)               # Cave floor walkable
CAVE_FL2     = T(0x211)               # Cave floor variant
CAVE_WL      = T(0x211, col=1, elv=0) # Cave wall
CAVE_WL2     = T(0x219, col=1, elv=0) # Cave wall variant
CAVE_WL3     = T(0x209, col=1, elv=0) # Another wall

# ═══ SECONDARY TILESET BUILDINGS (Petalburg) ═══
# PokéCenter exterior (4 wide × 4 tall)
POKECENTER = [
    [T(0x26C), T(0x26D), T(0x26D), T(0x26E)],
    [T(0x274, col=1, elv=0), T(0x275, col=1, elv=0), T(0x275, col=1, elv=0), T(0x276, col=1, elv=0)],
    [T(0x27C, col=1, elv=0), T(0x27F, col=1, elv=0), T(0x27D, col=1, elv=0), T(0x27E, col=1, elv=0)],
    [T(0x284, col=1, elv=0), T(0x287, col=1, elv=0), T(0x28F, col=1, elv=0), T(0x286, col=1, elv=0)],
]
# Mart exterior (4 wide × 3 tall)
MART = [
    [T(0x230, col=1, elv=0), T(0x231, col=1, elv=0), T(0x232, col=1, elv=0), T(0x233, col=1, elv=0)],
    [T(0x238, col=1, elv=0), T(0x239, col=1, elv=0), T(0x23A, col=1, elv=0), T(0x23B, col=1, elv=0)],
    [T(0x260, col=1, elv=0), T(0x241, col=1, elv=0), T(0x242, col=1, elv=0), T(0x243, col=1, elv=0)],
]
# House exterior (4 wide × 4 tall)
HOUSE = [
    [T(0x248), T(0x249), T(0x282), T(0x283)],
    [T(0x250, col=1, elv=0), T(0x251, col=1, elv=0), T(0x252, col=1, elv=0), T(0x253, col=1, elv=0)],
    [T(0x258, col=1, elv=0), T(0x259, col=1, elv=0), T(0x25A, col=1, elv=0), T(0x25B, col=1, elv=0)],
    [T(0x260, col=1, elv=0), T(0x261, col=1, elv=0), T(0x262, col=1, elv=0), T(0x263, col=1, elv=0)],
]


class Map:
    def __init__(self, w, h, fill=GRASS):
        self.w, self.h = w, h
        self.g = [[fill]*w for _ in range(h)]

    def s(self, x, y, t):
        if 0 <= x < self.w and 0 <= y < self.h:
            self.g[y][x] = t

    def r(self, x, y):
        if 0 <= x < self.w and 0 <= y < self.h:
            return self.g[y][x]
        return 0

    def rect(self, x1, y1, x2, y2, t):
        for y in range(max(0,y1), min(self.h,y2+1)):
            for x in range(max(0,x1), min(self.w,x2+1)):
                self.g[y][x] = t

    def tree_border(self, thickness=2):
        """Fill border with proper 2x2 tree pattern."""
        for y in range(0, self.h, 2):
            for x in range(0, self.w, 2):
                in_border = (x < thickness*2 or x >= self.w - thickness*2 or
                            y < thickness*2 or y >= self.h - thickness*2)
                if in_border:
                    self.s(x, y, TREE_TL); self.s(x+1, y, TREE_TR)
                    self.s(x, y+1, TREE_BL); self.s(x+1, y+1, TREE_BR)

    def tree_block(self, x, y):
        """Place a single 2x2 tree."""
        self.s(x,y,TREE_TL); self.s(x+1,y,TREE_TR)
        self.s(x,y+1,TREE_BL); self.s(x+1,y+1,TREE_BR)

    def place_building(self, x, y, pattern):
        """Place a building from a pattern array."""
        for dy, row in enumerate(pattern):
            for dx, t in enumerate(row):
                self.s(x+dx, y+dy, t)

    def path_rect(self, x1, y1, x2, y2):
        """Draw a path rectangle with proper edges."""
        # Corners
        self.s(x1, y1, PATH_TL); self.s(x2, y1, PATH_TR)
        self.s(x1, y2, PATH_BL); self.s(x2, y2, PATH_BR)
        # Edges
        for x in range(x1+1, x2):
            self.s(x, y1, PATH_T); self.s(x, y2, PATH_B)
        for y in range(y1+1, y2):
            self.s(x1, y, PATH_L); self.s(x2, y, PATH_R)
        # Fill center
        for y in range(y1+1, y2):
            for x in range(x1+1, x2):
                self.s(x, y, PATH_C)

    def path_v(self, x, y1, y2, w=3):
        """Vertical path with proper edges."""
        self.path_rect(x-w//2, y1, x+w//2, y2)

    def path_h(self, y, x1, x2, w=3):
        """Horizontal path with proper edges."""
        self.path_rect(x1, y-w//2, x2, y+w//2)

    def grass_oval(self, cx, cy, rx, ry):
        """Oval patch of encounter grass."""
        for y in range(self.h):
            for x in range(self.w):
                dx, dy = (x-cx)/max(rx,1), (y-cy)/max(ry,1)
                if dx*dx + dy*dy <= 1.0:
                    cur = self.r(x, y)
                    if cur == GRASS or cur == GRASS2:
                        self.s(x, y, TALL_GRASS)

    def scatter_trees(self, x1, y1, x2, y2, density=0.08):
        """Scatter 2x2 trees, only on grass tiles."""
        for y in range(y1, y2-1, 2):
            for x in range(x1, x2-1, 2):
                if random.random() < density:
                    if all(self.r(x+dx,y+dy) in (TALL_GRASS, GRASS)
                           for dx in range(2) for dy in range(2)):
                        self.tree_block(x, y)

    def entrance_n(self, cx, w=5):
        """Clear north entrance through tree border."""
        for x in range(cx-w//2, cx+w//2+1):
            for y in range(4):
                self.s(x, y, GRASS)

    def entrance_s(self, cx, w=5):
        for x in range(cx-w//2, cx+w//2+1):
            for y in range(self.h-4, self.h):
                self.s(x, y, GRASS)

    def entrance_e(self, cy, w=3):
        for y in range(cy-w//2, cy+w//2+1):
            for x in range(self.w-4, self.w):
                self.s(x, y, GRASS)

    def entrance_w(self, cy, w=3):
        for y in range(cy-w//2, cy+w//2+1):
            for x in range(4):
                self.s(x, y, GRASS)

    def to_bytes(self):
        out = bytearray()
        for row in self.g:
            for t in row:
                out += struct.pack("<H", t)
        return bytes(out)


# ═══════════════════════════════════════════════════
# INDIVIDUAL MAP DESIGNS
# ═══════════════════════════════════════════════════

def make_dawnflake_town():
    """Starting town. PokéCenter, 2 houses, grass patches, welcoming feel."""
    w, h = 28, 22
    m = Map(w, h, GRASS)
    m.tree_border(2)
    # Main path running N-S through town
    m.path_v(w//2, 0, h-1, 3)
    # East-west cross path
    m.path_h(h//2, 4, w-5, 3)
    # PokéCenter (upper left area)
    m.place_building(5, 5, POKECENTER)
    m.path_rect(5, 9, 8, h//2)  # Path from PC to main road
    # House 1 (upper right)
    m.place_building(w-9, 5, HOUSE)
    m.path_rect(w-9, 9, w-6, h//2)
    # House 2 (lower right) — player's house
    m.place_building(w-9, h-9, HOUSE)
    m.path_rect(w-9, h//2, w-6, h-9)
    # Grass patches for encounters
    m.grass_oval(7, h-6, 3, 2)
    m.grass_oval(w//2+5, 7, 2, 2)
    m.grass_oval(5, h//2+4, 2, 2)
    # Entrances
    m.entrance_n(w//2); m.entrance_s(w//2)
    return m, w, h

def make_powderpath_village():
    """Small village with Vanillite vendor. Mart, house, grass."""
    w, h = 24, 18
    m = Map(w, h, GRASS)
    m.tree_border(2)
    # Main path N-S
    m.path_v(w//2, 0, h-1, 3)
    # Mart (left side)
    m.place_building(5, 4, MART)
    m.path_rect(5, 7, 8, h//2-1)
    # House (right side)
    m.place_building(w-9, 4, HOUSE)
    m.path_rect(w-9, 8, w-6, h//2-1)
    # Connect to main path
    m.path_h(h//2-1, 8, w-6, 3)
    # Grass patches
    m.grass_oval(6, h-5, 3, 2)
    m.grass_oval(w-7, h-5, 3, 2)
    m.entrance_n(w//2); m.entrance_s(w//2)
    return m, w, h

def make_route1():
    """Powderpath Trail. Simple winding path, grass patches, 3 trainers."""
    w, h = 24, 40
    m = Map(w, h, GRASS)
    m.tree_border(2)
    # Fill interior with mix of grass and tall grass
    m.rect(4, 4, w-5, h-5, TALL_GRASS)
    # Winding main path
    cx = w // 2
    for y in range(h):
        off = int(3 * math.sin(y * 2 * math.pi / 12))
        px = cx + off
        for dx in range(-1, 2):
            m.s(px+dx, y, PATH_C)
        # Path edges
        m.s(px-2, y, PATH_L); m.s(px+2, y, PATH_R)
    # Trainer clearings (wider spots on path)
    for ty in [10, 20, 30]:
        cx_t = w//2 + int(3 * math.sin(ty * 2 * math.pi / 12))
        m.rect(cx_t-3, ty-1, cx_t+3, ty+1, GRASS)
        m.path_rect(cx_t-2, ty-1, cx_t+2, ty+1)
    # Scatter some trees in grass areas
    m.scatter_trees(4, 4, w//2-3, h-5, 0.06)
    m.scatter_trees(w//2+3, 4, w-5, h-5, 0.06)
    m.entrance_n(w//2); m.entrance_s(w//2)
    return m, w, h

def make_route2():
    """Icespire Pass. Rockier, narrow mountain pass."""
    w, h = 24, 35
    m = Map(w, h, CLIFF_DK)
    # Narrower passage carved through rock
    m.rect(4, 0, w-5, h-1, TALL_GRASS)
    # Rocky outcrops narrowing the path
    m.rect(4, 8, 8, 11, CLIFF_MD)
    m.rect(w-9, 16, w-5, 19, CLIFF_MD)
    m.rect(5, 24, 9, 27, CLIFF_MD)
    # Winding path through the pass
    cx = w // 2
    for y in range(h):
        off = int(2 * math.sin(y * 2 * math.pi / 10))
        px = cx + off
        for dx in range(-1, 2):
            m.s(px+dx, y, PATH_C)
        m.s(px-2, y, PATH_L); m.s(px+2, y, PATH_R)
    # Trainer clearings
    for ty in [6, 14, 22, 29]:
        m.rect(cx-3, ty-1, cx+3, ty+1, GRASS)
    m.entrance_n(w//2); m.entrance_s(w//2)
    return m, w, h

def make_icespire_town():
    """First gym town. PokéCenter, Gym, houses."""
    w, h = 28, 22
    m = Map(w, h, GRASS)
    m.tree_border(2)
    m.path_v(w//2, 0, h-1, 3)
    m.path_h(h//2, 4, w-5, 3)
    # PokéCenter (top-left)
    m.place_building(5, 4, POKECENTER)
    m.path_rect(5, 8, 8, h//2)
    # Gym placeholder (top-right, using Mart pattern as stand-in)
    m.place_building(w-9, 4, MART)
    m.path_rect(w-9, 7, w-6, h//2)
    # House (bottom-left)
    m.place_building(5, h-8, HOUSE)
    m.path_rect(5, h//2, 8, h-8)
    # Grass encounters
    m.grass_oval(w-7, h-6, 3, 2)
    m.grass_oval(w//2+4, 7, 2, 2)
    m.entrance_n(w//2); m.entrance_s(w//2)
    return m, w, h

def make_route3():
    """Pinehurst Woods. Dense forest, winding path, 5 trainers."""
    w, h = 30, 44
    m = Map(w, h, TREE_TL)
    # Fill with tree pattern
    for y in range(0, h, 2):
        for x in range(0, w, 2):
            m.tree_block(x, y)
    # Carve forest interior
    m.rect(4, 2, w-5, h-3, TALL_GRASS)
    # Dense winding path
    cx = w // 2
    for y in range(h):
        off = int(4 * math.sin(y * 2 * math.pi / 10))
        px = cx + off
        for dx in range(-1, 2):
            m.s(px+dx, y, PATH_C)
    # Trainer clearings
    for i, ty in enumerate([8, 16, 24, 32, 39]):
        off = int(3 * math.sin(ty * 0.5))
        m.rect(cx+off-3, ty-1, cx+off+3, ty+1, GRASS)
    # Scatter interior trees
    m.scatter_trees(4, 2, w-5, h-3, 0.12)
    # Side exit west to R4
    m.entrance_w(h//3, 3)
    m.path_h(h//3, 0, cx-2, 3)
    m.entrance_n(w//2); m.entrance_s(w//2)
    return m, w, h

def make_route4():
    """Timber Creek. Optional, no trainers, creek feature."""
    w, h = 24, 24
    m = Map(w, h, GRASS)
    m.tree_border(2)
    m.rect(4, 4, w-5, h-5, TALL_GRASS)
    # Creek running through
    for y in range(2, h-2):
        wx = w//2 + 3 + int(2 * math.sin(y * 0.5))
        m.s(wx, y, WATER); m.s(wx+1, y, WATER)
    # Path alongside creek
    for y in range(h):
        m.s(w//2, y, PATH_C); m.s(w//2+1, y, PATH_C); m.s(w//2-1, y, PATH_C)
    m.scatter_trees(4, 4, w//2-2, h-5, 0.1)
    # East entrance only (connects back to R3)
    m.entrance_e(h//2, 3)
    return m, w, h

def make_route5():
    """Ironfrost Cave. Cave with corridors and rooms."""
    w, h = 26, 34
    m = Map(w, h, CAVE_WL)
    # Main cavern
    m.rect(4, 2, w-5, h-3, CAVE_FL)
    # Rock pillars
    for py in range(6, h-6, 5):
        if py % 10 < 5:
            m.rect(4, py, 8, py+2, CAVE_WL2)
        else:
            m.rect(w-9, py, w-5, py+2, CAVE_WL2)
    # Central path
    cx = w // 2
    for y in range(h):
        for dx in range(-1, 2):
            m.s(cx+dx, y, CAVE_FL2)
    # Side rooms
    m.rect(4, h//4, 8, h//4+3, CAVE_FL2)
    m.rect(w-9, h//2, w-5, h//2+3, CAVE_FL2)
    m.rect(4, 3*h//4, 8, 3*h//4+3, CAVE_FL2)
    # Trainer clearings
    for ty in [5, 11, 17, 23, 28, 31]:
        m.rect(cx-2, ty, cx+2, ty+1, CAVE_FL)
    m.entrance_n(w//2); m.entrance_s(w//2)
    return m, w, h

def make_town_standard(w, h, has_pokecenter=True, has_mart=False, n_houses=1):
    """Standard town template."""
    m = Map(w, h, GRASS)
    m.tree_border(2)
    m.path_v(w//2, 0, h-1, 3)
    m.path_h(h//2, 4, w-5, 3)
    bx = 5
    if has_pokecenter:
        m.place_building(bx, 4, POKECENTER)
        m.path_rect(bx, 8, bx+3, h//2)
    if has_mart:
        m.place_building(w-9, 4, MART)
        m.path_rect(w-9, 7, w-6, h//2)
    for i in range(n_houses):
        hx = 5 + i * 8 if i < 2 else w-9
        hy = h - 8
        m.place_building(hx, hy, HOUSE)
        m.path_rect(hx, h//2, hx+3, hy)
    m.grass_oval(w-7, h-5, 2, 2)
    m.grass_oval(5, h//2+3, 2, 2)
    m.entrance_n(w//2); m.entrance_s(w//2)
    return m, w, h

def make_route6():
    """Glacier Lake. Ring path around central lake."""
    w, h = 30, 38
    m = Map(w, h, CLIFF_MD)
    m.rect(4, 2, w-5, h-3, TALL_GRASS)
    # Central lake
    cy, cx = h//2, w//2
    for y in range(h):
        for x in range(w):
            if (x-cx)**2 + (y-cy)**2 <= 36:
                m.s(x, y, WATER)
    # Ring path around lake
    for a in range(360):
        r = math.radians(a)
        for rad in range(7, 9):
            px = int(cx + rad * math.cos(r))
            py = int(cy + rad * math.sin(r))
            m.s(px, py, PATH_C)
    # N-S path on west side connecting to ring
    m.path_v(cx-8, 0, h-1, 3)
    m.path_h(cy, cx-8, cx-6, 3)
    # Trainer clearings around the lake
    for a in range(0, 360, 45):
        r = math.radians(a)
        tx = int(cx + 9 * math.cos(r))
        ty = int(cy + 9 * math.sin(r))
        m.rect(tx-1, ty-1, tx+1, ty, GRASS)
    m.scatter_trees(4, 2, cx-9, h-3, 0.08)
    m.scatter_trees(cx+9, 2, w-5, h-3, 0.08)
    m.entrance_n(cx-8); m.entrance_s(cx-8)
    return m, w, h

def make_route_outdoor(w, h, n_trainers, amp=3, period=10):
    """Generic outdoor route with winding path."""
    m = Map(w, h, CLIFF_MD)
    m.rect(4, 2, w-5, h-3, TALL_GRASS)
    cx = w // 2
    for y in range(h):
        off = int(amp * math.sin(y * 2 * math.pi / period))
        px = cx + off
        for dx in range(-1, 2):
            m.s(px+dx, y, PATH_C)
        m.s(px-2, y, PATH_L); m.s(px+2, y, PATH_R)
    sp = max(1, (h-8) // max(n_trainers, 1))
    for i in range(n_trainers):
        ty = 4 + i * sp
        off = int(amp * math.sin(ty * 2 * math.pi / period))
        m.rect(cx+off-3, ty-1, cx+off+3, ty+1, GRASS)
    m.scatter_trees(4, 2, cx-4, h-3, 0.06)
    m.scatter_trees(cx+4, 2, w-5, h-3, 0.06)
    m.entrance_n(w//2); m.entrance_s(w//2)
    return m, w, h

def make_coastal(w, h, n_trainers):
    """Coastal route with shore path."""
    m = Map(w, h, CLIFF_MD)
    split = w * 3 // 5
    m.rect(4, 2, split-1, h-3, TALL_GRASS)
    m.rect(split, 2, w-3, h-3, WATER)
    # Irregular shoreline
    for y in range(2, h-2):
        off = int(1.5 * math.sin(y * 0.4))
        m.s(split+off, y, GRASS)
        m.s(split+off-1, y, GRASS)
    # Shore path
    for y in range(h):
        m.s(split-3, y, PATH_C); m.s(split-2, y, PATH_C); m.s(split-1, y, PATH_C)
    sp = max(1, (h-8) // max(n_trainers, 1))
    for i in range(n_trainers):
        ty = 4 + i * sp
        m.rect(split-5, ty-1, split-1, ty+1, GRASS)
    m.scatter_trees(4, 2, split-6, h-3, 0.06)
    m.entrance_n(split-2); m.entrance_s(split-2)
    return m, w, h

def make_cave(w, h, n_trainers):
    """Cave interior."""
    m = Map(w, h, CAVE_WL)
    m.rect(3, 2, w-4, h-3, CAVE_FL)
    for i in range(3):
        py = (h * (i+1)) // 4
        if i % 2 == 0:
            m.rect(3, py-1, 7, py+1, CAVE_WL2)
        else:
            m.rect(w-8, py-1, w-4, py+1, CAVE_WL2)
    cx = w // 2
    for y in range(h):
        for dx in range(-1, 2): m.s(cx+dx, y, CAVE_FL2)
    m.rect(3, h//4, 7, h//4+3, CAVE_FL2)
    m.rect(w-8, 3*h//4-1, w-4, 3*h//4+2, CAVE_FL2)
    sp = max(1, (h-8) // max(n_trainers, 1)) if n_trainers > 0 else h
    for i in range(n_trainers):
        ty = 4 + i * sp
        m.rect(cx-2, ty, cx+2, ty+1, CAVE_FL)
    m.entrance_n(w//2); m.entrance_s(w//2)
    return m, w, h

def make_r13():
    """Verdant Jungle. Dense, humid, 9 trainers, stream."""
    w, h = 32, 48
    m = Map(w, h, TREE_TL)
    for y in range(0, h, 2):
        for x in range(0, w, 2):
            m.tree_block(x, y)
    m.rect(4, 2, w-5, h-3, TALL_GRASS)
    cx = w // 2
    for y in range(h):
        off = int(5 * math.sin(y * 2 * math.pi / 11))
        px = cx + off
        for dx in range(-1, 2): m.s(px+dx, y, PATH_C)
    # Jungle stream
    for y in range(h//4, 3*h//4):
        wx = cx + 7 + int(2 * math.sin(y * 0.3))
        m.s(wx, y, WATER); m.s(wx+1, y, WATER)
    for i in range(9):
        ty = 4 + i * 4 + random.randint(-1, 1)
        off = int(4 * math.sin(ty * 0.6))
        m.rect(cx+off-3, ty-1, cx+off+3, ty+1, GRASS)
    m.scatter_trees(4, 2, w-5, h-3, 0.15)
    m.entrance_n(w//2); m.entrance_s(w//2)
    return m, w, h


# ═══════════════════════════════════════════════════
# BUILD ALL MAPS
# ═══════════════════════════════════════════════════

ALL_MAPS = {
    "DawnflakeTown":      (make_dawnflake_town, "gTileset_Petalburg"),
    "PowderpathVillage":  (make_powderpath_village, "gTileset_Petalburg"),
    "SnowRoute1":         (make_route1, "gTileset_Petalburg"),
    "SnowRoute2":         (make_route2, "gTileset_Petalburg"),
    "IcespireTown":       (make_icespire_town, "gTileset_Petalburg"),
    "SnowRoute3":         (make_route3, "gTileset_Petalburg"),
    "SnowRoute4":         (make_route4, "gTileset_Petalburg"),
    "PinegroveCity":      (lambda: make_town_standard(28, 20, True, True, 2), "gTileset_Petalburg"),
    "SnowRoute5":         (make_route5, "gTileset_Cave"),
    "IronfrostCity":      (lambda: make_town_standard(30, 22, True, True, 2), "gTileset_Petalburg"),
    "SnowRoute6":         (make_route6, "gTileset_Petalburg"),
    "SnowRoute7":         (lambda: make_route_outdoor(28, 38, 5, 4, 12), "gTileset_Petalburg"),
    "FrostbreakLodge":    (lambda: make_town_standard(20, 16, False, False, 1), "gTileset_Petalburg"),
    "SnowRoute8":         (lambda: make_route_outdoor(28, 38, 6, 3, 9), "gTileset_Petalburg"),
    "DreamursTown":       (lambda: make_town_standard(26, 20, True, False, 2), "gTileset_Petalburg"),
    "SnowRoute9":         (lambda: make_coastal(30, 34, 8), "gTileset_Petalburg"),
    "IceharborCity":      (lambda: make_town_standard(30, 22, True, True, 2), "gTileset_Petalburg"),
    "DriftrockIsle":      (lambda: make_coastal(26, 26, 5), "gTileset_Petalburg"),
    "SnowRoute10":        (lambda: make_cave(26, 34, 8), "gTileset_Cave"),
    "SnowRoute11":        (lambda: make_route_outdoor(30, 38, 6, 5, 11), "gTileset_Petalburg"),
    "DragonforgeCity":    (lambda: make_town_standard(32, 24, True, True, 3), "gTileset_Petalburg"),
    "SnowRoute12":        (lambda: make_route_outdoor(26, 38, 7, 3, 8), "gTileset_Petalburg"),
    "SolaceTown":         (lambda: make_town_standard(24, 18, True, False, 1), "gTileset_Petalburg"),
    "SnowRoute13":        (make_r13, "gTileset_Petalburg"),
    "SnowRoute14":        (lambda: make_route_outdoor(28, 38, 9, 3, 7), "gTileset_Petalburg"),
    "SnowRoute15":        (lambda: make_coastal(30, 38, 9), "gTileset_Petalburg"),
    "PyrespireCity":      (lambda: make_town_standard(30, 22, True, True, 2), "gTileset_Petalburg"),
    "SnowVictoryRoad":    (lambda: make_cave(30, 42, 8), "gTileset_Cave"),
    "PokemonLeague":      (lambda: make_town_standard(26, 20, True, False, 1), "gTileset_Petalburg"),
    "IronfrostCaveB1":    (lambda: make_cave(26, 26, 0), "gTileset_Cave"),
    "IronfrostCaveB2B3":  (lambda: make_cave(30, 32, 0), "gTileset_Cave"),
}

CAVES = {"SnowRoute5","SnowRoute10","SnowVictoryRoad","IronfrostCaveB1","IronfrostCaveB2B3"}

def main():
    with open(REPO / "data/layouts/layouts.json") as f:
        ld = json.load(f)

    for name, (gen, tileset) in ALL_MAPS.items():
        m, w, h = gen()
        lid = "LAYOUT_" + ''.join(
            f'_{c}' if c.isupper() and i > 0 and name[i-1].islower() else c
            for i, c in enumerate(name)
        ).upper().replace('__','_')

        ldir = REPO / "data/layouts" / name
        ldir.mkdir(parents=True, exist_ok=True)
        (ldir / "map.bin").write_bytes(m.to_bytes())
        bdr = [CAVE_WL]*4 if name in CAVES else [TREE_TL, TREE_TR, TREE_BL, TREE_BR]
        with open(ldir / "border.bin", "wb") as f:
            for t in bdr: f.write(struct.pack("<H", t))

        ent = {"id": lid, "name": f"{name}_Layout", "width": w, "height": h,
               "primary_tileset": "gTileset_General", "secondary_tileset": tileset,
               "border_filepath": f"data/layouts/{name}/border.bin",
               "blockdata_filepath": f"data/layouts/{name}/map.bin"}
        ex = [l for l in ld["layouts"] if l["id"] == lid]
        if ex: ld["layouts"][ld["layouts"].index(ex[0])] = ent
        else: ld["layouts"].append(ent)

        mjp = REPO / "data/maps" / name / "map.json"
        with open(mjp) as f: mj = json.load(f)
        mj["layout"] = lid
        with open(mjp, "w") as f: json.dump(mj, f, indent=2); f.write("\n")
        print(f"  {name:25s} {w:2d}x{h:2d}")

    # Remove any stale duplicate entries
    seen = {}
    for i, l in enumerate(ld["layouts"]):
        seen[l["id"]] = i
    ld["layouts"] = [ld["layouts"][i] for i in sorted(seen.values())]

    with open(REPO / "data/layouts/layouts.json", "w") as f:
        json.dump(ld, f, indent=2); f.write("\n")
    print(f"\n{len(ALL_MAPS)} layouts generated")

if __name__ == "__main__":
    main()
