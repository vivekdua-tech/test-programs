//
//  LinkedList.cpp
//  test-Programs
//
//  Created by Vivek Dua on 5/27/18.
//  Copyright © 2018 Vivek Dua. All rights reserved.
//

#include <iostream>
#include <unordered_map>
#include <unordered_set>

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
    sll(node *n) : head(n) {}
    
    void insert(int val) {
        node *temp = new node(val);
        temp->next = head;
        this->head = temp;
    }
    // insert at the end.
    void insert(node* n) {
        node *t = head;
        node *p = head;
        while (t != nullptr) {
            t = t->next;
            p = t;
        }
        p->next = n;
    }
    void removeNode (node *prevNode, node* node) {
        if (!node) {
            return;
        }
        if (!prevNode) {
            // head
            head = node->next;
            delete node;
        } else {
            prevNode->next = node->next;
            delete node;
        }
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

// Remove a DUP node in the SLL

void removeDuplicates (sll& lst) {
    unordered_set<int> hashSet;
    node *n = lst.head;
    node *prevn = NULL;
    
    while (n != NULL) {
        if (hashSet.find(n->value) != hashSet.end()) {
            // found the DUP value
            // remove this node
            lst.removeNode(prevn, n);
        } else {
            // insert the value
            hashSet.insert(n->value);
        }
        prevn = n;
        n = n->next;
    }
}


// Move front node from one list to the other.
// src_list = { 2, 4, 5 }
// dst_list = { 3, 6, 7}
// dst_list becomes {2, 3, 6, 7} and the src_list becomes {4, 5}

void moveNode(node **destNode, node **srcNode) {
    node *src = *srcNode;
    
    (*srcNode)->next = *destNode;
    
    *destNode = *srcNode;
    
    src = src->next;
}

/* Takes two lists sorted in increasing order, and splices
 their nodes together to make one big sorted list which
 is returned.  */
sll SortedMerge(sll& first, sll& second) {
    
    node *fi = first.head;
    node *si = second.head;
    
    // dummy node
    node dummy = node(-1);
    // add nodes to the next of the dummy
    node *tail = &dummy;
    
    while (1) {
        
        //if no more elements in first...
        if (fi == nullptr) {
            // if there are elements in second, put those...
            while (si != nullptr) {
                moveNode(&(tail->next), &si);
                tail = tail->next;
            }
            break;
        }
        // if no more elements in second
        if (si == nullptr) {
            // if there are elements in first, put those...
            while (fi != nullptr) {
                moveNode(&(tail->next), &fi);
                tail = tail->next;
            }
            break;
        }
        
        if (fi->value < si->value) {
            moveNode(&(tail->next), &fi);
        }
        else if (si->value < fi->value) {
            moveNode(&(tail->next), &si);
        } else {
            // same value elements
            moveNode(&(tail->next), &fi);
            moveNode(&(tail->next), &si);
            tail = tail->next;
        }
        tail = tail->next;
    }
    return sll(dummy.next);
}


int main() {
    
    sll list1 = sll();
    list1.insert(1);
    list1.insert(3);
    list1.insert(5);
    list1.insert(7);
    list1.insert(9);

    sll list2 = sll();
    list2.insert(2);
    list2.insert(4);
    list2.insert(6);
    list2.insert(8);
    list2.insert(10);
    
    sll list3 = SortedMerge(list1, list2);
    list3.show();
    
}

