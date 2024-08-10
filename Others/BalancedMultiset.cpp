// include ordered set macros
class BalancedMultiset {
  private:
    ordered_set<int> s;
    multiset<int> low, high;
    int leftSum = 0, rightSum = 0;
    int k, half;

    void balance() {
        int mid = *s.find_by_order (half);

        while (true) {
            if (!low.empty() && *low.rbegin() > mid) {
                int top = *low.rbegin();
                leftSum -= top; rightSum += top;
                low.erase (low.find (top) ); high.insert (top);

            } else if (!high.empty() && *high.begin() <= mid) {
                int top = *high.begin();
                leftSum += top; rightSum -= top;
                low.insert (top); high.erase (high.find (top) );

            } else {
                break;
            }
        }
    }

  public:
    BalancedMultiset (int windowSize) : k (windowSize), half ( (k + 1) / 2 - 1) {}

    void insert (int x) {
        low.insert (x);
        leftSum += x;
        s.insert (x);
        balance();
    }
    void erase (int x) {
        if (!high.empty() && *high.begin() <= x) {
            high.erase (high.find (x) );
            rightSum -= x;

        } else {
            low.erase (low.find (x) );
            leftSum -= x;
        }

        s.erase (s.upper_bound (x) );
    }
    int median() {
        return *s.find_by_order (half);
    }
    int query() {
        int mid = *s.find_by_order (half);
        int left = low.size() * mid - leftSum;
        int right = rightSum - high.size() * mid;
        return left + right;
    }
};
