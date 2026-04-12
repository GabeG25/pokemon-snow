# Pokémon Snow — Project Files Map

Every location that matters for Pokémon Snow, what lives there, and how Claude Code should treat it. Read this when you need to locate a file or understand what a path represents. Keep in sync with the actual filesystem — update this file when locations change or new ones are added.

Three companion documents live alongside this one:

- `CLAUDE.md` — session rules, trainerproc format spec, build discipline (procedural rulebook)
- `PROJECT_OVERVIEW.md` — what Pokémon Snow is, design vision, mechanical decisions (project context)
- `design-archive/POKEMON_SNOW_RESUME_HANDOFF_v17.md` — canonical design archive (design canon)
- `PROJECT_FILES.md` — this file (filesystem map)

Read order for a fresh Claude Code session: CLAUDE.md → most recent handoff → PROJECT_FILES.md (when path questions arise) → PROJECT_OVERVIEW.md or v17 (when design questions arise).

---

## Repo Root: `~/pokemon-snow/`

The working project. Linux filesystem (WSL Ubuntu), not Windows. Full pokeemerald-expansion source tree with Snow-specific modifications. This is where `make` runs, where `git` history lives, where Claude Code sessions operate.

Absolute path: `/home/gabe/pokemon-snow/`

**Never move this directory.** The build system, tool, and session-continuity infrastructure all depend on files living at expected relative paths from this root.

### Repo Root: Top-Level Project Files

- **`CLAUDE.md`** — Session rules for Claude Code. Role/doctrines, 8 trainerproc format rules, opponents.h layout conventions, class fallbacks table, build-commit discipline, probe methodology, tool invocation syntax, canary verification command, spec hierarchy, locked design decisions, session handoff expectations. Read at every session start. Committed to repo.

- **`PROJECT_OVERVIEW.md`** — Project vision and design context. What Pokémon Snow is, the Boralyss region, story, starters, mechanics, boss fight structure, implementation state, methodology patterns. Read when design context is needed. Committed to repo.

- **`PROJECT_FILES.md`** — This file. Filesystem map. Committed to repo.

- **`pokeemerald.gba`** — The compiled ROM output. Not committed (gitignored). Regenerated every time `make` runs. Current MD5 captured in the most recent handoff as canary.

- **`pokeemerald.elf`** — The compiled ELF binary (pre-GBA-object-copy). Not committed. Used for symbol extraction via `arm-none-eabi-nm`, `arm-none-eabi-objdump`. The compiler-as-oracle methodology relies on reading literal pools from this file.

- **`pokeemerald.map`** — Linker map file. Not committed. Shows every symbol's address. Useful for debugging layout changes. Regenerated on build.

- **`.gitignore`** — Standard ignores plus project-specific entries: `design-archive/` (large markdown archive, tracked separately), `install-devkitpro-pacman` (toolchain installer, not project content). Committed.

- **`Makefile`** — The pokeemerald build system. Unmodified from upstream. Invoked as `make -j$(nproc)`.

### Repo Root: `src/`

Source code. C files, ASM files, data files. This is where engine code lives and where trainer data is emitted.

- **`src/data/trainers.party`** — **Critical.** Trainerproc-format source file listing every trainer in the ROM. Vanilla Emerald trainers followed by all Snow additions. The `port_trainers.py` tool appends to this file. Canary MD5 tracked in every handoff.

- **`src/data/trainers.h`** — Generated from `trainers.party` by trainerproc during build. Do not edit directly. Regenerated every build.

- **`src/data/pokemon/`** — Species data directory. Currently mostly vanilla; Snow's 317-species dex and 104 custom HAs have not yet been ported here. Future batch of work.

- **`src/trainer_slide.c`** — Contains `sTrainerSlides` array (ROM). Sized by `MAX_TRAINERS_COUNT` + 3. Grows automatically when ceiling expands. No manual edits needed during normal porting.

- **`src/save.c`** — Save-system code. Contains static assertions that SaveBlock1 size ≤ sector budget (15,872 bytes). Grep here if saveblock layout changes cause build errors.

- **Everything else under `src/`** — pokeemerald-expansion engine code. Not modified by Snow work unless engine behavior needs changing. Hands off unless there's a specific reason.

### Repo Root: `include/`

Header files. Defines constants, struct layouts, function prototypes.

- **`include/constants/opponents.h`** — **Critical.** Trainer `#define`s, `TRAINERS_COUNT_EMERALD`, `MAX_TRAINERS_COUNT_EMERALD`. The tool inserts new trainer defines here and auto-maintains the count + warning comment. Column-aligned at slot column 44 (convention locked by commit c0fd8e830c). Canary MD5 tracked in every handoff.

- **`include/constants/flags.h`** — Flag-space definitions. `TRAINER_FLAGS_START = 0x500`. `TRAINER_FLAGS_END = 0x500 + MAX_TRAINERS_COUNT - 1`. `SYSTEM_FLAGS`, `DAILY_FLAGS_START`, `DAILY_FLAGS_END`, `FLAGS_COUNT` all float relative to `TRAINER_FLAGS_END`. Hex comments at `SYSTEM_FLAGS_START` etc. are stale post-ceiling-expansion (cosmetic only, runtime uses computed values).

