class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;
    TrieNode() {
        isEndOfWord = false;
    }
};
class Trie {
private:
    TrieNode* root;
    
    bool removeUtil(TrieNode* node, const string& word, int depth) {
        if (!node) return false;
        
        if (depth == word.size()) {
            if (!node->isEndOfWord) return false; 
            node->isEndOfWord = false; 
            
            return node->children.empty();
        }
        char ch = word[depth];
        TrieNode* childNode = node->children[ch];
        
        bool shouldDeleteCurrentNode = removeUtil(childNode, word, depth + 1);
        
        if (shouldDeleteCurrentNode) {
            node->children.erase(ch);
            return node->children.empty() && !node->isEndOfWord;
        }
        return false;
    }
    
    bool searchSuffixHelper(TrieNode* node, const string& suffix) {
        if (!node) return false;
        if (suffix.empty()) return node->isEndOfWord;
        char ch = suffix.back();
        if (node->children.find(ch) == node->children.end()) return false;
        return searchSuffixHelper(node->children[ch], suffix.substr(0, suffix.size() - 1));
    }
public:
    Trie() {
        root = new TrieNode();
    }
    
    void insert(const string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            if (node->children.find(ch) == node->children.end()) {
                node->children[ch] = new TrieNode();
            }
            node = node->children[ch];
        }
        node->isEndOfWord = true;
    }
    
    bool search(const string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            if (node->children.find(ch) == node->children.end()) return false;
            node = node->children[ch];
        }
        return node->isEndOfWord;
    }
    
    bool startsWith(const string& prefix) {
        TrieNode* node = root;
        for (char ch : prefix) {
            if (node->children.find(ch) == node->children.end()) return false;
            node = node->children[ch];
        }
        return true;
    }
    
    bool endsWith(const string& suffix) {
        
        return searchSuffixHelper(root, suffix);
    }
    
    void remove(const string& word) {
        removeUtil(root, word, 0);
    }
};
