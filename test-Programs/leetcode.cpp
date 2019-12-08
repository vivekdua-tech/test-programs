//
//  leetcode.cpp
//  test-Programs
//
//  Created by vidua on 9/26/19.
//  Copyright © 2019 Vivek Dua. All rights reserved.
//

#include <vector>
#include <cstdlib>
#include <iostream>
#include <stack>
#include <map>

using namespace std;

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        vector<int> vec;
        map<int, int> fmap;
        for (auto i : nums) {
            auto it = fmap.find(i);
            if (it == fmap.end()) {
                fmap.insert(pair<int, int>(i, 1));
            } else {
                it->second++;
            }
        }
        int i = 0;
        for (auto it = fmap.begin();
             it != fmap.end() && i < k;
             it++, i++) {
            vec.push_back(it->first);
        }
        return vec;
    }
    
    
    
    
    vector<int> _nums;
    Solution(vector<int>& nums) {
        _nums = nums;
        std::srand(time(NULL));
    }
    
    /** Resets the array to its original configuration and return it. */
    vector<int> reset() {
        return _nums;
    }
    
    /** Returns a random shuffling of the array. */
    vector<int> shuffle() {
        vector<int> temp;
        // get the start index as random index
        int random = std::rand()%_nums.size();
        cout << "random:" << random << endl;
        for (int i = 0; i < _nums.size(); i++) {
            temp.push_back(_nums[(random + i)%_nums.size()]);
        }
        return temp;
    }
    
    void printvec (vector<int> vec) {
        for (auto i : vec) {
            cout << " " << i;
        }
        cout << endl;
    }
};
// Implement using vector and retain the min element at every operation of the stack.
class MinStack {
public:
    vector<int> _stk;
    int min;
    /** initialize your data structure here. */
    MinStack() {
        min = 2^32 - 1;
    }
    
    void push(int x) {
        if (x < min) {
            min = x;
        }
        _stk.push_back(x);
    }
    
    void pop() {
        if (_stk.back() == min) {
            // min element hence find the next min element
            _stk.pop_back();
            if (_stk.size()) {
                min = *(min_element(_stk.begin(), _stk.end()));
            }
        } else {
            _stk.pop_back();
        }
    }
    
    int top() {
        if (_stk.size()) {
            return _stk.back();
        } else {
            return -1;
        }
    }
    
    int getMin() {
        return min;
    }
};




int main() {
/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * vector<int> param_1 = obj->reset();
 * vector<int> param_2 = obj->shuffle();
 */
    vector<int> _vec = {1,2,3,4, 5, 6, 7, 8, 9, 10};
    Solution *sol = new Solution(_vec);
    vector<int> _resetvec = sol->reset();
    sol->printvec(_resetvec);
    for (int i = 0; i < 5; i++) {
        vector<int> _shufvec = sol->shuffle();
        sol->printvec(_shufvec);
    }
    
    /**
     * Your MinStack object will be instantiated and called as such:
     * MinStack* obj = new MinStack();
     * obj->push(x);
     * obj->pop();
     * int param_3 = obj->top();
     * int param_4 = obj->getMin();
     */
    
}
