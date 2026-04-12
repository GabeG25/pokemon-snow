# Pokémon Snow — Project Overview
This is the high-level "what and why" of Pokémon Snow. Read this alongside CLAUDE.md (session rules) and PROJECT_FILES.md (filesystem map) whenever Claude Code needs project context beyond the immediate task. Updated opportunistically as the project evolves.
What Pokémon Snow Is
A pokeemerald-expansion-based ROM hack set in the Boralyss region, a new ice-and-winter-themed region. Single-player main-story campaign with a gym-and-league progression structure, competitive-grade AI trainers, a 317-species Pokédex including custom Hidden Abilities, and an antagonist arc centered on Team Veil and the legendary Pokémon Kyurem.
Target platform: GBA ROM (.gba file), playable in any GBA emulator (mGBA, VisualBoyAdvance-M, etc.) or on original hardware via flash cart.
CEO and lead designer: Kirk Gibson.
Setting & Story
Boralyss region. Ice/winter-themed region with mountain routes, frozen lakes, pine forests, glacial caves, and a volcanic-thermal contrast zone. Route progression loosely: coastal start, then foothills, then mountain passes, then glacial interior, then volcanic contrast, then league.
Seasons and weather. Weather rocks in this hack provide permanent weather, not 5-turn timers. This is a core balance lever — Snow Warning ability users on early-route trainers shape matchups more aggressively than in vanilla.
Antagonist: Team Veil. A villain organization pursuing Kyurem. They appear as unnamed Grunts on mid-to-late routes (R3 and R5 confirmed, more through R15). Their sprite-equivalent in the current build is Team Magma (visual placeholder until real Veil art ships).
Main antagonist character: Tyrell. Tied to Kyurem, central to the late-game story arc.
Rival: Asher. Autumn seasonal connection. Rival battles at established milestones.
Other NPCs of note:

Xenon — gifts the player a Zorua early
Autumn — rival-adjacent character
Champion Tyrim — final boss of the league

Starters: Treecko, Torchic, Mudkip (Hoenn vanilla trio). This is intentional design — do not suggest ice-themed alternatives. The starters are deliberately thematically separate from the ice/winter region to make them feel unique as the only non-region-coded Pokémon the player receives. This is a locked CEO decision.
Pokédex & Species
317 species in the regional dex. Includes:

Pokémon that fit the ice/winter theme (Snover, Swinub, Cubchoo, Snorunt, Cryogonal, Vanillite line, etc.) heavily featured on early-to-mid routes
104 custom Hidden Abilities beyond vanilla
Custom learnsets where needed (Bellossom Quiver Dance, Nidorina Earth Power, Altaria Moonblast were early examples)
Weather-team Pokémon balanced around the permanent-weather rule

Note on implementation state: Species data exists fully in the v17 design archive but has not yet been ported into src/data/pokemon/ engine files. That's a future batch of work, pattern similar to trainer porting.
Boss Fights & Progression
35 total boss fights designed with competitive-grade movesets:

16 "F-list" boss fights (F1 through F16) use 0-EV teams for early-game difficulty tuning
F17 through F35 use full competitive EV spreads for late-game challenge
Every boss fight has locked species, moves, natures, abilities, held items
Gym leaders, rivals, Elite Four equivalents, and Champion Tyrim are all F-list entries

Boss fights are separate from route trainers (the ~93 generic trainers spread across routes). Route trainers are what the tooling in this repo ships via port_trainers.py.
Mechanics & Balance Rules (Locked)
Several non-vanilla mechanical decisions are locked engine-level:

