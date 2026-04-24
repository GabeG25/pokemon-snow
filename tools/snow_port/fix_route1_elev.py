#!/usr/bin/env python3
"""Snow Route 1 elevation normalization.

Four tile islands were painted at elev=0 inside rows where all other walkable
tiles were elev=3. Running east-west across those rows hiccups because the
engine clears the current-elevation state on every elev=0 tile and re-latches.

Targets (all set to elev=3, coll unchanged):
    (12,14) (13,14) (12,15) (13,15)   — grass patch middle
    ( 8,18) ( 9,18) ( 8,19) ( 9,19)   — south-exit path base

Idempotent — re-runnable safely.
"""
import struct
from pathlib import Path

MAP = Path(__file__).resolve().parents[2] / "data/layouts/SnowRoute1/map.bin"
W, H = 20, 20

def main():
    with open(MAP, "rb") as f:
        tiles = list(struct.unpack(f"<{W*H}H", f.read()[: W * H * 2]))

    targets = [(12,14),(13,14),(12,15),(13,15),(8,18),(9,18),(8,19),(9,19)]
    changes = 0
    for x, y in targets:
        i = y * W + x
        w = tiles[i]
        mt = w & 0x3FF
        c = (w >> 10) & 3
        e = (w >> 12) & 0xF
        if e != 3:
            new = mt | (c << 10) | (3 << 12)
            if new != w:
                tiles[i] = new
                changes += 1
                print(f"  ({x:2},{y:2}) elev {e}->3 mt=0x{mt:03x} coll={c}")

    print(f"\n[changes] {changes}")
    with open(MAP, "wb") as f:
        f.write(struct.pack(f"<{W*H}H", *tiles))
    print(f"[write] {MAP}")

if __name__ == "__main__":
    main()
