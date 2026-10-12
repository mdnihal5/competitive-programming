// KMP kmp(pattern) (pattern non-empty); kmp.pi = prefix function.
// kmp.match(text) -> 0-indexed start positions of every (overlapping) occurrence. O(|pat| + |text|).
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

#include "../../lib/Strings/KMP.cpp"

int32_t main() {
    mt19937 rng(1);
    for (int iter = 0; iter < 1000; iter++) {
        int k = 1 + rng() % 3;
        string pat, text;
        for (int i = 0, m = 1 + rng() % 6; i < m; i++) pat += char('a' + rng() % k);
        for (int i = 0, m = rng() % 40; i < m; i++) text += char('a' + rng() % k);
        vector<int> expect;
        for (int i = 0; i + (int)pat.size() <= (int)text.size(); i++) if (text.compare(i, pat.size(), pat) == 0) expect.push_back(i);
        assert(KMP(pat).match(text) == expect);
        vector<int> pi(pat.size());
        for (int i = 0; i < (int)pat.size(); i++)
            for (int l = i; l >= 1; l--) if (pat.compare(0, l, pat, i + 1 - l, l) == 0) { pi[i] = l; break; }
        assert(KMP(pat).pi == pi);
    }
    assert((KMP("aaa").match("aaaaa") == vector<int>{0, 1, 2}));
    cout << "OK\n";
}
