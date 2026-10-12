// MergeSortTree t(a): static array, 0-indexed, queries on [l, r] inclusive (no updates).
// countLess(l, r, x) = #a[i] < x; predecessor = largest a[i] <= x else -inf; successor = smallest a[i] >= x else inf.
// Build O(n log n) time+memory, query O(log^2 n). Values must satisfy |a[i]| < inf.
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

#include "../../lib/SegmentTree/MergeSortTree.cpp"

int32_t main() {
    mt19937 rng(6767);
    for (int n = 1; n <= 40; n++) {
        for (int mag : {30LL, 1000000000000LL}) {
            vector<int> a(n);
            for (auto &x : a) x = (int)(rng() % (2 * mag + 1)) - mag;
            MergeSortTree t(a);
            for (int iter = 0; iter < 100; iter++) {
                int l = rng() % n, r = rng() % n; if (l > r) swap(l, r);
                int x = rng() % 3 ? (int)(rng() % (2 * mag + 3)) - mag - 1 : a[rng() % n];
                int ecnt = 0, epred = -inf, esucc = inf;
                for (int i = l; i <= r; i++) {
                    if (a[i] < x) ecnt++;
                    if (a[i] <= x) epred = max(epred, a[i]);
                    if (a[i] >= x) esucc = min(esucc, a[i]);
                }
                assert(t.countLess(l, r, x) == ecnt);
                assert(t.predecessor(l, r, x) == epred);
                assert(t.successor(l, r, x) == esucc);
            }
        }
    }
    cout << "OK\n";
}
