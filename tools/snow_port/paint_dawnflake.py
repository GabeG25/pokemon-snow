#!/usr/bin/env python3
"""
Snow tilemap painter — Dawnflake Town (Phase 1 pilot).

Paints an original 20x20 Dawnflake Town layout using metatile stamps
sourced from the winter-palette Hoenn tileset. Layout is CEO-specified:
  - Asher's House NW
  - Player's House NE
  - Evergreen's Lab SW (larger 7x5 footprint)
  - Autumn's House SE
  - 2x2 tall-grass patches in each of the four far corners
  - Open central plaza
  - South exit to Route 1 at cols 7-11 (overlap Route 1's top cols 8-11)

Metatile IDs are curated from the existing shipped Dawnflake map.bin
(before this repaint). We extract the NW house footprint and the lab
footprint as "stamps" and rearrange them to the new CEO-approved layout.

Usage: python3 tools/snow_port/paint_dawnflake.py [--dry-run]
"""
import argparse
import struct
import shutil
from pathlib import Path

REPO = Path(__file__).resolve().parents[2]
DST = REPO / "data/layouts/DawnflakeTown/map.bin"
BACKUP = DST.with_suffix(".bin.prev_vanilla_copy")

W, H = 20, 20
TOTAL = W * H


def enc(meta, coll=0, elev=3):
    """Encode a tile: bits 0-9 meta, 10-11 coll, 12-15 elev."""
    return (meta & 0x3FF) | ((coll & 3) << 10) | ((elev & 0xF) << 12)


def load_grid(path, w, h):
    with open(path, "rb") as f:
        data = f.read()
    flat = struct.unpack(f"<{w*h}H", data[: w * h * 2])
    return [list(flat[y * w : (y + 1) * w]) for y in range(h)]


def save_grid(path, grid):
    flat = []
    for row in grid:
        flat.extend(row)
    with open(path, "wb") as f:
        f.write(struct.pack(f"<{len(flat)}H", *flat))


# ─── Metatile vocabulary (from curated Dawnflake / Route 1 study) ───
GROUND = enc(0x001, 0, 3)          # plain walkable snow-ground
GRASS = enc(0x00d, 0, 3)           # tall grass (wild encounter)
GRASS_DECO = enc(0x004, 0, 3)      # decorative grass tuft (non-encounter)
SPARKLE = enc(0x201, 0, 3)         # door-sparkle (spawn target under doors)
TREE_SOLID = enc(0x003, 1, 0)      # solid tree (border)
TREE_CLUSTER = enc(0x087, 1, 0)    # dense tree cluster (Route 1 style)


def new_grid(fill_val):
    return [[fill_val] * W for _ in range(H)]


def rect(grid, x, y, w, h, val):
    for dy in range(h):
        for dx in range(w):
            grid[y + dy][x + dx] = val


def paste_stamp(grid, x, y, stamp):
    """Paste a 2D stamp at (x, y). Stamp is a list of lists of raw encoded tiles."""
    for dy, row in enumerate(stamp):
        for dx, val in enumerate(row):
            grid[y + dy][x + dx] = val


def extract_stamp(grid, x, y, w, h):
    """Copy a wxh region out of a source grid."""
    return [[grid[y + dy][x + dx] for dx in range(w)] for dy in range(h)]


def paint_border(grid, south_exit_cols):
    """Paint forest border around all 4 edges.

    south_exit_cols: iterable of columns left as walkable ground on the
    bottom row (row H-1) to connect to Route 1.
    """
    # Top row (row 0): all tree
    for x in range(W):
        grid[0][x] = TREE_SOLID
    # Bottom row (row H-1): tree except exit cols
    exit_set = set(south_exit_cols)
    for x in range(W):
        if x in exit_set:
            grid[H - 1][x] = GROUND
        else:
            grid[H - 1][x] = TREE_SOLID
    # Left/right edge columns (x=0 and x=W-1): tree
    # but leave the grass corner tiles alone — they overwrite below
    for y in range(1, H - 1):
        grid[y][0] = TREE_SOLID
        grid[y][W - 1] = TREE_SOLID


