// MinDeque d (self-contained, two stacks): push_front/push_back(x), pop_front/pop_back(), front(), back(),
// getMin() (min of whole deque), size(), empty(). Amortised O(1) (a one-sided drain splits the stack in half).
// Does not clash with Others/MinStack.cpp. Calls on an empty deque are undefined.
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

#include "../../lib/Others/MinStack_Mindeque.cpp"

int32_t main() {
    mt19937 rng(31);
    for (int iter = 0; iter < 200; iter++) {
        MinDeque d;
        deque<int> ref;
        for (int step = 0; step < 300; step++) {
            int op = rng() % 6, x = (int)(rng() % 31) - 15;
            if (ref.empty() && op >= 2) op %= 2;
            if (op == 0) { d.push_front(x); ref.push_front(x); }
            else if (op == 1) { d.push_back(x); ref.push_back(x); }
            else if (op == 2) { d.pop_front(); ref.pop_front(); }
            else if (op == 3) { d.pop_back(); ref.pop_back(); }
            else if (op == 4) assert(d.front() == ref.front());
            else assert(d.back() == ref.back());
            assert(d.size() == (int)ref.size() && d.empty() == ref.empty());
            if (!ref.empty()) {
                assert(d.getMin() == *min_element(all(ref)));
                assert(d.front() == ref.front() && d.back() == ref.back());
            }
        }
    }
    MinDeque w;
    vector<int> a = {5, 3, 8, 6, 2, 7, 4, 1}, mins;
    for (int i = 0; i < (int)a.size(); i++) {
        w.push_back(a[i]);
        if (i >= 3) w.pop_front();
        if (i >= 2) mins.push_back(w.getMin());
    }
    assert((mins == vector<int>{3, 3, 2, 2, 2, 1}));
    cout << "OK\n";
}
