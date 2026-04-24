#!/usr/bin/env python3
"""Open SnowRoute2 north edge so the Powderpath south connection works.

Powderpath Village (26x20, offset 0) connects DOWN to SnowRoute2
(50x20). PV south edge (rows 18-19) is fully walkable; R2 top
edge (rows 0-1) was 100% blocked, leaving the player walled off
when crossing south from PV.

This script opens R2 rows 0 and 1 at the same column ranges that
R2 row 2 is already walkable (cols 8-16 + 18-23), preserving
col 17's vertical divider so the new opening matches the existing
two-strip corridor design on row 2.

Tile parameters: mtid=1 (blank walkable snow, same as the open
spots on row 2), coll=0, elev=3.

Cols 24-25 stay blocked (matches row 2). Cols 0-7 and 26-49 stay
blocked (decorative ice border). Result: 2 rows x 15 walkable
tiles = 30 tile changes, 5 column gap (col 17) preserved.

Idempotent.
"""
import struct
from pathlib import Path

MAP = Path(__file__).resolve().parents[2] / "data/layouts/SnowRoute2/map.bin"
W, H = 50, 20

OPEN_COLS = list(range(8, 17)) + list(range(18, 24))   # 8-16 + 18-23
OPEN_ROWS = [0, 1]
NEW_MTID = 1
NEW_COLL = 0
NEW_ELEV = 3


def main():
    with open(MAP, "rb") as f:
        tiles = list(struct.unpack(f"<{W*H}H", f.read()[: W * H * 2]))

    new_word = NEW_MTID | (NEW_COLL << 10) | (NEW_ELEV << 12)
    changes = 0
    for y in OPEN_ROWS:
        for x in OPEN_COLS:
            i = y * W + x
            w = tiles[i]
            if w != new_word:
                mt = w & 0x3FF
                c = (w >> 10) & 3
                e = (w >> 12) & 0xF
                tiles[i] = new_word
                changes += 1
                print(f"  ({x:2},{y:2}) mt=0x{mt:03x}->0x{NEW_MTID:03x} "
                      f"coll={c}->{NEW_COLL} elev={e}->{NEW_ELEV}")

    print(f"\n[changes] {changes}")
    with open(MAP, "wb") as f:
        f.write(struct.pack(f"<{W*H}H", *tiles))
    print(f"[write] {MAP}")


if __name__ == "__main__":
    main()
