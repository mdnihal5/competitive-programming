// Author : md_nihal
// Source/adapted-from: existing repo (problmes_with_templetes.txt PolyHash), restyled + randomized base
// modulus near 2^61-1 + runtime-randomized base -- resists precomputed anti-hash test cases
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

/* ---- SNIPPET START ---- */
struct PolyHash {
    static constexpr uint64_t MOD = (1ULL << 61) - 1;
    uint64_t base;
    vector<uint64_t> pw, pre;

    static uint64_t mulmod(uint64_t a, uint64_t b) {
        return (uint64_t)((__uint128_t)a * b % MOD);
    }
    static uint64_t randomBase() {
        static mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
        return rng() % (MOD - 256) + 256;
    }
    static uint64_t normalize(long long x) {
        long long m = (long long)MOD;
        x %= m; if (x < 0) x += m;
        return (uint64_t)x + 1;
    }

    template<typename T>
    PolyHash(const vector<T> &a) : base(randomBase()) {
        int n = a.size();
        pw.assign(n + 1, 1);
        pre.assign(n + 1, 0);
        for (int i = 0; i < n; i++) pw[i + 1] = mulmod(pw[i], base);
        for (int i = 0; i < n; i++) {
            uint64_t v = normalize((long long)a[i]);
            pre[i + 1] = mulmod(pre[i], base) + v;
            if (pre[i + 1] >= MOD) pre[i + 1] -= MOD;
        }
    }
    PolyHash(const string &s) : PolyHash(vector<int>(s.begin(), s.end())) {}

    uint64_t get(int l, int r) { // [l, r] inclusive, 0-indexed
        uint64_t res = pre[r + 1] + MOD - mulmod(pw[r - l + 1], pre[l]);
        if (res >= MOD) res -= MOD;
        return res;
    }
    uint64_t combine(uint64_t leftHash, uint64_t rightHash, int rightLen) {
        uint64_t res = mulmod(leftHash, pw[rightLen]) + rightHash;
        if (res >= MOD) res -= MOD;
        return res;
    }
};
/* ---- SNIPPET END ---- */

#ifdef LOCAL_TEST
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

    // 5. combine() matches a direct hash of the concatenation
    for (int iter = 0; iter < 1000; iter++) {
        int mid = 1 + rng() % (s.size() - 2);
        uint64_t left = h.get(0, mid - 1), right = h.get(mid, s.size() - 1);
        assert(h.combine(left, right, (int)(s.size() - mid)) == h.get(0, s.size() - 1));
    }

    cout << "OK\n";
}
#endif
