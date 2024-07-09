https://www.codechef.com/problems/BREAKSTRING?tab=statement
https://www.codechef.com/viewsolution/1067616677


/***
 *
 * 64-bit hashing for vectors or strings
 * Get the forward and reverse hash of any segment
 * Base is chosen randomly to prevent anti-hash cases from being constructed
 *
 * Complexity - O(n) to build, O(1) for each hash query
 *
***/

#include <bits/stdc++.h>


using namespace std;

#define MAXLEN 1000010
constexpr uint64_t prime = (1ULL << 61) - 1;
const uint64_t seed = chrono::system_clock::now().time_since_epoch().count();
const uint64_t base = mt19937_64 (seed) () % (prime / 3) + (prime / 3);
uint64_t base_pow[MAXLEN];
int64_t primemul (uint64_t a, uint64_t b) {
    uint64_t l1 = (uint32_t) a, h1 = a >> 32, l2 = (uint32_t) b, h2 = b >> 32;
    uint64_t l = l1 * l2, m = l1 * h2 + l2 * h1, h = h1 * h2;
    uint64_t ret = (l & prime) + (l >> 61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
    ret = (ret & prime) + (ret >> 61);
    ret = (ret & prime) + (ret >> 61);
    return ret - 1;
}
void init() {
    base_pow[0] = 1;

    for (int i = 1; i < MAXLEN; i++) {
        base_pow[i] = primemul (base_pow[i - 1], base);
    }
}
struct PolyHash {
    /// Remove suff vector and usage if reverse hash is not required for more speed
    vector<int64_t> pref, suff;

    PolyHash() {}

    template <typename T>
    PolyHash (const vector<T> &ar) {
        if (!base_pow[0]) init();

        int n = ar.size();
        assert (n < MAXLEN);
        pref.resize (n + 3, 0), suff.resize (n + 3, 0);

        for (int i = 1; i <= n; i++) {
            pref[i] = primemul (pref[i - 1], base) + ar[i - 1] + 997;

            if (pref[i] >= prime) pref[i] -= prime;
        }

        for (int i = n; i >= 1; i--) {
            suff[i] = primemul (suff[i + 1], base) + ar[i - 1] + 997;

            if (suff[i] >= prime) suff[i] -= prime;
        }
    }
    PolyHash (const string &str)
        : PolyHash (vector<char> (str.begin(), str.end() ) ) {}

    uint64_t hash (int l, int r) {
        int64_t h = pref[r + 1] - primemul (base_pow[r - l + 1], pref[l]);
        return h < 0 ? h + prime : h;
    }

    uint64_t rhash (int l, int r) {
        int64_t h = suff[l + 1] - primemul (base_pow[r - l + 1], suff[r + 2]);
        return h < 0 ? h + prime : h;
    }
    uint64_t combine (uint64_t hash1, uint64_t hash2, int len2) {
        return (primemul (hash1, base_pow[len2]) + hash2) % prime;
    }

};

int main() {
    PolyHash H = PolyHash ("racecar");
    assert (H.hash (0, 6) == H.rhash (0, 6) );
    assert (H.hash (1, 5) != H.rhash (0, 4) );
    assert (H.hash (1, 1) == H.rhash (5, 5) );
    assert (H.hash (1, 1) != H.rhash (5, 6) );
    assert (H.hash (2, 4) == H.rhash (2, 4) );
    H = PolyHash (vector<int> {1, 2, 3, 2, 1});
    assert (H.hash (0, 4) == H.rhash (0, 4) );
    // Example of combining two hashes
    uint64_t hash1 = H.hash (0, 2);
    uint64_t hash2 = H.hash (3, 6);
    uint64_t combined_hash = H.combine (hash1, hash2, 4);
    assert (H.hash (0, 6) == combined_hash);
    cout << combined_hash << endl;

    return 0;
}

