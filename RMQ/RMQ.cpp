class RMQ {
    typedef int T;
    T LOG = 17;
    vector<vector<T>> dp; int n;
    vector<int>Log;
    void build(vector<T>&v) {
        for (int i = 2; i < n; i++) Log[i] = Log[i / 2] + 1;
        for (int i = 0; i < n; i++) dp[0][i] = v[i];
        for (int i = 1; i <= LOG; i++) {
            for (int j = 0; (1 << i) + j - 1 <= n; j++) {
                dp[i][j] = min(dp[i - 1][j], dp[i - 1][j + (1 << (i - 1))]);
            }
        }
    }
public:
    RMQ(vector<int>&v, int n) : Log(n + 1), dp(LOG + 1, vector<T>(n + 1)), n(n) {build(v);}
    int query(int l, int r) {
        int k = Log[r - l + 1];
        return min(dp[k][l], dp[k][r - (1 << k) + 1]);
    }
};
