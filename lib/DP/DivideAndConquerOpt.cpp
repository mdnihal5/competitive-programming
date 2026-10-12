template <class Cost>
void solveDnC(vector<int> &cur, const vector<int> &prev, int lo, int hi, int optLo, int optHi, Cost cost) {
    if (lo >= hi) return;
    int mid = (lo + hi) / 2;
    pair<int, int> best = {inf, optLo};
    for (int k = optLo; k <= min(mid - 1, optHi); k++)
        best = min(best, {prev[k] + cost(k, mid), k});
    cur[mid] = best.first;
    solveDnC(cur, prev, lo, mid, optLo, best.second, cost);
    solveDnC(cur, prev, mid + 1, hi, best.second, optHi, cost);
}
