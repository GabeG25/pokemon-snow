#!/usr/bin/env python3
"""Powderpath Village collision cleanup (v80 iteration).

Rebuilds map.bin from the prev-audit backup + layers in the full
collision punch list from the v78/v79 playtests:

  A. Mart + PC roof solidity: row 1 over both buildings forced
     coll=1 so the top-right corner (and the whole top row) is a
     clean wall instead of a walkable-then-blocked checkerboard.
  B. Bottom 2 houses (House3 cols 1-6, House2 cols 15-19, rows
     14-17) forced coll=1 everywhere except the two door tiles
     (4,17) and (17,17). Clears the walkable holes the CEO
     spotted in the roofs/walls.
  C. Row 19 (bottom of town) fully blocked. The R2 path at cols
     10-15 was dead space (R2 row 0 is 100% blocked); blocking
     row 19 makes the south edge a clean border.
  D. East tall-grass strip cols 20-25 rows 1-18 left walkable
     (encounters trigger) with row 0 tree border blocked.
  E. Ice cream stand enclosure: (4,9) + (3,10) + (5,10) forced
     coll=1 so the only approach to the vendor at (4,10) is via
     the counter-front at (4,11) from the south.
  F. House2 door (17,17) coll=1 for convention consistency.

Preserves all metatile IDs. Backup in map.bin.prev_audit is the
baseline.
"""
import argparse
import shutil
import struct
from pathlib import Path

REPO = Path(__file__).resolve().parents[2]
MAP = REPO / "data/layouts/PowderpathVillage/map.bin"
BACKUP = MAP.with_suffix(".bin.prev_audit")

W, H = 26, 20


def load(path):
    with open(path, "rb") as f:
        return list(struct.unpack(f"<{W*H}H", f.read()[: W * H * 2]))


def save(path, tiles):
    with open(path, "wb") as f:
        f.write(struct.pack(f"<{W*H}H", *tiles))


def decode(t):
    return (t & 0x3FF, (t >> 10) & 3, (t >> 12) & 0xF)


def pack(mt, coll, elev):
    return (mt & 0x3FF) | ((coll & 3) << 10) | ((elev & 0xF) << 12)


def set_coll(tile, new_coll):
    mt, _, e = decode(tile)
    return pack(mt, new_coll, e)


def idx(x, y):
    return y * W + x


def force(tiles, x, y, new_coll, tag, changes):
    i = idx(x, y)
    mt, c, e = decode(tiles[i])
    if c != new_coll:
        tiles[i] = set_coll(tiles[i], new_coll)
        changes.append(f"{tag} ({x:2},{y:2}) coll {c}->{new_coll} mt=0x{mt:03x}")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--dry-run", action="store_true")
    args = ap.parse_args()

    if not BACKUP.exists():
        print(f"[error] {BACKUP} missing")
        return 1

    tiles = load(BACKUP)
    before = list(tiles)
    changes = []

    # Route 1 is fixed by a separate helper below — the main fixer stays focused
    # on Powderpath. (Route 1 elev normalization is in fix_route1_elev.py.)

    # A. Mart + PC roofs: the row-1 overhang stays walkable so the player can
    # slip behind the roof (CEO-confirmed convention). Hitbox covers rows 2-4
    # only — those are forced coll=1 below in the building-body pass.
    for x in range(1, 5):
        force(tiles, x, 1, 0, "mart overhang", changes)
    for x in range(15, 19):
        force(tiles, x, 1, 0, "pc overhang", changes)
    # Mart body rows 2-4 cols 1-4 forced coll=1 (except door at 2,4 handled by convention)
    for y in range(2, 5):
        for x in range(1, 5):
            force(tiles, x, y, 1, "mart body", changes)
    # PC body rows 2-4 cols 15-18 forced coll=1 (except door at 16,4)
    for y in range(2, 5):
        for x in range(15, 19):
            force(tiles, x, y, 1, "pc body", changes)

    # B. Bottom 2 houses: rows 14-17, cols 1-6 (House3) and 15-19 (House2)
    #    Doors at (4,17) and (17,17) are force-blocked anyway -> fine.
    for y in range(14, 18):
        for x in range(1, 7):
            force(tiles, x, y, 1, "house3", changes)
        for x in range(15, 20):
            force(tiles, x, y, 1, "house2", changes)

    # C. Row 19: entire bottom row walkable per CEO ("no invisible barriers
    # anywhere except visible buildings/vendor/trees").
    for x in range(W):
        force(tiles, x, 19, 0, "bottom row walk", changes)

    # D. East tall-grass strip cols 20-25 rows 1-18 -> coll=0 (walkable, encounters)
    for y in range(1, 19):
        for x in range(20, 26):
            force(tiles, x, y, 0, "east grass", changes)

    # Row 0 tree border cols 20-25 -> coll=1
    for x in range(20, 26):
        force(tiles, x, 0, 1, "east tree-row", changes)

    # E. Ice cream stand enclosure: block the whole canopy + side walls.
    # Vendor at (4,10); counter-front (4,11) walkable — only entry point.
    force(tiles, 4, 9, 1, "stand canopy mid", changes)
    force(tiles, 5, 9, 1, "stand canopy TR", changes)
    force(tiles, 3, 10, 1, "stand west-wall", changes)
    force(tiles, 5, 10, 1, "stand east-wall", changes)

    # F. House2 door (17,17) coll=1 convention
    force(tiles, 17, 17, 1, "house2 door", changes)

    print(f"\n[changes] total: {len(changes)}")
    for line in changes[:60]:
        print(f"  - {line}")
    if len(changes) > 60:
        print(f"  ... and {len(changes) - 60} more")

    def grid_str(ts, label):
        print(f"\n{label}")
        print("     " + "".join(str(x % 10) for x in range(W)))
        for y in range(H):
            row = [str(decode(ts[idx(x, y)])[1]) for x in range(W)]
            print(f"y{y:2}  " + "".join(row))

    grid_str(before, "[collision BEFORE (prev_audit)]")
    grid_str(tiles, "[collision AFTER]")

    if args.dry_run:
        print("\n[dry-run]")
        return 0

    save(MAP, tiles)
    print(f"\n[write] {MAP}")
    return 0


if __name__ == "__main__":
    import sys
    sys.exit(main() or 0)
