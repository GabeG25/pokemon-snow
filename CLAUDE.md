# Pokémon Snow — Claude Code Project Rules

## Role
CEO/CTO dynamic. User is CEO — direct feedback, push back when wrong, no validation-seeking. Claude is CTO.

## Trainerproc Format (8 rules)
1. `=== TRAINER_SNOW_R{N}_{N}_{NAME} ===` header, names UPPERCASE
2. AI: always full 5-flag suite (Check Bad Move / Try To Faint / Check Viability / Smart Switching / Smart Mon Choices)
3. Moves use `- Move` dash format, NOT `Moves: A / B`
4. Omit `Items:` line entirely if no trainer-level items
5. Omit `@ <item>` on species line if no held item
6. No trailing newline after final move of final Pokémon in batch
7. Single blank line between trainers, between header/species, between species blocks
8. Gender/Music derived from emit_class (post-fallback), not spec class

## opponents.h Layout
- All trainer #defines column-aligned at slot column 44
- Trainer region lives ABOVE the warning comment block; never insert between comment and count line
- TRAINERS_COUNT_EMERALD preserves 5-space padding
- Warning comment remaining-count auto-maintained by the tool

## Class Fallbacks (until real assets ship)
Boarder → Hiker, Skier → Hiker, Miner → Hiker. Gender-flip accepted (all three fall back to Male). No per-trainer override mechanism.

## Build-Commit Discipline
- NEVER chain `make` and `git commit` with `&&`. Two separate commands, human approval between.
- Always build before committing trainer data. Red commits are not acceptable.
- Always grep-verify TRAINERS_COUNT_EMERALD value after any opponents.h substitution.

## Probe Methodology
New trainer class → optimistic emit → `make` → if compiler rejects, add to CLASS_FALLBACKS in tools/snow_port/port_trainers.py → re-run.

## Tool Invocation
```
python3 tools/snow_port/port_trainers.py --route N --dry-run   # preview or round-trip
python3 tools/snow_port/port_trainers.py --route N --commit    # write + build
```

## Canary Verification
Every session starts with: `git status && git log --oneline -5 && md5sum pokeemerald.gba src/data/trainers.party include/constants/opponents.h`. Halt if drift from handoff expectations.

## Spec Hierarchy
v17 §20 (design-archive/POKEMON_SNOW_RESUME_HANDOFF_v17.md) is canonical. Shipped files can be wrong when contradicting spec — normalize first, then build.

## Do Not Change
- Starters are Treecko/Torchic/Mudkip. Not ice-themed. CEO decision, settled.

## Session Handoffs
At end of substantive sessions, produce structured handoff block (completed work, decisions + rationale, unfinished items, canary MD5s, next-session first-action). User stores and pastes at next session start.
