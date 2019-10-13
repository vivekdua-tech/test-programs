//
//  dynamic-progamming.cpp
//  test-Programs
//
//  Created by Vivek Dua on 4/7/18.
//  Copyright © 2018 Vivek Dua. All rights reserved.
//

#include <iostream>
#include <map>
#include <unordered_map>


using namespace std;

// Given an infinite number of coins of 25cents, 15cents, 10cents, 5cents, and 1cents, write a code to calculate
// the number of ways of representing n cents.

// Recursion, keep reducing by each coin and when we reach n equal to {25, 15, 10, 5, 1} increment the associated
// number by one. When we reach zero, increment the number of ways by one.


class way {
    
public:
    
    int q;
    int f;
    int d;
    int n;
    int c;
    
    bool operator <(const way& x) const {
        if (q < x.q) return true;
        if (f < x.f) return true;
        if (d < x.d) return true;
        if (n < x.n) return true;
        if (c < x.c) return true;
        
        return false;
    }
    
};

// Returns num of iterations called on count

void count (int n, way pway, map<way, int> &wayMap) {
    
    
    way  currentWay = pway;
    
    if (n == 0) {
        auto it = wayMap.find(pway);
        if (it == wayMap.end()) {
            // add it now
            wayMap.insert(pair<way, int>(pway, 1));
        } else {
            it->second++;
        }
        return;
    }

    if (n >= 1) {
        // 1-cent added
        currentWay.c++;
        count(n-1, currentWay, wayMap);
    }
    
    if (n >= 5) {
        // 5-cent added
        currentWay.n++;
        count(n-5, currentWay, wayMap);
    }
    
    if (n >= 10) {
        currentWay.d++;
        count(n-10, currentWay, wayMap);
    }
                          
    if (n >= 15) {
        currentWay.f++;
        count(n-15, currentWay, wayMap);
    }
    
    if (n >= 25) {
        currentWay.q++;
        count(n-25, currentWay, wayMap);
    }
    
}

int main() {
    
    map<way, int> waysMap;
    
    way currentWay;
    
    count(15, currentWay, waysMap);
    
    cout << "Number of ways.." << waysMap.size();
    
}


// You are climbing a stair case. It takes n steps to reach to the top.

// Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

// For stair level n (n>=3) , you can either (1) climb to stair n-2 , and climb 2 more steps to reach n , OR (2) climb to stair n-1,
// and climb 1 more step to reach n.
// 
// Fibonacci series
//
// vector<int> steps(n,0);
// steps[0]=1;
// steps[1]=2;
// for(int i=2;i<n;i++)
// {
//     steps[i]=steps[i-2]+steps[i-1];
// }
// return steps[n-1];



// You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you
// from robbing each of them is that adjacent houses have security system connected and it will automatically contact the police if two adjacent houses
// were broken into on the same night.

//Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without
// alerting the police.

// Example 1:

// Input: [1,2,3,1]
// Output: 4
// Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
// Total amount you can rob = 1 + 3 = 4.
// Example 2:
//
// Input: [2,7,9,3,1]
// Output: 12
// Explanation: Rob house 1 (money = 2), rob house 3 (money = 9) and rob house 5 (money = 1).
// Total amount you can rob = 2 + 9 + 1 = 12.

////////////////////////////////////////////////////////////////////////
There is some frustration when people publish their perfect fine-grained algorithms without sharing any information abut how they were derived.
This is an attempt to change the situation. There is not much more explanation but it's rather an example of higher level improvements.
Converting a solution to the next step shouldn't be as hard as attempting to come up with perfect algorithm at first attempt.

This particular problem and most of others can be approached using the following sequence:

    Find recursive relation
    Recursive (top-down)
    Recursive + memo (top-down)
    Iterative + memo (bottom-up)
    Iterative + N variables (bottom-up)
    Step 1. Figure out recursive relation.
    A robber has 2 options: a) rob current house i; b) don't rob current house.
    If an option "a" is selected it means she can't rob previous i-1 house but can safely proceed to the one before previous i-2
    and gets all cumulative loot that follows.
    If an option "b" is selected the robber gets all the possible loot from robbery of i-1 and all the following buildings.
    So it boils down to calculating what is more profitable:

    robbery of current house + loot from houses before the previous
    loot from the previous house robbery and any loot captured before that
    rob(i) = Math.max(rob(i - 2) + currentHouseValue, rob(i - 1) )

Step 2. Recursive (top-down)
Converting the recurrent relation from Step 1 shound't be very hard.

public int rob(int[] nums) {
    return rob(nums, nums.length - 1);
}
private int rob(int[] nums, int i) {
    if (i < 0) {
        return 0;
    }
    return Math.max(rob(nums, i - 2) + nums[i], rob(nums, i - 1));
}
This algorithm will process the same i multiple times and it needs improvement. Time complexity: [to fill]

Step 3. Recursive + memo (top-down).

int[] memo;
public int rob(int[] nums) {
    memo = new int[nums.length + 1];
    Arrays.fill(memo, -1);
    return rob(nums, nums.length - 1);
}

private int rob(int[] nums, int i) {
    if (i < 0) {
        return 0;
    }
    if (memo[i] >= 0) {
        return memo[i];
    }
    int result = Math.max(rob(nums, i - 2) + nums[i], rob(nums, i - 1));
    memo[i] = result;
    return result;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
