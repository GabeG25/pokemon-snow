# Pokémon Snow — Methodology Reference
Bug-catch lessons, verification patterns, and tactical techniques learned the hard way. When a situation in this file matches what you're doing, apply the pattern. When you discover a new pattern worth preserving, add it here with a commit.
Why This File Exists
Over the first 18 commits of this project, specific anti-patterns and catch-techniques emerged from real bugs that almost shipped. This document preserves them so future sessions don't re-discover them. Each entry below is grounded in an actual incident that happened during development.
Anti-Patterns (Bug Classes Seen in This Project)
Silent sed/regex corruption
What it looks like: A regex operation over a file appears to succeed (no error, exit code 0), but the output has subtle damage — a newline consumed, a define glued to a comment, a column misaligned. The next read of the file looks fine to a skim but fails validation.
Real incident: The LAST_TRAINER_DEFINE_RE pattern used \s*$ to anchor to end-of-line. Under re.MULTILINE, \s matches newlines, so \s* greedily consumed the \n after the last digit. Result: the next inserted #define got written flush against the warning comment. Shipped in commit 43ffd4cfb2, normalized by c32779f6db, root cause fixed by 512272272a.
The catch: After any batch-edit of trainers.party or opponents.h, run cat -A on the affected region to visualize line endings. Look for lines that should have $\n$ but show just $, or #define lines that don't end with $ before the next line's content. Column-44 alignment is also a canary — if a new define doesn't land at column 44, something corrupted the horizontal whitespace.
The prevention: When writing regex for opponents.h or trainers.party modifications, prefer [ \t]*$ over \s*$. The horizontal-whitespace-only character class is explicit and safer.
Confident fabrication in long sessions
What it looks like: After 30+ turns in a session, Claude Code cites a specific number ("the header says const u32 size = 227708") or a specific file content that sounds authoritative but was never actually read in the current session. The number feels remembered but is fabricated — synthesized from plausible-looking values, not from ground truth.
Real incident: During the flag-ceiling expansion discussion, Claude Code referenced 227708 as a saveblock constant without ever having read a file containing that number. When pressed to cite the source, it could not. The actual value (15588, from Debug_SaveBlock1Size literal pool) was found empirically via objdump.
The catch: When Claude Code cites a specific numeric value, file path, commit hash, or code snippet, check whether it appeared in output during the current session. If the CEO cannot recall seeing it, ask Claude Code to re-derive it or cite the tool invocation that produced it.
The prevention: Claude Code should never cite specific values from memory. Always ground citations in current-session evidence — a file read, a grep result, a git log line, an objdump output. When uncertain, run the tool and read the result rather than asserting from context.
Yes-Man Builder (next-step execution without approval)
What it looks like: Claude Code completes a step, self-validates with a checklist, and queues the next step without CEO approval. The checklist is correct but skips the CEO's review gate.
Real incident: After R3 dry-run appeared clean in summary form, Claude Code was about to run --commit without the CEO having reviewed the full byte output. The count mismatch (R3 should have 5 trainers, preview showed 4) would not have been caught because the summary said "looks right."
The catch: Any step that modifies shipped files (trainers.party, opponents.h, new commits to dawnflake-town) requires explicit CEO approval. A self-checklist is not approval. "Looks right to me" is not approval.
The prevention: Before any write-level operation, surface the full evidence (full dry-run output, full diff, full preview) and halt for CEO review. Do not queue follow-on commands in the same response.
Yes-Man Design (not pushing back on flawed plans)
What it looks like: The CEO proposes something that has a subtle flaw — wrong sequencing, wrong scope, missing a dependency. Claude Code executes because the CEO said so, even though the flaw is visible.
Real incident: The original commit-order plan for R3 batch was "R3 data first, tool enhancement second." This put the repo through a transient state where R3 trainer data existed in the repo but relied on tool code that wasn't yet committed — git bisect through that window would be broken. Reversing to "tool first, R3 second" produces a causal git history.
The catch: When a CEO plan has a visible problem, say so. Explain the flaw, propose the alternative, let the CEO decide. The CEO wants disagreement when it's grounded — that's the entire point of the CTO role.
The prevention: Pause before executing. Check: does this commit order make sense? Is the scope right for one commit? Does git history read causally? If any answer is no, flag it before executing.
Partial Route Commits
What it looks like: Some trainers in a route are ready, others are blocked. Claude Code offers to commit the ready ones as "partial R3" and handle the rest later.
Real incident: R3 had 4 named trainers ready and 1 Team Veil Grunt blocked on tool capability. The tempting option was to ship 4 of 5 as "R3 partial" and fix the grunt later. This would produce a commit labeled "R3 batch port" that was actually incomplete.
The catch: Routes ship atomically. If a route has a blocker, fix the blocker — never ship a partial labeled as complete. A commit body saying "missing R3-5, TBD" is a debt trap.
The prevention: When a scope reveals a gap, expand the scope to include the gap, or defer the whole batch until the gap is closed. Tooling fixes come before data commits that depend on them.
Verification Patterns
Compiler-as-oracle for engine measurements
Pattern: For any sizeof(struct) or layout value in the compiled ELF, extract it empirically from the binary rather than computing via bit math.
Recipe:

