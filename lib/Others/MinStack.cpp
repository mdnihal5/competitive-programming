struct MinStack {
    vector<pair<int, int>> st;

    void push(int x) { st.push_back({x, st.empty() ? x : min(x, st.back().second)}); }
    void pop() { st.pop_back(); }
    int top() { return st.back().first; }
    int getMin() { return st.back().second; }
    int size() { return st.size(); }
    bool empty() { return st.empty(); }
};
