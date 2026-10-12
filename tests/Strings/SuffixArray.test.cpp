// SuffixArray s(str): sa[i] = start of i-th smallest suffix, rnk = inverse of sa,
// lcp[i] = LCP(suffix sa[i], suffix sa[i-1]), lcp[0] = 0. Works for any bytes, any |s| >= 0.
// O(n log n) prefix doubling with counting sort + Kasai. LCP of arbitrary suffixes = range-min of lcp (SparseTable).
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

#include "../../lib/Strings/SuffixArray.cpp"

int32_t main() {
    mt19937 rng(3);
    for (int iter = 0; iter < 1500; iter++) {
        int k = 1 + rng() % (iter % 5 == 0 ? 200 : 3), n = rng() % 50;
        string s;
        for (int i = 0; i < n; i++) s += char(k > 3 ? 1 + rng() % k : 'a' + rng() % k);
        SuffixArray sa(s);
        vector<int> idx(n);
        iota(all(idx), 0);
        sort(all(idx), [&](int a, int b) { return s.substr(a) < s.substr(b); });
        assert(sa.sa == idx);
        for (int i = 0; i < n; i++) {
            assert(sa.rnk[sa.sa[i]] == i);
            int l = 0;
            if (i) while (sa.sa[i] + l < n && sa.sa[i - 1] + l < n && s[sa.sa[i] + l] == s[sa.sa[i - 1] + l]) l++;
            assert(sa.lcp[i] == l);
        }
    }
    SuffixArray b("banana");
    assert((b.sa == vector<int>{5, 3, 1, 0, 4, 2}));
    cout << "OK\n";
}
