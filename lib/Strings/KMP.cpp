struct KMP {
    string pat;
    vector<int> pi;

    KMP(const string &pat) : pat(pat), pi(pat.size()) {
        for (int i = 1; i < (int)pat.size(); i++) {
            int j = pi[i - 1];
            while (j && pat[i] != pat[j]) j = pi[j - 1];
            pi[i] = j + (pat[i] == pat[j]);
        }
    }

    vector<int> match(const string &text) const {
        vector<int> occ;
        int m = pat.size(), j = 0;
        for (int i = 0; i < (int)text.size(); i++) {
            while (j && text[i] != pat[j]) j = pi[j - 1];
            j += text[i] == pat[j];
            if (j == m) { occ.push_back(i - m + 1); j = pi[j - 1]; }
        }
        return occ;
    }
};
