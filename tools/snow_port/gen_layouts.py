#!/usr/bin/env python3
"""Generate detailed map layouts for all Snow locations."""
import json, struct, random, math
from pathlib import Path

random.seed(2026)
REPO = Path(__file__).resolve().parent.parent.parent

# ═══ Metatile encoding: metatile_id | (collision << 10) | (elevation << 12) ═══
def tile(meta, col=0, elv=3):
    return meta | (col << 10) | (elv << 12)

# Walkable ground tiles (elevation 3, passable)
GRASS       = tile(0x001)  # 0x3001 — short grass, no encounters
TALL_GRASS  = tile(0x00D)  # 0x300D — encounter grass
LONG_GRASS  = tile(0x015)  # 0x3015 — long encounter grass

# Water (elevation 1, passable)
WATER       = tile(0x170, elv=1)  # 0x1170 — surfable water

# Impassable terrain (collision=1, elevation 0)
CLIFF_DARK  = tile(0x075, col=1, elv=0)  # dark rock cliff
CLIFF_MED   = tile(0x073, col=1, elv=0)  # medium rock
CLIFF_LIGHT = tile(0x071, col=1, elv=0)  # light rock
TREE_A      = tile(0x0C7, col=1, elv=0)  # tree trunk
TREE_B      = tile(0x0C6, col=1, elv=0)  # tree canopy
ROCK_WALL   = tile(0x079, col=1, elv=0)  # rock wall

# Cave tiles (secondary tileset)
CAVE_FLOOR  = tile(0x201)               # 0x3201 walkable cave
CAVE_FLOOR2 = tile(0x211)               # 0x3211 cave floor variant
CAVE_WALL   = tile(0x211, col=1, elv=0) # 0x0611 cave wall
CAVE_WALL2  = tile(0x219, col=1, elv=0) # 0x0619 cave wall variant
CAVE_WALL3  = tile(0x209, col=1, elv=0) # 0x0609 yet another wall

# Border tiles
BORDER_GRASS = [GRASS, GRASS, GRASS, GRASS]
BORDER_CAVE  = [CAVE_WALL, CAVE_WALL, CAVE_WALL, CAVE_WALL]