Weather rocks equal permanent weather (no 5-turn timer)
Critical hits deal 2x damage (pre-Gen 6 rule, not 1.5x)
Starter-as-ace rule for rival: the rival's ace Pokémon throughout the story is the starter with type advantage over the player's choice
Nature consistency: trainer teams respect nature-appropriate stat distributions (no Modest physical attackers etc.)
Item uniqueness: Only certain items appear on trainers; many competitive items are struck from trainer use entirely (CEO design choice to prevent "item soup" feel on route trainers)
Eviolite pre-evo exception: trainer Pokémon can hold Eviolite only if the species has an evolution available in the dex
Trade evolution via held-item config toggle: species that normally require trade evolution use an in-engine toggle instead, preserving the evolution trigger without multiplayer dependency

Implementation State
This section is living — update as routes ship. Last updated: 2026-04-12 post-all-trainers.
Shipped (data layer, compiled into ROM):

Route trainers: R1(3) R2(4) R3(5) R5(6) R6(8) R7(5) R8(6) R9(8) R10(8) R11(6) R12(7) R13(9) R14(9) R15(9) DI(5) VR(8) = 106 trainers
Boss fights: F1-F35 = 57 trainer entries (35 fights, 11 with A/B/C starter variants)
Total: 163 Snow trainers in ROM. ALL v17 §20 + §5 trainer data shipped.

Engine state:

MAX_TRAINERS_COUNT_EMERALD expanded from 864 to 1024 (flag-ceiling expansion committed as save-breaking change)
TRAINERS_COUNT_EMERALD equals 1018 (163 Snow trainers plus 855 vanilla Emerald trainers retained)
6 flag slots free (64 facility grunts will require ceiling expansion to ~1088)
SaveBlock1 sizeof equals 15,588 bytes, budget 15,872, headroom 284 bytes
Build compiles clean via make -j$(nproc) using devkitARM under WSL Ubuntu

Shipped (species data layer):

104 custom Hidden Abilities applied to 167 species (port_species_ha.py)
~138 custom learnset additions (198 moves via port_species_learnsets.py)
2x crit damage, physical Water Shuriken, trade evo native in expansion
Gallade Sharpness already handled by pokeemerald-expansion GEN_9 guard

Not yet shipped — design exists in v17, awaiting implementation:

