// Trie t (lowercase a-z; change ALPHA/BASE for another alphabet): insert(s) (multiset: duplicates counted),
// search(s) exact word, startsWith(prefix), remove(s) -> false if absent (removes one copy).
// O(|s|) each. Nodes are never freed (counters keep it correct), so memory = total inserted length * 26 * 8 bytes.
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

#include "../../lib/Others/WordTrie.cpp"

int32_t main() {
    mt19937 rng(41);
    for (int iter = 0; iter < 300; iter++) {
        Trie t;
        multiset<string> ref;
        auto rs = [&]() { string s; for (int i = 0, m = rng() % 5; i < m; i++) s += char('a' + rng() % 3); return s; };
        for (int step = 0; step < 150; step++) {
            string s = rs();
            int op = rng() % 3;
            if (op == 0) { t.insert(s); ref.insert(s); }
            else if (op == 1) {
                bool had = ref.count(s);
                assert(t.remove(s) == had);
                if (had) ref.erase(ref.find(s));
            }
            string q = rs();
            assert(t.search(q) == (bool)ref.count(q));
            bool pre = false;
            for (auto &w : ref) if (w.compare(0, q.size(), q) == 0) pre = true;
            assert(t.startsWith(q) == pre);
        }
    }
    cout << "OK\n";
}
