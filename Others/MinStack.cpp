class MinStack {
public:
    stack<pair<int,int>> st;
    void push(int new_elem) {
        int new_min = st.empty() ? new_elem : min(new_elem, st.top().second);
        st.push({new_elem, new_min});
    }
    void pop() {
        int removed_element = st.top().first;
        st.pop();
    }
    int top() { return st.top().first; }
    int min() { return st.top().second; }
};
