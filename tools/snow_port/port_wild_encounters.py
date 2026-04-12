#!/usr/bin/env python3
"""
Port wild encounter tables from v17 §10 into pokeemerald wild_encounters.json.

Creates map stubs (data/maps/<Dir>/map.json + map_groups.json entries)
and populates src/data/wild_encounters.json with Snow encounter data.

Usage:
    python3 tools/snow_port/port_wild_encounters.py --create-stubs   # create map dirs
    python3 tools/snow_port/port_wild_encounters.py --dry-run        # preview encounters
    python3 tools/snow_port/port_wild_encounters.py --commit         # write encounters + make
"""

import json
import os
import sys
import hashlib
import subprocess
import argparse
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent.parent
ENCOUNTERS_JSON = REPO_ROOT / "src" / "data" / "wild_encounters.json"
MAP_GROUPS_JSON = REPO_ROOT / "data" / "maps" / "map_groups.json"
MAPS_DIR = REPO_ROOT / "data" / "maps"

# ═══════════════════════════════════════════════════════════
# Slot rate structures (pokeemerald encounter system)
# ═══════════════════════════════════════════════════════════
LAND_RATES = [20, 20, 10, 10, 10, 10, 5, 5, 4, 4, 1, 1]
WATER_RATES = [60, 30, 5, 4, 1]
# Fishing: Old Rod [0:2], Good Rod [2:5], Super Rod [5:10]
FISHING_RATES = [70, 30, 60, 20, 20, 40, 40, 15, 4, 1]

SNOW_MAP_GROUP = "gMapGroup_Snow"

MAP_STUB_TEMPLATE = {
    "layout": "LAYOUT_ROUTE101",
    "music": "MUS_ROUTE101",
    "region_map_section": "MAPSEC_ROUTE_101",
    "requires_flash": False,
    "weather": "WEATHER_NONE",
    "allow_cycling": True,
    "allow_escaping": False,
    "allow_running": True,
    "show_map_name": True,
    "battle_scene": "MAP_BATTLE_SCENE_NORMAL",
    "connections": [],
    "object_events": [],
    "warp_events": [],
    "coord_events": [],
    "bg_events": [],
}

# ═══════════════════════════════════════════════════════════
# ENCOUNTER DATA — v17 §10 species + §9 wild level ranges
# Species: (SPECIES_CONSTANT, rarity, explicit_pct_or_None)
# Rarity: "C"=Common, "U"=Uncommon, "R"=Rare
# ═══════════════════════════════════════════════════════════

