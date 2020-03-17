//
//  signal.cpp
//  test-Programs
//
//  Created by vidua on 2/16/20.
//  Copyright © 2020 Vivek Dua. All rights reserved.
//

#include <stdio.h>
#include <unordered_map>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;


/********************************************************************
There are N network nodes, labelled 1 to N.

Given times, a list of travel times as directed edges times[i] = (u, v, w), where u is the source node, v is the target node, and w is the time it takes for a signal to travel from source to target.

Now, we send a signal from a certain node K. How long will it take for all nodes to receive the signal? If it is impossible, return -1.



Example 1:



Input: times = [[2,1,1],[2,3,1],[3,4,1]], N = 4, K = 2
Output: 2


Note:

N will be in the range [1, 100].
K will be in the range [1, N].
The length of times will be in the range [1, 6000].
All edges times[i] = (u, v, w) will have 1 <= u, v <= N and 0 <= w <= 100.


***********************************************************************************/

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        
        unordered_map<int, bool> visited;
        unordered_map<int, vector<pair<int, int>>> adj;
        unordered_map<int, int> cost;
        int maxtime = 0;
        for (auto edge : times) {
            vector<pair<int, int>> curradjs;
            unordered_map<int, vector<pair<int, int>>>::iterator it;
            if ((it = adj.find(edge[0])) != adj.end()) {
                curradjs = it->second;
            }
            curradjs.push_back(pair<int, int>(edge[1], edge[2]));
            adj[edge[0]] = curradjs;
        }
        queue<int> bftq;
        bftq.push(K);
        while (visited.size() < N) {
            int currnode = bftq.front();
            bftq.pop();
            // if visited it is a cycle
            if (visited.find(currnode) != visited.end()) {
                return -1;
            }
            visited.insert(pair<int, bool>(currnode, true));
            unordered_map<int, vector<pair<int, int>>>::const_iterator it;
            if ((it = adj.find(currnode)) == adj.end()) {
                // not found
                continue;
            }
            int prevcost = cost[currnode];
            vector<pair<int, int>> vec = it->second;
            for (auto v : vec) {
                bftq.push(v.first);
                int mincost = prevcost + v.second;
                if (cost.find(v.first) != cost.end()) {
                    if (cost[v.first] < mincost) {
                        mincost = cost[v.first];
                    }
                }
                cost[v.first] = mincost;
            }
        }
        for (auto it = cost.begin();
             it != cost.end();
             it++) {
            if (it->second > maxtime) {
                maxtime = it->second;
            }
        }
        return maxtime;
    }
};

int main() {
    
    vector<vector<int>> times = {{2, 1, 1}, {2, 3, 1}, {3, 4, 1}};
    Solution soln;
    
    std::cout << "maxtime is:" << soln.networkDelayTime(times,4, 2) << std::endl;
}
