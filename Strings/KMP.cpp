// Author : md_nihal
// Source/adapted-from: KACTL strings/KMP.h (restructured to precompute the
// pattern's prefix function once in the constructor, so match() can be called
// against many texts without recomputation — common when one pattern is
// searched across multiple strings in a single problem)
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

/* ---- SNIPPET START ---- */
struct KMP {
    string pat;
    vector<int> pi; // prefix function of pat: pi[i] = longest proper prefix of pat[0..i] that is also a suffix

    explicit KMP(const string &pattern) : pat(pattern), pi(pattern.size(), 0) {
        for (int i = 1; i < (int)pat.size(); i++) {
            int j = pi[i - 1];
            while (j && pat[i] != pat[j]) j = pi[j - 1];
            if (pat[i] == pat[j]) j++;
            pi[i] = j;
        }
    }

    // all 0-indexed starting positions in text where pat occurs, O(|text|)
    vector<int> match(const string &text) const {
        vector<int> occ;
        int m = (int)pat.size(), j = 0;
        for (int i = 0; i < (int)text.size(); i++) {
            while (j && text[i] != pat[j]) j = pi[j - 1];
            if (text[i] == pat[j]) j++;
            if (j == m) { occ.push_back(i - m + 1); j = pi[j - 1]; }
        }
        return occ;
    }
};
/* Usage:
 *   KMP kmp(pattern);
 *   vector<int> occ = kmp.match(text);   // 0-indexed starting positions of pattern in text
 */
/* ---- SNIPPET END ---- */

#ifdef LOCAL_TEST
int32_t main() {
    KMP kmp("ab");
    auto occ = kmp.match("ababab");
    vector<int> expected = {0, 2, 4};
    assert(occ == expected);

    KMP kmp2("aaa");
    auto overlap = kmp2.match("aaaaa"); // overlapping matches must all be found
    vector<int> expOverlap = {0, 1, 2};
    assert(overlap == expOverlap);

    assert(kmp.match("xyz").empty());

    cout << "KMP OK\n";
}
#endif
