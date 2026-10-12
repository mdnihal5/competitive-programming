// minimumOperationsToMakeKPeriodic(word, k)  (LeetCode 3137; k divides |word|): one operation copies a k-block
// over another k-block. Answer = (#blocks) - (frequency of the most common k-block). O(|word|).
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

#include "../../lib/Others/divisor_window.cpp"

int bfs(const string &w, int k) {
    int n = w.size();
    auto periodic = [&](const string &s) {
        for (int i = k; i < n; i += k) if (s.compare(i, k, s, 0, k)) return false;
        return true;
    };
    map<string, int> dist = {{w, 0}};
    queue<string> q;
    q.push(w);
    while (!q.empty()) {
        string s = q.front(); q.pop();
        if (periodic(s)) return dist[s];
        for (int i = 0; i < n; i += k) for (int j = 0; j < n; j += k) if (i != j) {
            string t = s;
            t.replace(i, k, s, j, k);
            if (!dist.count(t)) { dist[t] = dist[s] + 1; q.push(t); }
        }
    }
    return -1;
}

int32_t main() {
    mt19937 rng(51);
    for (int iter = 0; iter < 400; iter++) {
        int k = 1 + rng() % 3, blocks = 1 + rng() % (k == 1 ? 6 : 4), alpha = 2 + rng() % 2;
        string w;
        for (int i = 0; i < k * blocks; i++) w += char('a' + rng() % alpha);
        assert(minimumOperationsToMakeKPeriodic(w, k) == bfs(w, k));
    }
    assert(minimumOperationsToMakeKPeriodic("leetcodeleet", 4) == 1);
    assert(minimumOperationsToMakeKPeriodic("leetcoleet", 2) == 3);
    cout << "OK\n";
}
