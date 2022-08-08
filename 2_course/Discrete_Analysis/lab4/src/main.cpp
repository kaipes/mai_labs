#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

struct TrieNode {
    map<string, TrieNode*> edge;
    TrieNode* outputLink;
    TrieNode* failCon;
    int patternNumber;
    int size;
    bool leaf;
    TrieNode() {
        failCon = nullptr;
        outputLink = nullptr;
        size = 0;
        leaf = false;
    }
};

struct Text {
    string val;
    int lineIdx;
    int valIdx;
    Text(string v, int l, int idx) {
        val = v;
        lineIdx = l;
        valIdx = idx;
    }
};

class Trie{
    public:
        Trie() {
            root = new TrieNode();
        }
        void Add(vector<string>& s, int numberOfPattern) {
            TrieNode* cur = root;
            for (int i = 0; i < s.size(); i++) {
                if (cur->edge.find(s[i]) == cur->edge.end()) {
                    cur->edge[s[i]] = new TrieNode();
                }
                cur = cur->edge[s[i]];
            }
            cur->size = s.size();
            cur->patternNumber = numberOfPattern;
            cur->leaf = true;
        }
        void BuildConnection(TrieNode* root) {
            vector<TrieNode *> bfs;
            bfs.push_back(root);
            while(bfs.size()!=0) {
                TrieNode* cur = bfs.front();
                bfs.erase(bfs.begin());;
                map<string, TrieNode*> :: iterator it;
                for(it = cur->edge.begin(); it != cur->edge.end(); it++) {
                    TrieNode* child = it->second;
                    bfs.push_back(child);
                    TrieNode* mid = cur->failCon;
                    while(child->failCon == nullptr) {
                        if (mid->edge.find(it->first) != mid->edge.end()) {
                            if (mid->edge.find(it->first) != it) {
                                child->failCon = mid->edge.find(it->first)->second;
                            } else {
                                child->failCon = root;
                            }
                        } else if (mid == root) {
                            child->failCon = root;
                        } else {
                            mid = mid->failCon;
                        }
                    }
                    if (child->failCon->leaf) {
                        child->outputLink = child->failCon;
                    } else if (child->failCon != nullptr && child->failCon->outputLink != nullptr) {
                        child->outputLink = child->failCon->outputLink;
                    }
                }
            }
        }
        void Search(TrieNode* cur, vector<Text*>& text, int pos, vector<int>& sizeString) {
            if (pos < text.size()) {
                while(cur->edge.find(text[pos]->val) == cur->edge.end()) {
                    cur = cur->failCon;
                    if (cur == root) {
                        break;
                    }
                }
                if (cur == root && cur->edge.find(text[pos]->val) == cur->edge.end()) {
                    pos++;
                }
                while(pos<text.size() && cur->edge.find(text[pos]->val) != cur->edge.end()) {
                    cur = cur->edge[text[pos]->val];
                    TrieNode* exit = cur;
                    while (exit->outputLink != nullptr) {
                        if  (text[pos]->valIdx - exit->outputLink->size + 1 > 0) {
                            cout << text[pos]->lineIdx << ", " << text[pos]->valIdx - exit->outputLink->size + 1 << ", " << exit->outputLink->patternNumber << endl;
                        } else {
                            int ansLine = text[pos]->lineIdx;
                            int valLine = text[pos]->valIdx;
                            int sizePatten = exit->outputLink->size;
                            if (sizePatten > valLine) {
                                ansLine--;
                                sizePatten-=valLine;
                            }
                            while (sizePatten >= sizeString[ansLine-1]) {
                                sizePatten-=sizeString[ansLine-1];
                                ansLine--;
                            }
                            cout << ansLine <<  ", " << sizeString[ansLine-1] - sizePatten + 1 << ", " << exit->outputLink->patternNumber << endl; 
                        }
                        exit = exit->outputLink;
                    }
                    if (cur->leaf) {
                        if  (text[pos]->valIdx - cur->size + 1  > 0) {
                            cout << text[pos]->lineIdx << ", " << text[pos]->valIdx - cur->size + 1 << ", " << cur->patternNumber << endl;
                        } else {
                            int ansLine = text[pos]->lineIdx;
                            int valLine = text[pos]->valIdx;
                            int sizePatten = cur->size;
                            if (sizePatten > valLine) {
                                ansLine--;
                                sizePatten-=valLine;
                            }
                            while (ansLine>0 && sizePatten > sizeString[ansLine-1]) {
                                sizePatten -= sizeString[ansLine-1];
                                ansLine--;
                            }
                            cout << ansLine <<  ", " << sizeString[ansLine-1] - sizePatten + 1 << ", " << cur->patternNumber << endl; 
                        }
                    }
                    pos++;
                }
                Search(cur, text, pos, sizeString);
            }
        }
        TrieNode* GetRoot() {
            return root;
        }
    private:
        TrieNode* root;  
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    Trie trie;
    trie.GetRoot()->failCon = trie.GetRoot();
    string str, letter;
    vector<string> input;
    vector<Text*> text;
    vector<int> sizeString;
    int numberOfPattern = 1;
    while(getline(cin, str) && str.size()!=0) {
        stringstream readForPattern(str);
        while (readForPattern >> letter) {
            transform(letter.begin(), letter.end(), letter.begin(), ::tolower);
            input.push_back(letter);
        }
        trie.Add(input, numberOfPattern);
        numberOfPattern++;
        input.clear();
    }
    int valIdx = 1;
    int lineIdx = 1;
    while(getline(cin, str)) {
        if (str.size() == 0) {
            lineIdx++;
            sizeString.push_back(0);
            continue;
        }
        stringstream readForText(str);
        while (readForText >> letter) {
            transform(letter.begin(), letter.end(), letter.begin(), ::tolower);
            Text* t = new Text(letter,lineIdx,valIdx);
            text.push_back(t);
            valIdx++;
        }
        sizeString.push_back(valIdx-1);
        valIdx = 1;
        lineIdx++;
    }
    int pos = 0;
    trie.BuildConnection(trie.GetRoot());
    trie.Search(trie.GetRoot(), text, pos, sizeString);
}