#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstring>
using namespace std;

const int T = 2;

struct DictPair {
    string str;
    unsigned long long val;
};


class BNode {
public:
    DictPair key[2*T];
    BNode* child[2*T+1];
    int size = 0;
    bool leaf = true;
    BNode(){
        for (int i = 0;i < 2*T+1; i++) {
            child[i] = nullptr;
        }
    }
};
bool operator>(DictPair &left, DictPair &right) {
    for (int i = 0; i < left.str.size() && i < right.str.size(); i++) {
        if (left.str[i]!=right.str[i]) {
            return left.str[i] > right.str[i];
        }
    }
    return left.str.size() > right.str.size();
}
bool operator<(DictPair &left, DictPair &right) {
    for (int i = 0; i < left.str.size() && i < right.str.size(); i++) {
        if (left.str[i]!=right.str[i]) {
            return left.str[i] < right.str[i];
        }
    }
    return left.str.size() < right.str.size();
}
class BTree {
public:
    BNode* root;
    BTree() {
        root = new BNode;
    }
    ~BTree() {
        DeleteTree(root);
    };
    void Insert(DictPair& value) {
        BNode* result;
        int pos;
        SearchNode(root,value.str, result,pos);
        if (result == nullptr) {
            if (root->size== 2*T - 1) {
                BNode* newRoot = new BNode;
                newRoot->leaf = false;
                newRoot->child[0] = root;
                root = newRoot;
                SplitChild(root, 0);
            }
        InsertNode(root, value);
        }
    }
    void InsertNode(BNode* node, DictPair& value) {
        int index = BinarySearchInNode(node,value);
        if (!node->leaf) {
            if (node->child[index]->size == 2*T-1) {
                SplitChild(node,index);
                if (value > node->key[index])  {
                    index++;
                }
            }
            InsertNode(node->child[index],value);
        } else {
            for (int i = node->size-1; i>=index && value < node->key[i]; i--) {
                node->key[i+1] = node->key[i]; 
            }
            node->key[index] = value;
            node->size++;
       }
    }   
    int BinarySearchInNode(BNode* node, DictPair &value) {
        int left = 0;
        int right = node->size-1;
        if (left == right && node->size!=1) {
            return 0;
        }
        while (left <= right) {
            int mid = (left+right)/2;
            if (node->key[mid] > value) {
                right = mid-1;
            } else {
                left = mid+1;
            }
        }
        return left;
    }
    int BinarySearchInNode(BNode* node, string value) {
        int left = 0;
        int right = node->size-1;
        if (left == right && node->size!=1) {
            return 0;
        }
        while (left <= right) {
            int mid = (left+right)/2;
            if (node->key[mid].str > value) {
                right = mid-1;
            } else {
                left = mid+1;
            }
        }
        return left;
    }
    void SplitChild(BNode* node, int idx) {
        BNode* left = new BNode;
        BNode* right = new BNode;
        BNode* children = node->child[idx];
        left->leaf = children->leaf;
        left->size = T - 1;
        right->leaf = children->leaf;
        right->size = T - 1;
        for (int i = 0; i < T - 1; i++) {
            left->key[i] = children->key[i];
            right->key[i] = children->key[i+T];
        }
        if (!children->leaf) {
            for (int i = 0; i < T; i++) {
                right->child[i] = children->child[i+T];
                children->child[i+T] = nullptr;
                left->child[i] = children->child[i];
            }
        }
        children->size = T - 1;
        for (int i = node->size; i>=idx+1;i--) {
            node->child[i+1] = node->child[i];
            node->child[i] = nullptr;
        }
        // if (node->child[idx + 1] != nullptr) {
        //     DeleteTree(node->child[idx + 1]);
        // }
        node->child[idx] = left;
        node->child[idx+1] = right;
        for (int i = node->size-1; i>=idx;i--) {
            node->key[i+1] = node->key[i];
        }
        node->key[idx]=children->key[T-1];
        for (unsigned long long i = 0; i < 2 * T+1; i++) {
            children->child[i] = nullptr;
        }
        delete children;
        node->size++;
    }
    void DeleteFromNode(BNode* node, int pos) {
        for (int i = pos; i < node->size - 1; i++) {
            node->key[i] = node->key[i + 1];
        }
        if (!node->leaf) {
            for (int i = pos; i < node->size; i++) {
                node->child[i] = node->child[i + 1];
                node->child[i + 1] = nullptr;
            }
            node->child[node->size] = nullptr;
        }
        node->size--;
    }
    void Deleting(BNode* node,string value) {
        BNode* result = nullptr;
        int pos = 0;
        SearchNode(root,value,result,pos);
        if (result != nullptr) {
            if (result == root && result->leaf) { 
                if (result->size == 1) {
                    result->size--;
                } else {
                    DeleteFromNode(result,pos);
                }
                result = nullptr;
            }  else if (result!=nullptr && result!=root &&result->leaf && result->size>=T ) {
                DeleteFromNode(result, pos);
            } else if ((result!=nullptr && !result->leaf && result->size>=T) || ((result == root) && (result->size == T-1))) {
                if (pos >= 0 && pos<= result->size && result->child[pos]!= nullptr && result->child[pos]->size >= T) {
                    DictPair q;
                    BNode* nodest = result->child[pos];
                    while(!nodest->leaf) {
                        nodest = nodest->child[nodest->size];
                    }
                    q.str = nodest->key[nodest->size-1].str;
                    q.val = nodest->key[nodest->size-1].val;
                    Deleting(result,nodest->key[nodest->size-1].str);
                    result->key[pos] = q;
                } else if (pos+1 <=result->size && result->child[pos+1]!=nullptr && result->child[pos+1]->size >= T) {
                    DictPair q;
                    BNode* nodest = result->child[pos+1];
                    while(!nodest->leaf) {
                        nodest = nodest->child[0];
                    }
                   q.str = nodest->key[0].str;
                   q.val = nodest->key[0].val;
                   Deleting(root,nodest->key[0].str);
                   nodest = nullptr;
                   result->key[pos] = q;
                } else if (pos+1 <= result->size && pos>=0 && result->child[pos]!=nullptr && result->child[pos+1]!=nullptr 
                        && result->child[pos]->size == T-1 && result->child[pos+1]->size == T-1) {
                    BNode *left = result->child[pos];
                    BNode *right = result->child[pos + 1];
                    left->key[left->size++] = result->key[pos];
                    for (int i = 0; i < right->size; i++) {
                        left->key[left->size++] = right->key[i];
                    }
                    if (!right->leaf) {
                        for (int i = 0; i <= right->size; i++) {
                            left->child[T + i] = right->child[i];
                            right->child[i] = nullptr;
                        }
                    }
                    right->size = 0;
                    delete right;
                    DeleteFromNode(result, pos);
                    result->child[pos] = left;
                    if (result->size == 0) {
                        BNode* tmp = root->child[0];
                        delete root;
                        root = tmp;
                    }
                    Deleting(root, value);
                } else if (pos+1 == result->size) {
                    result->child[pos-1]->key[T-1] = result->key[pos];
                    for (int i = 0; i < result->child[pos]->size; i++) {
                        result->child[pos-1]->key[T+i] = result->child[pos]->key[i];
                    }
                    for (int i = pos; i < result->size - 1; i++) {
                        result->key[i] = result->key[i + 1];
                    }
                    if (!result->leaf) {
                        for (int i = pos+1; i < result->size; i++) {
                            result->child[i] = result->child[i + 1];
                            result->child[i + 1] = nullptr;
                        }
                        result->child[result->size] = nullptr;
                    }
                    result->size--;
                    result->child[pos-1]->size = 2*T - 1;
                    if (!result->child[pos-1]->leaf) {
                        for (int i = 0; i <= result->child[pos]->size;i++) {
                           result->child[pos-1]->child[i+T] = result->child[pos]->child[i];
                           result->child[pos]->child[i] = nullptr;
                        }
                    }
                    Deleting(result,value);
                }
            } else {
                int idx = BinarySearchInNode(node,value);
                if (node->child[idx]->size >= T) {
                    Deleting(node->child[idx], value);
                } else if (node->child[idx]->size == T-1) {
                    if (idx+1 <= node->size && node->child[idx+1]!=nullptr && node->child[idx+1]->size >= T) {
                        node->child[idx]->key[T-1] = node->key[idx];
                        node->child[idx]->size++;
                        if (!node->child[idx]->leaf) {
                            node->child[idx]->child[node->child[idx]->size] = node->child[idx+1]->child[0];
                        }
                        node->key[idx] = node->child[idx+1]->key[0];
                        for (int i = 1; i < node->child[idx+1]->size; i++) {
                            node->child[idx+1]->key[i-1] = node->child[idx+1]->key[i];
                        }
                        if (!node->child[idx]->leaf) {
                            for (int i = 1; i <= node->child[idx+1]->size; i++) {
                                node->child[idx+1]->child[i-1] = node->child[idx+1]->child[i];
                                node->child[idx+1]->child[i] = nullptr;
                            }
                        node->child[idx+1]->child[node->child[idx+1]->size] = nullptr;
                        }
                        node->child[idx+1]->size--;
                        Deleting(node->child[idx], value);
                    } else if (idx-1>=0 && node->child[idx-1]->size >= T) {
                        for (int i = node->child[idx]->size-1; i >= 0; i--) { 
                            node->child[idx]->key[i+1] = node->child[idx]->key[i];
                        }
                        if (!node->child[idx]->leaf) {
                            for (int i = node->child[idx]->size;i>=0;i--) {
                                node->child[idx]->child[i+1] = node->child[idx]->child[i];
                                node->child[idx]->child[i] =nullptr;
                            }  
                        }
                        node->child[idx]->size++;
                        node->child[idx]->key[0] = node->key[idx-1]; 
                        node->key[idx-1] = node->child[idx-1]->key[node->child[idx-1]->size-1]; 
                        if (!node->child[idx-1]->leaf) {
                            node->child[idx]->child[0] = node->child[idx-1]->child[node->child[idx-1]->size];
                            node->child[idx-1]->child[node->child[idx-1]->size] = nullptr;
                        }             
                        node->child[idx-1]->size--;
                        Deleting(node->child[idx], value);
                    } else if (node->size == 1) { 
                        if  (idx == 0) idx++;
                            BNode *left = node->child[idx-1];
                            BNode *right = node->child[idx];
                            left->key[left->size++] = node->key[idx-1];
                            for (int i = 0; i < right->size; ++i) {
                                left->key[left->size++] = right->key[i];
                            }
                            if (!right->leaf) {
                                for (int i = 0; i <= right->size; i++) {
                                    left->child[T + i] = right->child[i];
                                    right->child[i] = nullptr;
                                }
                            }
                            right->size = 0;
                            delete right;
                            DeleteFromNode(node, idx);
                            node->child[idx-1] = left;
                            BNode* tmp = root->child[idx-1];
                            delete root;
                            root = tmp;
                            Deleting(root,value);
                    } else if ((idx - 1 >=0 && node->child[idx-1]!=nullptr && node->child[idx-1]->size == T-1 &&
                    idx + 1 <= node->size && node->child[idx+1]!=nullptr && node->child[idx+1]->size == T-1) ||
                    idx == 0) {
                        BNode *left = node->child[idx];
                        BNode *right = node->child[idx + 1];
                        left->key[left->size++] = node->key[idx];
                        for (int i = 0; i < right->size; i++) {
                            left->key[left->size++] = right->key[i];
                        }
                        if (!right->leaf) {
                            for (int i = 0; i <= right->size; i++) {
                                left->child[T + i] = right->child[i];
                                right->child[i] = nullptr;
                            }
                        }
                        right->size = 0;
                        delete right;
                        DeleteFromNode(node, idx);
                        node->child[idx] = left;
                        Deleting(node->child[idx], value);
                    } else if (idx == node->size) {
                        BNode *left = node->child[idx-1];
                        BNode *right = node->child[idx];
                        left->key[left->size++] = node->key[idx-1];
                        for (int i = 0; i < right->size; i++) {
                            left->key[left->size++] = right->key[i];
                        }
                        if (!right->leaf) {
                            for (int i = 0; i <= right->size; i++) {
                                left->child[T + i] = right->child[i];
                                right->child[i] = nullptr;
                            }
                        }
                        right->size = 0;
                        delete right;
                        DeleteFromNode(node, idx);
                        node->child[idx-1] = left;
                        Deleting(node, value);
                    } 
                }
            }
        }
    }
    void SearchNode(BNode* node, string cmd, BNode* &result, int& pos) {
        int i = 0;
        while (i < node->size && node->key[i].str < cmd) {
            ++i;
        }
        if (i < node->size && node->key[i].str == cmd) {
            result = node;
            pos = i;
            return;
        }
        if (node->leaf) {
            result = nullptr;
            return;
        }
        SearchNode(node->child[i], cmd, result, pos);
    }
    void SaveFile(BNode *node, ofstream& file) {
        file.write((char *)&node->leaf, sizeof(bool));
        file.write((char *)&node->size, sizeof(int));
        for (int i = 0; i < node->size; i++){
            int sizeValue = node->key[i].str.size();
            file.write((char *)&sizeValue, sizeof(int));
            file.write(node->key[i].str.c_str(), node->key[i].str.size());
            file.write((char *)&node->key[i].val, sizeof(unsigned long long));
            file.flush();
        }
        if(!node->leaf){
            for(int i = 0; i < node->size + 1; i++){
                SaveFile(node->child[i], file);
            }
        }
    }
    void LoadFile(BNode* node, std::ifstream &file){
        file.read((char *)&node->leaf, sizeof(bool));
        file.read((char *)&node->size, sizeof(int));
        for (int i = 0; i < node->size; ++i) {
            int sizeKey;
            file.read((char *)&sizeKey, sizeof(int));
            string value;
            value.resize(sizeKey);
            file.read((char *)value.c_str(),sizeKey);
            node->key[i].str = value;
            file.read((char *)&node->key[i].val, sizeof(unsigned long long));
        }
        if (!node->leaf) {
            for (int i = 0; i < node->size + 1; i++) {
                if (node->child[i] == nullptr) {
                    node->child[i] = new BNode;
                }
                LoadFile(node->child[i], file);
            }
        }
        else {
            for (int i = 0; i < 2 * T + 1; i++) {
                if (node->child[i] != nullptr) {
                    DeleteTree(node->child[i]);
                    node->child[i] = nullptr;
                }
            }
        }
    }
    void DeleteTree(BNode *node) {
        if (node!=nullptr) {
            if (!node->leaf) {
                for (int i = 0; i < 2 * T + 1; i++) {
                    if (node->child[i] != nullptr) {
                        DeleteTree(node->child[i]);
                        node->child[i] = nullptr;
                    }
                }
            }
            delete node;
        }
    }
    // void PrintNode(BNode* node) {
    //     for (int i = 0; i < node->size; i++) {
    //         cout << node->key[i].str << " " << node->key[i].val;
    //     }
    //     cout << endl;
    // }
    // void PrintTree(BNode* node, int length) {
    //     PrintNode(node);
    //     int i = 0;
    //     while (node->child[i]!=nullptr) {
    //         for (int j = 0; j < length; j++) {
    //             cout << " ";
    //         }
    //         length++;
    //         PrintTree(node->child[i],length);
    //         length--;
    //         i++;
    //     }
    // }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    BTree tree;
    string cmd;
    while (cin >> cmd) {
        if (cmd == "+") {
            DictPair input;
            string s;
            cin >> s >> input.val;
            transform(s.begin(), s.end(), s.begin(), ::tolower);
            input.str = s;
            BNode* find =nullptr;
            int pos = 0;
            tree.SearchNode(tree.root, input.str, find, pos);
            if (find != nullptr) {
                cout << "Exist" << endl;
            } else {
                tree.Insert(input);
                cout << "OK" << endl;
            }
        // } else if (cmd == "print") {
        //     tree.PrintTree(tree.root,0);
        } else if (cmd == "-") {
            string del;
            cin >> del;
            transform(del.begin(), del.end(), del.begin(), ::tolower);
            int pos = 0;
            BNode* find =nullptr;
            tree.SearchNode(tree.root, del, find, pos);
            if (find == nullptr) {
                cout << "NoSuchWord" << endl;
            } else {
                tree.Deleting(tree.root, del);
                cout << "OK" << endl;
            }
        } else if (cmd == "!") {
            cin >> cmd;
            if (cmd == "Save") {
                cin >> cmd;
                ofstream file(cmd, ios::binary | ios::trunc);
                tree.SaveFile(tree.root, file);
                cout << "OK" << endl;
                file.close();
            } else if (cmd == "Load") {
                cin >> cmd;
                ifstream file(cmd, ios::binary);
                tree.LoadFile(tree.root, file);
                file.close();
                cout << "OK" << endl;
            }
        } else {
            transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
            BNode* find;
            int pos;
            tree.SearchNode(tree.root, cmd, find, pos);
            if (find!=nullptr) {
                cout << "OK: " << find->key[pos].val << endl;
            } else {
                cout << "NoSuchWord" << endl;
            }
        }
    }
} 