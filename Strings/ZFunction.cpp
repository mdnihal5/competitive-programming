// Author : md_nihal
// Source/adapted-from: cp-algorithms.com/string/z-function.html
// Replaces the old duplicate z_algo.cpp (broken: class/ctor name mismatch, didn't
// even compile) and Z_fun.cpp (bare free function, collided with the repo's
// no-global-state rule) — merged into one struct-wrapped version.
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

/* ---- SNIPPET START ---- */
struct ZFunction {
    vector<int> z; // z[i] = length of longest common prefix of s and s.substr(i)

    explicit ZFunction(const string &s) : z(s.size(), 0) {
        int n = (int)s.size();
        for (int i = 1, l = 0, r = 0; i < n; i++) {
            if (i < r) z[i] = min(r - i, z[i - l]);
            while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
            if (i + z[i] > r) { l = i; r = i + z[i]; }
        }
    }

    // all starting positions in `text` where `pattern` occurs, O(|pattern|+|text|)
    static vector<int> findOccurrences(const string &pattern, const string &text) {
        ZFunction zf(pattern + '\1' + text); // '\1' assumed absent from real input
        int m = (int)pattern.size();
        vector<int> occ;
        for (int i = m + 1; i < (int)zf.z.size(); i++)
            if (zf.z[i] >= m) occ.push_back(i - m - 1);
        return occ;
    }
};
/* Usage:
 *   ZFunction zf(s);                             // zf.z[i] as above, zf.z[0] left 0
 *   auto occ = ZFunction::findOccurrences(p, t);  // 0-indexed match positions of p in t
 */
/* ---- SNIPPET END ---- */

#ifdef LOCAL_TEST
int32_t main() {
    ZFunction zf("aaaaa");
    vector<int> expected = {0, 4, 3, 2, 1};
    assert(zf.z == expected);

    auto occ = ZFunction::findOccurrences("ab", "ababab");
    vector<int> expOcc = {0, 2, 4};
    assert(occ == expOcc);

    auto none = ZFunction::findOccurrences("xyz", "ababab");
    assert(none.empty());

    cout << "ZFunction OK\n";
}
#endif