LOCATIONS = [
    # ═══ Act 1 — Heavy Snow Zone ═══
    {
        "map_dir": "DawnflakeTown", "map_id": "MAP_DAWNFLAKE_TOWN",
        "base_label": "gDawnflakeTown", "is_cave": False,
        "map_type": "MAP_TYPE_TOWN",
        "encounters": {
            "land": {
                "range": (2, 4),
                "species": [
                    ("SPECIES_SENTRET", "C", None),
                    ("SPECIES_SPEAROW", "C", None),
                    ("SPECIES_POOCHYENA", "U", None),
                    ("SPECIES_DELIBIRD", "U", None),
                    ("SPECIES_VULPIX_ALOLA", "R", 5),
                ],
            },
        },
    },
    {
        "map_dir": "PowderpathVillage", "map_id": "MAP_POWDERPATH_VILLAGE",
        "base_label": "gPowderpathVillage", "is_cave": False,
        "map_type": "MAP_TYPE_TOWN",
        "encounters": {
            "land": {
                "range": (3, 6),
                "species": [
                    ("SPECIES_SENTRET", "C", None),
                    ("SPECIES_SNOVER", "C", None),
                    ("SPECIES_MEOWTH", "U", None),
                    ("SPECIES_STARLY", "R", 5),
                ],
            },
        },
    },
    {
        "map_dir": "SnowRoute1", "map_id": "MAP_SNOW_ROUTE1",
        "base_label": "gSnowRoute1", "is_cave": False,
        "map_type": "MAP_TYPE_ROUTE",
        "encounters": {
            "land": {
                "range": (3, 7),
                "species": [
                    ("SPECIES_SENTRET", "C", None),
                    ("SPECIES_SPEAROW", "C", None),
                    ("SPECIES_POOCHYENA", "U", None),
                    ("SPECIES_SNOVER", "U", None),
                    ("SPECIES_STARLY", "U", None),
                    ("SPECIES_CUBCHOO", "R", None),
                    ("SPECIES_MEOWTH", "R", None),
                ],
            },
        },
    },
    {
        "map_dir": "SnowRoute2", "map_id": "MAP_SNOW_ROUTE2",
        "base_label": "gSnowRoute2", "is_cave": False,
        "map_type": "MAP_TYPE_ROUTE",
        "encounters": {
            "land": {
                "range": (6, 9),
                "species": [
                    ("SPECIES_GEODUDE", "C", None),
                    ("SPECIES_ROGGENROLA", "C", None),
                    ("SPECIES_SNOVER", "U", None),
                    ("SPECIES_SNORUNT", "U", None),
                    ("SPECIES_TEDDIURSA", "U", None),
                    ("SPECIES_SANDSHREW_ALOLA", "U", None),
                    ("SPECIES_SWINUB", "R", None),
                    ("SPECIES_ZUBAT", "R", None),
                ],
            },
        },
    },
    {
        "map_dir": "IcespireTown", "map_id": "MAP_ICESPIRE_TOWN",
        "base_label": "gIcespireTown", "is_cave": False,
        "map_type": "MAP_TYPE_TOWN",
        "encounters": {
            "land": {
                "range": (9, 12),
                "species": [
                    ("SPECIES_SNOVER", "C", None),
                    ("SPECIES_SNORUNT", "C", None),
                    ("SPECIES_CUBCHOO", "U", None),
                    ("SPECIES_SANDSHREW_ALOLA", "U", None),
                    ("SPECIES_TEDDIURSA", "R", 5),
                    ("SPECIES_STANTLER", "R", 5),
                ],
            },
        },
    },
    {
        "map_dir": "SnowRoute3", "map_id": "MAP_SNOW_ROUTE3",
        "base_label": "gSnowRoute3", "is_cave": False,
        "map_type": "MAP_TYPE_ROUTE",
        "encounters": {
            "land": {
                "range": (10, 15),
                "species": [
                    ("SPECIES_SEEDOT", "C", None),
                    ("SPECIES_LOTAD", "C", None),
                    ("SPECIES_VENIPEDE", "C", None),
                    ("SPECIES_DEERLING", "C", None),
                    ("SPECIES_PINECO", "U", None),
                    ("SPECIES_PACHIRISU", "U", None),
                    ("SPECIES_JOLTIK", "R", None),
                    ("SPECIES_TEDDIURSA", "R", None),
                    ("SPECIES_SHROOMISH", "R", None),
                    ("SPECIES_MURKROW", "R", 5),
                    ("SPECIES_CHIKORITA", "R", 5),
                ],
            },
        },
    },
    {
        "map_dir": "SnowRoute4", "map_id": "MAP_SNOW_ROUTE4",
        "base_label": "gSnowRoute4", "is_cave": False,
        "map_type": "MAP_TYPE_ROUTE",
        "encounters": {
            "land": {
                "range": (10, 14),
                "species": [
                    ("SPECIES_ODDISH", "C", None),
                    ("SPECIES_WOOPER", "C", None),
                    ("SPECIES_VENONAT", "C", None),
                    ("SPECIES_RIOLU", "R", 5),
                    ("SPECIES_TOTODILE", "R", 5),
                    ("SPECIES_DARUMAKA_GALAR", "R", 5),
                ],
            },
        },
    },
    # Pinegrove City — Fishing + Surf only
    {
        "map_dir": "PinegroveCity", "map_id": "MAP_PINEGROVE_CITY",
        "base_label": "gPinegroveCity", "is_cave": False,
        "map_type": "MAP_TYPE_TOWN",
        "encounters": {
            "water": {
                "range": (20, 25),
                "species": [
                    ("SPECIES_POLIWHIRL", "C", None),
                    ("SPECIES_LOMBRE", "U", None),
                ],
            },
            "fishing": {
                "range": (12, 18),
                "species": [
                    ("SPECIES_POLIWAG", "C", None),
                    ("SPECIES_FINNEON", "U", None),
                    ("SPECIES_LOTAD", "U", None),
                    ("SPECIES_WOOPER", "R", 5),
                ],
            },
        },
    },
    {
        "map_dir": "SnowRoute5", "map_id": "MAP_SNOW_ROUTE5",
        "base_label": "gSnowRoute5", "is_cave": True,
        "map_type": "MAP_TYPE_UNDERGROUND",
        "encounters": {
            "land": {
                "range": (18, 22),
                "species": [
                    ("SPECIES_GEODUDE", "C", None),
                    ("SPECIES_ROGGENROLA", "C", None),
                    ("SPECIES_WOOBAT", "C", None),
                    ("SPECIES_ARON", "U", None),
                    ("SPECIES_SANDSHREW_ALOLA", "U", None),
                    ("SPECIES_MAWILE", "U", None),
                    ("SPECIES_SABLEYE", "U", None),
                    ("SPECIES_ZUBAT", "R", None),
                    ("SPECIES_MACHOP", "R", None),
                    ("SPECIES_VOLTORB", "R", None),
                    ("SPECIES_MAGNEMITE", "R", 5),
                ],
            },
        },
    },
    # ═══ Act 2 — Transitional Zone ═══
    {
        "map_dir": "SnowRoute6", "map_id": "MAP_SNOW_ROUTE6",
        "base_label": "gSnowRoute6", "is_cave": False,
        "map_type": "MAP_TYPE_ROUTE",
        "encounters": {
            "land": {
                "range": (26, 30),
                "species": [
                    ("SPECIES_CUBCHOO", "C", None),
                    ("SPECIES_SWINUB", "C", None),
                    ("SPECIES_SNOVER", "U", None),
                    ("SPECIES_DEERLING", "U", None),
                    ("SPECIES_CRYOGONAL", "R", None),
                    ("SPECIES_PIPLUP", "R", 5),
                    ("SPECIES_DARUMAKA_GALAR", "R", 5),
                ],
            },
            "water": {
                "range": (26, 30),
                "species": [
                    ("SPECIES_FINNEON", "C", 95),
                    ("SPECIES_PIPLUP", "R", 5),
                ],
            },
            "fishing": {
                "range": (26, 30),
                "species": [
                    ("SPECIES_FINNEON", "C", None),
                    ("SPECIES_SHELLDER", "U", None),
                    ("SPECIES_DRATINI", "R", 5),
                ],
            },
        },
    },
    {
        "map_dir": "SnowRoute7", "map_id": "MAP_SNOW_ROUTE7",
        "base_label": "gSnowRoute7", "is_cave": False,
        "map_type": "MAP_TYPE_ROUTE",
        "encounters": {
            "land": {
                "range": (29, 34),
                "species": [
                    ("SPECIES_SWABLU", "C", None),
                    ("SPECIES_NIDORAN_F", "C", None),
                    ("SPECIES_NIDORAN_M", "C", None),
                    ("SPECIES_MAREEP", "U", None),
                    ("SPECIES_SUDOWOODO", "U", None),
                    ("SPECIES_VULPIX_ALOLA", "U", None),
                    ("SPECIES_STANTLER", "U", None),
                    ("SPECIES_CLEFFA", "R", 5),
                    ("SPECIES_MUNCHLAX", "R", 5),
                    ("SPECIES_SKARMORY", "R", 5),
                ],
            },
        },
    },
    {
        "map_dir": "SnowRoute8", "map_id": "MAP_SNOW_ROUTE8",
        "base_label": "gSnowRoute8", "is_cave": False,
        "map_type": "MAP_TYPE_ROUTE",
        "encounters": {
            "land": {
                "range": (34, 38),
                "species": [
                    ("SPECIES_MAREEP", "C", None),
                    ("SPECIES_NIDORAN_F", "C", None),
                    ("SPECIES_NIDORAN_M", "C", None),
                    ("SPECIES_JIGGLYPUFF", "U", None),
                    ("SPECIES_MARILL", "U", None),
                    ("SPECIES_ROSELIA", "U", None),
                    ("SPECIES_CLEFAIRY", "U", 10),
                    ("SPECIES_RALTS", "R", 5),
                ],
            },
            "water": {
                "range": (34, 38),
                "species": [
                    ("SPECIES_MARILL", "C", None),
                    ("SPECIES_TYMPOLE", "U", None),
                ],
            },
            "fishing": {
                "range": (34, 38),
                "species": [
                    ("SPECIES_TYMPOLE", "C", None),
                    ("SPECIES_POLIWAG", "U", None),
                    ("SPECIES_STARYU", "R", 5),
                ],
            },
        },
    },
    {
        "map_dir": "SnowRoute9", "map_id": "MAP_SNOW_ROUTE9",
        "base_label": "gSnowRoute9", "is_cave": False,
        "map_type": "MAP_TYPE_ROUTE",
        "encounters": {
            "land": {
                "range": (37, 41),
                "species": [
                    ("SPECIES_WINGULL", "C", None),
                    ("SPECIES_KRABBY", "C", None),
                    ("SPECIES_CRYOGONAL", "U", None),
                    ("SPECIES_OSHAWOTT", "R", 5),
                    ("SPECIES_SPHEAL", "R", 5),
                ],
            },
            "fishing": {
                "range": (37, 41),
                "species": [
                    ("SPECIES_KRABBY", "C", None),
                    ("SPECIES_SHELLDER", "C", None),
                    ("SPECIES_CHINCHOU", "U", None),
                    ("SPECIES_CARVANHA", "R", 10),
                ],
            },
        },
    },
    {
        "map_dir": "IceharborCity", "map_id": "MAP_ICEHARBOR_CITY",
        "base_label": "gIceharborCity", "is_cave": False,
        "map_type": "MAP_TYPE_TOWN",
        "encounters": {
            "water": {
                "range": (40, 45),
                "species": [
                    ("SPECIES_WINGULL", "C", None),
                    ("SPECIES_FINNEON", "C", None),
                    ("SPECIES_TENTACOOL", "U", None),
                    ("SPECIES_ALOMOMOLA", "U", 10),
                ],
            },
            "fishing": {
                "range": (38, 43),
                "species": [
                    ("SPECIES_KRABBY", "C", None),
                    ("SPECIES_FINNEON", "C", None),
                    ("SPECIES_CHINCHOU", "C", None),
                    ("SPECIES_STARYU", "U", 10),
                    ("SPECIES_CARVANHA", "U", 10),
                ],
            },
        },
    },
    {
        "map_dir": "DriftrockIsle", "map_id": "MAP_DRIFTROCK_ISLE",
        "base_label": "gDriftrockIsle", "is_cave": False,
        "map_type": "MAP_TYPE_ROUTE",
        "encounters": {
            "land": {
                "range": (42, 46),
                "species": [
                    ("SPECIES_SPHEAL", "C", None),
                    ("SPECIES_CORSOLA", "C", None),
                    ("SPECIES_NOSEPASS", "U", None),
                    ("SPECIES_LARVITAR", "R", 5),
                ],
            },
            "water": {
                "range": (42, 46),
                "species": [
                    ("SPECIES_SEALEO", "C", None),
                    ("SPECIES_FINNEON", "C", None),
                    ("SPECIES_LAPRAS", "R", 5),
                ],
            },
            "fishing": {
                "range": (42, 46),
                "species": [
                    ("SPECIES_FINNEON", "C", None),
                    ("SPECIES_CORSOLA", "C", None),
                    ("SPECIES_RELICANTH", "R", 15),
                ],
            },
        },
    },
    {
        "map_dir": "SnowRoute10", "map_id": "MAP_SNOW_ROUTE10",
        "base_label": "gSnowRoute10", "is_cave": True,
        "map_type": "MAP_TYPE_UNDERGROUND",
        "encounters": {
            "land": {
                "range": (44, 48),
                "species": [
                    ("SPECIES_SLUGMA", "C", None),
                    ("SPECIES_SNORUNT", "C", None),
                    ("SPECIES_LITWICK", "C", None),
                    ("SPECIES_SWINUB", "C", None),
                    ("SPECIES_MAGMAR", "U", None),
                    ("SPECIES_TYNAMO", "U", None),
                    ("SPECIES_GOLBAT", "U", None),
                    ("SPECIES_CYNDAQUIL", "R", 5),
                ],
            },
        },
    },
    {
        "map_dir": "SnowRoute11", "map_id": "MAP_SNOW_ROUTE11",
        "base_label": "gSnowRoute11", "is_cave": False,
        "map_type": "MAP_TYPE_ROUTE",
        "encounters": {
            "land": {
                "range": (48, 53),
                "species": [
                    ("SPECIES_SKIPLOOM", "C", None),
                    ("SPECIES_ROSELIA", "C", None),
                    ("SPECIES_SKORUPI", "C", None),
                    ("SPECIES_PETILIL", "C", None),
                    ("SPECIES_TOGETIC", "U", None),
                    ("SPECIES_VULPIX", "U", None),
                    ("SPECIES_GROWLITHE", "U", None),
                    ("SPECIES_EEVEE", "R", 5),
                    ("SPECIES_TURTWIG", "R", 5),
                ],
            },
        },
    },
    # ═══ Act 3 — Tropical/Volcanic Zone ═══
    {
        "map_dir": "SnowRoute12", "map_id": "MAP_SNOW_ROUTE12",
        "base_label": "gSnowRoute12", "is_cave": False,
        "map_type": "MAP_TYPE_ROUTE",
        "encounters": {
            "land": {
                "range": (54, 57),
                "species": [
                    ("SPECIES_XATU", "C", None),
                    ("SPECIES_DUSKULL", "C", None),
                    ("SPECIES_MUNNA", "C", None),
                    ("SPECIES_SIGILYPH", "U", None),
                    ("SPECIES_MISDREAVUS", "U", None),
                    ("SPECIES_DUOSION", "U", None),
                    ("SPECIES_GOLETT", "U", None),
                    ("SPECIES_ABSOL", "R", 5),
                    ("SPECIES_KIRLIA", "R", 5),
                ],
            },
        },
    },
    {
        "map_dir": "SolaceTown", "map_id": "MAP_SOLACE_TOWN",
        "base_label": "gSolaceTown", "is_cave": False,
        "map_type": "MAP_TYPE_TOWN",
        "encounters": {
            "land": {
                "range": (54, 58),
                "species": [
                    ("SPECIES_MUNNA", "C", None),
                    ("SPECIES_MISDREAVUS", "C", None),
                    ("SPECIES_SKORUPI", "U", None),
                    ("SPECIES_GOLETT", "U", None),
                    ("SPECIES_BALTOY", "R", 5),
                ],
            },
        },
    },
    {
        "map_dir": "SnowRoute13", "map_id": "MAP_SNOW_ROUTE13",
        "base_label": "gSnowRoute13", "is_cave": False,
        "map_type": "MAP_TYPE_ROUTE",
        "encounters": {
            "land": {
                "range": (58, 61),
                "species": [
                    ("SPECIES_CROAGUNK", "C", None),
                    ("SPECIES_EXEGGCUTE", "C", None),
                    ("SPECIES_CARNIVINE", "C", None),
                    ("SPECIES_SIMISAGE", "U", None),
                    ("SPECIES_SIMISEAR", "U", None),
                    ("SPECIES_SIMIPOUR", "U", None),
                    ("SPECIES_YANMA", "U", None),
                    ("SPECIES_SNIVY", "R", 5),
                    ("SPECIES_HERACROSS", "R", 5),
                ],
            },
            "water": {
                "range": (58, 61),
                "species": [
                    ("SPECIES_TYMPOLE", "C", None),
                    ("SPECIES_LOTAD", "U", None),
                    ("SPECIES_POLIWHIRL", "U", None),
                ],
            },
            "fishing": {
                "range": (58, 61),
                "species": [
                    ("SPECIES_TYMPOLE", "C", None),
                    ("SPECIES_LOTAD", "U", None),
                    ("SPECIES_POLIWHIRL", "U", None),
                ],
            },
        },
    },
    {
        "map_dir": "SnowRoute14", "map_id": "MAP_SNOW_ROUTE14",
        "base_label": "gSnowRoute14", "is_cave": False,
        "map_type": "MAP_TYPE_ROUTE",
        "encounters": {
            "land": {
                "range": (61, 63),
                "species": [
                    ("SPECIES_MAGCARGO", "C", None),
                    ("SPECIES_KROKOROK", "C", None),
                    ("SPECIES_TROPIUS", "C", None),
                    ("SPECIES_HOUNDOUR", "U", None),
                    ("SPECIES_CLAYDOL", "U", None),
                    ("SPECIES_TORKOAL", "U", None),
                    ("SPECIES_CHIMCHAR", "R", 5),
                    ("SPECIES_DARUMAKA", "R", 5),
                ],
            },
        },
    },
    {
        "map_dir": "SnowRoute15", "map_id": "MAP_SNOW_ROUTE15",
        "base_label": "gSnowRoute15", "is_cave": False,
        "map_type": "MAP_TYPE_ROUTE",
        "encounters": {
            "land": {
                "range": (63, 66),
                "species": [
                    ("SPECIES_PONYTA", "C", None),
                    ("SPECIES_HIPPOPOTAS", "C", None),
                    ("SPECIES_STUNFISK", "C", None),
                    ("SPECIES_KROKOROK", "U", None),
                    ("SPECIES_LARVESTA", "U", None),
                    ("SPECIES_TEPIG", "R", 5),
                ],
            },
            "water": {
                "range": (63, 66),
                "species": [
                    ("SPECIES_TENTACRUEL", "C", None),
                    ("SPECIES_LUMINEON", "C", None),
                    ("SPECIES_ALOMOMOLA", "U", None),
                    ("SPECIES_FRILLISH", "U", None),
                    ("SPECIES_SEADRA", "R", 5),
                ],
            },
            "fishing": {
                "range": (63, 66),
                "species": [
                    ("SPECIES_LUMINEON", "C", None),
                    ("SPECIES_CARVANHA", "C", None),
                    ("SPECIES_SHARPEDO", "U", None),
                    ("SPECIES_SEADRA", "R", 5),
                ],
            },
        },
    },
    # ═══ Postgame ═══
    {
        "map_dir": "IronfrostCaveB1", "map_id": "MAP_IRONFROST_CAVE_B1",
        "base_label": "gIronfrostCaveB1", "is_cave": True,
        "map_type": "MAP_TYPE_UNDERGROUND",
        "encounters": {
            "land": {
                "range": (72, 78),
                "species": [
                    ("SPECIES_PILOSWINE", "C", None),
                    ("SPECIES_SNEASEL", "C", None),
                    ("SPECIES_GRAVELER", "C", None),
                    ("SPECIES_GOLBAT", "U", None),
                    ("SPECIES_CRYOGONAL", "U", None),
                    ("SPECIES_SANDSLASH_ALOLA", "U", None),
                    ("SPECIES_DRUDDIGON", "U", 10),
                ],
            },
        },
    },
    {
        "map_dir": "IronfrostCaveB2B3", "map_id": "MAP_IRONFROST_CAVE_B2B3",
        "base_label": "gIronfrostCaveB2B3", "is_cave": True,
        "map_type": "MAP_TYPE_UNDERGROUND",
        "encounters": {
            "land": {
                "range": (76, 82),
                "species": [
                    ("SPECIES_PILOSWINE", "C", None),
                    ("SPECIES_SNEASEL", "C", None),
                    ("SPECIES_GRAVELER", "C", None),
                    ("SPECIES_SANDSLASH_ALOLA", "C", None),
                    ("SPECIES_GOLBAT", "U", None),
                    ("SPECIES_CRYOGONAL", "U", None),
                    ("SPECIES_DRUDDIGON", "U", 10),
                ],
            },
        },
    },
    {
        "map_dir": "SnowVictoryRoad", "map_id": "MAP_SNOW_VICTORY_ROAD",
        "base_label": "gSnowVictoryRoad", "is_cave": True,
        "map_type": "MAP_TYPE_UNDERGROUND",
        "encounters": {
            "land": {
                "range": (82, 86),
                "species": [
                    ("SPECIES_GRAVELER", "C", None),
                    ("SPECIES_BOLDORE", "C", None),
                    ("SPECIES_LAIRON", "C", None),
                    ("SPECIES_MAWILE", "C", None),
                    ("SPECIES_SABLEYE", "C", None),
                    ("SPECIES_GOLBAT", "U", None),
                    ("SPECIES_PAWNIARD", "U", None),
                    ("SPECIES_FRAXURE", "U", None),
                ],
            },
        },
    },
]


