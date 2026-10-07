# Stage 1b: Tooling and Topic 01 (Tasks 3–4)

Read `00-index.md` first. This stage depends on Tasks 1–2.

---

### Task 3: `./dsa` script, self-test, root README

**Files:**
- Create: `dsa` (executable)
- Create: `tests/dsa_selftest.sh` (executable)
- Create: `README.md`

**Interfaces:**
- Consumes: CMake targets `ex_NN_<name>` / `sol_NN_<name>` with binaries in `build/bin/` (Task 1). `topics/02_arrays_hashing/two_sum` (Task 2).
- Produces (used by every topic task):
  - `./dsa test <topic>[/<ex>] [--solution]`, `./dsa list [topic]`, `./dsa reset <topic>/<ex>`, `./dsa verify [topic] [--starters]`.
  - Result words: `PASS`, `FAIL`, `BUILD-ERROR`, `TIMEOUT`, `CRASH`, `MISSING`, `STARTER-DIFF`, `NO-TODO`, `STUB-<result>`.
  - The final line of `verify` is `verify: OK` or `verify: FAILED`.
  - The env var `DSA_RUN_TIMEOUT` (seconds, default 60).

- [ ] **Step 1: Write the failing self-test `tests/dsa_selftest.sh`**

```bash
#!/bin/bash
# Exercises ./dsa against throwaway fixtures in topics/99_selftest. Run: tests/dsa_selftest.sh
set -u
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
DSA="$ROOT/dsa"
T="$ROOT/topics/99_selftest"
S="$ROOT/solutions/99_selftest"
ST="$ROOT/.starter/99_selftest"
cleanup() { rm -rf "$T" "$S" "$ST" "$ROOT/.attempts/99_selftest_ok"; }
trap cleanup EXIT
cleanup
fails=0

expect() { # <description> <extended regex> <output>
  if printf '%s\n' "$3" | grep -Eq "$2"; then
    echo "ok   $1"
  else
    echo "FAIL $1"; printf '%s\n' "$3" | sed 's/^/       /'; fails=$((fails + 1))
  fi
}

fixture() { # <name> <function body>
  mkdir -p "$T/$1" "$ST/$1"
  printf '#pragma once\ninline int answer() { %s }\n' "$2" > "$T/$1/$1.hpp"
  cp "$T/$1/$1.hpp" "$ST/$1/$1.hpp"
  printf '#include <%s.hpp>\n#include <doctest.h>\nTEST_CASE("answer") { CHECK(answer() == 42); }\n' "$1" > "$T/$1/test.cpp"
}

fixture ok     'return 0; // TODO: implement'
fixture broken 'return this_does_not_compile;'
fixture hang   'volatile bool spin = true; while (spin) {} return 42;'
fixture crash  'int* p = new int[1]; int x = p[1]; delete[] p; return x;'
mkdir -p "$S/ok"
printf '#pragma once\ninline int answer() { return 42; }\n' > "$S/ok/ok.hpp"

expect "list shows untouched stub"         'untouched +99_selftest/ok'          "$("$DSA" list 99)"
expect "failing stub reports FAIL"         '^FAIL +99_selftest/ok$'              "$("$DSA" test 99/ok 2>&1)"
expect "solution passes"                   '^PASS +99_selftest/ok \(solution\)' "$("$DSA" test 99/ok --solution 2>&1)"
expect "compile error reported"            '^BUILD-ERROR +99_selftest/broken'   "$("$DSA" test 99/broken 2>&1)"
expect "compiler output shown"             'this_does_not_compile'               "$("$DSA" test 99/broken 2>&1)"
expect "hang is killed"                    '^TIMEOUT +99_selftest/hang'         "$(DSA_RUN_TIMEOUT=3 "$DSA" test 99/hang 2>&1)"
expect "memory error is CRASH"             '^CRASH +99_selftest/crash'          "$("$DSA" test 99/crash 2>&1)"
expect "topic run continues past failures" '^FAIL +99_selftest/ok$'              "$(DSA_RUN_TIMEOUT=3 "$DSA" test 99 2>&1)"
expect "topic run prints summary"          '0/4 passing'                         "$(DSA_RUN_TIMEOUT=3 "$DSA" test 99 2>&1)"
expect "tab-completed path accepted"       '^FAIL +99_selftest/ok$'              "$("$DSA" test topics/99_selftest/ok/ 2>&1)"
expect "folder-name topic accepted"        '99_selftest/ok'                      "$("$DSA" list 99_selftest)"
expect "works from another directory"      'untouched +99_selftest/ok'          "$(cd / && "$DSA" list 99)"
cp "$S/ok/ok.hpp" "$T/ok/ok.hpp"
expect "edited after change"               'edited +99_selftest/ok'             "$("$DSA" list 99)"
"$DSA" test 99/ok >/dev/null 2>&1
expect "passing after run"                 'passing +99_selftest/ok'            "$("$DSA" list 99)"
expect "reset backs up attempt"            'Saved attempt'                       "$("$DSA" reset 99/ok)"
expect "backup file exists"                '\.hpp$'                              "$(ls "$ROOT/.attempts/99_selftest_ok" 2>&1)"
expect "reset restores stub"               'untouched +99_selftest/ok'          "$("$DSA" list 99)"
expect "verify flags missing solutions"    '^MISSING +99_selftest/broken'       "$(DSA_RUN_TIMEOUT=3 "$DSA" verify 99 2>&1)"
expect "verify fails overall"              'verify: FAILED'                      "$(DSA_RUN_TIMEOUT=3 "$DSA" verify 99 2>&1)"
expect "unknown topic is an error"         "no topic matching '77'"              "$("$DSA" test 77 2>&1)"
expect "two_sum stub fails"                '^FAIL +02_arrays_hashing/two_sum$'   "$("$DSA" test 2/two_sum 2>&1)"
expect "two_sum verifies with starters"    'verify: OK'                          "$("$DSA" verify 02 --starters 2>&1)"

echo
if [ "$fails" -eq 0 ]; then echo "dsa selftest: all passed"; else echo "dsa selftest: $fails failed"; fi
exit "$fails"
```

