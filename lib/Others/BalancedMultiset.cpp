struct BalancedMultiset {
    multiset<int> low, high;
    int lowSum = 0, highSum = 0;

    void balance() {
        while (low.size() > high.size() + 1) {
            auto it = prev(low.end());
            lowSum -= *it; highSum += *it;
            high.insert(*it); low.erase(it);
        }
        while (low.size() < high.size()) {
            auto it = high.begin();
            highSum -= *it; lowSum += *it;
            low.insert(*it); high.erase(it);
        }
    }

    void insert(int x) {
        if (!low.empty() && x > *low.rbegin()) high.insert(x), highSum += x;
        else low.insert(x), lowSum += x;
        balance();
    }

    void erase(int x) {
        if (!low.empty() && x <= *low.rbegin()) low.erase(low.find(x)), lowSum -= x;
        else high.erase(high.find(x)), highSum -= x;
        balance();
    }

    int size() { return low.size() + high.size(); }
    int median() { return *low.rbegin(); }

    int query() {
        int m = median();
        return m * (int)low.size() - lowSum + highSum - m * (int)high.size();
    }
};
