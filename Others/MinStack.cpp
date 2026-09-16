// Author : md_nihal
// Source/adapted-from: existing repo (Others/MinStack.cpp) -- fixed a real bug:
// the old version's member function was named min(), which shadows std::min
// inside the class and breaks the unqualified min(a, b) call on the next line.

#include "bits/stdc++.h"
using namespace std;
#define int long long

/* ---- SNIPPET START ---- */
struct MinStack {
    stack<pair<int, int>> st;   // (value, min-so-far)

    void push(int x) {
        int m = st.empty() ? x : min(x, st.top().second);
        st.push({x, m});
    }
    void pop() { st.pop(); }
    int top() { return st.top().first; }
    int getMin() { return st.top().second; }
    bool empty() { return st.empty(); }
};
/* Usage:
 *   MinStack ms;
 *   ms.push(5); ms.push(2); ms.push(7);
 *   ms.getMin();   // 2
 *   ms.pop();      // removes 7, getMin() still 2
 */
/* ---- SNIPPET END ---- */

#ifdef LOCAL_TEST
int32_t main() {
    MinStack ms;
    ms.push(5); assert(ms.getMin() == 5);
    ms.push(2); assert(ms.getMin() == 2);
    ms.push(7); assert(ms.getMin() == 2 && ms.top() == 7);
    ms.pop();   assert(ms.getMin() == 2 && ms.top() == 2);
    ms.pop();   assert(ms.getMin() == 5 && ms.top() == 5);
    ms.push(-3); assert(ms.getMin() == -3);
    cout << "OK\n";
}
#endif
