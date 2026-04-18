# Pokémon Snow — Design Decisions Log
Every locked design decision for Pokémon Snow, with rationale and alternatives considered. This file is the answer to "why is this the way it is?" Future sessions read this before re-litigating any decision that appears locked.
How to Read This File
Each decision entry has four fields:

Decision: the locked position
Rationale: why this position was chosen
Alternatives considered: what else was evaluated and why those were rejected
Locked in: the commit, handoff, or session that finalized it

When Claude Code encounters a question that matches a locked decision, the answer is "see DECISIONS.md" rather than re-debate. The CEO may override any decision — but only the CEO. Claude Code does not re-open locked decisions on its own initiative.
Adding to This File
When a new design decision is made, add it here in the appropriate section with a docs(DECISIONS): commit. Include all four fields. Un-rationalized decisions are debt.

Gameplay & Mechanics
Starters are Treecko, Torchic, Mudkip
Decision: Player starters remain the Hoenn trio (Treecko, Torchic, Mudkip). No ice-themed starter alternatives.
Rationale: Intentional thematic separation. The Boralyss region is ice/winter-coded throughout — routes, gym leaders, wild Pokémon, story. The starters are deliberately not region-coded so they feel unique as the only non-regional companions the player receives on arrival. Getting an ice starter in an ice region collapses this contrast.
Alternatives considered: Snover/Vanillite/Cubchoo trio; Piplup/Cyndaquil/Chespin tri-type; custom fakemon starters. All rejected — they either duplicate the region's theme or introduce scope not needed for the core experience.
Locked in: Design archive v17, reinforced across all route spec sessions.
Weather rocks = permanent weather
Decision: Weather rocks in Snow produce weather that lasts indefinitely, not the 5-turn duration of vanilla.
Rationale: Core balance lever for the ice-region identity. Snow Warning ability users on early routes shape matchups meaningfully only if the weather persists. 5-turn weather is a micro-optimization concern rather than a strategic axis. Permanent weather makes ability choice matter on entry and item choice matter for defense.
Alternatives considered: Vanilla 5-turn; 8-turn (Gen 6 with rock); permanent with stronger counter-weather effects. The 8-turn compromise was considered but rejected — permanent is cleaner rule and better fits a region where winter is the permanent condition.
Locked in: Design archive v17, mechanics section.
2× critical hit damage
Decision: Critical hits in Snow deal 2× damage, not Gen 6+'s 1.5×.
Rationale: Pre-Gen 6 convention. Increases the stakes of crit-fishing strategies and makes High Crit Rate moves meaningfully different from high base power moves. 1.5× flattens strategic diversity.
Alternatives considered: Vanilla Emerald's 2× (already matches); Gen 6+ 1.5×. The project uses pokeemerald-expansion which defaults to configurable crit damage; 2× was explicitly set as the project's value.
Locked in: Design archive v17, mechanics section.
Starter-as-ace rivalry rule
Decision: The rival's ace Pokémon throughout the story is the starter with type advantage over the player's choice.
Rationale: Creates a consistent narrative thread where the rival is the player's specific counterpoint. The player who chose Treecko faces a rival with Torchic/Blaziken as ace; Mudkip → Sceptile; Torchic → Swampert. Each playthrough has a different rival team dynamic despite identical story beats.
Alternatives considered: Random rival ace; fixed rival ace regardless of player choice; rotating rival aces based on story milestone. All rejected — starter-as-ace gives consistent narrative identity to rival encounters.
Locked in: Design archive v17, story section.
Item uniqueness / no trainer item soup
Decision: Route trainers do not use the full competitive item pool. Many common trainer items are struck. Held items on route trainers are restricted to a curated list for thematic and difficulty reasons.
Rationale: Prevents "item soup" where every trainer has a different defensive item and every matchup becomes arithmetic rather than strategic. Route trainers should feel like people with specific themes, not optimized AI teams.
Alternatives considered: Full competitive item pool; no trainer items at all; theme-gated items per trainer class. The theme-gated approach is partially used (see Eviolite rule below) but the broader "no item soup" principle limits total distribution.
Locked in: Design archive v17, items section.
Eviolite pre-evo exception
Decision: Route trainer Pokémon can hold Eviolite only if the species has an available evolution in the regional dex.
Rationale: Eviolite on a species without an evolution is mechanically incoherent — the item's effect depends on being pre-evolution. Restricting it to actual pre-evos prevents illegal-feeling uses and keeps the item thematic.
Alternatives considered: Eviolite banned from trainers entirely; Eviolite allowed on any pre-evo species regardless of regional availability. The "must have evolution in regional dex" rule is stricter than necessary but keeps team-building consistent with what the player could build.
Locked in: Design archive v17.
Trade evolution via held-item toggle
Decision: Species that normally evolve via trade use an in-engine config toggle instead, preserving the evolution trigger without requiring multiplayer.
Rationale: ROM hacks are single-player experiences. Trade evolution as a mechanic assumes networking that the player doesn't have access to. The held-item toggle lets players evolve Kadabra → Alakazam, Haunter → Gengar, Machoke → Machamp, etc. without workarounds.
Alternatives considered: Level-up evolution replacement (changes the species' identity); NPC trade scripts (still single-player but adds story constraint); leave trade evolution as-is (blocks the player entirely). The held-item toggle is cleanest — mechanically preserves intent without story encumbrance.
Locked in: pokeemerald-expansion config, validated in design archive.
ITEM_CANDY_BOX as the cap-bound infinite Rare Candy
Decision: A new key item, ITEM_CANDY_BOX, replaces every Rare Candy gift and pickup in Snow. It functions like vanilla Rare Candy (raises a Pokémon's level by one) but is reusable indefinitely AND is gated by the active zone level cap (refuses use when the holder is already at cap). The bedroom "Box of Candy" pickup gives the player one ITEM_CANDY_BOX on day one and that single item is the entire game's Rare-Candy supply.
Rationale: Two design holes if vanilla Rare Candy stays. (1) Economy abuse — Rare Candy sells for nontrivial PokéDollars in pokeemerald, so any stack a player accumulates becomes free money, defeating Snow's curated economy. (2) Cap circumvention — a Rare Candy stash lets a player over-level between zone-cap fights, breaking the cap system (a core design pillar). Making the source a single non-sellable key item that respects the cap closes both holes while preserving the day-one "found candy in your bedroom" beat (Platinum Kaizo's "Box of Candy under Barry's bed" pattern).
Alternatives considered: (a) Keep vanilla Rare Candy and accept the exploits — rejected; cap system is non-negotiable. (b) Remove all Rare Candy from Snow — rejected; the bedroom-box flavor moment is a locked design beat. (c) Make Rare Candy unsellable but consumable — rejected; some stacks would honor the cap and others would not, depending on when the player acquired them; rule has to be uniform.
Implementation: Deferred to a dedicated session. Touchpoints will be src/data/items.h (item definition), src/data/item_effects.h or pokeemerald-expansion's modern equivalent (custom field-use callback that checks src/caps.c's active cap before allowing the level-up), and a sweep of all existing Rare Candy gifts/pickups in data/maps/ to replace with ITEM_CANDY_BOX or remove. Until then, the bedroom hidden-item gives 1× ITEM_RARE_CANDY as a placeholder so the bedroom interaction is testable.
Locked in: 2026-04-18 (this DECISIONS entry). Bedroom hidden-item placeholder shipped same commit; real ITEM_CANDY_BOX is a tracked deferred task.
Regional & Content
317-species regional dex
Decision: Boralyss regional Pokédex contains 317 species including 104 with custom Hidden Abilities.
Rationale: Large enough to support route variety and team-building diversity; small enough to maintain regional identity and avoid the "every Pokémon everywhere" problem. 317 includes strong ice-type representation, cross-type coverage for balance, and cross-gen picks for narrative scope.
Alternatives considered: Full national dex; sub-200 focused dex; generation-locked dex (Gen 3 only). Mid-range was chosen — the region can feature a handful of each generation's standouts without sprawling.
Locked in: Design archive v17, dex section.
35 boss fights with competitive-grade AI
Decision: 35 total F-list boss fights, split into F1–F16 (0-EV teams for early-game) and F17–F35 (full competitive EVs for late-game).
Rationale: Route trainers provide connective tissue; boss fights provide difficulty spikes. The 0-EV → full-EV escalation aligns with player progression without being arbitrary level-scaling. Every F-list fight has locked species, moves, natures, abilities, items — nothing randomized.
Alternatives considered: Fewer bosses (20 or so) with all competitive EVs; more bosses (50+) with difficulty scaling instead of EV scaling; no EV distinction. The 16/19 split lets early game feel fair-difficult and late game feel brutal-difficult.
Locked in: Design archive v17, bosses section.
Team Veil as antagonist organization
Decision: The region's antagonist team is Team Veil, a fictional organization pursuing Kyurem.
Rationale: Original team identity preserves design flexibility — not tied to existing Team Magma/Aqua/Rocket/etc. lore. Kyurem-focused antagonism aligns with the ice/winter regional theme and gives the story a legendary Pokémon climax.
Alternatives considered: Team Plasma (Gen 5, thematically ice-adjacent); generic bandits; no organized antagonist. Team Plasma was considered but rejected — their Unova-specific lore would either need to be imported (awkward) or ignored (feels wrong). An original team is clean.
Locked in: Design archive v17, story section.
Team Veil uses Magma visual assets as fallback
Decision: Until real Team Veil sprites exist, Team Veil Grunts emit as Team Magma Grunts in-engine. Class: Team Magma, Pic: Magma Grunt M, Music: Magma.
Rationale: Unblocks shipping Team Veil encounters without waiting for art assets. Magma is closest visually (evil-team grunt archetype) and trivially available in pokeemerald-expansion. Revisit when real Veil class assets ship.
Alternatives considered: Team Aqua Grunt (alternate evil-team available); no grunt encounters until art ships (blocks content). Magma was chosen — Aqua has water-theme baggage that clashes with Boralyss's cold/arid character.
Locked in: Commit aa9208a44f (2026-04-12), GRUNT_TEAM_FALLBACK dict pre-loaded "Veil": "Magma".
Boarder/Skier/Miner fall back to Hiker
Decision: Until real Boarder, Skier, and Miner class assets exist, all three trainer classes fall back to Hiker in-engine.
Rationale: Hiker is the generic mountain/outdoor class in pokeemerald-expansion, closest thematic match for Snow's outdoor trainer types. Keeps content shipping without blocking on sprite/music work. Gender-flip to Male accepted as a consequence (Hiker has only Male variant) — revisit when real assets ship.
Alternatives considered: PkmnBreeder (generic but doesn't fit mountain theme); Camper (too warm-region-coded); invent three new classes now. Hiker chosen — single fallback class simplifies tooling and maintains thematic coherence.
Locked in: Commit 592e85b064 (Boarder validated), commit 43ffd4cfb2 (Skier/Miner added, probed R2 commit). CLASS_FALLBACKS dict in tools/snow_port/port_trainers.py.
Engine & Build
Flag ceiling expansion is save-breaking by design
Decision: The expansion of MAX_TRAINERS_COUNT_EMERALD from 864 to 1024 is intentionally save-breaking. Saves from before commit 5ae831757f are incompatible with saves after.
Rationale: Flag space is packed into the SaveBlock1 struct. Expanding the ceiling grows the flag array which grows SaveBlock1 which shifts every subsequent field's offset. Old saves have data at old offsets; new saves have data at new offsets. No migration path within the project's current scope — supporting one would require a save-versioning system that isn't justified during pre-playable development.
Alternatives considered: Stay within 864 trainer ceiling (blocks content beyond ~R5); implement save migration (scope creep, not worth it pre-playable); reserve flag space explicitly with padding (wastes flag slots to avoid a theoretical migration). Save-breaking is the clean pick.
Locked in: Commit 5ae831757f (2026-04-12). Documented in commit body. Save format freeze only becomes a concern if Pokémon Snow ships publicly with save-compatibility guarantees, which is not the current phase.
Tag-double parser deferred to R5-session
Decision: Tag-double pair parsing (R5-5/6, R6, R12, R14) is deferred until the R5 batch is actively being ported. Not bundled with grunt-support work in commit aa9208a44f.
Rationale: Blast-radius isolation. Grunt support is a validated pattern (3 single-grunt instances ship R3). Tag-double parsing is a new structural pattern (sub-labeled tables under a shared ### header). Bundling both risks the tag-double code having a bug that blocks R3 from shipping. Separate commits = independent failure modes.
Alternatives considered: Bundle both in aa9208a44f (couples risk); ship R3 without grunt support and defer all grunts (blocks R3 entirely). Separating was the clean choice.
Locked in: Commit aa9208a44f (2026-04-12), scope note in commit body. To be implemented in the R5-session.
Column-44 alignment for opponents.h defines
Decision: All #define TRAINER_SNOW_* lines in include/constants/opponents.h align the slot number at column 44.
Rationale: Matches pokeemerald-expansion's existing convention for trainer defines in the vanilla block. Preserves visual grep-ability — any line matching /^#define TRAINER_/ has its slot number at the same column regardless of trainer name length.
Alternatives considered: Tab-align (varies by editor); space-align at a different column; no alignment. No alignment was rejected — diff-readability suffers. Different column was rejected — mixing two conventions in one file is worse than picking either consistently. Column 44 matches vanilla.
Locked in: Commit c0fd8e830c (normalization to spec).
Single fallback for grunt team name
Decision: GRUNT_TEAM_FALLBACK is a single dict keyed on team name (e.g., {"Veil": "Magma"}), with Class, Pic, and Music all derived from the resolved team name.
Rationale: One source of truth for the team fallback. Evolving the fallback requires changing one line, not three. Matches the pattern of pokeemerald-expansion's vanilla grunt emission (all three fields derive from team identity).
Alternatives considered: Three separate dicts (GRUNT_CLASS_FALLBACK, GRUNT_PIC_FALLBACK, GRUNT_MUSIC_FALLBACK). Rejected — introduces possibility of inconsistent fallback state (Class says Magma, Music says Aqua) with no enforcement.
Locked in: Commit aa9208a44f.
Workflow & Process
Commit messages never include Co-Authored-By trailers
Decision: Commit messages are exactly what the CEO drafts. No auto-generated attribution trailers, no AI signatures, no emoji signatures, no "Generated with" lines.
Rationale: Git history is project history. Attribution belongs to the project owner. Auto-trailers pollute git log output and encode information that is not meaningful to the project's future.
Alternatives considered: Allow trailers for "commits authored primarily by Claude Code" (introduces inconsistency); allow emoji-only lightweight attribution. Both rejected — simpler and cleaner to have zero attribution beyond git's built-in author field.
Locked in: CLAUDE.md, enforced across all commits in dawnflake-town.
Never && chain make and git commit
Decision: Build and commit are separate shell commands with explicit human approval between. Never write make && git commit.
Rationale: Red builds can't be committed. && chaining tempts "just-commit-anyway" patterns where a broken build silently slips into history. Separate steps force the human to see the build pass before authorizing the commit.
Alternatives considered: Allow chaining for "trivial" changes where build failure is unexpected (drift risk); chain with verification (same risk with extra step). Banning chaining is simple and auditable.
Locked in: CLAUDE.md, tool implementation (tool itself never commits).
Byte-identical round-trip regression gates emit-path refactors
Decision: Any refactor that touches emit_trainer, emit_class, property derivations, or class-fallback logic must pass byte-identical round-trip regression against R1 AND R2 before any new route ships.
Rationale: Refactors that look equivalent in code can produce different output due to whitespace, property-resolution order, or edge cases. Shipped files are ground truth. If new code reproduces them byte-for-byte, refactor is safe. R1 alone is insufficient — R2 is the test that exercises class-fallback paths.
Alternatives considered: Trust code review alone; accept non-identical output if "semantically equivalent." Both rejected — the tool's job is to produce stable output, and byte-identity is the strongest proof.
Locked in: Commit aa9208a44f (first use of the discipline on a real refactor). Pattern documented in METHODOLOGY.md.
Pre-load fallbacks when outcome is known; probe when unknown
Decision: When adding a class or team name fallback, if the outcome is known with certainty (e.g., fictional team with no canonical equivalent in any Pokémon game), pre-load the fallback to skip a failed-build cycle. When outcome is unknown, probe via optimistic emit → build failure → read compiler suggestion → add fallback → re-run.
Rationale: Probing is valuable for real uncertainty (e.g., does pokeemerald-expansion include a class the vanilla game didn't?). Probing where outcome is pre-known is ritual, not discipline — wastes a build cycle and a commit. The probe pattern exists for uncertainty resolution.
Alternatives considered: Always probe (consistent but ritualistic); never probe (risky on unknowns). Mixed discipline based on certainty level is the right balance.
Locked in: Commit aa9208a44f (pre-loaded "Veil": "Magma" without probe since Team Veil is fictional). Pattern documented in METHODOLOGY.md.
Routes ship atomically
Decision: Trainer routes ship as complete batches. A route with N trainers in v17 §20 commits as N trainers or not at all. No "partial R3 with placeholder for R3-5" style commits.
Rationale: Partial commits create debt — a commit labeled "R3" that is actually 4-of-5 trainers is a trap for git bisect and for future sessions reading commit history. Scope creep is the path to forgotten gaps.
Alternatives considered: Ship partials with TODO markers in commit bodies (still debt); ship single trainers per commit (high commit volume for low information). Atomic-route is the right unit.
Locked in: R3 planning session (2026-04-12). R3-5 Veil Grunt shipped in the same commit as R3-1 through R3-4 after tool enhancement unblocked it.
Deferred (Not Yet Decided)
These questions exist in the project but have no locked answer yet. When a session requires one, the CEO decides and the decision moves to the relevant section above.

Save format freeze: if/when Pokémon Snow enters public release, save compatibility may become a constraint. No current plan.
Post-R15 map wiring strategy: Porymap vs. hex editing vs. custom tooling. Defer until data-complete.
Species data port methodology: manual editing vs. tool-assisted vs. scraped from v17. Defer until first species actively being ported.
Real asset pipeline: sprite creation workflow, music composition, sound effect sourcing. Defer to art-asset session.
Balance playtesting methodology: automated trainer-simulation vs. human playthroughs vs. both. Defer until at least R1–R5 has map wiring and is actually playable.
Public release format: patched ROM distribution vs. IPS/UPS patches vs. both. Defer until near-release.
