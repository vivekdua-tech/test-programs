//
//  linkedlist.cpp
//  test-Programs
//
//  Created by Vivek Dua on 5/29/18.
//  Copyright © 2018 Vivek Dua. All rights reserved.
//

#include <iostream>
#include <unordered_set>


class node {
public:
    int data;
    node *next;
    
};

class sll {
    
public:
    
    node *head;
    sll() {}
    
    void insert (node *temp) {
        
    }
    
    void removeDupNodes();
    
};



sll::removeDupNodes() {
    
    node *temp = head;
    std::unordered_set<int> set;
    node *prev = head;
    
    while (temp != nullptr) {
        if (set.find(temp->data) != set.end()) {
            // delete this node
            prev->next = temp->next;
            node *tobeDeleted = temp;
            temp = temp->next;
            delete tobeDeleted;
        } else {
            set.insert(temp->data);
            prev = temp;
            temp = temp->next;
        }
        
    }
}




class node {
public:
    int data;
    
    node *left;
    node *right;
};


bool validateBST(node *root) {
    
    if (!root) {
        return false;
    }
    
    bool flag = true;
    
    node *leftnode = root->left;
    node *rightnode = root->right;
    
    if (leftnode) {
        if (leftnode->data > root->data) {
            flag = false;
         }
        flag = validateBST(leftnode);
        if (flag == false) {
            return flag;
        }
    }
    
    if (rightnode) {
        if (rightnode->data < root->data) {
            flag = false;
        }
        flag = validateBST(rightnode);
        if (flag == false) {
            return flag;
        }
    }
    
    return flag;
}
































