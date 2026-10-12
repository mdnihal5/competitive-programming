// PolyHash h(string) or h(vector<T>) (any integer T, negatives ok); 0-indexed.
// h.get(l, r) inclusive substring hash mod 2^61-1 with a random base per run; h.combine(hashL, hashR, lenR) = hash of concat.
// O(n) build, O(1) get. Every element maps to [1, MOD-1], so [-1, 5] never collides with [5] (old code mapped -1 to 0).
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

#include "../../lib/Strings/PolyHash.cpp"

int32_t main() {
    mt19937 rng(1717);

    // 1. correctness of mulmod against an independent __int128 reference
    for (int i = 0; i < 100000; i++) {
        uint64_t a = rng(), b = rng();
        a %= PolyHash::MOD; b %= PolyHash::MOD;
        __uint128_t ref = (__uint128_t)a * b % PolyHash::MOD;
        assert(PolyHash::mulmod(a, b) == (uint64_t)ref);
    }

    // 2. equal substrings hash equal, different substrings (almost certainly) hash different
    string s;
    for (int i = 0; i < 200; i++) s += char('a' + rng() % 26);
    PolyHash h(s);
    for (int iter = 0; iter < 5000; iter++) {
        int l1 = rng() % s.size(), r1 = rng() % s.size(); if (l1 > r1) swap(l1, r1);
        int l2 = rng() % s.size(), r2 = rng() % s.size(); if (l2 > r2) swap(l2, r2);
        bool sameStr = s.substr(l1, r1 - l1 + 1) == s.substr(l2, r2 - l2 + 1);
        bool sameHash = h.get(l1, r1) == h.get(l2, r2);
        assert(sameStr == sameHash); // exact match required (false positive would be a real collision -- vanishingly unlikely here)
    }

    // 3. adversarial: long run of identical characters -- catches off-by-one in the hash formula
    string rep(500, 'a');
    PolyHash hr(rep);
    for (int len = 1; len <= 500; len++) {
        uint64_t base = hr.get(0, len - 1);
        for (int start = 0; start + len - 1 < 500; start += 37) {
            assert(hr.get(start, start + len - 1) == base);
        }
    }
    for (int l1 = 1; l1 <= 20; l1++)
        for (int l2 = 1; l2 <= 20; l2++)
            if (l1 != l2) assert(hr.get(0, l1 - 1) != hr.get(0, l2 - 1));

    // 4. array hash with negative and large values
    vector<long long> arr(100);
    for (auto &x : arr) x = (long long)(rng() % 2000000000ULL) - 1000000000LL;
    PolyHash ha(arr);
    for (int iter = 0; iter < 2000; iter++) {
        int l1 = rng() % arr.size(), r1 = rng() % arr.size(); if (l1 > r1) swap(l1, r1);
        int l2 = rng() % arr.size(), r2 = rng() % arr.size(); if (l2 > r2) swap(l2, r2);
        bool sameArr = vector<long long>(arr.begin() + l1, arr.begin() + r1 + 1) ==
                        vector<long long>(arr.begin() + l2, arr.begin() + r2 + 1);
        bool sameHash = ha.get(l1, r1) == ha.get(l2, r2);
        assert(sameArr == sameHash);
    }

    // 4b. elements -1 / 0 / MOD-1 must not vanish (regression: -1 used to hash like 0)
    vector<long long> z = {-1, 5};
    vector<long long> w = {5};
    assert(PolyHash(z).get(0, 1) != PolyHash(w).get(0, 0));
    vector<long long> edge = {-1, 0, -1, 0, 0, -1};
    PolyHash he(edge);
    for (int l1 = 0; l1 < 6; l1++) for (int r1 = l1; r1 < 6; r1++)
        for (int l2 = 0; l2 < 6; l2++) for (int r2 = l2; r2 < 6; r2++) {
            bool same = vector<long long>(edge.begin() + l1, edge.begin() + r1 + 1) == vector<long long>(edge.begin() + l2, edge.begin() + r2 + 1);
            assert(same == (he.get(l1, r1) == he.get(l2, r2)));
        }

    // 5. combine() matches a direct hash of the concatenation
    for (int iter = 0; iter < 1000; iter++) {
        int mid = 1 + rng() % (s.size() - 2);
        uint64_t left = h.get(0, mid - 1), right = h.get(mid, s.size() - 1);
        assert(h.combine(left, right, (int)(s.size() - mid)) == h.get(0, s.size() - 1));
    }

    cout << "OK\n";
}
