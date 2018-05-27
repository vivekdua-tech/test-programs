//
//  stack.cpp
//  test-Programs
//
//  Created by Vivek Dua on 5/7/18.
//  Copyright © 2018 Vivek Dua. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

#define MAX_NODES 100


template <typename T>
class node {
public:
    T data;
};


class mystack {
    
private:
    vector<node<char>> vec;
    node<char> top;
    
    
public:
    void push (node<char> n) {
        vec.push_back(n);
    }
    
    node<char> pop() {
        node<char> n = vec.back();
        vec.pop_back();
        return n;
    }
    
    bool isEmpty() {
        return vec.size() == 0;
    }
};










