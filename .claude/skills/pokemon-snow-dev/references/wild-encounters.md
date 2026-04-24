# Wild Encounters Format Reference

Wild encounter data is at `src/data/wild_encounters.json`.

## Encounter Slot Counts (EXACT — wrong count = array bounds error)

| Method | Slots Required | Probability Weights |
|--------|---------------|-------------------|
| `land_mons` | **12** exactly | [20, 20, 10, 10, 10, 10, 5, 5, 4, 4, 1, 1] |
| `water_mons` | **5** exactly | [60, 30, 5, 4, 1] |
| `fishing_mons` | **10** exactly | [70, 30, 60, 20, 20, 40, 40, 15, 4, 1] |
| `rock_smash_mons` | **5** exactly | [60, 30, 5, 4, 1] |

## Adding Encounters to a Map

Find the correct encounter type in the JSON. Add your map under `groups`:

```json
{
    "type": "land_mons",
    "encounter_rates": [20, 20, 10, 10, 10, 10, 5, 5, 4, 4, 1, 1],
    "groups": {
        "MAP_ROUTE1": {
            "encounter_rate": 20,
            "mons": [
                {"min_level": 4, "max_level": 5, "species": "SPECIES_SWINUB"},
                {"min_level": 4, "max_level": 5, "species": "SPECIES_SNOVER"},
                {"min_level": 4, "max_level": 5, "species": "SPECIES_SWINUB"},
                {"min_level": 5, "max_level": 6, "species": "SPECIES_SNOVER"},
                {"min_level": 5, "max_level": 6, "species": "SPECIES_SMOOCHUM"},
                {"min_level": 5, "max_level": 6, "species": "SPECIES_SMOOCHUM"},
                {"min_level": 5, "max_level": 7, "species": "SPECIES_SNEASEL"},
                {"min_level": 5, "max_level": 7, "species": "SPECIES_SNEASEL"},
                {"min_level": 6, "max_level": 7, "species": "SPECIES_DELIBIRD"},
                {"min_level": 6, "max_level": 7, "species": "SPECIES_DELIBIRD"},
                {"min_level": 6, "max_level": 8, "species": "SPECIES_ABSOL"},
                {"min_level": 6, "max_level": 8, "species": "SPECIES_EEVEE"}
            ]
        }
    }
}
```

## Entry Format

```json
{"min_level": 5, "max_level": 7, "species": "SPECIES_SWINUB"}
```

- `min_level`, `max_level`: integers. min <= max. Game picks random level in range.
- `species`: SPECIES_* constant. Verify with `grep -r "SPECIES_NAME" include/constants/species.h`

## encounter_rate

Controls frequency. Range 0-20. Higher = more encounters.
- 0: No encounters (table exists but never triggers)
- 5-10: Low frequency
- 15-20: High frequency

## Slot Probability (land_mons example)

| Slot | Weight | Use For |
|------|--------|---------|
| 0-1 | 20% each | Common (40% total) |
| 2-5 | 10% each | Uncommon (40% total) |
| 6-7 | 5% each | Semi-rare (10% total) |
| 8-9 | 4% each | Rare (8% total) |
| 10-11 | 1% each | Very rare (2% total) |

## Fishing Slots (10 total)

| Slots | Rod | Weight |
|-------|-----|--------|
| 0-1 | Old Rod | [70, 30] |
| 2-4 | Good Rod | [60, 20, 20] |
| 5-9 | Super Rod | [40, 40, 15, 4, 1] |

## Common Mistakes

- **Wrong mons count:** land_mons needs EXACTLY 12 entries. Not 11. Not 13. Exactly 12.
- **Map key mismatch:** Must be the MAP_* constant from map.json `id` field
- **Invalid species:** Always verify SPECIES_* exists with grep
- **min > max level:** Will cause undefined behavior