Identify a function that uses the value as an immediate operand (e.g., Debug_SaveBlock1Size returns sizeof(struct SaveBlock1))
Find its address: arm-none-eabi-nm pokeemerald.elf | grep SaveBlock1Size
Disassemble the function: arm-none-eabi-objdump -d pokeemerald.elf --disassemble=Debug_SaveBlock1Size
Read the literal pool entry — typically loaded via ldr r0, [pc, #N]
Cross-validate against independent sources (budget arithmetic, T_SAVEBLOCK1_SIZE in test/save.c)

Why: Hand-computed sizes using ROUND_BITS_TO_BYTES macros, field alignment rules, and struct padding rules are error-prone. The compiler already did the computation correctly when it built the ROM. Extract its answer.
Applied: sizeof(struct SaveBlock1) = 15588 extracted this way during flag-ceiling expansion (5ae831757f). Cross-validated against maxSb1Size = 248 << 6 = 15872 and remaining = 142 << 1 = 284 computed values. All three agreed.
Byte-identical round-trip regression
Pattern: After any change to the emitter code path (emit_trainer, emit_class, property derivations, class-fallback logic), run dry-run against every already-shipped route. Each must round-trip byte-identical against its shipped state.
Recipe:
python3 tools/snow_port/port_trainers.py --route 1 --dry-run
python3 tools/snow_port/port_trainers.py --route 2 --dry-run
Expected: R1 round-trip: PASS (3 trainers byte-identical) and R2 round-trip: PASS (4 trainers byte-identical). Anything else halts the session.
Why: A refactor that looks equivalent in the code may produce different output due to whitespace, property-resolution order, or an edge case that only appears on a specific trainer. The shipped files are ground truth — if new code reproduces them byte-for-byte, the refactor is safe. If not, something changed.
Critical: R1 alone is not sufficient. R2 is the test that exercises class-fallback paths (Kai/Mila/Gus → Hiker). A refactor could pass R1 and fail R2 if it broke the fallback logic.
Applied: After grunt-support enhancement (aa9208a44f), both R1 and R2 PASSed byte-identical before R3 was shipped. If either had failed, R3 would have been halted.
Canary MD5 verification at session start
Pattern: Every session begins by computing MD5 of tracked files and comparing against expected values in the most recent handoff. Halt if anything differs.
Recipe:
cd ~/pokemon-snow && git status && git log --oneline -8 && md5sum pokeemerald.gba src/data/trainers.party include/constants/opponents.h test/save.c design-archive/POKEMON_SNOW_RESUME_HANDOFF_v17.md
Why: A session-to-session handoff assumes the repo is in a specific state. If the CEO did any work between sessions that the handoff doesn't capture (an accidental edit, a rebase, a file touch), the session will be operating on false ground. MD5 comparison catches this in under a second.
Rule: Do not proceed with new work if canary verification fails. Reconcile first — either update the handoff to match reality, or restore files to match the handoff, then proceed.
Grep-verify numeric substitutions
Pattern: After any sed or script that edits a numeric value in a header file (TRAINERS_COUNT_EMERALD, MAX_TRAINERS_COUNT_EMERALD), grep-verify the target file contains the expected value before committing.
Recipe:
grep -n "TRAINERS_COUNT_EMERALD" include/constants/opponents.h
Should show lines with expected values. Compare against what the tool claimed to write.
Why: Silent sed failures — where the substitution pattern didn't match and the file is unchanged but exit code is 0 — have happened in this project. Trust-but-verify.
Tactical Techniques
cat -A to reveal invisible corruption
When a file looks right on normal read but something feels off (tool error, round-trip mismatch, column misalignment), run cat -A on the suspicious region. -A shows:

$ at end of each line (if missing, line has no newline)
^I for tabs
M- prefixes for high-bit chars

Glued lines, missing newlines, and whitespace drift become visible immediately.
git diff before git checkout --
Before discarding uncommitted changes with git checkout -- <file>, always git diff <file> first. The discard is irreversible without stash. Twice in this project, legitimate in-progress work was almost lost to reflex discards.
git log --all --oneline -- <file> for file history
When investigating why a file is in a particular state, git log --all --oneline -- <file> shows every commit that touched it across all branches. git log -p -- <file> shows the full diff of every change. These are the primary tools for "how did this file get this way?"
find and ls -la before assuming file state
When Claude Code says "I'll check tools/snow_port/port_trainers.py" — first verify the file exists at that path. ls -la tools/snow_port/ confirms. A missing file means either the path is wrong or the repo state is unexpected; both are halt conditions.
event_scripts.s include ordering matters
When adding new .include directives for map scripts to data/event_scripts.s, place them NEAR THE BEGINNING of the map-scripts section (after the @ comment header, before the vanilla map includes), not at the end. The pokeemerald build pipeline processes event_scripts.s through a multi-stage pipe chain (preproc → cpp → preproc → as). Includes placed at the end of the file (~line 1018+) can be silently truncated by pipe buffer limitations — the preprocessing stages produce correct output but the final assembler never receives the content. This was discovered when 25 Snow map scripts.inc includes placed after the FRLG maps all produced "undefined reference to MapScripts" linker errors despite the preproc stage correctly resolving them. Moving the includes to line 128 (before PetalburgCity) fixed all 25 errors immediately. Clean builds (make clean && make) do not resolve this — the truncation is inherent to the pipe chain at that file size.
Commit Message Standards
Every commit message has a subject line (≤72 chars) and, for non-trivial changes, a body.
Subject format: type(scope): summary

feat(scope): — new capability
fix(scope): — bug fix
chore(scope): — housekeeping, normalization, formatting
docs(scope): — documentation-only change
refactor(scope): — no behavior change, code restructuring

Examples from this project:

feat(snow_port): support unnamed Team Veil Grunt trainers
fix(snow_port): regex \s*$ consumed newlines under re.MULTILINE
chore(flags): expand MAX_TRAINERS_COUNT_EMERALD 864 → 1024 (+160 slots)
docs(CLAUDE): expand to full CTO operating contract

Body format: Wrap at 72 cols. State the problem/motivation, the change, and the validation. Cite specific commits, MD5s, or measurements when relevant. Preserve decision rationale for future sessions reading git log -p.
Never use: Co-Authored-By trailers, emoji, "🤖 Generated with Claude" signatures, or any automated attribution. Commit messages are exactly what the CEO drafts.
Session Discipline
Handoff at session end
Every substantive session produces a handoff file. Minimum sections:

Current state (branch, HEAD, canary MD5s)
Commits landed this session
Decisions and findings with rationale
What remains unfinished
CEO options for next session with recommendation
Deferred/blocked items
First-action verification command
START HERE section with exact next steps

Save to ~/pokemon-snow-handoffs/YYYY-MM-DD-post-[milestone].md.
Resume verification at session start
First action of every session: run the canary command from the most recent handoff. Halt if mismatch. Only after verification passes does real work begin.
Scope discipline
One conceptual unit of work per session. "Ship R3" is a session. "Ship R3 and R4" is two sessions. "Ship R3 and add tag-double support" is two sessions (shipped separately because they commit separately and can fail independently). Scope creep during a session is a cause of bugs.
When Something Goes Wrong
Build fails unexpectedly

Read the compiler error message carefully. It usually identifies the file and line.
Check recent git log — was something just changed that might be related?
Run make clean && make to rule out stale build artifacts.
If still failing, git stash your changes, verify clean repo builds, then git stash pop and narrow the problem.

Round-trip regression fails

Do not proceed with new work. The emitter is producing different output than the shipped state.
Diff the regression output against the shipped file — what changed?
Check the most recent commits to the tool — is there an emit-path change?
Revert the tool change, confirm R1/R2 pass, then re-apply the change incrementally to find the break point.

Canary MD5 mismatch at session start

Do not start new work.
git log --oneline -5 — is HEAD where expected?
git status — any uncommitted changes?
git diff HEAD — what's different?
Reconcile: either the file drifted (restore from commit) or the handoff is stale (update handoff). Do not proceed until the state is understood.

Tool does something unexpected

Do not commit any changes the tool made.
git status and git diff to see what it wrote.
git checkout -- <file> to discard tool output if it's wrong.
Investigate the tool code. The tool is in-repo and all its logic is readable.
If the bug is real, add a test case (a dry-run command that demonstrates it), fix the tool, commit the fix as fix(snow_port): <summary>.

Adding to This File
When a new pattern is discovered — a new bug class, a new verification technique, a new tactical tool — add it here. Format follows the examples above. Commit with a docs(METHODOLOGY): prefix.
