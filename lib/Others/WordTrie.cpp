struct Trie {
    static constexpr int ALPHA = 26, BASE = 'a';
    vector<array<int, ALPHA>> nx;
    vector<int> pass, ends;

    Trie() { newNode(); }

    int newNode() {
        nx.emplace_back();
        nx.back().fill(0);
        pass.push_back(0);
        ends.push_back(0);
        return nx.size() - 1;
    }

    int walk(const string &s) {
        int cur = 0;
        for (char c : s) if (!(cur = nx[cur][c - BASE])) return -1;
        return cur;
    }

    void insert(const string &s) {
        int cur = 0;
        pass[0]++;
        for (char c : s) {
            if (!nx[cur][c - BASE]) { int v = newNode(); nx[cur][c - BASE] = v; }
            cur = nx[cur][c - BASE];
            pass[cur]++;
        }
        ends[cur]++;
    }

    bool search(const string &s) { int v = walk(s); return v >= 0 && ends[v] > 0; }
    bool startsWith(const string &s) { int v = walk(s); return v >= 0 && pass[v] > 0; }

    bool remove(const string &s) {
        if (!search(s)) return false;
        int cur = 0;
        pass[0]--;
        for (char c : s) { cur = nx[cur][c - BASE]; pass[cur]--; }
        ends[cur]--;
        return true;
    }
};
