#!/bin/bash
# Exercises ./dsa against throwaway fixtures in topics/99_selftest. Run: tests/dsa_selftest.sh
set -u
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
DSA="$ROOT/dsa"
T="$ROOT/topics/99_selftest"
S="$ROOT/solutions/99_selftest"
ST="$ROOT/.starter/99_selftest"
cleanup() { rm -rf "$T" "$S" "$ST" "$ROOT/.attempts/99_selftest_ok"; rmdir "$ROOT/.attempts" 2>/dev/null; }
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
  printf '#pragma once\ninline int answer() { %s\n}\n' "$2" > "$T/$1/$1.hpp"
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
