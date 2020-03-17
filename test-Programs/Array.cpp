//
//  vector.cpp
//  test-Programs
//
//  Created by Vivek Dua on 4/11/18.
//  Copyright © 2018 Vivek Dua. All rights reserved.
//

#include <iostream>
#include <vector>

// Merge two sorted vectors and store the result in the third.

using namespace std;

vector<int> sortVector(vector<int>& arr1, vector<int>& arr2) {

    // Go over the elements in both vector and start copying the elements in order to the result
    vector<int> result;
    unsigned int i = 0;
    unsigned int j = 0;
    result.reserve(arr1.size() + arr2.size());
    
    while(1) {
        
        // if there are no more elements in arr1
        if (i == arr1.size()) {
            // copy the remaining elements in arr2.
            while (j < arr2.size()) {
                result.emplace_back(arr2[j++]);
            }
            break;
        }
        if (j == arr2.size()) {
            // copy the elements in arr1 if there are...
            while (i < arr1.size()) {
                result.emplace_back(arr1[i++]);
            }
            break;
        }
        if (arr1[i] < arr2[j]) {
            result.emplace_back(arr1[i++]);
        } else if (arr2[j] < arr1[i]) {
            result.emplace_back(arr2[j++]);
        } else {
            result.emplace_back(arr1[i++]);
            result.emplace_back(arr2[j++]);
        }
    }
    return result;
}

int main() {
    
    vector<int> arr1 = {1, 3, 5, 7, 9};
    vector<int> arr2 = {2, 4, 6, 8, 10};
    
    cout << "Vector1 elements: " << std::endl;
    for (auto i : arr1)
        cout << " " << i;
    cout << "Vector2 elements: " << std::endl;
    for (auto i : arr2)
        cout << " " << i;
    
    vector<int> result = sortVector(arr1, arr2);
    cout << "Result Elements: " << std::endl;
    for (auto i : result) {
        cout << " " << i;
    }
}
