// ordered_set<T>: s.find_by_order(k) -> iterator to k-th smallest (0-indexed), s.order_of_key(x) -> #elements < x.
// ordered_map<K,V>: same two calls. A set collapses duplicates: for multiset use ordered_set<pair<int,int>> with a unique id.
// Erase by value: s.erase(x). The #undef/#define int sandwich is required when `int` is already macro-ed to long long.
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

#include "../../lib/Templete/PBDS.cpp"

int32_t main() {
    mt19937 rng(61);
    for (int iter = 0; iter < 200; iter++) {
        ordered_set<int> s;
        set<int> ref;
        ordered_map<int, int> m;
        map<int, int> rm;
        for (int step = 0; step < 150; step++) {
            int x = (int)(rng() % 40) - 20;
            if (rng() % 3) { s.insert(x); ref.insert(x); m[x] = step; rm[x] = step; }
            else { s.erase(x); ref.erase(x); m.erase(x); rm.erase(x); }
            assert(s.size() == ref.size() && m.size() == rm.size());
            int q = (int)(rng() % 44) - 22;
            assert((int)s.order_of_key(q) == (int)distance(ref.begin(), ref.lower_bound(q)));
            assert((int)m.order_of_key(q) == (int)distance(rm.begin(), rm.lower_bound(q)));
            if (!ref.empty()) {
                int k = rng() % ref.size();
                assert(*s.find_by_order(k) == *next(ref.begin(), k));
                assert(m.find_by_order(k)->first == next(rm.begin(), k)->first);
                assert(m.find_by_order(k)->second == next(rm.begin(), k)->second);
            }
        }
    }
    ordered_set<pair<int, int>> ms;
    int id = 0;
    for (int x : {5, 5, 5, 2}) ms.insert({x, id++});
    assert(ms.size() == 4 && ms.order_of_key({5, -1}) == 1 && ms.order_of_key({6, -1}) == 4);
    cout << "OK\n";
}
