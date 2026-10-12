struct MinDeque {
    vector<pair<int, int>> l, r;

    static void push(vector<pair<int, int>> &s, int x) { s.push_back({x, s.empty() ? x : min(x, s.back().second)}); }

    static void refill(vector<pair<int, int>> &empty, vector<pair<int, int>> &full) {
        vector<int> v;
        for (auto &p : full) v.push_back(p.first);
        full.clear();
        int k = (v.size() + 1) / 2;
        for (int i = k - 1; i >= 0; i--) push(empty, v[i]);
        for (int i = k; i < (int)v.size(); i++) push(full, v[i]);
    }

    void push_front(int x) { push(l, x); }
    void push_back(int x) { push(r, x); }
    void pop_front() { front(); l.pop_back(); }
    void pop_back() { back(); r.pop_back(); }
    int front() { if (l.empty()) refill(l, r); return l.back().first; }
    int back() { if (r.empty()) refill(r, l); return r.back().first; }
    int getMin() { return l.empty() ? r.back().second : r.empty() ? l.back().second : min(l.back().second, r.back().second); }
    int size() { return l.size() + r.size(); }
    bool empty() { return l.empty() && r.empty(); }
};
