https://www.codechef.com/problems/BREAKSTRING?tab=statement
https://www.codechef.com/viewsolution/1067616677

#include <iostream>
#include <vector>
#include <string>
using namespace std;

typedef long long ll;

const int BASE = 31;
const ll MOD = 1e9 + 9;

// Function to compute hash and power values
void computeHashAndPower (const string &s, vector<ll> &hash, vector<ll> &power) {
    int n = s.size();
    hash[0] = 0;
    power[0] = 1;

    for (int i = 1; i <= n; ++i) {
        hash[i] = (hash[i - 1] * BASE + (s[i - 1] - 'a' + 1) ) % MOD;
        power[i] = (power[i - 1] * BASE) % MOD;
    }
}

// Function to get the hash of a substring s[l:r] (1-based)
ll getSubstringHash (const vector<ll> &hash, const vector<ll> &power, int l, int r) {
    ll result = (hash[r] - hash[l - 1] * power[r - l + 1] % MOD + MOD) % MOD;
    return result;
}

int main() {
    int T;
    cin >> T;

    while (T--) {
        string S;
        cin >> S;
        int n = S.size();

        if (n % 2 != 0) {
            // If the length of the string is odd, there are no valid ways to split
            cout << 0 << endl;
            continue;
        }

        int halfN = n / 2;
        vector<ll> prefixHash (n + 1, 0), power (n + 1, 1);
        computeHashAndPower (S, prefixHash, power);

        int ways = 0;

        // Iterate over possible lengths of P
        for (int lenP = 0; lenP <= halfN; ++lenP) {
            ll hashP = getSubstringHash (prefixHash, power, 1, lenP);
            ll hashR = getSubstringHash (prefixHash, power, lenP + halfN + 1, n);

            // Compute hash of P + R
            ll combinedHash = (hashP * power[halfN - lenP] % MOD + hashR) % MOD;

            ll hashQ = getSubstringHash (prefixHash, power, lenP + 1, lenP + halfN);

            if (hashQ == combinedHash) {
                ways++;
            }
        }

        cout << ways << endl;
    }

    return 0;
}

