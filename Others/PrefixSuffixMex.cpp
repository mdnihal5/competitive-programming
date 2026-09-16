// Author : md_nihal
// Source/adapted-from: existing repo (Others/PrefixSuffixMex.cpp) -- the old version
// was a bare code fragment relying on the removed `vi` macro and external arr/n
// variables; wrapped into a real self-contained function.

#include "bits/stdc++.h"
using namespace std;
#define int long long

/* ---- SNIPPET START ---- */
// preMex[i] = mex of arr[0..i], suffMex[i] = mex of arr[i..n-1]
pair<vector<int>, vector<int>> prefixSuffixMex(vector<int> &arr) {
    int n = (int)arr.size();
    vector<int> preMex(n, -1), suffMex(n, -1);

    int mex = 0; set<int> s;
    for (int i = 0; i < n; i++) {
        if (arr[i] >= mex) s.insert(arr[i]);
        while (!s.empty() && *s.begin() == mex) { mex++; s.erase(s.begin()); }
        preMex[i] = mex;
    }

    s.clear(); mex = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (arr[i] >= mex) s.insert(arr[i]);
        while (!s.empty() && *s.begin() == mex) { mex++; s.erase(s.begin()); }
        suffMex[i] = mex;
    }

    return {preMex, suffMex};
}
/* Usage:
 *   auto [preMex, suffMex] = prefixSuffixMex(arr);
 *   preMex[i]   // mex of arr[0..i]
 *   suffMex[i]  // mex of arr[i..n-1]
 */
/* ---- SNIPPET END ---- */

#ifdef LOCAL_TEST
int naiveMex(vector<int> v) {
    sort(v.begin(), v.end());
    int m = 0;
    for (int x : v) { if (x == m) m++; else if (x > m) break; }
    return m;
}

int32_t main() {
    vector<int> arr = {1, 0, 2, 0, 3, 1};
    auto [preMex, suffMex] = prefixSuffixMex(arr);
    int n = (int)arr.size();
    for (int i = 0; i < n; i++) {
        assert(preMex[i] == naiveMex(vector<int>(arr.begin(), arr.begin() + i + 1)));
        assert(suffMex[i] == naiveMex(vector<int>(arr.begin() + i, arr.end())));
    }

    mt19937 rng(42);
    for (int iter = 0; iter < 300; iter++) {
        int n2 = 1 + rng() % 12;
        vector<int> a(n2);
        for (auto &x : a) x = rng() % 8;
        auto [pm, sm] = prefixSuffixMex(a);
        for (int i = 0; i < n2; i++) {
            assert(pm[i] == naiveMex(vector<int>(a.begin(), a.begin() + i + 1)));
            assert(sm[i] == naiveMex(vector<int>(a.begin() + i, a.end())));
        }
    }
    cout << "OK\n";
}
#endif
