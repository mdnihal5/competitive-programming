class MinStack {
  public:
    std::stack<std::pair<int, int>> st;
    void push (int x) {
        int current_min = st.empty() ? x : std::min (x, st.top().second);
        st.push ({x, current_min});
    }
    void pop() {if (!st.empty() ) st.pop(); }
    int top() const { return st.top().first; }
    int getMin() const { return st.top().second; }
    bool empty() const { return st.empty(); }
    int size() const { return st.size(); }
    void swap (MinStack &other) {
        st.swap (other.st);
    }
};
class MinDeque {
  public:
    MinStack l, r, t;
    void rebalance() {
        if (r.empty() ) l.swap (r);

        for (int sz = r.size() / 2; sz--; r.pop() ) t.push (r.top() );

        while (!r.empty() ) l.push (r.top() ), r.pop();

        while (!t.empty() ) r.push (t.top() ), t.pop();
    }
    int getMin() {
        if (l.empty() ) return r.getMin();

        if (r.empty() ) return l.getMin();

        return std::min (l.getMin(), r.getMin() );
    }
    bool empty() { return l.empty() && r.empty(); }
    int size() { return l.size() + r.size(); }
    void push_front (int x) { l.push (x); }
    void push_back (int x) { r.push (x); }
    void pop_front() { if (l.empty() ) rebalance(); l.pop(); }
    void pop_back() { if (r.empty() ) rebalance(); r.pop(); }
    int front() { if (l.empty() ) rebalance(); return l.top(); }
    int back() { if (r.empty() ) rebalance(); return r.top(); }
    void swap (MinDeque &x) { l.swap (x.l), r.swap (x.r); }
};

