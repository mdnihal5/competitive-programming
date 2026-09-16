#!/usr/bin/env bash
# Compiles every template's own LOCAL_TEST harness (fixed cases + brute-force
# stress tests against hundreds of random inputs, embedded right in the .cpp
# file below its SNIPPET markers) and runs it. This is the real regression
# suite -- rerun after any future edit to a template.
#
# Usage: tests/run_all.sh          (from anywhere)

set -u
REPO="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BIN_DIR="$(mktemp -d)"
trap 'rm -rf "$BIN_DIR"' EXIT

pass=0
fail=0
skip=0
failed_files=()

while IFS= read -r -d '' f; do
    rel="${f#"$REPO"/}"
    if ! grep -q 'LOCAL_TEST' "$f"; then
        skip=$((skip + 1))
        continue
    fi

    bin="$BIN_DIR/$(basename "$f").bin"
    if ! g++ -std=c++23 -Wall -Wextra -O2 -DLOCAL_TEST -o "$bin" "$f" 2> "$BIN_DIR/err.txt"; then
        echo "COMPILE FAIL  $rel"
        sed 's/^/    /' "$BIN_DIR/err.txt" | head -20
        fail=$((fail + 1))
        failed_files+=("$rel")
        continue
    fi

    if ! out=$("$bin" 2>&1); then
        echo "RUNTIME FAIL  $rel"
        echo "    $out" | head -20
        fail=$((fail + 1))
        failed_files+=("$rel")
        continue
    fi

    echo "PASS          $rel"
    pass=$((pass + 1))
done < <(find "$REPO" -name '*.cpp' -print0 | sort -z)

echo
echo "== $pass passed, $fail failed, $skip skipped (no LOCAL_TEST harness) =="

if [ "$fail" -gt 0 ]; then
    echo "Failed: ${failed_files[*]}"
    exit 1
fi
exit 0
