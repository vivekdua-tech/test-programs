//
//  test.cpp
//  test-Programs
//
//  Created by vivekdua on 3/26/22.
//  Copyright © 2022 Vivek Dua. All rights reserved.
//

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

///
///Consider an instance of the optimal binary search tree problem with 7 keys (say 1,2,3,4,5,6,7 in sorted order) and frequencies w_1 = .05,
///w_2 = .4, w_3 = .08, w_4 = .04, w_5 = .1, w_6 = .1, w_7 = .23
///What is the minimum-possible average search time of a binary search tree with these keys?
///
///
///
int main() {
    
    int n = 7;
    //vector<int> opt(n, -1);
    vector<vector<double>> opt(n, vector<double>(n, 0.0));
    vector<double> freq = {0.2, 0.05, 0.17, 0.1, 0.2, 0.03, 0.25};
    double freqSum = 0.0;
    for (int i = 0; i < n; i++) {
        opt[i][i] = freq[i];
    }
    for (int s = 2; s <= n; s++) {
        // freqSum += freq[i + s];
        for (int i = 0; i <= n - s; i++) {
            int j = i + s - 1;
            opt[i][j] = 10000.0;
            freqSum = accumulate(freq.begin() + i, freq.begin() + j + 1, 0.0);
            for (int k = i ; k <= j; k++) {
                double val = freqSum + (k - 1 < i ? 0 : opt[i][k-1]) +
                                    (k + 1 > j? 0 : opt[k+1][j]);
                if (val < opt[i][j]) {
                    opt[i][j] = val;
                }
            }
        }
    }
    cout << " the min BST search time is:" << opt[0][n - 1];
    
}
