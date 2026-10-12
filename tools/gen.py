#!/usr/bin/env python3
"""Regenerates vimrc/UltiSnips/cpp.snippets and INDEX.md from lib/ (code) and tests/ (usage header).

Edit lib/ or the TRIGGERS table below, then run: python3 tools/gen.py
`normal`, `list` and `nCr` snippets are kept verbatim from the existing cpp.snippets.
"""
import re, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
SNIP = ROOT / "vimrc/UltiSnips/cpp.snippets"
INDEX = ROOT / "vimrc/UltiSnips/INDEX.md"
KEEP = {"normal", "list", "nCr"}

# trigger -> (category, lib path, description or None to keep the existing one)
TRIGGERS = {
    "PBDS": ("Templates & data structures", "Templete/PBDS", None),
    "DSU": ("Templates & data structures", "Graphs/DSU", None),
    "Dijkstra": ("Graphs", "Graphs/Dijkstra", None),
    "BellmanFord": ("Graphs", "Graphs/BellmanFord", None),
    "BinaryLift": ("Graphs", "Graphs/BinaryLifting", None),
    "WeightedLCA": ("Graphs", "Trees/WeightedLCA", None),
    "SCC": ("Graphs", "Graphs/SCC", None),
    "Bridges": ("Graphs", "Graphs/BridgesArticulation", None),
    "TopoSort": ("Graphs", "Graphs/TopoSort", None),
    "HLD": ("Graphs", "Graphs/HLD", None),
    "Centroid": ("Graphs", "Graphs/CentroidDecomposition", None),
    "Dinic": ("Graphs", "Graphs/Dinic", None),
    "ZFunction": ("Strings", "Strings/ZFunction", None),
    "KMP": ("Strings", "Strings/KMP", None),
    "SuffixArray": ("Strings", "Strings/SuffixArray", "O(n log n) suffix array + Kasai's LCP"),
    "AhoCorasick": ("Strings", "Strings/AhoCorasick", None),
    "PolyHash": ("Strings", "Strings/PolyHash", None),
    "Trie": ("Strings", "Others/WordTrie", "array trie: insert/erase, count words and prefixes"),
    "ModInt": ("Math", "Maths/ModInt", None),
    "Comb": ("Math", "Maths/Combinatorics", None),
    "CRT": ("Math", "Maths/CRT", None),
    "Totient": ("Math", "Maths/Totient", None),
    "FastPow": ("Math", "Maths/FastPow", None),
    "NTT": ("Math", "Maths/NTT", None),
    "Sieve": ("Math", "Maths/primes", None),
    "SegTree": ("Segment trees", "SegmentTree/SegmentTree", None),
    "LazySegTree": ("Segment trees", "SegmentTree/LazySegmentTree", None),
    "PersistentSegTree": ("Segment trees", "SegmentTree/PersistentSegmentTree", None),
    "MergeSortTree": ("Segment trees", "SegmentTree/MergeSortTree", None),
    "MaxSubarraySeg": ("Segment trees", "SegmentTree/DynamicSubarraySum", None),
    "RangeToggleSum": ("Segment trees", "SegmentTree/RangeToggleSum", None),
    "Fenwick": ("Fenwick trees", "FenwickTree/FenwickTree", None),
    "FenwickRUPQ": ("Fenwick trees", "FenwickTree/FenwickRangeUpdatePointQuery", None),
    "FenwickRURQ": ("Fenwick trees", "FenwickTree/FenwickRangeUpdateRangeQuery", None),
    "Fenwick2D": ("Fenwick trees", "FenwickTree/Fenwick2D", None),
    "SparseTable": ("RMQ", "RMQ/SparseTable", None),
    "RMQ2D": ("RMQ", "RMQ/RMQ2D", None),
    "DigitDP": ("DP scaffolds & optimizations", "DP/DigitDP", None),
    "BitmaskDP": ("DP scaffolds & optimizations", "DP/BitmaskDP", None),
    "SOSDP": ("DP scaffolds & optimizations", "DP/SOSDP", None),
    "DnCOpt": ("DP scaffolds & optimizations", "DP/DivideAndConquerOpt", None),
    "KnuthOpt": ("DP scaffolds & optimizations", "DP/KnuthOpt", None),
    "CHT": ("DP scaffolds & optimizations", "DP/ConvexHullTrick", None),
    "MinStack": ("Misc", "Others/MinStack", None),
    "MinDeque": ("Misc", "Others/MinStack_Mindeque", "O(1) queue with running minimum (sliding window)"),
    "PrefixSuffixMex": ("Misc", "Others/PrefixSuffixMex", None),
    "TernarySearch": ("Misc", "Others/TernarySearch", None),
    "BalMultiset": ("Misc", "Others/BalancedMultiset", "multiset with lower median and sum of |v - median|"),
    "DivWindow": ("Misc", "Others/divisor_window", "n/k minus max block frequency over divisor windows"),
}


def usage(libpath):
    t = ROOT / "tests" / (libpath + ".test.cpp")
    out = []
    for line in t.read_text().splitlines():
        if not line.startswith("//"):
            break
        out.append(line[2:].strip())
    return out


def escape(code):
    return code.replace("\\", "\\\\").replace("$", "\\$").replace("`", "\\`")


def main():
    text = SNIP.read_text()
    blocks = re.findall(r"^snippet (\S+) (\".*?\")(?: (\w+))?\n(.*?)^endsnippet\n", text, re.S | re.M)
    old = {b[0]: b for b in blocks}
    for trig in KEEP:
        if trig not in old:
            sys.exit(f"missing kept snippet {trig}")
    head = text[: text.index("snippet ")]
    out = [head] if head.strip() else []
    for trig in ("normal", "list", "nCr"):
        _, desc, opt, body = old[trig]
        out.append(f"snippet {trig} {desc}{' ' + opt if opt else ''}\n{body}endsnippet\n")

    descs = {}
    for trig, (cat, lib, desc) in TRIGGERS.items():
        d = desc or (old[trig][1].strip('"') if trig in old else None)
        if d is None:
            sys.exit(f"no description for {trig}")
        descs[trig] = d
        code = (ROOT / "lib" / (lib + ".cpp")).read_text().rstrip("\n")
        out.append(f'snippet {trig} "{d}" b\n{escape(code)}\nendsnippet\n')
    SNIP.write_text("\n".join(out))

    idx = INDEX.read_text()
    keep_top = idx[: idx.index("## Templates & data structures")]
    ncr = re.search(r"### `nCr`.*?(?=\n### |\n## |\Z)", idx, re.S).group(0).rstrip() + "\n"
    cats = []
    for trig, (cat, _, _) in TRIGGERS.items():
        if cat not in cats:
            cats.append(cat)
    parts = [keep_top.rstrip() + "\n"]
    for cat in cats:
        parts.append(f"\n## {cat}\n")
        for trig, (c, lib, _) in TRIGGERS.items():
            if c != cat:
                continue
            parts.append(f"\n### `{trig}` — {descs[trig]}\n")
            parts.append("```\n" + "\n".join(usage(lib)) + "\n```\n")
            parts.append(f"Source: `lib/{lib}.cpp`\n")
            if trig == "Comb":
                parts.append("\n" + ncr)
    INDEX.write_text("".join(parts))
    print(f"{len(TRIGGERS)} snippets + {len(KEEP)} kept, INDEX.md rewritten")


main()
