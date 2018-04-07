//
//  reverse-ll.cpp
//  test-Programs
//
//  Created by Vivek Dua on 3/31/18.
//  Copyright © 2018 Vivek Dua. All rights reserved.
//

#include <iostream>
#include <stack>

using namespace std;

class node{
public:
    node *next;
    int  value;
    
    node (int val) : value(val), next(nullptr) {};
};

class sll {
public:
    node *head;
    
    sll() : head(nullptr) {}
    
    void insert(int val) {
        node *temp = new node(val);
        temp->next = head;
        this->head = temp;
    }
    
    void show () {
        node *temp = head;
        cout << " list is : " << endl;
        while (temp) {
            cout << temp->value << " ";
            temp = temp->next;
        }
    }
};


void reverse (sll *list) {
    
    std::stack<node*> nodeStack;
    
    // Put entries in the stack and pop it out and set the next node entries accordingly.
    node *temp = list->head;
    while (temp != nullptr) {
        nodeStack.push(temp);
        temp = temp->next;
    }
    node *returnNode = nodeStack.top();
    node *prevNode = nullptr;
    list->head = returnNode;
    while (returnNode) {
        nodeStack.pop();
        returnNode->next = nullptr;
        if (prevNode) {
            prevNode->next = returnNode;
        }
        prevNode = returnNode;
        if (nodeStack.size()) {
            returnNode = nodeStack.top();
        } else {
            returnNode = nullptr;
        }
    }
    return;
}

#if 0
int main() {
    sll list = sll();
    list.insert(2);
    list.insert(3);
    list.insert(4);
    list.show();
    
    reverse(&list);
    list.show();
}

#endif
