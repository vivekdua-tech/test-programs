//
//  graph.cpp
//  test-Programs
//
//  Created by Vivek Dua on 4/10/18.
//  Copyright © 2018 Vivek Dua. All rights reserved.
//

#include <iostream>



using namespace std;

class node {

public:
    
    node *left;
    node *right;
    node *parent;
    int value;
    
    node(int val) : value(val), left(nullptr), right(nullptr), parent(nullptr) {};
};

class BST {
public:
    
    node *root;
    static node *leftMostNode(node*);
    static node *nextNode(node*);
    static node *createBST(int arr[], int, int);
    static void inOrderTraversal(node*);
};

node* BST::createBST (int arr[], int low, int high)
{
    if (low > high) return nullptr;
    
    int mid = (low + high)/ 2;
    node *midnode = new node(arr[mid]);
    
    node *leftnode = createBST(arr, low, mid - 1);
    node *rightnode = createBST(arr, mid + 1, high);
    midnode->left = leftnode;
    midnode->right = rightnode;
    if (leftnode) {
        leftnode->parent = midnode;
    }
    if (rightnode) {
        rightnode->parent = midnode;
    }
    return  midnode;
}

node*  BST::leftMostNode(node *root)
{
    
    node *node = root;
    while (node->left) {
        node = node->left;
    }
    return node;
}

void BST::inOrderTraversal(node *root) {
    
    if (!root) return;
    
    if (root->left)
        inOrderTraversal(root->left);
    
    cout << " " << root->value;
    
    if (root->right)
        inOrderTraversal(root->right);
}

// Write an algo to get the next node in the BST - Binary search tree.

node* BST::nextNode (node *root) {
//
//  if node has a right sub-tree, return the left most node in the right sub-tree.
//  If node does not have a right sub-tree, traverse up the parent till we get to the
//  left node of the parent.
    node *node = root;
    if (node->right) {
        return leftMostNode(node->right);
    } else {
        // traverse up till we get to the the left node of the parent.
        while (node->parent && node->parent->right == node) {
            node = node->parent;
        }
        return node;
    }
}


// Write an algo to check if the BST is balanced:
//        Left and Right subtree height differ by no more than 1.
//        Get the height of the Sub tree: get the height of the ST + 1;

int getHeight(node *root) {
    if (!root) return -1;
    
    return max(getHeight(root->left), getHeight(root->right)) + 1;
}

bool isBalanced(node *root) {
    return std::abs(getHeight(root->left) - getHeight(root->right)) <= 1;
}


int main() {
    
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    node *root = BST::createBST(arr, 0, 10);
    
    node *next = BST::nextNode(root);
    cout << "next node is " << next->value;
    
}


