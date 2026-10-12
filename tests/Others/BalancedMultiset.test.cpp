// BalancedMultiset s: insert(x), erase(x) (x must be present), size(), median() = LOWER median (sorted[(size-1)/2]),
// query() = sum |v - median| over all elements (the min total cost to make all equal). Sliding-window median/cost.
// All O(log n); median()/query() need a non-empty set.
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

#include "../../lib/Others/BalancedMultiset.cpp"

int32_t main() {
    mt19937 rng(21);
    for (int iter = 0; iter < 300; iter++) {
        BalancedMultiset s;
        multiset<int> ref;
        int range = 1 + rng() % 12;
        for (int step = 0; step < 150; step++) {
            if (ref.empty() || rng() % 5 < 3) { int x = (int)(rng() % (2 * range + 1)) - range; s.insert(x); ref.insert(x); }
            else { auto it = ref.begin(); advance(it, rng() % ref.size()); s.erase(*it); ref.erase(it); }
            assert(s.size() == (int)ref.size());
            if (ref.empty()) continue;
            vector<int> v(all(ref));
            int med = v[(v.size() - 1) / 2], cost = 0;
            for (int x : v) cost += abs(x - med);
            assert(s.median() == med);
            assert(s.query() == cost);
        }
    }
    cout << "OK\n";
}