- **`include/global.h`** — Saveblock struct definitions. `struct SaveBlock1` contains `u8 flags[NUM_FLAG_BYTES]` where `NUM_FLAG_BYTES = ROUND_BITS_TO_BYTES(FLAGS_COUNT)`. The flag array grows automatically when `MAX_TRAINERS_COUNT_EMERALD` bumps. Current `sizeof(struct SaveBlock1) = 15,588` (measured via compiler-as-oracle, 2026-04-12).

- **Everything else under `include/`** — pokeemerald-expansion headers. Not modified by Snow work.

### Repo Root: `tools/`

Build tools and custom scripts.

- **`tools/snow_port/port_trainers.py`** — **Critical.** The trainer port pipeline. Reads v17 §20, emits trainerproc blocks to `trainers.party` and `#define`s to `opponents.h`. Full safety rails: refuse-on-dirty-tree, MD5 snapshots, ceiling check, post-write verification, make-as-oracle, round-trip validator. Currently handles named trainers, class-fallback trainers, unnamed Team Veil Grunts. Tag-double pairs (R5-5/6, R6, R12, R14) not yet supported — next session's work.
  - Invocation: `python3 tools/snow_port/port_trainers.py --route N [--dry-run|--commit|--dump-parsed]`
  - Committed to repo as commits `aad25a889f` (v1), `512272272a` (regex fix), `aa9208a44f` (grunt support).

- **`tools/trainerproc/trainerproc`** — Upstream binary tool. Parses `trainers.party`, emits `trainers.h`. Not modified. Called automatically by `make`.

- **`tools/scaninc/scaninc`** — Upstream dependency scanner. Used by make. Not modified.

- **`tools/agbcc/`** — ARM GBA C compiler toolchain. Provided by pokeemerald. Not modified.

### Repo Root: `test/`

Test-suite files. Not part of the production ROM build.

- **`test/save.c`** — **Tracked in canary.** Defines `T_SAVEBLOCK1_SIZE` (currently 15,588) and other saveblock size constants. The runtime test suite compares actual `sizeof(struct SaveBlock1)` against these values. Updated when saveblock grows. MD5 tracked in post-ceiling canary.

- **Other test files** — pokeemerald-expansion's standard test suite. Not actively used in Snow development.

### Repo Root: `design-archive/`

Design canon. Gitignored as a directory (too large, tracked-but-not-tracked arrangement — see `.gitignore`). Claude Code can read these freely.

- **`design-archive/POKEMON_SNOW_RESUME_HANDOFF_v17.md`** — **The v17 master.** 4,769 lines. MD5 `6543478428f9ca064b2b8dddf8041875`. Canonical source of truth for:
  - Story bible (Boralyss region, Tyrell/Kyurem arc, Team Veil, rival Asher, Champion Tyrim)
  - All route trainer specs (R1–R15 + Driftrock Isle) in §20
  - All 35 boss fights with competitive movesets
  - 317-species Pokédex with 104 custom Hidden Abilities
  - Custom learnsets
  - Item economy (Dragonforge Dept. Store, Frostbreak Lodge, 22 hidden items)
  - Tag-double encounter specs
  - Mechanical rules (permanent weather, 2× crits, etc.)
  
  When a spec detail is needed, grep this file. Do not assume content — read and verify.

- **`design-archive/POKEMON_SNOW_HANDOFF_NEW_CHAT_v17.md`** — 1,010 lines. Resume wrapper for chat sessions. Less authoritative than the master. Use the master (above) for design canon.

- **`design-archive/`** may contain other historical design documents. Treat the v17 master as canonical; older files are archival.

### Repo Root: `data/`, `graphics/`, `sound/`, etc.

Upstream pokeemerald-expansion content. Not modified by Snow work currently. Will be touched when map wiring, species data port, and art-asset sessions happen in the future.

### Repo Root: `build/`

Generated during `make`. Contains intermediate `.o` object files, preprocessed source, etc. Gitignored. Regenerated every build. Safe to delete and rebuild if anything goes sideways (`make clean && make`).

### Repo Root: `.git/`

Git metadata. **Never modify directly.** `git log --oneline` shows the commit history (current: ~15 commits on branch `dawnflake-town`).

---

## Session Archive: `~/pokemon-snow-handoffs/`

Session-to-session handoff archives. Outside the repo intentionally — these are transient session-continuity artifacts, not project content. Claude Code needs permission to read from this directory each session (it's outside the repo scope).

Absolute path: `/home/gabe/pokemon-snow-handoffs/`

Files are named `YYYY-MM-DD-post-[milestone].md`. Each one is the state-of-the-project snapshot at the end of the session that produced it. The most recent file is what Claude Code should `cat` at session start to load context.

**Current files (as of 2026-04-12):**
- `2026-04-11-post-R2.md` — End of R2 batch ship session
- `2026-04-12-post-ceiling.md` — End of flag-ceiling expansion session  
- `2026-04-12-post-R3.md` — End of R3 batch ship session (most recent)

**Format of each handoff:**
- Current state (branch, HEAD, canary MD5s, counters, shipped routes)
- Commits landed this session
- Design decisions and findings
- CEO decision for next session (A/B options with recommendation)
- Deferred/blocked items
- Progress honesty
- First-action resume verification command
- START HERE section with exact next steps

**Session start ritual:**