# ═══════════════════════════════════════════════════════════
# SLOT ALLOCATION ALGORITHM
# ═══════════════════════════════════════════════════════════

def allocate_slots(species_entries, slot_rates):
    """
    Allocate species to encounter slots respecting C/U/R tiers.

    Algorithm:
    1. Place species with explicit percentages in best-matching slots
    2. Each remaining species gets one slot, ordered by tier (C→U→R)
       with commons getting highest-rate slots
    3. Bonus slots (leftovers) cycle through commons to boost their rates

    Returns: list of species constants, one per slot.
    """
    n = len(slot_rates)
    slots = [None] * n
    taken = set()

    explicit = [(s, p) for s, r, p in species_entries if p is not None]
    commons = [s for s, r, p in species_entries if r == "C" and p is None]
    uncommons = [s for s, r, p in species_entries if r == "U" and p is None]
    rares = [s for s, r, p in species_entries if r == "R" and p is None]

    # Step 1: Place explicit-percentage species in best-matching slots
    for sp, pct in sorted(explicit, key=lambda x: -x[1]):
        best = min(
            (i for i in range(n) if i not in taken),
            key=lambda i: (abs(slot_rates[i] - pct), i),
        )
        slots[best] = sp
        taken.add(best)

    # Step 2: Remaining slots sorted by descending rate
    remaining = sorted(
        [i for i in range(n) if i not in taken], key=lambda i: -slot_rates[i]
    )

    # Determine how many slots each tier gets
    n_avail = len(remaining)
    n_c = len(commons)
    n_u = len(uncommons)
    n_r = len(rares)
    n_species = n_c + n_u + n_r

    # Each species gets at least one slot; extras go to commons
    if n_species <= n_avail:
        extra = n_avail - n_species
        # Distribute extra: ~60% C, ~30% U, ~10% R
        if n_c > 0 and n_u > 0 and n_r > 0:
            c_extra = round(extra * 0.6)
            u_extra = round(extra * 0.3)
            r_extra = extra - c_extra - u_extra
        elif n_c > 0 and n_u > 0:
            c_extra = round(extra * 0.7)
            u_extra = extra - c_extra
            r_extra = 0
        elif n_c > 0:
            c_extra = extra
            u_extra = r_extra = 0
        else:
            u_extra = extra
            c_extra = r_extra = 0

        c_slots = n_c + c_extra
        u_slots = n_u + u_extra
        r_slots = n_r + r_extra
    else:
        # More species than slots — truncate rares first
        c_slots = min(n_c, n_avail)
        u_slots = min(n_u, max(0, n_avail - c_slots))
        r_slots = max(0, n_avail - c_slots - u_slots)

    # Assign commons to top slots
    idx = 0
    for i in range(c_slots):
        if commons:
            slots[remaining[idx]] = commons[i % len(commons)]
            idx += 1

    # Assign uncommons to middle slots
    for i in range(u_slots):
        if uncommons:
            slots[remaining[idx]] = uncommons[i % len(uncommons)]
            idx += 1

    # Assign rares to bottom slots
    for i in range(r_slots):
        if rares:
            slots[remaining[idx]] = rares[i % len(rares)]
            idx += 1

    # Fill any remaining None slots (happens when all species are explicit)
    all_species = (
        commons + uncommons + rares
        + [s for s, _ in explicit]
    )
    if not all_species:
        all_species = [s for s, _, _ in species_entries]
    fill_idx = 0
    for i in range(n):
        if slots[i] is None:
            slots[i] = all_species[fill_idx % len(all_species)]
            fill_idx += 1

    assert all(s is not None for s in slots), f"Unfilled slots: {slots}"
    return slots


