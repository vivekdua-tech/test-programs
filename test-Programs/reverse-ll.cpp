//
//  reverse-ll.cpp
//  test-Programs
//
//  Created by Vivek Dua on 3/31/18.
//  Copyright © 2018 Vivek Dua. All rights reserved.
//

#include <iostream>
#include <stack>
#include <vector>

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
    
    if (!list->head) {
        return;
    }
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

int main() {
#if 0
    sll list = sll();
    list.insert(2);
    list.insert(3);
    list.insert(4);
    list.insert(5);
    list.insert(6);
    list.show();
    
    reverse(&list);
    list.show();
#endif
    vector<long> vec = {3, 4, 5, 2, 3, 6};
    auto bit = vec.begin() + 1;
    auto eit = vec.begin() + 2;
    cout << "min: " << *min_element(bit, eit);
    
    
#if 0
    for (unsigned int index = 0; index < vec.size() - 1; index++) {
        swap(vec[index], vec[index + 1]);
    }
    cout << "vector is: " << endl;
    for (auto i : vec) {
        cout <<  " " << i;
    }
#endif
    
    
}