- [ ] **Step 2: Run it to see it fail**

```bash
chmod +x tests/dsa_selftest.sh && tests/dsa_selftest.sh
```
Expected: every line `FAIL …` (`./dsa` doesn't exist yet), ending in `dsa selftest: 22 failed`.

- [ ] **Step 3: Write `dsa`**

```bash
#!/bin/bash
# dsa: build, run, and manage the C++ DSA exercises. Run `./dsa help` for usage.
# Must stay compatible with macOS's /bin/bash 3.2 (no associative arrays, no ${x,,}).
set -u

ROOT="$(cd "$(dirname "$0")" && pwd)"
BUILD="$ROOT/build"
STATUS="$BUILD/.status"
RUN_TIMEOUT="${DSA_RUN_TIMEOUT:-60}"
CRASH_CODE=86
export ASAN_OPTIONS="${ASAN_OPTIONS:-detect_leaks=0:exitcode=$CRASH_CODE}"
export UBSAN_OPTIONS="${UBSAN_OPTIONS:-print_stacktrace=1:halt_on_error=1:exitcode=$CRASH_CODE}"
LAST_RESULT=""

die() { echo "dsa: $*" >&2; exit 2; }

usage() {
  cat <<'EOF'
Usage:
  ./dsa test <topic>[/<exercise>] [--solution]   build and run tests
  ./dsa list [topic]                             show exercise status
  ./dsa reset <topic>/<exercise>                 back up your attempt and restore the stub
  ./dsa verify [topic] [--starters]              run the tests against the reference solutions
  ./dsa help

<topic> may be 8, 08, 08_linked_lists, or topics/08_linked_lists.
Examples:
  ./dsa test 02/two_sum
  ./dsa test 8
  ./dsa test 02/two_sum --solution
EOF
}

# "./topics/08_x/ex/" -> "08_x/ex"
normalize() {
  local s="${1#./}"
  s="${s#topics/}"
  echo "${s%/}"
}

# Prints the topic folder matching a number or folder name; returns 1 if none match.
resolve_topic() {
  local want="$1" d name
  case "$want" in [0-9]) want="0$want" ;; esac
  for d in "$ROOT"/topics/*/; do
    [ -d "$d" ] || continue
    name="$(basename "$d")"
    if [ "$name" = "$want" ] || [ "${name%%_*}" = "$want" ]; then echo "$name"; return 0; fi
  done
  return 1
}

all_topics() {
  local d
  for d in "$ROOT"/topics/*/; do [ -d "$d" ] && basename "$d"; done
}

exercises_in() {
  local f
  for f in "$ROOT/topics/$1"/*/test.cpp; do [ -e "$f" ] && basename "$(dirname "$f")"; done
}

header_path()  { echo "$ROOT/topics/$1/$2/$2.hpp"; }
starter_path() { echo "$ROOT/.starter/$1/$2/$2.hpp"; }
checksum()     { cksum < "$1" | awk '{print $1 "-" $2}'; }

# Re-runs CMake only when the set of exercises or solutions has changed.
configure() {
  local fp
  mkdir -p "$BUILD"
  fp="$(cd "$ROOT" && ls -1 topics/*/*/test.cpp solutions/*/*/*.hpp 2>/dev/null | cksum)"
  if [ -f "$BUILD/CMakeCache.txt" ] && [ "$fp" = "$(cat "$BUILD/.fingerprint" 2>/dev/null)" ]; then
    return 0
  fi
  if ! cmake -S "$ROOT" -B "$BUILD" -DCMAKE_BUILD_TYPE=Debug >"$BUILD/configure.log" 2>&1; then
    cat "$BUILD/configure.log"
    die "cmake configure failed"
  fi
  echo "$fp" > "$BUILD/.fingerprint"
}

record_status() { # <topic/ex> <checksum> <RESULT>
  local state
  case "$3" in
    PASS) state=passing ;;
    FAIL) state=failing ;;
    *) state="$(echo "$3" | tr '[:upper:]' '[:lower:]')" ;;
  esac
  touch "$STATUS"
  grep -v "^$1 " "$STATUS" > "$STATUS.tmp"
  echo "$1 $2 $state" >> "$STATUS.tmp"
  mv "$STATUS.tmp" "$STATUS"
}

lookup_status() { # <topic/ex> <checksum>
  if [ ! -f "$STATUS" ]; then echo edited; return; fi
  awk -v k="$1" -v c="$2" '$1 == k { found = 1; print ($2 == c ? $3 : "edited") }
                           END { if (!found) print "edited" }' "$STATUS"
}

# Runs a command, killing it with SIGALRM (exit 142) after RUN_TIMEOUT seconds.
run_timed() {
  perl -e 'alarm shift @ARGV; exec @ARGV or die "exec failed: $!\n"' "$RUN_TIMEOUT" "$@"
}

run_one() { # <topic> <exercise> <ex|sol> <verbose 0|1>; sets LAST_RESULT, returns 0 on PASS
  local t="$1" ex="$2" mode="$3" verbose="$4"
  local target="${mode}_${t:0:2}_${ex}"
  local log="$BUILD/logs/$target.log" code=0 suffix=""
  [ "$mode" = sol ] && suffix=" (solution)"
  mkdir -p "$BUILD/logs"
  if ! cmake --build "$BUILD" --target "$target" >"$log" 2>&1; then
    LAST_RESULT=BUILD-ERROR
  else
    if [ "$verbose" = 1 ]; then
      run_timed "$BUILD/bin/$target"; code=$?
    else
      run_timed "$BUILD/bin/$target" >>"$log" 2>&1; code=$?
    fi
    case "$code" in
      0) LAST_RESULT=PASS ;;
      1) LAST_RESULT=FAIL ;;
      142) LAST_RESULT=TIMEOUT ;;
      *) LAST_RESULT=CRASH ;;
    esac
  fi
  if [ "$verbose" = 1 ]; then
    case "$LAST_RESULT" in
      BUILD-ERROR) cat "$log" ;;
      TIMEOUT) echo "Stopped after ${RUN_TIMEOUT}s: an infinite loop, or an algorithm far slower than the target." ;;
      CRASH) echo "The test binary crashed (exit $code). Read the sanitizer report above." ;;
    esac
    echo
  fi
  printf '%-12s %s/%s%s\n' "$LAST_RESULT" "$t" "$ex" "$suffix"
  if [ "$mode" = ex ]; then
    record_status "$t/$ex" "$(checksum "$(header_path "$t" "$ex")")" "$LAST_RESULT"
  fi
  [ "$LAST_RESULT" = PASS ]
}

cmd_test() {
  local spec="" mode=ex arg t ex pass=0 total=0
  for arg in "$@"; do
    case "$arg" in
      --solution) mode=sol ;;
      -*) die "unknown option: $arg" ;;
      *) spec="$(normalize "$arg")" ;;
    esac
  done
  [ -n "$spec" ] || die "usage: ./dsa test <topic>[/<exercise>] [--solution]"
  t="$(resolve_topic "${spec%%/*}")" || die "no topic matching '${spec%%/*}'"
  configure
  case "$spec" in
    */*)
      ex="${spec#*/}"
      [ -f "$ROOT/topics/$t/$ex/test.cpp" ] || die "no exercise '$ex' in $t"
      if [ "$mode" = sol ] && [ ! -f "$ROOT/solutions/$t/$ex/$ex.hpp" ]; then
        die "no reference solution for $t/$ex"
      fi
      run_one "$t" "$ex" "$mode" 1
      ;;
    *)
      for ex in $(exercises_in "$t"); do
        if [ "$mode" = sol ] && [ ! -f "$ROOT/solutions/$t/$ex/$ex.hpp" ]; then continue; fi
        total=$((total + 1))
        run_one "$t" "$ex" "$mode" 0 && pass=$((pass + 1))
      done
      [ "$total" -gt 0 ] || die "$t has no code exercises (see its README.md)"
      echo "$pass/$total passing. Run ./dsa test ${t:0:2}/<exercise> for details."
      [ "$pass" -eq "$total" ]
      ;;
  esac
}

cmd_list() {
  local topics t ex hdr state
  if [ $# -ge 1 ]; then
    topics="$(resolve_topic "$(normalize "$1")")" || die "no topic matching '$1'"
  else
    topics="$(all_topics)"
  fi
  for t in $topics; do
    for ex in $(exercises_in "$t"); do
      hdr="$(header_path "$t" "$ex")"
      if cmp -s "$hdr" "$(starter_path "$t" "$ex")"; then
        state=untouched
      else
        state="$(lookup_status "$t/$ex" "$(checksum "$hdr")")"
      fi
      printf '%-12s %s/%s\n' "$state" "$t" "$ex"
    done
  done
}

cmd_reset() {
  [ $# -eq 1 ] || die "usage: ./dsa reset <topic>/<exercise>"
  local spec t ex hdr starter dir
  spec="$(normalize "$1")"
  case "$spec" in */*) ;; *) die "usage: ./dsa reset <topic>/<exercise>" ;; esac
  t="$(resolve_topic "${spec%%/*}")" || die "no topic matching '${spec%%/*}'"
  ex="${spec#*/}"
  hdr="$(header_path "$t" "$ex")"
  starter="$(starter_path "$t" "$ex")"
  [ -f "$starter" ] || die "no starter copy for $t/$ex"
  if cmp -s "$hdr" "$starter"; then echo "$t/$ex is already the untouched stub."; return 0; fi
  dir="$ROOT/.attempts/${t}_${ex}"
  mkdir -p "$dir"
  cp "$hdr" "$dir/$(date +%Y%m%d-%H%M%S).hpp"
  cp "$starter" "$hdr"
  echo "Saved attempt to .attempts/${t}_${ex}/ and restored the stub for $t/$ex."
}

cmd_verify() {
  local topics="" starters=0 arg t ex hdr fail=0
  for arg in "$@"; do
    case "$arg" in
      --starters) starters=1 ;;
      -*) die "unknown option: $arg" ;;
      *) topics="$(resolve_topic "$(normalize "$arg")")" || die "no topic matching '$arg'" ;;
    esac
  done
  [ -n "$topics" ] || topics="$(all_topics)"
  configure
  for t in $topics; do
    for ex in $(exercises_in "$t"); do
      if [ -f "$ROOT/solutions/$t/$ex/$ex.hpp" ]; then
        run_one "$t" "$ex" sol 0 || fail=1
      else
        printf '%-12s %s/%s\n' MISSING "$t" "$ex"; fail=1
      fi
      [ "$starters" = 1 ] || continue
      hdr="$(header_path "$t" "$ex")"
      if ! cmp -s "$hdr" "$(starter_path "$t" "$ex")"; then
        printf '%-12s %s/%s\n' STARTER-DIFF "$t" "$ex"; fail=1
      elif ! grep -q 'TODO: implement' "$hdr"; then
        printf '%-12s %s/%s\n' NO-TODO "$t" "$ex"; fail=1
      else
        run_one "$t" "$ex" ex 0 >/dev/null
        if [ "$LAST_RESULT" != FAIL ]; then
          printf '%-12s %s/%s\n' "STUB-$LAST_RESULT" "$t" "$ex"; fail=1
        fi
      fi
    done
  done
  if [ "$fail" -eq 0 ]; then echo "verify: OK"; else echo "verify: FAILED"; fi
  return "$fail"
}

cmd="${1:-help}"
[ $# -gt 0 ] && shift
case "$cmd" in
  test) cmd_test "$@" ;;
  list) cmd_list "$@" ;;
  reset) cmd_reset "$@" ;;
  verify) cmd_verify "$@" ;;
  help|-h|--help) usage ;;
  *) usage >&2; exit 2 ;;
esac
```

- [ ] **Step 4: Run the self-test**

```bash
chmod +x dsa && tests/dsa_selftest.sh
```
Expected: 22 `ok` lines and `dsa selftest: all passed`.

If "failing stub reports FAIL" reports `CRASH` instead, doctest is not exiting with code 1 on failure. Print the actual code with `build/bin/ex_99_ok; echo $?` (re-create the fixture by commenting out the `trap` line) and add that code to the `FAIL` arm of `run_one`'s `case`.

- [ ] **Step 5: Write the root `README.md`**

````markdown
# DSA Refresher: C++ Exercises

Hands-on exercises for every topic in [`dsa-refresher-plan.md`](dsa-refresher-plan.md).
Each topic folder has a checklist README; each exercise has a problem statement,
a stub for you to fill in, and a test suite.

## Quick start
```bash
./dsa test 02/two_sum     # build + run one exercise
./dsa test 02             # every exercise in a topic, one line each
./dsa list                # untouched / edited / failing / passing for everything
```
Requirements: Apple clang (Xcode command line tools) and CMake ≥ 3.20. Nothing else to install.

## Working an exercise
1. Read `topics/NN_topic/<name>/PROBLEM.md`. It ends with the target complexity and, where useful, a CLRS pointer.
2. State the brute force and its complexity, then edit `<name>.hpp`. Don't edit `test.cpp`.
3. Run `./dsa test NN/<name>`. The tests cover examples, edge cases, a randomized check
   against brute force, and (for some exercises) a large input that a slow algorithm fails.
4. Stuck for 30–40 minutes? Hints are folded at the bottom of PROBLEM.md. After that, read
   `solutions/NN_topic/<name>/<name>.hpp` and record the missed insight in your error log.

## Re-solving (spaced repetition)
`./dsa reset NN/<name>` saves your current attempt to `.attempts/` and restores the
blank stub, so you can re-solve at ~3 days, ~1 week, and ~3 weeks.

## Result words
| Word | Meaning |
|---|---|
| PASS / FAIL | Tests passed / at least one check failed |
| BUILD-ERROR | Your header doesn't compile; compiler output is shown |
| TIMEOUT | Killed after 60 s (`DSA_RUN_TIMEOUT` overrides): infinite loop or wrong complexity class |
| CRASH | AddressSanitizer / UBSan caught a memory error or undefined behavior; read the report |

## CLRS
Topic READMEs have a "CLRS quick reference" table; PROBLEM.md files point to specific
sections when one directly helps. Every pointer gives both 3e and 4e numbering, the section
title, what to read, a time budget, and a "skip if" check. All of it is optional.

## Layout
`topics/` (your work) · `solutions/` (references; don't peek early) · `common/` (test helpers)
· `.starter/` (pristine stubs used by reset) · `docs/superpowers/` (design spec and build plan)
````

- [ ] **Step 6: Commit**

```bash
git add dsa tests/dsa_selftest.sh README.md
git commit -m "Add dsa helper script, its self-test, and README"
```

---

### Task 4: Topic 01 Complexity worksheet

**Files:**
- Create: `topics/01_complexity/README.md`, `topics/01_complexity/WORKSHEET.md`
- Create: `solutions/01_complexity/ANSWERS.md`

**Interfaces:** None. Topic 01 has no `test.cpp`, so CMake and `./dsa` ignore it (`./dsa test 01` prints "has no code exercises").

- [ ] **Step 1: Write `WORKSHEET.md`**

Each question gets a blank `**Your answer:**` line. The questions, in order:

1. Derive the recurrence and closed-form running time of **merge sort**. Draw the recursion tree and give the per-level cost and the number of levels.
2. **Binary search** on n sorted elements: give the recurrence and the solution, for both the iterative and the recursive version. State the extra space each uses.
3. **Build-heap** (heapify bottom-up): explain why the naive "n sift-downs × O(log n)" bound is loose, and derive O(n) using the sum Σ h · n/2^(h+1).
4. **Recursive Fibonacci**: give the time without memoization (a bound in terms of φ, or at least O(2ⁿ)) and with memoization, and the recursion-stack space for each.
5. Apply the **Master Theorem**, naming the case, to:
   - (a) T(n)=2T(n/2)+n
   - (b) T(n)=T(n/2)+1
   - (c) T(n)=2T(n/2)+1
   - (d) T(n)=4T(n/2)+n
   - (e) T(n)=7T(n/2)+n²
   - (f) T(n)=2T(n/2)+n log n
6. **Amortized analysis**: show that n appends to a dynamic array that doubles when full cost O(n) in total. Then show the total becomes Θ(n²) if the array instead grows by a constant 10 slots each time.
7. **Input-size table**: for a 1-second limit (≈10⁸ simple operations), give the largest n that is practical for O(n!), O(2ⁿ), O(n³), O(n²), O(n log n) and O(n).

At the end, add the plan's instruction: *"From Topic 02 on, write the time and space complexity in a comment before running the tests."*

- [ ] **Step 2: Write `solutions/01_complexity/ANSWERS.md`**

Write a worked derivation for each question. Each must reach these results:

| Q | Result |
|---|---|
| 1 | T(n)=2T(n/2)+Θ(n); log₂n levels × cn per level → Θ(n log n); space Θ(n) for the merge buffer |
| 2 | T(n)=T(n/2)+Θ(1) → Θ(log n); iterative O(1) space, recursive O(log n) stack |
| 3 | Σ_{h=0}^{⌊log n⌋} ⌈n/2^(h+1)⌉·O(h) = O(n · Σ h/2^h) = O(n), since Σ h/2^h = 2 |
| 4 | Naive Θ(φⁿ) ≈ O(1.618ⁿ) time, O(n) stack; memoized Θ(n) time, Θ(n) space |
| 5 | (a) case 2 → Θ(n log n); (b) case 2 → Θ(log n); (c) case 1 → Θ(n); (d) case 1 → Θ(n²); (e) case 1 → Θ(n^log₂7) ≈ Θ(n^2.81); (f) the 3e statement does not apply (f(n) = n log n is not polynomially larger than n); the 4e extended case 2 with k=1 gives Θ(n log² n) |
| 6 | Copies total ≤ n + n/2 + n/4 + … < 2n, so the amortized cost is O(1) per append; with +10 growth, copies = 10+20+…+n ≈ n²/20 = Θ(n²) |
| 7 | n! → ~11; 2ⁿ → ~25; n³ → ~450; n² → ~10⁴; n log n → ~5·10⁶; n → ~10⁸ |

- [ ] **Step 3: Write `topics/01_complexity/README.md`**

Use template D from `00-index.md`, with these differences:
- **Diagnostic:** "Answer questions 1 and 5 of WORKSHEET.md without notes."
- **Implement:** "Complete WORKSHEET.md; check against `solutions/01_complexity/ANSWERS.md` only after finishing." This is the one README allowed to name the solutions path, because there are no tests.
- **CLRS quick reference:**

| When | Read (3e / 4e) | What to read |
|---|---|---|
| Notation feels shaky | Ch. 3 / Ch. 3, "Growth of Functions" / "Characterizing Running Times" | Definitions of O, Ω, Θ only (≈15 min) |
| Q5 | §4.5 / §4.5, "The master method for solving recurrences" | Theorem statement and the worked examples. 4e: note the extended case 2 (≈15 min) |
| Q6 | §17.4 / §16.4, "Dynamic tables" | Table expansion only, skip contraction (≈15 min) |

- [ ] **Step 4: Commit**

```bash
git add topics/01_complexity solutions/01_complexity
git commit -m "Add topic 01 complexity worksheet and answer key"
```
