# trainers.party Format Reference (pokeemerald-expansion trainerproc)

pokeemerald-expansion uses a competitive-syntax `.party` file at `src/data/trainers.party`.
The `trainerproc` tool compiles this into C headers at build time. This is NOT the legacy
C struct format from vanilla pokeemerald.

## IMPORTANT: Read Before Writing

Before editing trainers.party, ALWAYS `cat src/data/trainers.party | head -100` to see
the actual format your project uses. The format below is the pokeemerald-expansion standard,
but Pokémon Snow may have project-specific conventions on top of it.

## Pokémon Snow Trainerproc Conventions (LOCKED)

These are project-specific rules that override defaults:
- Blank lines between trainer blocks
- Omit empty/default fields (don't include fields with default values)
- Move format: `- Move` (dash space MoveName)
- Trainer names: UPPERCASE
- No trailing newline at end of file
- 5-space padding on the party count line
- Never chain `git commit` behind `make` with `&&`

## Trainer Block Structure

```
= TRAINER_ROUTE1_HIKER // trainer constant (must match opponents.h)
Name: HIKER MARCUS
Class: HIKER
Pic: TRAINER_PIC_HIKER
Music: ENCOUNTER_HIKER
Gender: Male
Items: ITEM_SUPER_POTION
Double Battle: No
AI: Check Bad Move / Try To Faint / Check Viability

     Pokemon:

Geodude (M) @ Oran Berry
Ability: Sturdy
Level: 14
IVs: 10 HP / 10 Atk / 10 Def / 10 SpA / 10 SpD / 10 Spe
- Rock Throw
- Magnitude
- Defense Curl
- Tackle

Machop (M) @ None
Ability: Guts
Level: 13
IVs: 10 HP / 10 Atk / 10 Def / 10 SpA / 10 SpD / 10 Spe
- Low Kick
- Leer
- Focus Energy
- Karate Chop
```

## Field Reference

### Trainer Header Fields

| Field | Required | Format | Notes |
|-------|----------|--------|-------|
| `= TRAINER_*` | YES | First line, starts with `=` | Constant from opponents.h |
| `Name:` | YES | Up to 12 characters | Display name in battle |
| `Class:` | YES | Trainer class name | Must match a valid class |
| `Pic:` | YES | `TRAINER_PIC_*` | Trainer sprite constant |
| `Music:` | NO | `ENCOUNTER_*` | Battle music theme |
| `Gender:` | NO | `Male` or `Female` | Defaults based on class |
| `Items:` | NO | Up to 4 ITEM_* constants | Healing items the trainer uses |
| `Double Battle:` | NO | `Yes` or `No` | Default: No |
| `AI:` | NO | AI flag names separated by ` / ` | Trainer intelligence |

### AI Flags

Common AI flags (separated by ` / `):
- `Check Bad Move` — Don't use ineffective moves
- `Try To Faint` — Prioritize KO moves
- `Check Viability` — Evaluate move effectiveness
- `Setup First Turn` — Use setup moves early
- `Risky` — Take more risks
- `Prefer Strongest Move` — Always use strongest available
- `Prefer Baton Pass` — Use Baton Pass when possible
- `Double Battle` — Double battle AI awareness
- `HP Aware` — Factor HP into decisions

### Pokémon Entry Fields

| Field | Required | Format | Notes |
|-------|----------|--------|-------|
| Species line | YES | `Species (Gender) @ Item` | `(M)`, `(F)`, or omit for random |
| `Ability:` | NO | Ability name | Must be valid for that species |
| `Level:` | YES | Integer | Pokémon's level |
| `IVs:` | NO | `X HP / X Atk / X Def / X SpA / X SpD / X Spe` | Default: 0 all |
| `EVs:` | NO | Same format as IVs | Default: 0 all |
| `Nature:` | NO | Nature name | Default: Hardy |
| `Shiny:` | NO | `Yes` | Only include if shiny |
| `Ball:` | NO | Ball type | Poké Ball if omitted |
| `Nickname:` | NO | Up to 12 characters | Custom nickname |
| Moves | NO | `- MoveName` (one per line, max 4) | If omitted, uses level-up moves |

### Species Line Format

```
Swinub (F) @ Oran Berry          // Female Swinub holding Oran Berry
Sneasel (M) @ None               // Male Sneasel, no held item
Piloswine @ Sitrus Berry          // Random gender, holding Sitrus Berry
```

`@ None` means no held item. If the `@ Item` part is omitted entirely, it also means no item.

## opponents.h

The `opponents.h` file at `src/data/trainers/opponents.h` (or similar path) defines the
TRAINER_* constants. Every trainer in `trainers.party` must have a matching constant.

When adding a new trainer:
1. Add the TRAINER_* constant to opponents.h
2. Add the trainer block to trainers.party
3. Create the event script with `trainerbattle_*` command
4. Set up the object event in map.json with TRAINER_TYPE_NORMAL

## Common Mistakes

- **Missing blank line between trainer blocks** — trainerproc may merge trainers
- **Wrong IV format** — Must be `X HP / X Atk / X Def / X SpA / X SpD / X Spe` (all 6)
- **Invalid ability for species** — Check the species data to confirm ability is available
- **Move not learnable** — Verify the Pokémon can actually learn the move in the expansion
- **Mismatched TRAINER_* constant** — The `= TRAINER_*` line must exactly match opponents.h
- **Gender on genderless species** — Don't add (M) or (F) to genderless Pokémon
