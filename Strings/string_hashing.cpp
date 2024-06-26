https://www.codechef.com/problems/BREAKSTRING?tab=statement
https://www.codechef.com/viewsolution/1067616677
class StringHash {
  public:
    const int base = 31;
    const int mod = 1e9 + 9;
    vector<int> hash;
    vector<int> power;
    StringHash (const string &s) {
        int n = s.size();
        hash.resize (n + 1);
        power.resize (n + 1);
        hash[0] = 0;
        power[0] = 1;

        for (int i = 1; i <= n; ++i) {
            hash[i] = (hash[i - 1] * base + (s[i - 1] - 'a' + 1) ) % mod;
            power[i] = (power[i - 1] * base) % mod;
        }
    }

    int getHash (int l, int r) const {
        int result = (hash[r] - hash[l - 1] * power[r - l + 1] % mod + mod) % mod;
        return result;
    }
};
