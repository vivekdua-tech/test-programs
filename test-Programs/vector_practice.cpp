//
//  vector_practice.cpp
//  test-Programs
//
//  Created by vidua on 6/23/19.
//  Copyright © 2019 Vivek Dua. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;


// implement binary search algo using vector/array

// return the index of the element given the element value
int bin_search(vector<int> &vec, int key)
{
    int high = vec.size() - 1;
    int low = 0;
    int mid = (high + low)/2;
    while (low <= high) {
        if (key == vec[mid]) {
            return mid;
        } else if (vec[mid] > key) {
            high = mid - 1;
            mid = (high + low)/2;
        } else {
            low = mid + 1;
            mid = (high + low)/2;
        }
    }
    return -1;
}

int main(int argc, const char * argv[]) {
    
    std::vector<int> vec = {1, 4, 6, 8, 9, 12, 15, 17, 20};
    
    cout <<"Binary search for elem:7 is:" << bin_search(vec, 7);
    cout <<"Binary search for elem:8 is:" << bin_search(vec, 8);
    cout <<"Binary search for elem:9 is:" << bin_search(vec, 9);
    cout <<"Binary search for elem:10 is:" << bin_search(vec, 10);
    
    return 0;
}
