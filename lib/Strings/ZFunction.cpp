struct ZFunction {
    vector<int> z;

    ZFunction(const string &s) : z(s.size()) {
        int n = s.size();
        for (int i = 1, l = 0, r = 0; i < n; i++) {
            if (i < r) z[i] = min(r - i, z[i - l]);
            while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
            if (i + z[i] > r) l = i, r = i + z[i];
        }
    }

    static vector<int> findOccurrences(const string &pattern, const string &text) {
        ZFunction zf(pattern + '\1' + text);
        int m = pattern.size();
        vector<int> occ;
        for (int i = m + 1; i < (int)zf.z.size(); i++)
            if (zf.z[i] >= m) occ.push_back(i - m - 1);
        return occ;
    }
};
