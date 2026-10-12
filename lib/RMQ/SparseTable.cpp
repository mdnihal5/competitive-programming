template<typename T, typename F>
struct SparseTable {
    vector<vector<T>> sp;
    F combine;

    SparseTable(const vector<T> &a, F combine) : sp(1, a), combine(combine) {
        int n = a.size();
        for (int j = 1; (1 << j) <= n; j++) {
            sp.emplace_back(n - (1 << j) + 1);
            for (int i = 0; i + (1 << j) <= n; i++)
                sp[j][i] = combine(sp[j - 1][i], sp[j - 1][i + (1 << (j - 1))]);
        }
    }

    T query(int l, int r) {
        int k = __lg(r - l + 1);
        return combine(sp[k][l], sp[k][r - (1 << k) + 1]);
    }
};
