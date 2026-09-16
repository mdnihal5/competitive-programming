// Author : md_nihal
// Source/adapted-from: KACTL strings/SuffixArray.h (idea), rewritten with an
// out-of-bounds sentinel rank of -1 instead of appending a sentinel character —
// avoids the usual "input must not contain a NUL byte" restriction entirely.
// O(n log^2 n) via std::sort each doubling round; swap the comparator-sort for a
// counting/radix sort per round (KACTL's actual approach) if n approaches ~1e6+
// and the TL is tight — this version trades a log factor for being much harder
// to get wrong.
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

/* ---- SNIPPET START ---- */
struct SuffixArray {
    int n;
    vector<int> sa;   // sa[i] = start index of the i-th smallest suffix
    vector<int> rnk;  // rnk[i] = rank of the suffix starting at i (inverse of sa)
    vector<int> lcp;  // lcp[i] = LCP(suffix sa[i], suffix sa[i-1]), lcp[0] = 0

    explicit SuffixArray(const string &s) : n((int)s.size()), sa(n), rnk(n) {
        vector<int> tmp(n);
        iota(sa.begin(), sa.end(), 0);
        for (int i = 0; i < n; i++) rnk[i] = s[i];

        for (int k = 1; k < n; k <<= 1) {
            auto key = [&](int i) { return i + k < n ? rnk[i + k] : -1; };
            auto cmp = [&](int a, int b) {
                if (rnk[a] != rnk[b]) return rnk[a] < rnk[b];
                return key(a) < key(b);
            };
            sort(sa.begin(), sa.end(), cmp);
            tmp[sa[0]] = 0;
            for (int i = 1; i < n; i++) tmp[sa[i]] = tmp[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
            rnk = tmp;
            if (rnk[sa[n - 1]] == n - 1) break;
        }

        lcp.assign(n, 0); // Kasai's algorithm
        int h = 0;
        for (int i = 0; i < n; i++) {
            if (rnk[i] > 0) {
                int j = sa[rnk[i] - 1];
                while (i + h < n && j + h < n && s[i + h] == s[j + h]) h++;
                lcp[rnk[i]] = h;
                if (h > 0) h--;
            } else h = 0;
        }
    }
};
/* Usage:
 *   SuffixArray sa(s);
 *   sa.sa[i]   // i-th suffix in sorted order (start index into s)
 *   sa.rnk[i]  // rank of the suffix starting at i
 *   sa.lcp[i]  // LCP between sa.sa[i] and sa.sa[i-1], for i >= 1 (min-LCP over a
 *              // range of sa.sa via a sparse table on sa.lcp gives LCP of any two suffixes)
 */
/* ---- SNIPPET END ---- */

#ifdef LOCAL_TEST
int32_t main() {
    SuffixArray sa("banana");
    vector<int> expectedSA = {5, 3, 1, 0, 4, 2};
    vector<int> expectedLCP = {0, 1, 3, 0, 0, 2};
    assert(sa.sa == expectedSA);
    assert(sa.lcp == expectedLCP);

    cout << "SuffixArray OK\n";
}
#endif
