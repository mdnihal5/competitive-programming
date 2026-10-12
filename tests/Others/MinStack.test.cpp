// MinStack ms: push(x), pop(), top(), getMin() (min of whole stack), size(), empty(). All O(1).
// pop/top/getMin on an empty stack is undefined (check empty() first).
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

#include "../../lib/Others/MinStack.cpp"

int32_t main() {
    mt19937 rng(11);
    MinStack ms;
    vector<int> ref;
    for (int iter = 0; iter < 20000; iter++) {
        if (ref.empty() || rng() % 5 < 3) { int x = (int)(rng() % 41) - 20; ms.push(x); ref.push_back(x); }
        else { ms.pop(); ref.pop_back(); }
        assert(ms.empty() == ref.empty() && ms.size() == (int)ref.size());
        if (!ref.empty()) { assert(ms.top() == ref.back()); assert(ms.getMin() == *min_element(all(ref))); }
    }
    cout << "OK\n";
}
