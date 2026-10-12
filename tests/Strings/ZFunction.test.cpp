// ZFunction zf(s): zf.z[i] = LCP(s, s[i..]), z[0] = 0.
// ZFunction::findOccurrences(p, t) -> 0-indexed starts of p in t (assumes char \1 absent from input). O(|p| + |t|).
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

#include "../../lib/Strings/ZFunction.cpp"

int32_t main() {
    mt19937 rng(2);
    for (int iter = 0; iter < 1000; iter++) {
        int k = 1 + rng() % 3;
        string s, pat;
        for (int i = 0, m = rng() % 40; i < m; i++) s += char('a' + rng() % k);
        for (int i = 0, m = 1 + rng() % 5; i < m; i++) pat += char('a' + rng() % k);
        ZFunction zf(s);
        for (int i = 0; i < (int)s.size(); i++) {
            int l = 0;
            if (i) while (i + l < (int)s.size() && s[l] == s[i + l]) l++;
            assert(zf.z[i] == l);
        }
        vector<int> expect;
        for (int i = 0; i + (int)pat.size() <= (int)s.size(); i++) if (s.compare(i, pat.size(), pat) == 0) expect.push_back(i);
        assert(ZFunction::findOccurrences(pat, s) == expect);
    }
    cout << "OK\n";
}
