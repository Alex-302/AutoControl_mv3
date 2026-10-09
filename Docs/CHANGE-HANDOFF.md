# CHANGE-HANDOFF - what a finished change must state

**What this file is:** the checklist for handing a finished change to the next
person - a reviewer or the next agent session. The point is that nobody should
have to rebuild the intent from the diff. A one-line fix gets a short note; a
zone/engine change gets every section. The note goes into the commit body
and/or the dated block of the matching doc (`CHANGELOG.md` for a user-facing
fix, `Docs/TODO-*.md` for an open item).

## 1. What and why

The story in plain words: what was wrong as the user saw it, what happens now,
why it was done this way. Not a file list, not a walk through the diff - the
reviewer reads the diff anyway. If nearby behavior is deliberately left alone
and a reader might expect otherwise, say it in one line.

## 2. Surfaces touched

One table; `-` where nothing changed, "not tested" where it was not exercised.
"Not applicable" is an answer, a blank cell is not.

| Surface | Chrome 148 | Canary | Brave | Opera | Vivaldi |
|---|---|---|---|---|---|
| SW (sw.js / bundle) |  |  |  |  |  |
| Helper (`ac_zone_helper.cs`) |  |  |  |  |  |
| Engine (v19 patch) |  |  |  |  |  |
| Settings UI |  |  |  |  |  |
| Tooling / docs |  |  |  |  |  |

## 3. Validation

Exact commands with the observed result - a command name without a result is
not evidence. The usual minimum:

- `node Test/verify_all.js` - the verdict line (harness + tool inventory, plus
  the byte proof when native files changed);
- for native work, the full proof chain from `Docs/BUILD-NATIVE.md` (hashes
  AND sizes, `PROOF HOLDS`, `ABI AUDIT: OK`);
- after any bundle-list edit, the rebuild + arrow check from
  `Docs/BUNDLE-BUILD.md`.

## 4. Live run

For anything real input can reach, state: the browser build and OS, the
PHYSICAL action (wheel / hotkey / click - the engine drops synthetic input),
and what was observed. The strongest evidence is the SW console marker
(`zones=[...] ∩ [...] → executing/skipped`) plus a negative control over a
point that must stay silent. If the run did not happen, write why and what
stays unverified - a green harness is not a live run.

## 5. Evidence

Keep what lets the next person re-check the claim: the SW console excerpt, a
screenshot for a visual change, before/after numbers for a timing claim, the
helper hash + size when the helper was rebuilt (recorded in
`Test/zone-tests/README.md`). Screenshots and log excerpts belong with the
change or in `Test/` - never in `mv3-build/`, that folder is the shipped
artifact and stays clean.

## 6. Risks and rollback

What can break and how to get back: the previous engine/helper hashes, the
`alive=0` fallback when the helper is missing, the re-deploy steps
(`Test/deploy_patched_engine.ps1`). One line per real risk, not a formality.

## 7. Explicitly not verified

The honest list: which browser, zone or OS was not exercised, and why. An
honest gap is reviewable; a silent one is not.
