//
//  LeadingZero.cpp
//  test-Programs
//
//  Created by Vivek Dua on 3/31/18.
//  Copyright © 2018 Vivek Dua. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;


int moveZerosToLeft (vector<int> &vec)
{
    // iterate and put the non-zero elements to the end of the vector
    auto index = vec.size();
    auto i = vec.size();
    
    while (i <= vec.size()  && index <= vec.size()) {
        // if non-zero put the elements in the right index
        auto element = vec[i--];
        if (element) {
            vec[index--] = element;
        }
    }
    // Fill in the leading zeros
    while (index <= vec.size()) {
        vec[index--] = 0;
    }
    return 0;
}



/*
 * clockwise rotate
 * first reverse up to down, then swap the symmetry
 * 1 2 3     7 8 9     7 4 1
 * 4 5 6  => 4 5 6  => 8 5 2
 * 7 8 9     1 2 3     9 6 3
 */
void rotate(vector<vector<int> > &matrix) {
    reverse(matrix.begin(), matrix.end());
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = i + 1; j < matrix[i].size(); ++j)
            swap(matrix[i][j], matrix[j][i]);
    }
}


int main(int argc, const char * argv[]) {
    
    std::vector<int> vec = {5, 2, 0, 6, 7, 0, 8, 3, 0};
    
    moveZerosToLeft(vec);
    for (auto &i : vec) {
        cout << i ;
    }
    return 0;
}
