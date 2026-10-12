struct AhoCorasick {
    static constexpr int ALPHA = 26, BASE = 'a';
    struct Node {
        array<int, ALPHA> next;
        int fail = 0, cnt = 0;
        Node() { next.fill(-1); }
    };
    vector<Node> t;

    AhoCorasick() : t(1) {}

    void addPattern(const string &s) {
        int cur = 0;
        for (char c : s) {
            int &nx = t[cur].next[c - BASE];
            if (nx == -1) { nx = t.size(); t.emplace_back(); }
            cur = t[cur].next[c - BASE];
        }
        t[cur].cnt++;
    }

    void build() {
        queue<int> q;
        q.push(0);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (u) t[u].cnt += t[t[u].fail].cnt;
            for (int c = 0; c < ALPHA; c++) {
                int v = t[u].next[c], f = u ? t[t[u].fail].next[c] : 0;
                if (v == -1) t[u].next[c] = f;
                else { t[v].fail = f; q.push(v); }
            }
        }
    }

    int countMatches(const string &text) const {
        int total = 0, cur = 0;
        for (char c : text) { cur = t[cur].next[c - BASE]; total += t[cur].cnt; }
        return total;
    }
};
