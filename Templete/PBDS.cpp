// Author : md_nihal
// Source/adapted-from: standard GCC PBDS idiom (ext/pb_ds), as used across the repo's notes

#include "bits/stdc++.h"
using namespace std;
#define int long long

/* ---- SNIPPET START ---- */
// #undef/redefine around the include: if `int` is already macro'd to `long long`
// (the normal template does this), the substitution reaches INTO these system
// headers too and collides with their own `int`/`long long` specializations --
// a real, reproducible compile error, not a style nitpick. This makes the
// snippet safe to paste either before or after that #define.
#undef int
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define int long long
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template <class Key, class Value, class Cmp = less<Key>>
using ordered_map = tree<Key, Value, Cmp, rb_tree_tag, tree_order_statistics_node_update>;
/* Usage:
 *   ordered_set<int> s;
 *   s.insert(5); s.insert(1); s.insert(3);
 *   s.find_by_order(1);        // iterator to the 2nd smallest (0-indexed) -> 3
 *   s.order_of_key(4);         // count of elements strictly < 4 -> 3
 *   // duplicates collapse in a plain ordered_set (it's a set) -- use ordered_set<pair<int,int>>
 *   // with a unique tiebreaker (e.g. insertion index) if you need multiset behaviour.
 */
/* ---- SNIPPET END ---- */

#ifdef LOCAL_TEST
int32_t main() {
    ordered_set<int> s;
    for (int x : {5, 1, 3, 9, 2}) s.insert(x);
    // sorted order is 1,2,3,5,9
    assert(*s.find_by_order(0) == 1);
    assert(*s.find_by_order(2) == 3);
    assert(*s.find_by_order(4) == 9);
    assert(s.order_of_key(4) == 3);   // {1,2,3} < 4
    assert(s.order_of_key(10) == 5);  // all elements < 10

    ordered_map<int, string> m;
    m[10] = "a"; m[20] = "b"; m[30] = "c";
    assert(m.find_by_order(1)->first == 20);
    assert(m.order_of_key(25) == 2);

    cout << "OK\n";
}
#endif
