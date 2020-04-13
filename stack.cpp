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



template <typename T>
class node {
public:
    T _data;
    node(T t) : _data(t) {};
    node() {};
};


template <typename T>
class mystack {
    
private:
    vector<node<T>> vec;
    node<T> top;
    
    
public:
    
    mystack<T> () : top(node<T>()) {};
    
    
    void push (T n) {
        node<T> n1(n);
        vec.push_back(n1);
    }
    
    
    T pop() {
        node<T> n = vec.back();
        vec.pop_back();
        return n._data;
    }
    
    bool isEmpty() {
        return vec.size() == 0;
    }
};



bool isPalindrome(string str) {
    
    // Push data into the stack till the mid -1
    // use fast and slow runner technique to reach the middle of the string.
    
    mystack<char> stk;
    
    unsigned int midindex = str.length()/2;
    unsigned int i = 0;
    
    // For even lengths, midindex need to be len/2 - 1;
    if (str.length() % 2 == 0) {
        midindex--;
    }
    
    while (i <= midindex) {
        stk.push(str[i++]);
    }
    
    while (i <= str.length() - 1) {
        // stack members should be in the same seq as the next
        char top = stk.pop();
        
        if (top != str[i]) {
            // not a palindrome
            return false;
        }
        i++;
    }
    return true;
    
}


int main() {
    
    
    string s1 = "ABBA";
    
    bool flag = isPalindrome(s1);
    
    string flagstr = flag == true ? " true" : "false";
    
    cout << " the flag is :" << flagstr;
    
    return 0;
}












