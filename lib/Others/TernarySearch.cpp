template <class F>
int ternarySearchMin(int lo, int hi, F f) {
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (f(mid) <= f(mid + 1)) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}
