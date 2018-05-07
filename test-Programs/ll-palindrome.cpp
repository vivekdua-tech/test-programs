//
//  ll-palindrome.cpp
//  test-Programs
//
//  Created by Vivek Dua on 5/6/18.
//  Copyright © 2018 Vivek Dua. All rights reserved.
//

#include <iostream>
#include <list>
#include <stack>

using namespace std;

// Implement a function to check if the LL is a palindrome


class node {
public:
    
    int data;
    node *next;
};


bool isPalindrome(std::list<node> ll);


bool isPalindrome(std::list<node> ll) {
    
    // Push data into the stack till the mid -1 nodes.
    // use fast and slow runner technique to reach the middle of the ll.
    
    node *slow = &(ll.front());
    node *fast = &(ll.front());
    std::stack<int> stk;
    
    
    while (fast != NULL && fast->next != nullptr) {
        stk.push(slow->data);
        slow = slow->next;
        fast = fast->next->next;
    }
    
    // has odd elements if the fast and slow are at the end and the mid.
    if (fast != nullptr) {
        // get to the next of the mid.
        slow = slow->next;
    } else {
        return false;
    }
    
    while (slow != nullptr) {
        // stack members should be in the same seq as the  next
        int top = stk.top();
        stk.pop();
        
        if (top != slow->data) {
            // not a palindrome
            return false;
        }
        slow = slow->next;
    }
    return true;
    
}




// Implement a function to check if the two LLs intersect and if they did, return the intersection ref node.
// Here the intersection is defined based on the reference , i.e the references match.

// Algorighthm:
//                3-->1-->5-->9-->7-->2-->1
//                        4-->6-->7-->2-->1
//      if the tail reference match there is a intersection.
//       How to detect the intersection node.
//       Calculate lenghts and start two runners one from the head of the shorter list
//       and from the head + (lenght-diff) for the longer list and once they hit a node
//       with the same reference, it is the intersection point.

// return true if they intersect and return the first intersecting node in the node reference.

bool intersect(list<node> list1, list<node> list2, node& intersect) {
    
    int len1 = list1.size();
    int len2 = list2.size();
    
    if (list1.end() != list2.end()) {
        return false;
    }
    
    auto it1 = list1.begin();
    auto it2 = list2.begin();
    
    if (len1 > len2) {
        std::advance(it1, len1 - len2 + 1);
    } else if (len1 < len2) {
        std::advance(it2 , len2 - len1 + 1);
    }
    
    while (it1++ != it2++ && it1 != list1.end() && it2 != list2.end()) {}
    
    if ( it1 == it2 && it1 != list1.end() && it2 != list2.end()) {
        intersect = *it1;
    }
    
    return true;
}

