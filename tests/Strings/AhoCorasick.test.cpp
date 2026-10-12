// AhoCorasick ac; ac.addPattern(p) for each pattern; ac.build() ONCE after all adds.
// ac.countMatches(text) = total (overlapping, duplicates-counted) occurrences of all patterns.
// Alphabet is ALPHA/BASE (default a-z); change both constants for another alphabet. O(total + |text|*1).
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

#include "../../lib/Strings/AhoCorasick.cpp"

string rs(mt19937 &rng, int len, int k) { string s; for (int i = 0; i < len; i++) s += char('a' + rng() % k); return s; }

int32_t main() {
    AhoCorasick a1;
    for (string p : {"a", "ab", "bc"}) a1.addPattern(p);
    a1.build();
    assert(a1.countMatches("abc") == 3);
    AhoCorasick a2;
    for (string p : {"he", "she", "his", "hers"}) a2.addPattern(p);
    a2.build();
    assert(a2.countMatches("ushers") == 3);

    mt19937 rng(777);
    for (int iter = 0; iter < 500; iter++) {
        int k = 1 + rng() % 3, np = 1 + rng() % 6;
        vector<string> pats;
        AhoCorasick ac;
        for (int i = 0; i < np; i++) { pats.push_back(rs(rng, 1 + rng() % 5, k)); ac.addPattern(pats.back()); }
        if (rng() % 2) { pats.push_back(pats[0]); ac.addPattern(pats[0]); }
        ac.build();
        string text = rs(rng, rng() % 40, k);
        int expect = 0;
        for (auto &p : pats)
            for (int i = 0; i + (int)p.size() <= (int)text.size(); i++) expect += text.compare(i, p.size(), p) == 0;
        assert(ac.countMatches(text) == expect);
    }
    cout << "OK\n";
}
