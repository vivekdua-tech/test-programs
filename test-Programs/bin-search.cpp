//
//  main.cpp
//  test-Programs
//
//  Created by Vivek Dua on 3/28/18.
//  Copyright © 2018 Vivek Dua. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

pair<int, int> binary_search_iterative(int A[], int key, int len);


pair<int, int> binary_search_iterative(int A[], int key, int len) {
    
    int low = 0;
    int high = len - 1;
    int lowindex = 0, highindex = 0;
    
    while (low <= high) {
        if (low == high) {
            lowindex = low;
        }
        int mid = (low + high)/2;
        if (key <= A[mid]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    low = 0;
    high = len - 1;
    while (low <= high) {
        if (low == high) {
            highindex = low;
        }
        int mid = (low + high)/2;
        if (key >= A[mid]) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    
    return pair<int, int>(lowindex, highindex);
}


int moveZerosToLeft (vector<int> &vec) {
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


int main(int argc, const char * argv[]) {
 
    std::vector<int> vec = {5, 2, 0, 6, 7, 0, 8, 3, 0};
    
    moveZerosToLeft(vec);
    for (auto &i : vec) {
        // cout << i ;
    }
    
    vector<int> vec1 = { 2, 3, 4, 5, 5, 5, 5, 5, 6, 6, 6, 7, 8, 9};
    pair<int, int> tuple = ::binary_search_iterative(vec1.data(), 5, (int)vec1.size());
    cout << "lookup index for the vector is: "
         << tuple.first << " " << tuple.second
         << endl;
    
    return 0;
}