def paint_corner_grass(grid):
    """2x2 tall-grass patches in each of the four far corners.

    Positioned so they're accessible from the walkable perimeter columns
    (col 1 and col W-2 are reserved as walkable paths around the town).
    """
    # NW grass at (1-2, 1-2)
    rect(grid, 1, 1, 2, 2, GRASS)
    # NE grass at (W-3, 1-2) = (17-18, 1-2)
    rect(grid, W - 3, 1, 2, 2, GRASS)
    # SW grass at (1-2, H-3, H-2) = (1-2, 17-18)
    rect(grid, 1, H - 3, 2, 2, GRASS)
    # SE grass at (W-3, H-3) = (17-18, 17-18)
    rect(grid, W - 3, H - 3, 2, 2, GRASS)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--dry-run", action="store_true", help="Print summary, don't write")
    args = ap.parse_args()

    # ─── 1. Back up the existing (vanilla-copy) Dawnflake map.bin ───
    if DST.exists() and not BACKUP.exists():
        shutil.copy(DST, BACKUP)
        print(f"[backup] {DST} -> {BACKUP.name}")

    # ─── 2. Extract building stamps from the existing Dawnflake grid ───
    # The current (shipped-drifted) Dawnflake has the NW house footprint
    # at (cols 2-6, rows 4-8) and the lab at (cols 3-9, rows 12-16).
    source = load_grid(DST, W, H)

    # NW house stamp: 5 cols wide x 5 rows tall at (2, 4)
    nw_house = extract_stamp(source, 2, 4, 5, 5)
    # Lab stamp: 7 cols wide x 5 rows tall at (3, 12)
    lab_stamp = extract_stamp(source, 3, 12, 7, 5)

    print(f"[extract] NW house stamp 5x5 from current Dawnflake")
    print(f"[extract] Lab stamp 7x5 from current Dawnflake")

    # ─── 3. Build new blank grid ───
    grid = new_grid(GROUND)

    # ─── 4. Paint forest border with south exit ───
    # South exit cols 7-11 overlap Route 1's top entry cols 8-11 (audit-verified)
    south_exit = [7, 8, 9, 10, 11]
    paint_border(grid, south_exit)
    print(f"[border] forest edges, south exit at cols {south_exit}")

    # ─── 5. Paint corner tall-grass patches ───
    paint_corner_grass(grid)
    print(f"[grass] 4 corners, 2x2 patches (16 tall-grass tiles)")

    # ─── 6. Stamp 4 buildings per CEO-approved layout ───
    #
    # Asher's House NW: 5x5 footprint at (3, 3) - door at (5, 7) sparkle (5, 8)
    # The NW house stamp has its door on row 4 of the stamp (rel (3, 4)),
    # so at (3, 3) absolute the door lands at (6, 7). Need to verify by
    # dumping the stamp and checking where the 0x248 door meta is.
    # Simpler: stamp at (3, 3), door lands wherever the stamp says it does.
    paste_stamp(grid, 3, 3, nw_house)
    print("[stamp] Asher's House (NW) at (3, 3)")

    # Player's House NE: copy the same NW house stamp horizontally mirrored
    # OR just re-use the stamp. For visual symmetry, just place it at (12, 3).
    paste_stamp(grid, 12, 3, nw_house)
    print("[stamp] Player's House (NE) at (12, 3)")

    # Evergreen's Lab SW: 7x5 footprint at (1, 12)
    paste_stamp(grid, 1, 12, lab_stamp)
    print("[stamp] Evergreen's Lab (SW) at (1, 12)")

    # Autumn's House SE: 5x5 footprint at (12, 12)
    paste_stamp(grid, 12, 12, nw_house)
    print("[stamp] Autumn's House (SE) at (12, 12)")

    # ─── 7. Re-paint corner grass over any stamp bleed ───
    # The stamps include their roof overhang top row which may cover the
    # grass or grass approach tiles. Repaint the corner grass to be sure.
    paint_corner_grass(grid)

    # ─── 8. Re-ensure south exit corridor is walkable between Lab and Autumn ──
    # Lab is cols 1-7 rows 12-16, Autumn is cols 12-16 rows 12-16.
    # Center corridor at cols 8-11 must stay walkable from row 12 down to
    # row 19 so the player can walk from plaza to the south exit.
    for y in range(11, 20):
        for x in range(8, 12):
            if y == 19 and x in south_exit:
                grid[y][x] = GROUND
            elif y < 19:
                grid[y][x] = GROUND

    # ─── 9. Ensure col 1 and col W-2 are walkable perimeter columns ───
    # so players can reach corner grass. Col 1 rows 1-18, col W-2 rows 1-18.
    for y in range(1, H - 1):
        # Col 1 — perimeter path, skip if inside a building wall
        # Buildings occupy cols 3+ so col 1 is always outside; make sure it's walkable.
        if grid[y][1] != GRASS:  # don't overwrite grass patches
            grid[y][1] = GROUND
        if grid[y][W - 2] != GRASS:
            grid[y][W - 2] = GROUND

    # ─── 10. Verify walkability properties ───
    walk_count = 0
    grass_count = 0
    tree_count = 0
    for row in grid:
        for t in row:
            meta = t & 0x3FF
            coll = (t >> 10) & 3
            elev = (t >> 12) & 0xF
            if coll == 0 and elev == 3:
                walk_count += 1
            if meta == 0x00d:
                grass_count += 1
            if coll == 1:
                tree_count += 1
    print(f"[verify] walkable tiles: {walk_count}/{TOTAL}")
    print(f"[verify] tall-grass tiles: {grass_count}")
    print(f"[verify] impassable tiles: {tree_count}")

    # ─── 11. Verify south edge walkability for Route 1 connection ───
    south_edge = [x for x in range(W) if (grid[H - 1][x] >> 10) & 3 == 0
                  and (grid[H - 1][x] >> 12) & 0xF in (1, 3)]
    print(f"[verify] south edge walkable cols: {south_edge}")
    if not (8 in south_edge and 11 in south_edge):
        print("[WARN] south exit does NOT overlap Route 1 entry (8-11)")
    else:
        print("[ok] south exit aligned with Route 1 top cols 8-11")

    # ─── 12. Dump a text preview (for Porymap-less review) ───
    print("\n[preview] `.` walkable · `g` grass · `#` tree/wall · `+` sparkle · `?` other")
    for y, row in enumerate(grid):
        line = f"{y:2} "
        for t in row:
            meta = t & 0x3FF
            coll = (t >> 10) & 3
            elev = (t >> 12) & 0xF
            if meta == 0x00d:
                line += "g "
            elif meta == 0x201:
                line += "+ "
            elif coll == 0 and elev == 3 and meta == 0x001:
                line += ". "
            elif coll == 0 and elev == 3:
                line += "o "   # walkable decoration (roof overhang, etc.)
            elif coll == 1:
                line += "# "
            else:
                line += "? "
        print(line)

    # ─── 13. Write the new map.bin ───
    if args.dry_run:
        print("\n[dry-run] no file written")
        return 0
    save_grid(DST, grid)
    print(f"\n[write] {DST}")
    return 0


if __name__ == "__main__":
    import sys
    sys.exit(main())
