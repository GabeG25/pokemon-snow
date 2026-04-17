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
This section is living — update as routes ship. Last updated: 2026-04-17 post-autonomous-completion.
Shipped (data layer, compiled into ROM):

Route trainers: R1(3) R2(4) R3(5) R5(6) R6(8) R7(5) R8(6) R9(8) R10(8) R11(6) R12(7) R13(9) R14(9) R15(9) DI(5) VR(8) = 106 trainers
Boss fights: F1-F35 = 57 trainer entries (35 fights, 11 with A/B/C starter variants). E4 (F31-F34 Brynn/Vesper/Reverie/Wyatt) + Champion (F35 Tyrim) named per v17 canon.
Total: 163 Snow trainers in ROM. ALL v17 §20 + §5 trainer data shipped.

Engine state:

MAX_TRAINERS_COUNT_EMERALD expanded 864 → 1024 → 1088 (save-breaking expansions)
TRAINERS_COUNT_EMERALD equals 1018 (163 Snow + 855 vanilla Emerald retained)
70 trainer flag slots free (64 facility grunts fit within 1088 ceiling with 6 headroom)
FLAG_SNOW_* count: 51 allocated (0x20-0x4F + 0x54-0x55 + Act 1 intro flags + 6 in 0x1DE-0x1E3 block for facility caps and TM18)
VAR_SNOW_* count: 1 (VAR_SNOW_INTRO_STATE at 0x404E)
SaveBlock1 sizeof equals 15,596 bytes, budget 15,872, headroom 276 bytes
Build compiles clean via make -j$(nproc) using devkitARM under WSL Ubuntu

Shipped (species data layer):

104 custom Hidden Abilities applied to 167 species (port_species_ha.py)
~138 custom learnset additions (198 moves via port_species_learnsets.py)
2x crit damage, physical Water Shuriken, trade evo native in expansion
Gallade Sharpness already handled by pokeemerald-expansion GEN_9 guard
51-TM Snow remap (TMs 01-51 per v17 §11, shipped via commit c5f61fe218)

Shipped (engine mechanics, all active globally):

B_CRIT_MULTIPLIER = GEN_5 (2x crits per DECISIONS.md locked)
Weather rocks duration 0 (permanent per v17 §2)
Water Shuriken = DAMAGE_CATEGORY_PHYSICAL
Amulet Coin 3x prize multiplier (per v17 §16)
B_PROTEAN_LIBERO = GEN_8
Snow level-cap progression: badges 1-8 (15/23/30/40/50/59/66/72) + facility-boss cascade F18→73, F22→79, F27→89, F28→92, F30→95, Champion→95+ (v17 §21)
ITEM_PERMAFROST_SHARD + HOLD_EFFECT_PERMAFROST_SHARD: +50% Ice damage for Kyurem (v17 §23)

Shipped (map infrastructure + wild encounters):

73 Snow maps registered in gMapGroup_Snow: 31 outdoor + 42 interior
All 31 outdoor/primary maps painted with custom layouts (Dawnflake, Route 1, Powderpath, Route 2, Icespire, Route 3 at CEO-polished quality; R4-R15 + VR + DI algorithmically generated via gen_layouts.py)
60 outdoor-to-outdoor connections (north-to-south flow per v17 geography)
8 gym cities fully walkable with PC 1F/2F + Mart + heal loop: Icespire, Pinegrove, Ironfrost, Dreamurs, Iceharbor, Dragonforge (+ 5-floor Dept Store + Rooftop with 108-item inventory), Solace, Pyrespire
Frostbreak Lodge: 8-item specialty shop + Shell Bell + TM18 Rest NPCs
10 Snow heal locations (Dawnflake bedroom + 8 city PCs + implicit Frostbreak)
Wild encounter tables: 22 locations (21 land, 6 water, 7 fishing), 131 unique species, levels 2-4 (Dawnflake) through 82-86 (Victory Road), includes regional forms (Alolan Vulpix/Sandshrew/Sandslash, Galarian Darumaka)

