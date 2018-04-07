//
//  quicksort.cpp
//  test-Programs
//
//  Created by Vivek Dua on 4/1/18.
//  Copyright © 2018 Vivek Dua. All rights reserved.
//

#include <iostream>



using namespace std;

// last element as pivot, places pivot at its correct postion in a sorted array,
// and places all smaller(smaller than pivot) to the left of pivot and all greater
// elements to the right of the pivot.
// {12, 7, 14, 9, 10, 11} - P, Q, U = arr[low]
// pivot = arr[high].
// iterate from low to high-1 and then if the element is smaller or equal to pivot
//  increment the smaller element index and swap with the bigger element bucket index.

int partition (int arr[], int low, int high)
{
    
    int pivot = arr[high];
    int small_bucket_index = low - 1;
    
    for (int u = low; u < high - 1; u++) {
        if (arr[u] <= pivot) {
            small_bucket_index++;
            // swap the smaller element with the first element of the bigger bucket
            std::swap(arr[small_bucket_index], arr[u]);
        }
    }
    // Now the bucket is partitioned such that low to small_bucket_index have smaller numbers.
    // and small_bucket_index + 1 to high - 1 have larger elements.
    
    // Now swap the pivot with the first element of the larger bucket.
    std::swap(arr[small_bucket_index + 1], arr[high]);
    return small_bucket_index + 1;
}


// Given arr[] unsorted list of numbers, sort the numbers using quicksort.
void quicksort (int arr[], int low, int high) {

    if (low < high) {
        // only if there are more than one elements we need to pursue quicksort.
        // partition the bucket with the pivot recursively.
        
        // Get the partition index for the bucket assuming pivot as the last element.
        // Partition the array with the pivot as well.
        int pi = partition(arr, low, high);
        
        // now recursively call with the new buckets.
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
    
}

/* Function to print an array */
void printArray(int arr[], int size)
{
    int i;
    for (i=0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

// Driver program to test above functions
int main()
{
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr)/sizeof(arr[0]);
    quicksort(arr, 0, n-1);
    cout << " Sorted array..";
    printArray(arr, n);
    return 0;
}



