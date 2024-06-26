class Zalgo{
private:
    string text;
    string pattern;
    vector<int> Z;
    vector<int> calculateZ(const string& s) {
        int n = s.length();
        vector<int> Z(n, 0);
        int l = 0, r = 0;
        for (int i = 1; i < n; ++i) {
            if (i <= r)
                Z[i] = min(r - i + 1, Z[i - l]);
            while (i + Z[i] < n && s[Z[i]] == s[i + Z[i]])
                ++Z[i];
            if (i + Z[i] - 1 > r) {
                l = i;
                r = i + Z[i] - 1;
            }
        }
        return Z;
    }
public:
    ZAlgorithm(const string& txt, const string& pat) : text(txt), pattern(pat) {
        string combined = pattern + "$" + text;
        Z = calculateZ(combined);
    }
    vector<int> findOccurrences() {
        int patternLength = pattern.length();
        vector<int> occurrences;
        for (int i = patternLength + 1; i < Z.size(); ++i) {
            if (Z[i] == patternLength)
                occurrences.push_back(i - patternLength - 1);
        }
        return occurrences;
    }
};

