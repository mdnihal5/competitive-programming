class Trie{
    public:
    map<char, Trie*> next;
    set<pair<int, int>> index;
};
void insert(Trie* root, string &s, int id){
    // reverse(s.begin(), s.end());    // for suffix
    int len = s.size(); root->index.insert({len, id});
    for (auto &e : s){
        if (!root->next[e]) root->next[e] = new Trie();
        root = root->next[e];
        root->index.insert({len, id});
    }
}
int query(Trie* root, string &s){
    // reverse(s.begin(), s.end());   // for suffix
    int len = s.size(), match = 0;
    for (auto &e : s){
        if (!root->next[e]) return root->index.begin()->second;
        root = root->next[e], ++match;
    }
    return root->index.begin()->second;
}
class Solution {
public:
    vector<int> stringIndices(vector<string>& wordsContainer, vector<string>& wordsQuery) {
        Trie* root = new Trie();
        vector<int> ans;
        for (int i = 0; i < wordsContainer.size(); i++) insert(root, wordsContainer[i], i);
        for (auto &e : wordsQuery) ans.push_back(query(root, e));
        return ans;
    }
};
