//
//  bst.cpp
//  test-Programs
//
//  Created by vidua on 3/20/20.
//  Copyright © 2020 Vivek Dua. All rights reserved.
//

#include <iostream>

using namespace std;

class node {
    
public:
    
    node *left;
    node *right;
    int value;
    int hd; // horizontal distance required for vertical traversal
    
    node(int val) : value(val), left(nullptr), right(nullptr) {};
};

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

class Solution {
public:
    
private:
    node *prev = NULL;
public:
    
    void toDLL(node *root, node **head) {
        
        if (!root) return;
        
        toDLL(root->left, head);
        if (!prev) {
            *head = root;
        } else if (prev) {
            prev->right = root;
        }
        if (root) {
            root->left = prev;
        }
        prev = root;
        toDLL(root->right, head);
    }
    
    node* treeToDoublyList(node* root) {
        node *head = NULL;
        toDLL(root, &head);
        return head;
    }
    
    void dlltraverse (node *head) {
        if (head) {
            cout << " " << head->value;
        }
        node *temp = head->right;
        while (temp && temp != head) {
            cout << " " << temp->value;
            temp = temp->right;
        }
    }
    
};


int main() {
    
    int arr[] = {4, 2, 5, 1, 3};
    node *root = createBST<node>(arr, 0, 4);
    // BST to DLL
    Solution s;
    node *head = s.treeToDoublyList(root);
    s.dlltraverse(head);
    return 0;
}