317-species full Pokédex data files (base stats, types beyond what's already in expansion)
64 facility grunts (Facilities Delta/Beta/Alpha — requires ceiling expansion)

Not yet started:

Map wiring — every trainer currently exists only as a data structure. None can be encountered in-game until map data references them (Porymap or hex editing, event scripting, sight ranges)
NPC scripting — dialog, rival encounters, Team Veil story cutscenes, Kyurem confrontation
Real Team Veil / Boarder / Skier / Miner class sprites (currently using Magma / Hiker fallbacks)
Item distribution across maps (Dragonforge Dept. Store inventory, Frostbreak Lodge, 22 designed hidden items)
Music, art, sound beyond vanilla Emerald
Balance playtesting (blocked until at least R1 through R5 has map wiring)

Rough completeness: ~35% toward a fully playable build. All trainer data (163 route + 57 boss = 220 entries), custom HAs (167 species), and custom learnsets (198 moves) are shipped. The remaining work is map wiring, wild encounter tables, NPC scripting, facility grunts, and art.
Tool Architecture
The core tool is tools/snow_port/port_trainers.py — reads the v17 design archive and emits ROM data with full safety rails. Currently ~650 lines.
What the tool does:

Parses section 20 of v17 (route trainer specs, markdown tables)
Emits trainerproc-format blocks into src/data/trainers.party
Inserts #define lines into include/constants/opponents.h with correct column alignment
Auto-maintains TRAINERS_COUNT_EMERALD and the ceiling warning comment
Validates against shipped state via byte-identical round-trip comparison
Supports preview mode (--dry-run) and write mode (--commit)

Trainer shapes the tool handles:

Named trainers with vanilla classes (Youngster, Lass, Bug Catcher, Hiker, etc.) — works natively
Named trainers with non-vanilla classes (Boarder, Skier, Miner) — via CLASS_FALLBACKS dict, all map to Hiker
Unnamed Team Veil Grunts — via GRUNT_TEAM_FALLBACK dict, Veil maps to Magma

Trainer shape NOT yet handled (R5 blocker):
4. Tag-double pairs — R5-5/6 Veil Grunts share one heading with two sub-labeled tables. R6, R12, R14 also have tag-double pairs. Next session's enhancement.
Safety rails:

Refuses to run with uncommitted changes to tracked files
MD5 snapshots before and after writes
Ceiling check (batch size plus current count must not exceed MAX)
Post-write grep verification of count and warning comment values
Compiler is the oracle (runs make, halts on failure, does not auto-commit)
Round-trip validator for already-shipped routes (regression gate)

Methodology Patterns (Locked)
Three durable patterns emerged from the first 14 commits and should persist across future sessions:
1. Spec/file hierarchy. The v17 design archive is canonical for design. Shipped files are canonical for current state but are allowed to contradict spec when probing-era drift occurred. When contradicted, normalize the shipped file to spec first as a standalone chore commit, then build tooling against the corrected state. Never build on top of known-drifted state.
2. Probe methodology for unknown classes. When a new trainer class appears in v17 that may or may not exist in pokeemerald-expansion: emit optimistically using the spec class name, run make, let the compiler's "did you mean" suggestion reveal the correct fallback, add to CLASS_FALLBACKS, re-run. Validated for Boarder, Skier, Miner — all map to Hiker. Exception: when the outcome is known (fictional team like Team Veil has no canonical counterpart), pre-load the fallback to skip a failed-build cycle.
3. Compiler-as-oracle for engine measurements. For any sizeof(struct) or layout value in the compiled ELF, extract it empirically from the binary rather than computing via naive bit math. Pattern: find a function that uses the value as an immediate operand, disassemble with arm-none-eabi-objdump, read the literal pool entry. Cross-validate against independent sources.
Design Decisions (Locked — Do Not Re-Litigate)
These are CEO decisions. Claude Code should not propose alternatives.

Starters are Treecko/Torchic/Mudkip. Not ice-themed. Intentional thematic separation.
Hoenn vanilla dex structure retained where species not replaced. Not a full regional replacement — Snow extends and modifies pokeemerald, doesn't gut it.
Weather rocks equal permanent weather. Not 5-turn.
2x crit damage. Not 1.5x.
Tag-double parser deferred to R5-session. Not bundled with grunt support.
Save-breaking flag-ceiling expansion is acceptable during dev. No migration path.
Class fallback gender-flip accepted (all grunts default Male when falling back).
No Co-Authored-By trailers in commit messages. Commit messages are exactly what the CEO drafts.
Never chain make and git commit with double-ampersand. Build and commit are separate commands with human approval between.

Deferred Work (Known Blockers, Not Bugs)
These exist in the project plan but are intentionally not being worked yet:

Map wiring for all routes. Blocks in-game encounters. Defer until data-complete through R15.
Section 2 HA gap: Altaria Aerilate. Handle when porting R13-2 Musician Lyric.
Real Team Veil / Boarder / Skier / Miner class assets. Defer to dedicated art-asset session.
Stale hex comments in include/constants/flags.h. Cosmetic only.
Save format freeze. Only matters if project goes public with save-compatibility requirements.

For Claude Code Reading This
You have five sources of truth, in order of authority:

CEO's explicit instruction in the current session (highest authority)
CLAUDE.md (session rules), PROJECT_FILES.md (filesystem map), and this file (project vision) — persistent project context
The most recent handoff in ~/pokemon-snow-handoffs/ (session-to-session state)
The v17 design archive (design canon — read when spec details are needed)
The git history (decision rationale via commit message bodies)

When any conflict between these, escalate to the CEO. Do not auto-resolve design conflicts or re-litigate locked decisions.
Role is CEO/CTO: the CEO defines what is needed, you determine how to execute. Push back when the approach is wrong. Direct feedback, no validation-seeking. The methodology patterns above exist because they've been stress-tested through real bug-catch-and-fix cycles. Trust them.
