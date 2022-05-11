//
//  temp.cpp
//  test-Programs
//
//  Created by vidua on 4/5/20.
//  Copyright © 2020 Vivek Dua. All rights reserved.
//

#include <iostream>
#include <vector>
#include <set>

using namespace std;


class Solution {
public:
    
    void print(vector<vector<int>>& result) {
        for (auto vec: result) {
            for (auto i : vec) {
                cout << " " << i;
            }
            cout << endl;
        }
    }
    
    
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> result;
        for (int i = 0; i < n; i++) {
            vector<int> temp(n, 0);
            result.push_back(temp);
        }
        int runner = 1;
        int col = 0, row = 0;
        int rowslice = 1;
        int colslice = 1;
        int rowsize = n;
        int colsize = n;
        while (colslice < n && rowslice < n) {
            while (col < colsize) {
                result[row][col] = runner++;
                col++;
            }
            col--;
            row++;
            while (row < rowsize) {
                result[row][col] = runner++;
                row++;
            }
            row--;
            col--;
            while (col >= colslice - 1) {
                result[row][col] = runner++;
                col--;
            }
            col++;
            row--;
            rowslice++;
            while (row >= rowslice - 1) {
                result[row][col] = runner++;
                row--;
            }
            row++;
            col++;
            colslice += 2;
            rowslice++;
            rowsize -= rowslice - 1;
            colsize -= colslice - 1;
        }
        return result;
    }
};

int main() {
    
    Solution s;
    vector<vector<int>> result = s.generateMatrix(5);
    s.print(result);
}
