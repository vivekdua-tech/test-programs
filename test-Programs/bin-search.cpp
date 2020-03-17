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
    int lowindex = -1, highindex = -1;
    
    while (low < high) {
        
        int mid = (low + high)/2;
        if (key <= A[mid]) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    lowindex = low;
    low = 0;
    high = len - 1;
    while (low < high) {
        
        int mid = (low + high)/2;
        if (key < A[mid]) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    highindex = low - 1;
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



class Solution {
public:
    int findMin(vector<int>& nums) {
        
        int high = nums.size() - 1;
        int low = 0;
        int mid = 0;
        while (low <= high) {
            int mid = (high + low)/2;
            if (nums[mid] < nums[mid-1]) {
                return nums[mid];
            }
            
            if (nums[mid] > nums[low]) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return nums[mid];
    }
};



int main(int argc, const char * argv[]) {
 
#if 0
    std::vector<int> vec = {5, 2, 0, 6, 7, 0, 8, 3, 0};
    
    moveZerosToLeft(vec);
    for (auto &i : vec) {
        // cout << i ;
    }
    
    vector<int> vec1 = {5, 7, 7, 8, 8, 10};
    pair<int, int> tuple = ::binary_search_iterative(vec1.data(), 8, (int)vec1.size());
    cout << "lookup index for the vector is: "
         << tuple.first << " " << tuple.second
         << endl;
    
#endif
    
    vector<int> nums = {3, 4, 5, 1, 2};
    Solution s;
    cout << "min element is:" << s.findMin(nums);
    return 0;
}
