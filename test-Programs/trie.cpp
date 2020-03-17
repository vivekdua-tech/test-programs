//
//  trie.cpp
//  test-Programs
//
//  Created by vidua on 2/22/20.
//  Copyright © 2020 Vivek Dua. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

class tnode {
public:
    char letter;
    vector<tnode*> ref;
    bool leaf;
    
    tnode(char c) : letter(c), ref(26, NULL), leaf(false) {};
};

class trie {
    
public:
    tnode *head;
    
    trie() {
        head = new tnode(NULL);
    }
    
    void newbranch (tnode *node, string word) {
        tnode *n = node;
        for (auto c : word) {
            tnode *temp = new tnode(c);
            n->ref[c - 'a'] = temp;
            n = n->ref[c - 'a'];
        }
        n->leaf = true;
    }
    
    void insert(string word) {
        tnode *n = head;
        for (int i = 0; i < word.length(); i++) {
            if (n->ref[word[i] - 'a'] == NULL) {
                newbranch(n, word.substr(i));
            } else {
                n = n->ref[word[i] - 'a'];
            }
        }
    }
    bool find(string prefix){
        tnode *n = head;
        for (int i = 0; i < prefix.length(); i++) {
            if (n->ref[prefix[i] - 'a'] == NULL &&
                i != prefix.length() - 1) {
                return false;
            }
            n = n->ref[prefix[i] - 'a'];
        }
        if (n->leaf) {
            return true;
        }
        return false;
    }
    bool findprefix(string prefix) {
        tnode *n = head;
        if (n->ref[prefix[0] - 'a'] == NULL) {
            return false;
        }
        for (int i = 0; i < prefix.length(); i++) {
            if (n->ref[prefix[i] - 'a'] == NULL &&
                i != prefix.length() - 1) {
                return false;
            }
            n = n->ref[prefix[i] - 'a'];
        }
        return true;
    }
};


class Solution {
public:
    string licenseKeyFormatting(string S, int K) {
        string str = S;
        string result;
        size_t pos;
        while((pos = str.find('-')) != string::npos) {
            str.erase(str.begin() + pos);
        }
        transform(str.begin(), str.end(), str.begin(), ::toupper);
        size_t rem = str.length() % K;
        string first;
        if (rem) {
            first = str.substr(0, rem);
        }
        result += first;
        size_t num = str.length() / K;
        size_t count = num;
        size_t it = rem;
        result += (result != "" ? "-" : "") + str.substr(it, it + K - 1);
        count--;
        it += K;
        while (count--) {
            result += "-" + str.substr(it, it + K - 1);
            it += K;
        }
        return result;
    }
};

int main() {
    
    Solution s;
    cout << "the str is: " << s.licenseKeyFormatting("5FW3-3FJ3", 2);
    return 0;
    
    
    
#if 0
    trie t;
    
    t.insert(string("apple"));
    t.insert(string("amazon"));
    cout << "find apple:" << (t.find("apple") ? string("Yes") : string("no"));
    cout << "find apricot:" << (t.find("apricot") ? string("Yes") : string("no"));
#endif
}
