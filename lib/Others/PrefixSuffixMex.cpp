pair<vector<int>, vector<int>> prefixSuffixMex(const vector<int> &a) {
    int n = a.size();
    auto prefMex = [&](const vector<int> &v) {
        vector<int> res(n);
        vector<char> seen(n + 2);
        for (int i = 0, mex = 0; i < n; i++) {
            if (0 <= v[i] && v[i] <= n) seen[v[i]] = 1;
            while (seen[mex]) mex++;
            res[i] = mex;
        }
        return res;
    };
    vector<int> suf = prefMex(vector<int>(a.rbegin(), a.rend()));
    reverse(all(suf));
    return {prefMex(a), suf};
}