Shipped (scripting):

Act 1 complete: bedroom wake-up → Mom cutscene → lab starter ceremony (with Asher F1 + Autumn pitch + TM01 Work Up) → Running Shoes → R1 Autumn tutorial (F2 battle + 5 Poké Balls) → first route trainers
106 trainer battle scripts with placeholder dialogue
Badge-gated Poké Mart shared clerk (Snow_PokeMart_EventScript_Clerk) used by all 7 city marts
Dragonforge Dept Store clerks (2F Poke Mart Plus, 3F TM Shop, 4F Battle Items A+B, 5F Evolution, Rooftop Vending)
All 8 gym leader scripts functional (Silvan richest, Gyms 2-8 with placeholder dialogue)
NPC gifts: TM01/02/03/04/05/18, Shell Bell, Toxic Orb, Dragon Scale, Wide Lens, Bright Powder, Black Sludge, Old Rod, Root Fossil, Vanillite (Powderpath), Move Tutors (5 cities)
Region MAPSEC naming per-location (29 Snow MAPSECs defined; grid coords placeholder)

Shipped (tooling):

tools/snow_port/ — 12 scripts, ~5500 lines:
port_trainers.py, port_boss_fights.py, port_species_ha.py, port_species_learnsets.py, port_wild_encounters.py, gen_layouts.py, audit_scripts.py, paint_dawnflake.py, blend_dawnflake_route1.py
audit_scripts.py: semantic gym-leader vs trainer-ID cross-check (catches IronfrostCity-class bugs), flag/trainer/item cross-reference, 14 cap-entry validation
gen_layouts.py: --only flag for non-destructive single-map regeneration
port_trainers.py: GRUNT_NAME_OVERRIDES dict for narrative-name decoupling from constant IDs

Not yet shipped — CEO-blocked (design decisions required):

29 MAPSEC grid coordinates for Town Map UI (Phase 1 blocker)
Kyurem confrontation design (location, trigger, battle shape — Phase 4)
Tyrell F22 + F27 encounter sites + cutscene content (Phase 4)
64 facility grunt teams (species/moves/items/natures/abilities/EVs per Delta/Beta/Alpha — Phase 6)
Xenon Zorua gift specifics (location, conditions, flag — Phase 7)
Post-game scope boundary for v1.0 (Phase 7)
4 E4 member + Champion HoF flavor text + credits content (Phase 5; names already locked)

Not yet started:

Pokémon League interior maps (PokemonLeague/scripts.inc is `.byte 0` stub — E4 rooms, Champion room, Hall of Fame cutscene)
Dialogue polish R6-R15 + VR + DI (~60 trainers running 6-voice placeholder pool — Phase 3)
Story scripts for Acts 2-3 rival encounters (Asher F8/F21/F30, Autumn F10/F15)
Team Veil scripted events past R5 (R6 tag-double grunts, R12/R14 grunt pairs, Facility Delta/Beta/Alpha grunt waves)
22 hidden items placed across maps (v17 §16)
Real Team Veil / Boarder / Skier / Miner class sprites (fallbacks active)
Custom Boralyss region map PNG (vanilla Hoenn placeholder)
Music, art, sound beyond vanilla Emerald
Balance playtesting

Rough completeness: ~55-60% toward a fully playable build. All engine mechanics, data layers, structural map infrastructure (73 maps), Act 1 scripting, and post-Act-1 gym-city interiors are shipped. Remaining work is CEO creative (dialogue, 64 grunts, Kyurem design, League interior) and art.
Tool Architecture
The core tools are in tools/snow_port/:
port_trainers.py (~870 lines) — route/DI/VR trainers with tag-doubles
port_boss_fights.py (~460 lines) — boss fight data with variant support
port_species_ha.py (~430 lines) — custom Hidden Abilities
port_species_learnsets.py (~365 lines) — custom learnset additions
port_wild_encounters.py (~530 lines) — wild encounter tables + map stub creation
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