def assign_levels(n_slots, lo, hi):
    """
    Assign levels across slots. Lower slots (common) get lower levels,
    higher slots (rare) get higher levels. Each entry is (min_level, max_level).
    """
    span = hi - lo
    if span == 0:
        return [(lo, lo)] * n_slots
    levels = []
    for i in range(n_slots):
        t = i / max(n_slots - 1, 1)
        lvl = round(lo + t * span)
        levels.append((lvl, lvl))
    return levels


def assign_fishing_levels(lo, hi):
    """
    Assign levels to 10 fishing slots by rod type.
    Old Rod: lowest levels, Good Rod: mid, Super Rod: highest.
    """
    span = hi - lo
    if span <= 2:
        return [(lo, hi)] * 10

    # Split range into thirds for each rod
    old_hi = lo + max(1, span // 3)
    good_lo = lo + 1
    good_hi = lo + max(2, 2 * span // 3)
    super_lo = lo + span // 3
    super_hi = hi

    levels = []
    # Old Rod (2 slots)
    levels.append((lo, old_hi))
    levels.append((lo, old_hi))
    # Good Rod (3 slots)
    levels.append((good_lo, good_hi))
    levels.append((good_lo, good_hi))
    levels.append((good_lo + 1, good_hi))
    # Super Rod (5 slots)
    for i in range(5):
        t = i / 4
        mn = round(super_lo + t * (super_hi - super_lo))
        levels.append((mn, super_hi))

    return levels


# ═══════════════════════════════════════════════════════════
# ENCOUNTER ENTRY GENERATION
# ═══════════════════════════════════════════════════════════

def generate_encounter_entry(loc):
    """Generate a wild_encounters.json entry dict for one location."""
    entry = {
        "map": loc["map_id"],
        "base_label": loc["base_label"],
    }

    enc = loc["encounters"]

    if "land" in enc:
        land = enc["land"]
        lo, hi = land["range"]
        species_list = land["species"]
        slot_species = allocate_slots(species_list, LAND_RATES)
        slot_levels = assign_levels(12, lo, hi)
        rate = 10 if loc["is_cave"] else 20
        entry["land_mons"] = {
            "encounter_rate": rate,
            "mons": [
                {
                    "min_level": slot_levels[i][0],
                    "max_level": slot_levels[i][1],
                    "species": slot_species[i],
                }
                for i in range(12)
            ],
        }

    if "water" in enc:
        water = enc["water"]
        lo, hi = water["range"]
        species_list = water["species"]
        slot_species = allocate_slots(species_list, WATER_RATES)
        slot_levels = assign_levels(5, lo, hi)
        entry["water_mons"] = {
            "encounter_rate": 4,
            "mons": [
                {
                    "min_level": slot_levels[i][0],
                    "max_level": slot_levels[i][1],
                    "species": slot_species[i],
                }
                for i in range(5)
            ],
        }

    if "fishing" in enc:
        fish = enc["fishing"]
        lo, hi = fish["range"]
        species_list = fish["species"]
        slot_species = allocate_slots(species_list, FISHING_RATES)
        slot_levels = assign_fishing_levels(lo, hi)
        entry["fishing_mons"] = {
            "encounter_rate": 30,
            "mons": [
                {
                    "min_level": slot_levels[i][0],
                    "max_level": slot_levels[i][1],
                    "species": slot_species[i],
                }
                for i in range(10)
            ],
        }

    return entry


# ═══════════════════════════════════════════════════════════
# MAP STUB CREATION
# ═══════════════════════════════════════════════════════════

def create_map_stubs():
    """Create minimal map.json stubs and update map_groups.json."""
    created = []

    for loc in LOCATIONS:
        map_dir = MAPS_DIR / loc["map_dir"]
        map_json = map_dir / "map.json"

        if map_json.exists():
            print(f"  SKIP {loc['map_dir']} (already exists)")
            continue

        map_dir.mkdir(parents=True, exist_ok=True)

        stub = dict(MAP_STUB_TEMPLATE)
        stub["id"] = loc["map_id"]
        stub["name"] = loc["map_dir"]
        stub["map_type"] = loc["map_type"]

        with open(map_json, "w") as f:
            json.dump(stub, f, indent=2)
            f.write("\n")

        created.append(loc["map_dir"])
        print(f"  CREATE {map_dir}/map.json")

    # Update map_groups.json
    with open(MAP_GROUPS_JSON) as f:
        groups = json.load(f)

    snow_maps = [loc["map_dir"] for loc in LOCATIONS]

    if SNOW_MAP_GROUP in groups:
        existing = set(groups[SNOW_MAP_GROUP])
        new_maps = [m for m in snow_maps if m not in existing]
        if new_maps:
            groups[SNOW_MAP_GROUP].extend(new_maps)
            print(f"  UPDATE {SNOW_MAP_GROUP}: added {len(new_maps)} maps")
        else:
            print(f"  SKIP {SNOW_MAP_GROUP} (all maps present)")
    else:
        groups["group_order"].append(SNOW_MAP_GROUP)
        groups[SNOW_MAP_GROUP] = snow_maps
        print(f"  CREATE {SNOW_MAP_GROUP} with {len(snow_maps)} maps")

    with open(MAP_GROUPS_JSON, "w") as f:
        json.dump(groups, f, indent=2)
        f.write("\n")

    return created


# ═══════════════════════════════════════════════════════════
# ENCOUNTER JSON INJECTION
# ═══════════════════════════════════════════════════════════

def md5(path):
    return hashlib.md5(Path(path).read_bytes()).hexdigest()


def inject_encounters(dry_run=False):
    """Generate all Snow encounter entries and inject into wild_encounters.json."""
    pre_md5 = md5(ENCOUNTERS_JSON)

    with open(ENCOUNTERS_JSON) as f:
        data = json.load(f)

    # Find the main encounter group
    main_group = None
    for g in data["wild_encounter_groups"]:
        if g.get("for_maps"):
            main_group = g
            break
    assert main_group is not None, "Could not find for_maps encounter group"

    # Check which Snow maps already have entries
    existing_maps = {e["map"] for e in main_group["encounters"]}
    snow_map_ids = {loc["map_id"] for loc in LOCATIONS}

    already = snow_map_ids & existing_maps
    if already:
        print(f"  WARNING: {len(already)} Snow maps already in encounters:")
        for m in sorted(already):
            print(f"    {m}")

    # Generate entries
    new_entries = []
    for loc in LOCATIONS:
        if loc["map_id"] in existing_maps:
            continue
        entry = generate_encounter_entry(loc)
        new_entries.append(entry)

    if not new_entries:
        print("  No new entries to add.")
        return

    # Display preview
    total_land = sum(1 for e in new_entries if "land_mons" in e)
    total_water = sum(1 for e in new_entries if "water_mons" in e)
    total_fish = sum(1 for e in new_entries if "fishing_mons" in e)
    print(f"\n  Encounters to add: {len(new_entries)} locations")
    print(f"    land: {total_land}, water: {total_water}, fishing: {total_fish}")

    # Show per-location summary
    for entry in new_entries:
        types = []
        if "land_mons" in entry:
            species = set(m["species"] for m in entry["land_mons"]["mons"])
            types.append(f"land({len(species)}sp)")
        if "water_mons" in entry:
            species = set(m["species"] for m in entry["water_mons"]["mons"])
            types.append(f"water({len(species)}sp)")
        if "fishing_mons" in entry:
            species = set(m["species"] for m in entry["fishing_mons"]["mons"])
            types.append(f"fish({len(species)}sp)")
        print(f"    {entry['map']:40s} {', '.join(types)}")

    if dry_run:
        print("\n  DRY RUN — no files modified.")
        # Print first entry as sample
        print("\n  Sample entry (first location):")
        print(json.dumps(new_entries[0], indent=2))
        return

    # Write
    main_group["encounters"].extend(new_entries)

    with open(ENCOUNTERS_JSON, "w") as f:
        json.dump(data, f, indent=2)
        f.write("\n")

    post_md5 = md5(ENCOUNTERS_JSON)
    print(f"\n  wild_encounters.json:")
    print(f"    pre-write  MD5: {pre_md5}")
    print(f"    post-write MD5: {post_md5}")
    print(f"    entries added:  {len(new_entries)}")


# ═══════════════════════════════════════════════════════════
# CLI
# ═══════════════════════════════════════════════════════════

def main():
    parser = argparse.ArgumentParser(
        description="Port v17 §10 wild encounters into pokeemerald"
    )
    group = parser.add_mutually_exclusive_group(required=True)
    group.add_argument(
        "--create-stubs", action="store_true",
        help="Create map stub directories and update map_groups.json",
    )
    group.add_argument(
        "--dry-run", action="store_true",
        help="Preview encounter entries without writing",
    )
    group.add_argument(
        "--commit", action="store_true",
        help="Write encounter entries and run make",
    )

    args = parser.parse_args()

    # Safety: refuse on dirty tree (matches port_trainers.py pattern)
    result = subprocess.run(
        ["git", "status", "--porcelain"],
        capture_output=True, text=True, cwd=REPO_ROOT,
    )
    dirty = [
        line for line in result.stdout.strip().split("\n")
        if line and not line.startswith("??")
    ]
    if dirty and not args.dry_run:
        print("ERROR: Uncommitted changes to tracked files. Commit or stash first.")
        for line in dirty:
            print(f"  {line}")
        sys.exit(1)

    if args.create_stubs:
        print("Creating map stubs...")
        created = create_map_stubs()
        print(f"\nDone. {len(created)} new map stubs created.")
        print("Next: commit stubs, then run --dry-run to preview encounters.")

    elif args.dry_run:
        print("Generating encounter preview...")
        inject_encounters(dry_run=True)

    elif args.commit:
        print("Injecting encounters...")
        inject_encounters(dry_run=False)
        print("\nRunning make...")
        result = subprocess.run(
            ["make", f"-j{os.cpu_count()}"],
            cwd=REPO_ROOT,
        )
        if result.returncode != 0:
            print("\nBUILD FAILED. Encounters written but build broken.")
            print("Investigate, fix, then re-run make.")
            sys.exit(1)
        print("\nBuild green. Encounters shipped.")
        rom_md5 = md5(REPO_ROOT / "pokeemerald.gba")
        print(f"ROM MD5: {rom_md5}")


if __name__ == "__main__":
    main()
