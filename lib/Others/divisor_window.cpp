int minimumOperationsToMakeKPeriodic(const string &word, int k) {
    unordered_map<string, int> freq;
    int best = 0;
    for (int i = 0; i < (int)word.size(); i += k) best = max(best, ++freq[word.substr(i, k)]);
    return (int)word.size() / k - best;
}
