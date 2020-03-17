//
//  test.cpp
//  test-Programs
//
//  Created by vidua on 9/24/18.
//  Copyright © 2018 Vivek Dua. All rights reserved.
//

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <queue>


using namespace std;

unordered_map<string,string> mapStr;
int getIndex(string s) {
    
    for (int index = 0; index < s.length() - 1; index++) {
        if (s[index] != s[index + 1]) {
            return index;
        }
    }
    return -1;
}

string shortStr(string s) {
    string origStr = s;
    auto it = mapStr.find(s);
    if (it != mapStr.end()) {
        return it->second;
    }
    if (s.length() == 1) {
        return s;
    }
    int index = getIndex(s);
    while (index != -1) {
        string firstHalf = s.substr(getIndex(s), 2);
        string shortFirstHalf = shortStr(firstHalf);
        s.replace(getIndex(s), 2, shortFirstHalf);
        if ((it = mapStr.find(s)) != mapStr.end()) {
            // stash it if s > 3
            //if (origStr.length() >= 3) {
            //    mapStr.insert(pair<string, string>(origStr, it->second));
            //}
            return it->second;
        }
        index = getIndex(s);
    }
    return s;
}


// Complete the stringReduction function below.
int stringReduction(string s) {
    
    
    return shortStr(s).length();
}



class A {
private:
    int _a;
public:
    A() {
        cout << "class A cons called" << endl;
    }
};

class B : public A {
private:
    int _b;
public:
    B() {
        cout << "class B cons called" << endl;
    }
};

class C : public B {
private:
    int _c;
public:
    C() {
        cout << "class C cons called" << endl;
    }
};


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

vector<vector<int>> levelOrder(TreeNode* root) {
        queue<TreeNode*> bft_q;
        vector<vector<int>> finalvec;
        // BFT -
        if (!root) {
            return vector<vector<int>>();
        }
        bft_q.push(root);
        bft_q.push(NULL);
        vector<int> intvec;
        
        while (!bft_q.empty()) {
            // pop the node and create a new vector for this level
            TreeNode *node = bft_q.front();
            intvec.push_back(node->left->val);
            intvec.push_back(node->right->val);
            bft_q.pop();
            bft_q.push(node->left);
            bft_q.push(node->right);
            if (bft_q.front() == NULL) {
                // reached marker - flush the vector and add new node to the Q
                finalvec.push_back(intvec);
                intvec.clear();
                bft_q.pop();
                bft_q.push(NULL);
            }
        }
        return finalvec;
}

int main()
{
    
    // check if the string is palindrome - string can be having spaces and non-alphanumeric chars
    // for palindrome checking we just need to check for alphnum chars only
    // template <class ForwardIterator, class UnaryPredicate>
    // ForwardIterator remove_if (ForwardIterator first, ForwardIterator last,
    //                           UnaryPredicate pred);
    
    // remove_if: Transforms the range [first,last) into a range with all the elements for which pred returns true removed,
    // and returns an iterator to the new end of that range.
    // The removal is done by replacing the elements for which pred returns true by the next element for which it does not,
    // and signaling the new size of
    // the shortened range by returning an iterator to the element that should be considered its new past-the-end element.
    
    // transform: Applies an operation sequentially to the elements of range inputted and stores the
    // result in the range that begins at result which is inputted.
    
    string str = "Vivek, keviv";
    // remove all non-alphanum
    str.erase(std::remove_if(str.begin(), str.end(),
                             [](unsigned char c){ return !isalnum(c); }), str.end());
    // convert all into lower cases
    transform(str.begin(), str.end(), str.begin(), [](unsigned char c){ return tolower(c);});
    cout << "str is" << str;
    string reversestr = str;
    reverse(reversestr.begin(), reversestr.end());
    cout << "Is this palindrome: " << ((reversestr == str) ? "Yes" : "No");
    
    
    
    // Level order traversal
    queue<TreeNode*> bft_q;
    
    
    
    
    
    
    
#if 0
    mapStr.insert(pair<string, string>(string("ab"), string("c")));
    mapStr.insert(pair<string, string>(string("ac"), string("b")));
    mapStr.insert(pair<string, string>(string("ba"), string("c")));
    mapStr.insert(pair<string, string>(string("bc"), string("a")));
    mapStr.insert(pair<string, string>(string("ca"), string("b")));
    mapStr.insert(pair<string, string>(string("cb"), string("a")));
    
    string s = "accbaacabbbaacabcbcaccaabcbccbacbcbaabacacababcaacbcccbaccacaabcbaaccbcabccbccbcbbcba";
        
    int result = stringReduction(s);
    cout << " Result: " << result << endl;
    
#endif
    return 0;
}
