//
//  bst-codec.cpp
//  test-Programs
//
//  Created by vidua on 12/3/19.
//  Copyright © 2019 Vivek Dua. All rights reserved.
//

#include <iostream>
#include <map>
#include <vector>
#include <unordered_map>
#include <queue>
#include <string>

/**
 * Definition for a binary tree node.
 */
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

using namespace std;


template <typename T>
T* createBST(int arr[], int low, int high) {
    if (low > high) return nullptr;
    
    int mid = (low + high)/ 2;
    T *midnode = new T(arr[mid]);
    
    T *leftnode = createBST<T>(arr, low, mid - 1);
    T *rightnode = createBST<T>(arr, mid + 1, high);
    midnode->left = leftnode;
    midnode->right = rightnode;
    return midnode;
}


class Codec {
public:
    
    // buildString
    void buildString(string& str, TreeNode* root) {
        if (!root) {
            str += string(",") + string("nullnull");
            return;
        }
        str += string(",") + to_string(root->val) ;
        buildString(str, root->left);
        buildString(str, root->right);
    }
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string str = "";
        buildString(str, root);
        return str;
    }
    
    // buildTree - from the encoded string
    TreeNode *buildTree(string& str) {
        size_t pos = str.find(",");
        TreeNode *newnode = NULL;
        if (pos != std::string::npos) {
            string strval = str.substr(0, pos);
            if (strval != "nullnull" && strval != "") {
                newnode = new TreeNode(stoi(strval));
            }
            str.erase(0, pos + 1); // "," delimiter len = 1
            if (newnode) {
                newnode->left = buildTree(str);
                newnode->right = buildTree(str);
            }
        }
        return newnode;
    }
    
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data[0] == ',') {
            data = data.substr(1);
        }
        return buildTree(data);
    }
};


int main() {
    
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    TreeNode *root = createBST<TreeNode>(arr, 0, 10);
    Codec codec;
    string encodedstr = codec.serialize(root);
    cout << "encoded string is:" << encodedstr << endl;
    TreeNode *newRoot = codec.deserialize(encodedstr);
    string encodedstr1 = codec.serialize(newRoot);
    cout << "the new encoded string is:" << encodedstr1 << endl;
    return 0;
}
