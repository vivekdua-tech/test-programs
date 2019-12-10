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
    
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> res;
        sort(intervals.begin(), intervals.end(),
             [&](vector<int>& interval1, vector<int>& interval2){
                 return interval1.front() < interval2.front();
             });
        auto it = intervals.begin();
        if (it != intervals.end()) {
            res.push_back(*it);
        } else {
            return vector<vector<int>>();
        }
        
        for (int i = 1;i < intervals.size(); i++) {
            if (intervals[i][0] <= (res.back())[1]) {
                // merge it
                res.back().back() = intervals[i][1];
            } else {
                res.push_back(intervals[i]);
            }
        }
        return res;
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



/****** Task Scheduler *********************************************************************
 
 Given a char array representing tasks CPU need to do. It contains capital letters A to Z where
 different letters represent different tasks. Tasks could be done without original order.
 Each task could be done in one interval. For each interval, CPU could finish one task or
 just be idle. However, there is a non-negative cooling interval n that means between two same tasks,
 there must be at least n intervals that CPU are doing different tasks or just be idle.
 
 You need to return the least number of intervals the CPU will take to finish all the given tasks.

 Algorithm:
 
First count the number of occurrences of each element.
Let the max frequency seen be M for element E
We can schedule the first M-1 occurrences of E, each E will be followed by at least N CPU cycles in
 between successive schedules of E
 Total CPU cycles after scheduling M-1 occurrences of E = (M-1) * (N + 1) // 1 comes for the CPU cycle for E itself
Now schedule the final round of tasks. We will need at least 1 CPU cycle of the last occurrence of E. If there are multiple tasks with
 frequency M, they will all need 1 more cycle.
Run through the frequency dictionary and for every element which has frequency == M, add 1 cycle to result.
If we have more number of tasks than the max slots we need as computed above we will return the length of the tasks array as we need
 at least those many CPU cycles.
*****************************************************************************************/


class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        unordered_map<char,int>mp;
        int count = 0;
        for(auto e : tasks)
        {
            mp[e]++;
            count = max(count, mp[e]);
        }
        
        int ans = (count-1)*(n+1);
        for(auto e : mp) if(e.second == count) ans++;
        return max((int)tasks.size(), ans);
    }
};

/**************************************************
Sum of Two Integers
Use ^ and & to add two integers

int getSum(int a, int b) {
    return b==0? a:getSum(a^b, (a&b)<<1);
    //be careful about the terminating condition;
}
**************************************************/