class MapGrid:
    def __init__(self, w, h, fill):
        self.w, self.h = w, h
        self.grid = [[fill] * w for _ in range(h)]

    def set(self, x, y, t):
        if 0 <= x < self.w and 0 <= y < self.h:
            self.grid[y][x] = t

    def get(self, x, y):
        if 0 <= x < self.w and 0 <= y < self.h:
            return self.grid[y][x]
        return None

    def fill_rect(self, x1, y1, x2, y2, t):
        for y in range(max(0,y1), min(self.h,y2+1)):
            for x in range(max(0,x1), min(self.w,x2+1)):
                self.grid[y][x] = t

    def fill_circle(self, cx, cy, r, t):
        for y in range(self.h):
            for x in range(self.w):
                if (x-cx)**2 + (y-cy)**2 <= r*r:
                    self.grid[y][x] = t

    def path_v(self, x, y1, y2, width=3):
        """Vertical path."""
        for y in range(min(y1,y2), max(y1,y2)+1):
            for dx in range(-(width//2), width//2+1):
                self.set(x+dx, y, GRASS)

    def path_h(self, y, x1, x2, width=3):
        """Horizontal path."""
        for x in range(min(x1,x2), max(x1,x2)+1):
            for dy in range(-(width//2), width//2+1):
                self.set(x, y+dy, GRASS)

    def winding_path_v(self, start_x, y1, y2, width=3, amplitude=3, period=8):
        """Vertical winding path."""
        for y in range(min(y1,y2), max(y1,y2)+1):
            offset = int(amplitude * math.sin(y * 2 * math.pi / period))
            x = start_x + offset
            for dx in range(-(width//2), width//2+1):
                self.set(x+dx, y, GRASS)

    def grass_patch(self, cx, cy, rx, ry):
        """Oval patch of tall grass."""
        for y in range(self.h):
            for x in range(self.w):
                if ((x-cx)/max(rx,1))**2 + ((y-cy)/max(ry,1))**2 <= 1:
                    if self.get(x,y) not in (WATER, CAVE_WALL, CAVE_WALL2, CAVE_WALL3):
                        self.set(x, y, TALL_GRASS)

    def scatter_trees(self, x1, y1, x2, y2, density=0.15):
        """Scatter trees in an area, preserving non-wall tiles."""
        for y in range(max(0,y1), min(self.h,y2+1)):
            for x in range(max(0,x1), min(self.w,x2+1)):
                if self.get(x,y) == TALL_GRASS and random.random() < density:
                    self.set(x, y, TREE_A)

    def entrance_south(self, cx, width=5):
        for x in range(cx-width//2, cx+width//2+1):
            self.set(x, self.h-1, GRASS)
            self.set(x, self.h-2, GRASS)

    def entrance_north(self, cx, width=5):
        for x in range(cx-width//2, cx+width//2+1):
            self.set(x, 0, GRASS)
            self.set(x, 1, GRASS)

    def to_bytes(self):
        out = bytearray()
        for row in self.grid:
            for t in row:
                out += struct.pack("<H", t)
        return bytes(out)


# ═══════════════════════════════════════════════════════════
# ROUTE DESIGNS — Each route crafted individually
# ═══════════════════════════════════════════════════════════

def design_dawnflake_town(w=24, h=18):
    """Starting town. Open, welcoming. Small grass areas."""
    m = MapGrid(w, h, GRASS)
    # Tree border
    m.fill_rect(0, 0, w-1, 0, TREE_B)
    m.fill_rect(0, h-1, w-1, h-1, TREE_B)
    for y in range(h):
        m.set(0, y, TREE_A); m.set(w-1, y, TREE_A)
    # Small grass patches (encounter areas)
    m.grass_patch(5, 5, 3, 2)
    m.grass_patch(w-6, 5, 3, 2)
    m.grass_patch(w//2, h-5, 4, 2)
    # Open center area (town square)
    m.fill_rect(w//2-3, h//2-2, w//2+3, h//2+2, GRASS)
    # Entrances (north to PowderpathVillage)
    m.entrance_north(w//2)
    m.entrance_south(w//2)
    return m, w, h

def design_powderpath_village(w=22, h=16):
    """Small village with vendor. Cozy feel."""
    m = MapGrid(w, h, GRASS)
    m.fill_rect(0, 0, w-1, 0, TREE_B)
    m.fill_rect(0, h-1, w-1, h-1, TREE_B)
    for y in range(h):
        m.set(0, y, TREE_A); m.set(w-1, y, TREE_A)
    # Grass patches in corners
    m.grass_patch(4, 4, 3, 2)
    m.grass_patch(w-5, h-5, 3, 2)
    # Central path
    m.path_v(w//2, 0, h-1)
    m.entrance_north(w//2)
    m.entrance_south(w//2)
    return m, w, h

def design_route1(w=22, h=35):
    """Powderpath Trail. First route — simple winding path, grass patches, 3 trainers."""
    m = MapGrid(w, h, CLIFF_MED)
    # Carve interior
    m.fill_rect(2, 1, w-3, h-2, TALL_GRASS)
    # Winding main path
    m.winding_path_v(w//2, 0, h-1, width=3, amplitude=3, period=10)
    # Additional grass-free clearings for trainer battles
    m.fill_rect(w//2-2, 8, w//2+2, 10, GRASS)   # trainer 1 area
    m.fill_rect(w//2-2, 18, w//2+2, 20, GRASS)  # trainer 2 area
    m.fill_rect(w//2-2, 28, w//2+2, 30, GRASS)  # trainer 3 area
    # Tree clusters for visual interest
    m.scatter_trees(2, 1, 6, h-2, 0.2)
    m.scatter_trees(w-7, 1, w-3, h-2, 0.2)
    # Entrances
    m.entrance_north(w//2)
    m.entrance_south(w//2)
    return m, w, h

def design_route2(w=22, h=30):
    """Icespire Pass. Mountain pass — rockier, narrower path sections."""
    m = MapGrid(w, h, CLIFF_DARK)
    m.fill_rect(2, 1, w-3, h-2, TALL_GRASS)
    # Narrower winding path
    m.winding_path_v(w//2, 0, h-1, width=3, amplitude=2, period=7)
    # Rocky outcrops creating bottlenecks
    m.fill_rect(3, 7, 7, 9, CLIFF_MED)
    m.fill_rect(w-8, 14, w-4, 16, CLIFF_MED)
    m.fill_rect(4, 21, 8, 23, CLIFF_MED)
    # Trainer clearing spots
    m.fill_rect(w//2-2, 6, w//2+2, 7, GRASS)
    m.fill_rect(w//2-2, 13, w//2+2, 14, GRASS)
    m.fill_rect(w//2-2, 20, w//2+2, 21, GRASS)
    m.fill_rect(w//2-2, 26, w//2+2, 27, GRASS)
    m.entrance_north(w//2)
    m.entrance_south(w//2)
    return m, w, h

def design_icespire_town(w=24, h=18):
    """First gym town. Larger than starting towns."""
    m = MapGrid(w, h, GRASS)
    m.fill_rect(0, 0, w-1, 0, CLIFF_DARK)
    m.fill_rect(0, h-1, w-1, h-1, CLIFF_DARK)
    for y in range(h):
        m.set(0, y, CLIFF_DARK); m.set(w-1, y, CLIFF_DARK)
    # Town grass patches
    m.grass_patch(5, 5, 3, 3)
    m.grass_patch(w-6, 5, 3, 3)
    m.grass_patch(5, h-6, 3, 2)
    m.grass_patch(w-6, h-6, 3, 2)
    # Central plaza
    m.fill_rect(w//2-4, h//2-3, w//2+4, h//2+3, GRASS)
    m.entrance_north(w//2)
    m.entrance_south(w//2)
    return m, w, h

def design_route3(w=28, h=40):
    """Pinehurst Woods. Dense forest, winding path, scattered trees."""
    m = MapGrid(w, h, TREE_A)
    # Forest interior — mix of tall grass and clearings
    m.fill_rect(2, 1, w-3, h-2, TALL_GRASS)
    # Winding forest path
    m.winding_path_v(w//2, 0, h-1, width=3, amplitude=4, period=9)
    # Dense tree clusters throughout
    m.scatter_trees(2, 1, w-3, h-2, 0.25)
    # Clearings for trainers
    for i, ty in enumerate([7, 14, 21, 28, 35]):
        cx = w//2 + ((-3, 2, -2, 3, 0)[i])
        m.fill_rect(cx-2, ty-1, cx+2, ty+1, GRASS)
    # Side path to R4 (left exit)
    m.path_h(h//3, 0, w//2-3)
    for y in range(h//3-1, h//3+2):
        m.set(0, y, GRASS)
    m.entrance_north(w//2)
    m.entrance_south(w//2)
    return m, w, h

def design_route4(w=24, h=22):
    """Timber Creek. Optional route, no trainers, just wild encounters."""
    m = MapGrid(w, h, TREE_A)
    m.fill_rect(2, 1, w-3, h-2, TALL_GRASS)
    # Meandering creek path
    m.winding_path_v(w//2, 0, h-1, width=2, amplitude=3, period=6)
    # Small water feature (creek)
    for y in range(4, h-4):
        wx = w//2 + 4 + int(2 * math.sin(y * 0.5))
        m.set(wx, y, WATER); m.set(wx+1, y, WATER)
    m.scatter_trees(2, 1, w-3, h-2, 0.18)
    # Right entrance (connects back to R3)
    for y in range(h//2-1, h//2+2):
        m.set(w-1, y, GRASS); m.set(w-2, y, GRASS)
    return m, w, h

def design_town_generic(w=24, h=18, wall=CLIFF_DARK):
    """Generic town template."""
    m = MapGrid(w, h, GRASS)
    m.fill_rect(0, 0, w-1, 0, wall)
    m.fill_rect(0, h-1, w-1, h-1, wall)
    for y in range(h):
        m.set(0, y, wall); m.set(w-1, y, wall)
    m.grass_patch(5, 5, 3, 2)
    m.grass_patch(w-6, h-6, 3, 2)
    m.entrance_north(w//2)
    m.entrance_south(w//2)
    return m, w, h

def design_route5(w=24, h=30):
    """Ironfrost Cave. First cave — corridors, openings, rock walls."""
    m = MapGrid(w, h, CAVE_WALL)
    # Main corridor
    m.fill_rect(3, 1, w-4, h-2, CAVE_FLOOR)
    # Rocky obstacles creating rooms
    m.fill_rect(8, 6, 12, 8, CAVE_WALL2)
    m.fill_rect(14, 13, 18, 15, CAVE_WALL2)
    m.fill_rect(6, 20, 10, 22, CAVE_WALL2)
    m.fill_rect(15, 24, 19, 26, CAVE_WALL2)
    # Central path through rooms
    m.path_v(w//2, 0, h-1, width=3)
    # Side alcoves with cave floor
    m.fill_rect(3, 10, 7, 12, CAVE_FLOOR2)
    m.fill_rect(w-8, 17, w-4, 19, CAVE_FLOOR2)
    # Trainer clearings
    for ty in [5, 11, 17, 23, 27]:
        m.fill_rect(w//2-2, ty, w//2+2, ty+1, CAVE_FLOOR)
    m.entrance_north(w//2)
    m.entrance_south(w//2)
    return m, w, h

def design_route6(w=28, h=35):
    """Glacier Lake. Central lake with ring path."""
    m = MapGrid(w, h, CLIFF_MED)
    m.fill_rect(2, 1, w-3, h-2, TALL_GRASS)
    # Central lake
    m.fill_circle(w//2, h//2, 6, WATER)
    # Ring path around lake
    for angle in range(360):
        rad = math.radians(angle)
        for r in range(7, 9):
            px = int(w//2 + r * math.cos(rad))
            py = int(h//2 + r * math.sin(rad))
            m.set(px, py, GRASS)
    # Main path connecting N-S through the ring
    m.path_v(w//2-7, 0, h-1, width=3)
    m.path_h(h//2, w//2-9, w//2-5)
    m.path_h(h//2, w//2+5, w//2+9)
    # Trainer areas around the lake
    for i, (tx, ty) in enumerate([(5, 8), (w-6, 12), (5, h-12), (w-6, h-8),
                                   (w//2, 5), (w//2, h-6), (5, h//2), (w-6, h//2)]):
        m.fill_rect(tx-1, ty-1, tx+1, ty, GRASS)
    m.scatter_trees(2, 1, 8, h-2, 0.15)
    m.scatter_trees(w-9, 1, w-3, h-2, 0.15)
    m.entrance_north(w//2-7)
    m.entrance_south(w//2-7)
    return m, w, h

def design_route_standard(w, h, n_trainers, amplitude=3, period=8):
    """Standard outdoor route with winding path."""
    m = MapGrid(w, h, CLIFF_MED)
    m.fill_rect(2, 1, w-3, h-2, TALL_GRASS)
    m.winding_path_v(w//2, 0, h-1, width=3, amplitude=amplitude, period=period)
    # Trainer clearings evenly spaced
    spacing = (h - 6) // max(n_trainers, 1)
    for i in range(n_trainers):
        ty = 3 + i * spacing
        cx = w//2 + int(amplitude * math.sin(ty * 2 * math.pi / period))
        m.fill_rect(cx-2, ty, cx+2, ty+1, GRASS)
    m.scatter_trees(2, 1, w//2-4, h-2, 0.12)
    m.scatter_trees(w//2+4, 1, w-3, h-2, 0.12)
    m.entrance_north(w//2)
    m.entrance_south(w//2)
    return m, w, h

def design_coastal(w, h, n_trainers):
    """Coastal route — land on left, water on right."""
    m = MapGrid(w, h, CLIFF_MED)
    split = w * 3 // 5
    m.fill_rect(2, 1, split-1, h-2, TALL_GRASS)
    m.fill_rect(split, 1, w-2, h-2, WATER)
    # Shoreline path
    m.path_v(split-2, 0, h-1, width=3)
    # Irregular shoreline
    for y in range(1, h-1):
        offset = int(2 * math.sin(y * 0.4))
        for dx in range(-1, 2):
            m.set(split+offset+dx, y, WATER if dx > 0 else GRASS)
    # Trainer areas
    spacing = (h - 6) // max(n_trainers, 1)
    for i in range(n_trainers):
        ty = 3 + i * spacing
        m.fill_rect(split-4, ty, split-1, ty+1, GRASS)
    m.scatter_trees(2, 1, split//2, h-2, 0.1)
    m.entrance_north(split-2)
    m.entrance_south(split-2)
    return m, w, h

def design_cave_route(w, h, n_trainers):
    """Cave interior with rooms and corridors."""
    m = MapGrid(w, h, CAVE_WALL)
    # Carve main corridor
    m.fill_rect(3, 1, w-4, h-2, CAVE_FLOOR)
    # Add wall pillars for visual interest
    for i in range(4):
        py = (h * (i+1)) // 5
        # Alternating left/right obstacles
        if i % 2 == 0:
            m.fill_rect(3, py-1, 7, py+1, CAVE_WALL2)
        else:
            m.fill_rect(w-8, py-1, w-4, py+1, CAVE_WALL2)
    # Central path
    m.path_v(w//2, 0, h-1, width=3)
    # Side rooms
    m.fill_rect(3, h//4, 7, h//4+3, CAVE_FLOOR2)
    m.fill_rect(w-8, h*3//4-1, w-4, h*3//4+2, CAVE_FLOOR2)
    # Trainer spots
    spacing = (h - 6) // max(n_trainers, 1)
    for i in range(n_trainers):
        ty = 3 + i * spacing
        m.fill_rect(w//2-2, ty, w//2+2, ty+1, CAVE_FLOOR)
    m.entrance_north(w//2)
    m.entrance_south(w//2)
    return m, w, h


# ═══════════════════════════════════════════════════════════
# MAP LIST WITH CUSTOM DESIGNS
# ═══════════════════════════════════════════════════════════

def build_all():
    MAPS = {
        "DawnflakeTown":     lambda: design_dawnflake_town(),
        "PowderpathVillage": lambda: design_powderpath_village(),
        "SnowRoute1":        lambda: design_route1(),
        "SnowRoute2":        lambda: design_route2(),
        "IcespireTown":      lambda: design_icespire_town(),
        "SnowRoute3":        lambda: design_route3(),
        "SnowRoute4":        lambda: design_route4(),
        "PinegroveCity":     lambda: design_town_generic(24, 18, TREE_A),
        "SnowRoute5":        lambda: design_route5(),
        "IronfrostCity":     lambda: design_town_generic(28, 18, CLIFF_DARK),
        "SnowRoute6":        lambda: design_route6(),
        "SnowRoute7":        lambda: design_route_standard(26, 35, 5, amplitude=4, period=10),
        "FrostbreakLodge":   lambda: design_town_generic(18, 14, TREE_A),
        "SnowRoute8":        lambda: design_route_standard(26, 35, 6, amplitude=3, period=8),
        "DreamursTown":      lambda: design_town_generic(24, 18, CLIFF_MED),
        "SnowRoute9":        lambda: design_coastal(28, 30, 8),
        "IceharborCity":     lambda: design_town_generic(28, 20, CLIFF_MED),
        "DriftrockIsle":     lambda: design_coastal(24, 24, 5),
        "SnowRoute10":       lambda: design_cave_route(24, 30, 8),
        "SnowRoute11":       lambda: design_route_standard(28, 35, 6, amplitude=5, period=12),
        "DragonforgeCity":   lambda: design_town_generic(30, 22, CLIFF_DARK),
        "SnowRoute12":       lambda: design_route_standard(24, 35, 7, amplitude=3, period=9),
        "SolaceTown":        lambda: design_town_generic(22, 16, CLIFF_MED),
        "SnowRoute13":       lambda: design_route3.__wrapped__(30, 42) if hasattr(design_route3, '__wrapped__') else (lambda: (MapGrid(30,42,TREE_A).fill_rect(2,1,27,40,TALL_GRASS) or design_forest_gen(30, 42, 9)))(),
        "SnowRoute14":       lambda: design_route_standard(28, 35, 9, amplitude=3, period=7),
        "SnowRoute15":       lambda: design_coastal(28, 35, 9),
        "PyrespireCity":     lambda: design_town_generic(28, 20, CLIFF_DARK),
        "SnowVictoryRoad":   lambda: design_cave_route(28, 38, 8),
        "PokemonLeague":     lambda: design_town_generic(24, 18, CLIFF_DARK),
        "IronfrostCaveB1":   lambda: design_cave_route(24, 24, 0),
        "IronfrostCaveB2B3": lambda: design_cave_route(28, 30, 0),
    }

    # Fix R13 — dense jungle
    def design_r13():
        w, h = 30, 42
        m = MapGrid(w, h, TREE_A)
        m.fill_rect(2, 1, w-3, h-2, TALL_GRASS)
        m.winding_path_v(w//2, 0, h-1, width=3, amplitude=5, period=9)
        m.scatter_trees(2, 1, w-3, h-2, 0.3)
        # Water feature (jungle stream)
        for y in range(h//3, 2*h//3):
            wx = w//2 + 6 + int(2 * math.sin(y * 0.3))
            m.set(wx, y, WATER); m.set(wx+1, y, WATER)
        # 9 trainer clearings
        for i in range(9):
            ty = 3 + i * 4
            cx = w//2 + int(4 * math.sin(ty * 0.7))
            m.fill_rect(cx-2, ty, cx+2, ty+1, GRASS)
        m.entrance_north(w//2)
        m.entrance_south(w//2)
        return m, w, h

    MAPS["SnowRoute13"] = design_r13

    TILESETS = {
        "DawnflakeTown": "gTileset_Petalburg", "PowderpathVillage": "gTileset_Petalburg",
        "SnowRoute1": "gTileset_EverGrande", "SnowRoute2": "gTileset_EverGrande",
        "IcespireTown": "gTileset_Rustboro", "SnowRoute3": "gTileset_Fortree",
        "SnowRoute4": "gTileset_Fortree", "PinegroveCity": "gTileset_Rustboro",
        "SnowRoute5": "gTileset_Cave", "IronfrostCity": "gTileset_Mauville",
        "SnowRoute6": "gTileset_EverGrande", "SnowRoute7": "gTileset_EverGrande",
        "FrostbreakLodge": "gTileset_Fallarbor", "SnowRoute8": "gTileset_EverGrande",
        "DreamursTown": "gTileset_Fallarbor", "SnowRoute9": "gTileset_EverGrande",
        "IceharborCity": "gTileset_Slateport", "DriftrockIsle": "gTileset_EverGrande",
        "SnowRoute10": "gTileset_Cave", "SnowRoute11": "gTileset_EverGrande",
        "DragonforgeCity": "gTileset_Mauville", "SnowRoute12": "gTileset_EverGrande",
        "SolaceTown": "gTileset_Fallarbor", "SnowRoute13": "gTileset_Fortree",
        "SnowRoute14": "gTileset_Lavaridge", "SnowRoute15": "gTileset_Lavaridge",
        "PyrespireCity": "gTileset_Sootopolis", "SnowVictoryRoad": "gTileset_Cave",
        "PokemonLeague": "gTileset_EverGrande", "IronfrostCaveB1": "gTileset_Cave",
        "IronfrostCaveB2B3": "gTileset_Cave",
    }

    IS_CAVE = {"SnowRoute5","SnowRoute10","SnowVictoryRoad","IronfrostCaveB1","IronfrostCaveB2B3"}

    with open(REPO / "data/layouts/layouts.json") as f:
        layouts_data = json.load(f)

    for map_dir, gen_fn in MAPS.items():
        m, w, h = gen_fn()
        lid = "LAYOUT_" + ''.join(f'_{c}' if c.isupper() and i > 0 and map_dir[i-1].islower()
                                   else c for i, c in enumerate(map_dir)).upper()
        # Clean up double underscores
        while '__' in lid:
            lid = lid.replace('__', '_')

        layout_dir = REPO / "data/layouts" / map_dir
        layout_dir.mkdir(parents=True, exist_ok=True)

        with open(layout_dir / "map.bin", "wb") as f:
            f.write(m.to_bytes())

        border = BORDER_CAVE if map_dir in IS_CAVE else BORDER_GRASS
        with open(layout_dir / "border.bin", "wb") as f:
            for t in border:
                f.write(struct.pack("<H", t))

        entry = {
            "id": lid, "name": f"{map_dir}_Layout",
            "width": w, "height": h,
            "primary_tileset": "gTileset_General",
            "secondary_tileset": TILESETS[map_dir],
            "border_filepath": f"data/layouts/{map_dir}/border.bin",
            "blockdata_filepath": f"data/layouts/{map_dir}/map.bin",
        }
        existing = [l for l in layouts_data["layouts"] if l["id"] == lid]
        if existing:
            layouts_data["layouts"][layouts_data["layouts"].index(existing[0])] = entry
        else:
            layouts_data["layouts"].append(entry)

        # Update map.json
        mjp = REPO / "data/maps" / map_dir / "map.json"
        with open(mjp) as f:
            mj = json.load(f)
        mj["layout"] = lid
        with open(mjp, "w") as f:
            json.dump(mj, f, indent=2); f.write("\n")

        print(f"  {map_dir:25s} {w:2d}x{h:2d}")

    with open(REPO / "data/layouts/layouts.json", "w") as f:
        json.dump(layouts_data, f, indent=2); f.write("\n")

    print(f"\n{len(MAPS)} layouts generated")


if __name__ == "__main__":
    build_all()
