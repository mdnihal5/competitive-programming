struct SuffixArray {
    int n;
    vector<int> sa, rnk, lcp;

    SuffixArray(const string &s) : n(s.size()), sa(n), rnk(n), lcp(n) {
        int m = 256;
        vector<int> x(n), y(n), c(max(m, n) + 1);
        for (int i = 0; i < n; i++) c[x[i] = (unsigned char)s[i]]++;
        partial_sum(c.begin(), c.begin() + m, c.begin());
        for (int i = n - 1; i >= 0; i--) sa[--c[x[i]]] = i;
        for (int k = 1; k < n; k <<= 1) {
            int p = 0;
            for (int i = n - k; i < n; i++) y[p++] = i;
            for (int i = 0; i < n; i++) if (sa[i] >= k) y[p++] = sa[i] - k;
            fill(c.begin(), c.begin() + m, 0);
            for (int i = 0; i < n; i++) c[x[i]]++;
            partial_sum(c.begin(), c.begin() + m, c.begin());
            for (int i = n - 1; i >= 0; i--) sa[--c[x[y[i]]]] = y[i];
            swap(x, y);
            auto second = [&](int i) { return i + k < n ? y[i + k] : -1; };
            p = 1;
            x[sa[0]] = 0;
            for (int i = 1; i < n; i++) {
                int a = sa[i - 1], b = sa[i];
                x[b] = y[a] == y[b] && second(a) == second(b) ? p - 1 : p++;
            }
            if (p >= n) break;
            m = p;
        }
        for (int i = 0; i < n; i++) rnk[sa[i]] = i;
        for (int i = 0, h = 0; i < n; i++) {
            if (rnk[i] == 0) { h = 0; continue; }
            int j = sa[rnk[i] - 1];
            while (i + h < n && j + h < n && s[i + h] == s[j + h]) h++;
            lcp[rnk[i]] = h;
            if (h) h--;
        }
    }
};
