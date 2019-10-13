//
//  LRU.cpp
//  test-Programs
//
//  Created by vidua on 10/13/18.
//  Copyright © 2018 Vivek Dua. All rights reserved.
//


#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
#include <memory>


// LRU cache implementation -
//      Entries stored in a MAP - RBT with {key, value} pair
//      Each entries are also linked on a doubly linked list to get to the least recently used(tail)
//      and most recently used(head)
//      Every time an entry is added it is added to the head and deleted from the tail(Least recently used)
//
//      Most commonly used in MAC-addr table implementation which is suppose to flush out least recently used
//      macs. It could also be used in user-session entries which are suppose to expire least recently used
//      ones.


using namespace std;

struct Node{
    Node* next;
    Node* prev;
    int value;
    int key;
    Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val){};
    Node(int k, int val):prev(NULL),next(NULL),key(k),value(val){};
};

class Cache{
    
protected:
    map<int,shared_ptr<Node>> mp; //map the key to the node in the linked list
    int cp;  //capacity
    Node* tail; // double linked list tail pointer
    Node* head; // double linked list head pointer
    virtual void set(int, int) = 0; //set function
    virtual int get(int) = 0; //get function
    
};
class LRUCache : public Cache {
    
public:
    
    LRUCache (int cap) {
        head = nullptr;
        tail = nullptr;
        cp = cap;
    }
    
    void set (int key, int value) override {
        // constraint check
        if (key < 1 || key > 20 ||
            value < 1 || value > 2000) {
            return;
        }
        // if reached capacity then get the LRU and remove the same.
        if (cp == mp.size()) {
            // tail points to the LRU entry
            Node* lru = tail;
            if (head == tail) {
                // only entry
                head = nullptr;
                tail = nullptr;
            } else {
                tail = tail->prev;
                if (tail) {
                    tail->next = nullptr;
                }
            }
            mp.erase(lru->key);
        }
        // Now add the new entry - as a head - MRU Entry
        shared_ptr<Node> mru = make_shared<Node>(key, value);
        mru->next = head;
        if (head) {
            head->prev = mru.get();
        }
        head = mru.get();
        if (!tail) {
            tail = head;
        }
        // if key exists - delete it and then add it
        auto it = mp.find(key);
        if (it != mp.end()) {
            mp.erase(key);
        }
        mp.insert(pair<int, shared_ptr<Node>>(key, mru));
    }
    
    int get (int key) override {
        auto it = mp.find(key);
        if (it != mp.end()) {
            return it->second != nullptr ? it->second->value : -1;
        }
        return -1;
    }
};

int main() {
    int n, capacity,i, key;
    cout << "Enter the capacity:" << endl;
    cin >> n >> capacity;
    
    LRUCache l(capacity);
    for (i = 0 ; i < n ; i++) {
            int key, value;
            cout << "Enter the (key value) pair in 2 3" << endl;
            cin >> key >> value;
            l.set(key,value);
    }
    cout << "Enter the key to get..." << endl;
    cin >> key;
    cout << l.get(key) << endl;
    // test code
    vector<int> intvec = {0, 1, 2, 3, 3, 4};
    
    for (vector<int>::const_iterator it = intvec.begin();
         it != intvec.end();
         it ++) {
        if (it != intvec.begin() && *previt == *it) {
            // delete this reference
            intvec.erase(previt);
        }
        previt = it;
    }
    return 0;
}




