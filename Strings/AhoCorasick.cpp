// Author : md_nihal
// Source/adapted-from: KACTL strings/AhoCorasick.h (alphabet made a single
// static constexpr pair instead of hardcoded in three places — change ALPHA/BASE
// once, not throughout the file)
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

/* ---- SNIPPET START ---- */
struct AhoCorasick {
    static constexpr int ALPHA = 26, BASE = 'a'; // change both here for a different alphabet

    struct Node {
        array<int, ALPHA> next;
        int fail = 0, cnt = 0; // cnt = number of added patterns ending here or at a fail-suffix of here
        Node() { next.fill(-1); }
    };
    vector<Node> t;

    AhoCorasick() : t(1) {}

    void addPattern(const string &s) {
        int cur = 0;
        for (char c : s) {
            int ch = c - BASE;
            if (t[cur].next[ch] == -1) { t[cur].next[ch] = (int)t.size(); t.emplace_back(); }
            cur = t[cur].next[ch];
        }
        t[cur].cnt++;
    }

    // BFS: builds fail links and turns `next` into the full automaton transition
    // table (the "goto" function) — call once after all addPattern() calls.
    void build() {
        queue<int> q;
        for (int c = 0; c < ALPHA; c++) {
            if (t[0].next[c] == -1) t[0].next[c] = 0;
            else { t[t[0].next[c]].fail = 0; q.push(t[0].next[c]); }
        }
        while (!q.empty()) {
            int u = q.front(); q.pop();
            t[u].cnt += t[t[u].fail].cnt;
            for (int c = 0; c < ALPHA; c++) {
                int v = t[u].next[c];
                if (v == -1) t[u].next[c] = t[t[u].fail].next[c];
                else { t[v].fail = t[t[u].fail].next[c]; q.push(v); }
            }
        }
    }

    // total count of (possibly overlapping) pattern occurrences in text, O(|text|)
    int countMatches(const string &text) const {
        int total = 0, cur = 0;
        for (char c : text) { cur = t[cur].next[c - BASE]; total += t[cur].cnt; }
        return total;
    }
};
/* Usage:
 *   AhoCorasick ac;
 *   for (auto &p : patterns) ac.addPattern(p);
 *   ac.build();
 *   int matches = ac.countMatches(text);
 */
/* ---- SNIPPET END ---- */

#ifdef LOCAL_TEST
int32_t main() {
    AhoCorasick ac;
    for (string p : {"a", "ab", "bc"}) ac.addPattern(p);
    ac.build();
    // "abc": "a"@0, "ab"@0, "bc"@1 -> 3 occurrences
    assert(ac.countMatches("abc") == 3);

    AhoCorasick ac2;
    for (string p : {"he", "she", "his", "hers"}) ac2.addPattern(p);
    ac2.build();
    // "ushers": "she"@1, "he"@2, "hers"@2 -> 3 occurrences
    assert(ac2.countMatches("ushers") == 3);

    cout << "AhoCorasick OK\n";
}
#endif
