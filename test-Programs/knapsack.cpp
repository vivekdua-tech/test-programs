//
//  knapsack.cpp
//  test-Programs
//
//  Created by vivekdua on 3/26/22.
//  Copyright © 2022 Vivek Dua. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>



using namespace std;

/****************
 Question 1
 In this programming problem and the next you'll code up the knapsack algorithm from lecture.

 Let's start with a warm-up.  Download the text file below.

 knapsack1
 TXT File
 Download file
 This file describes a knapsack instance, and it has the following format:

 [knapsack_size][number_of_items]

 [value_1] [weight_1]

 [value_2] [weight_2]

 ...
 For example, the third line of the file is "50074 659", indicating that the second item has value 50074 and size 659, respectively.

 You can assume that all numbers are positive.  You should assume that item weights and the knapsack capacity are integers.

 In the box below, type in the value of the optimal solution.
 ******************************/

int main() {
    
    int n = 0;
    int W = 0;
    
    ifstream file("/Users/vivekdua/Documents/Personal/test-programs/test-Programs/knapsack1.txt");
    if (!file) {
        cout << "File not found" << endl;
    }
    file >> W >> n;
    
    int v, w;
    vector<pair<int,int>> vec;
    while (file >> v >> w) {
        vec.push_back(make_pair(v, w));
    }
    cout << " Knapsack-Size: " << W << "Number of items:" << n << endl;
    vector<vector<int>> arr(W + 1, vector<int>(n + 1));
    
    for (int i = 0; i <= W; i++) {
        arr[0][i] = 0;
    }
    
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (vec[i-1].second > w) {
                arr[i][w] = arr[i-1][w];
            } else {
                arr[i][w] = max(arr[i-1][w],
                                arr[i-1][w - vec[i-1].second] + vec[i-1].first);
            }
        }
    }
    
    cout << arr[n][W] << endl;
    
}
