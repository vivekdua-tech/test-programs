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
        wayMap[pway]++;
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

/**********************************************************************************************
Now the strategy is here:

Add coins one-by-one, starting from base case "no coins".

For each added coin, compute recursively the number of combinations for each amount of money from 0 to amount.

Algorithm

Initiate number of combinations array with the base case "no coins": dp[0] = 1, and all the rest = 0.

Loop over all coins:

For each coin, loop over all amounts from 0 to amount:

For each amount x, compute the number of combinations: dp[x] += dp[x - coin].
Return dp[amount].

********************************************************/

int change(int amount, int[] coins) {
    int[] dp = new int[amount + 1];
    dp[0] = 1; // one combination for amount = 0 , no coin {0,0,0}

    for (int coin : coins) {
      for (int x = coin; x < amount + 1; ++x) {
        dp[x] += dp[x - coin];
      }
    }
    return dp[amount];
  }
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


///// 0-1 knapsack problem:
/////   Given weights and values of n items, put these items in a knapsack of capacity W to get the maximum total value in the knapsack.
/////  In other words, given two integer arrays val[0..n-1] and wt[0..n-1] which represent values and weights associated with n items
/////  respectively. Also given an integer W which represents knapsack capacity, find out the maximum value subset of val[] such
/////  that sum of the weights of this subset is smaller than or equal to W. You cannot break an item, either pick the complete
/////   item, or don’t pick it (0-1 property).
/////   https://www.geeksforgeeks.org/0-1-knapsack-problem-dp-10/
////    http://www.es.ele.tue.nl/education/5MC10/Solutions/knapsack.pdf
/////


/// coin change problem:

/// You are given coins of different denominations and a total amount of money amount.
/// Write a function to compute the fewest number of coins that you need to make up that amount.
/// If that amount of money cannot be made up by any combination of the coins, return -1.

/// Example 1:

/// Input: coins = [1, 2, 5], amount = 11
/// Output: 3
/// Explanation: 11 = 5 + 5 + 1


/// class Solution {
/// public:
///     int coinChange(vector<int>& coins, int amount) {
///         int Max = amount + 1;
///         vector<int> dp(amount + 1, Max);
///         dp[0] = 0;
///         for (int i = 1; i <= amount; i++) {
///             for (int j = 0; j < coins.size(); j++) {
///                 if (coins[j] <= i) {
///                     dp[i] = min(dp[i], dp[i - coins[j]] + 1);
///                 }
///             }
///         }
///         return dp[amount] > amount ? -1 : dp[amount];
///     }
/// };


/************************************************************
 
 
 Longest Palindromic Substring
 Given a string, find the longest substring which is palindrome.
 
The time complexity can be reduced by storing results of subproblems.
The idea is similar to this post. We maintain a boolean table[n][n] that is filled in bottom up manner.
The value of table[i][j] is true, if the substring is palindrome, otherwise false.
To calculate table[i][j], we first check the value of table[i+1][j-1], if the value is true
and str[i] is same as str[j], then we make table[i][j] true. Otherwise, the value of table[i][j] is made false.

 / This function prints the longest palindrome substring
 // It also returns the length of the longest palindrome
 int longestPalSubstr(string str)
 {
 // get length of input string
 int n = str.size();
 
 // table[i][j] will be false if substring str[i..j]
 // is not palindrome.
 // Else table[i][j] will be true
 bool table[n][n];
 
 memset(table, 0, sizeof(table));
 
 // All substrings of length 1 are palindromes
 int maxLength = 1;
 
 for (int i = 0; i < n; ++i)
 table[i][i] = true;
 
 // check for sub-string of length 2.
 int start = 0;
 for (int i = 0; i < n-1; ++i)
 {
 if (str[i] == str[i+1])
 {
 table[i][i+1] = true;
 start = i;
 maxLength = 2;
 }
 }
 
 // Check for lengths greater than 2. k is length
 // of substring
 for (int k = 3; k <= n; ++k)
 {
 // Fix the starting index
 for (int i = 0; i < n-k+1 ; ++i)
 {
 // Get the ending index of substring from
 // starting index i and length k
 int j = i + k - 1;
 
 // checking for sub-string from ith index to
 // jth index iff str[i+1] to str[j-1] is a
 // palindrome
 if (table[i+1][j-1] && str[i] == str[j])
 {
 table[i][j] = true;
 
 if (k > maxLength)
 {
 start = i;
 maxLength = k;
 }
 }
 }
 }
 
 cout << "Longest palindrome substring is: ";
 printSubStr( str, start, start + maxLength - 1 );
 
 // return length of LPS
 return maxLength;
 }
 
 *************************************************/


/***************************************************FROG Jump***************************************************
 
 A frog is crossing a river. The river is divided into x units and at each unit there may or may not exist a stone. The frog can jump on a stone, but it must not jump into the water.

 Given a list of stones' positions (in units) in sorted ascending order, determine if the frog is able to cross the river by landing on the last stone. Initially, the frog is on the first stone and assume the first jump must be 1 unit.

 If the frog's last jump was k units, then its next jump must be either k - 1, k, or k + 1 units. Note that the frog can only jump in the forward direction.

 Note:

 The number of stones is ≥ 2 and is < 1,100.
 Each stone's position will be a non-negative integer < 231.
 The first stone's position is always 0.
 Example 1:

 [0,1,3,5,6,8,12,17]

 There are a total of 8 stones.
 The first stone at the 0th unit, second stone at the 1st unit,
 third stone at the 3rd unit, and so on...
 The last stone at the 17th unit.

 Return true. The frog can jump to the last stone by jumping
 1 unit to the 2nd stone, then 2 units to the 3rd stone, then
 2 units to the 4th stone, then 3 units to the 6th stone,
 4 units to the 7th stone, and 5 units to the 8th stone.
 
 Approach #3 Using Memorization [Accepted]
 Algorithm

 Another problem with above approaches is that we can make the same function calls coming through different paths e.g. For a given currentIndexcurrentIndex, we can call the recursive function canCrosscanCross with the jumpsizejumpsize, say nn. This nn could be resulting from previous jumpsizejumpsize being n-1n−1,nn or n+1n+1. Thus, many redundant function calls could be made prolonging the running time. This redundancy can be removed by making use of memorization. We make use of a 2-d memomemo array, initialized by -1−1s, to store the result returned from a function call for a particular currentIndexcurrentIndex and jumpsizejumpsize. If the same currentIndexcurrentIndex and jumpsizejumpsize happens is encountered again, we can return the result directly using the memomemo array. This helps to prune the search tree to a great extent.
 
 Approach #5 Using Dynamic Programming[Accepted]
 Algorithm

 In the DP Approach, we make use of a hashmap mapmap which contains key:valuekey:value pairs such that keykey refers to the position at which a stone is present and valuevalue is a set containing the jumpsizejumpsize which can lead to the current stone position. We start by making a hashmap whose keykeys are all the positions at which a stone is present and the valuevalues are all empty except position 0 whose value contains 0. Then, we start traversing the elements(positions) of the given stone array in sequential order. For the currentPositioncurrentPosition, for every possible jumpsizejumpsize in the valuevalue set, we check if currentPosition + newjumpsizecurrentPosition+newjumpsize exists in the mapmap, where newjumpsizenewjumpsize can be either jumpsize-1jumpsize−1, jumpsizejumpsize, jumpsize+1jumpsize+1. If so, we append the corresponding valuevalue set with newjumpsizenewjumpsize. We continue in the same manner. If at the end, the valuevalue set corresponding to the last position is non-empty, we conclude that reaching the end is possible, otherwise, it isn't.

 *************************************************************************************************************************/


