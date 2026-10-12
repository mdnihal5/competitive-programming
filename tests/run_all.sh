#!/usr/bin/env bash
# Compiles and runs every tests/**/*.test.cpp against its lib/ template.
# Usage: tests/run_all.sh [filter]   (substring of the path, e.g. Graphs/DSU)

set -u
REPO="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BIN_DIR="$(mktemp -d)"
trap 'rm -rf "$BIN_DIR"' EXIT
filter="${1:-}"

pass=0
fail=0
failed=()

while IFS= read -r -d '' f; do
    rel="${f#"$REPO"/}"
    [[ -n "$filter" && "$rel" != *"$filter"* ]] && continue
    bin="$BIN_DIR/$(basename "$f").bin"
    if ! g++ -std=c++23 -Wall -Wextra -O2 -o "$bin" "$f" 2> "$BIN_DIR/err.txt"; then
        echo "COMPILE FAIL  $rel"
        head -20 "$BIN_DIR/err.txt" | sed 's/^/    /'
        fail=$((fail + 1)); failed+=("$rel"); continue
    fi
    if ! out=$("$bin" 2>&1); then
        echo "RUNTIME FAIL  $rel"
        echo "$out" | head -20 | sed 's/^/    /'
        fail=$((fail + 1)); failed+=("$rel"); continue
    fi
    pass=$((pass + 1))
done < <(find "$REPO/tests" -name '*.test.cpp' -print0 | sort -z)

echo "passed $pass, failed $fail"
[[ $fail -eq 0 ]] || { printf '  %s\n' "${failed[@]}"; exit 1; }
