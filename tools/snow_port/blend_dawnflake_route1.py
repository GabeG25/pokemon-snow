#!/usr/bin/env python3
"""
Blend the tree border at the Dawnflake ↔ Route 1 map boundary.

Dawnflake row 19 (south edge) uses a 1-row tree border style with metas
0x1ce / 0x1cf. Route 1 row 0 (north edge) originally uses a 2-row tree
border style with metas 0x1d4 / 0x1d5 / 0x1dc / 0x1dd. At the boundary
these two styles abut, which reads as 'wonky' — you see one border style
become another in a single step.

This script surgically retiles Route 1's row 0 and row 1 so that the
Route-1-side border matches Dawnflake's 1-row border style:
  - Row 0 impassable tiles (tree metas) → 0x1ce / 0x1cf alternating
  - Row 1 impassable tiles (tree-bottom metas) → walkable ground 0x001
  - Walkable entry tiles (cols 8-11) are left alone

Dawnflake's map.bin is NOT touched — the CEO's Porymap edits are
preserved.

Usage: python3 tools/snow_port/blend_dawnflake_route1.py [--dry-run]
"""
import argparse
import struct
import shutil
from pathlib import Path

REPO = Path(__file__).resolve().parents[2]
R1 = REPO / "data/layouts/SnowRoute1/map.bin"
R1_BACKUP = R1.with_suffix(".bin.prev_blend")

W, H = 20, 20


def enc(meta, coll=0, elev=3):
    return (meta & 0x3FF) | ((coll & 3) << 10) | ((elev & 0xF) << 12)


def decode(t):
    return (t & 0x3FF, (t >> 10) & 3, (t >> 12) & 0xF)


def load(path):
    with open(path, "rb") as f:
        data = f.read()
    return list(struct.unpack(f"<{W*H}H", data[: W * H * 2]))


def save(path, tiles):
    with open(path, "wb") as f:
        f.write(struct.pack(f"<{W*H}H", *tiles))


# Dawnflake's 1-row tree border metatiles (impassable)
TREE_1CE = enc(0x1CE, 1, 0)
TREE_1CF = enc(0x1CF, 1, 0)
# Dawnflake's corner-wall style (tall-grass-themed impassable border)
CORNER_WALL = enc(0x00D, 1, 0)
GROUND = enc(0x001, 0, 3)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--dry-run", action="store_true")
    args = ap.parse_args()

    if R1.exists() and not R1_BACKUP.exists():
        shutil.copy(R1, R1_BACKUP)
        print(f"[backup] {R1.name} -> {R1_BACKUP.name}")

    tiles = load(R1)

    changes = 0

    # Row 0: replace impassable tree tiles with 0x1ce/0x1cf alternating
    for x in range(W):
        idx = 0 * W + x
        meta, coll, elev = decode(tiles[idx])
        if coll == 1:  # impassable border tile
            new = TREE_1CE if (x % 2 == 0) else TREE_1CF
            if tiles[idx] != new:
                tiles[idx] = new
                changes += 1

    # Row 0 corners (cols 0-2 and 17-19): match Dawnflake's 0x00d corner
    # wall style so the boundary is tile-continuous
    for x in list(range(0, 3)) + list(range(17, 20)):
        idx = 0 * W + x
        if tiles[idx] != CORNER_WALL:
            tiles[idx] = CORNER_WALL
            changes += 1

    # Row 1: replace impassable tree-bottom tiles with walkable ground
    # (the border becomes 1 row tall instead of 2)
    for x in range(W):
        idx = 1 * W + x
        meta, coll, elev = decode(tiles[idx])
        if coll == 1:  # was a tree-bottom
            if tiles[idx] != GROUND:
                tiles[idx] = GROUND
                changes += 1

    print(f"[blend] Route 1: {changes} tiles updated on rows 0-1")

    # Preview rows 0, 1 for verification
    print("\n[preview] Route 1 rows 0-1 after blend:")
    for y in (0, 1):
        line = f"y={y}: "
        for x in range(W):
            m, c, e = decode(tiles[y * W + x])
            if c == 1:
                line += "# "
            elif c == 0 and e == 3:
                if m == 0x00D:
                    line += "g "
                elif m == 0x001:
                    line += ". "
                else:
                    line += "o "
            else:
                line += "? "
        print(line)

    if args.dry_run:
        print("\n[dry-run] no file written")
        return 0

    save(R1, tiles)
    print(f"\n[write] {R1}")
    return 0


if __name__ == "__main__":
    import sys
    sys.exit(main())
