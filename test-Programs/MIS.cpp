//
//  MIS.cpp
//  test-Programs
//
//  Created by vivekdua on 3/19/22.
//  Copyright © 2022 Vivek Dua. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <set>


using namespace std;
/****************
This file describes the weights of the vertices in a path graph (with the weights listed in the order in which vertices appear in the path). It has the following format:

[number_of_vertices]

[weight of first vertex]

[weight of second vertex]

...

For example, the third line of the file is "6395702," indicating that the weight of the second vertex of the graph is 6395702.

Your task in this problem is to run the dynamic programming algorithm (and the reconstruction procedure) from lecture on this data set.  The question is: of the vertices 1, 2, 3, 4, 17, 117, 517, and 997, which ones belong to the maximum-weight independent set?  (By "vertex 1" we mean the first vertex of the graph---there is no vertex 0.)   In the box below, enter a 8-bit string, where the ith bit should be 1 if the ith of these 8 vertices is in the maximum-weight independent set, and 0 otherwise. For example, if you think that the vertices 1, 4, 17, and 517 are in the maximum-weight independent set and the other four vertices are not, then you should enter the string 10011010 in the box below.

*************************/


int main() {
    
    
   
    int num;
    ifstream file("/Users/vivekdua/Documents/Personal/test-programs/test-Programs/leetcode/mwis.txt");
    if (!file.is_open()) {
        cout << "could not open file.." << std::endl;
    }
    file >> num;
    vector<int> vec(num + 1, 0);
    int weight = 0;
    int i = 1;
    while (file >> weight) {
        vec[i++] = weight;
    }
    vector<int> wvec(num, 0);
    wvec[1] = vec[1];
    for (int i = 2; i <= num; i++) {
        wvec[i] = max(wvec[i-1], wvec[i-2] + vec[i]);
    }
    set<int> s;
    i = num;
    while (i > 1) {
        if (wvec[i-1] >= wvec[i-2] + vec[i]) {
            // i is not in s
            i--;
        } else {
            s.insert(i);
            i -= 2;
        }
    }
    if (i == 1) {
        if (wvec[i] == vec[i]) {
            s.insert(i);
        }
    }
    cout << "The num of nodes is:" << s.size() << endl;
    
    vector<int> sample{1, 2, 3, 4, 17, 117, 517, 997};
    for (auto i : sample) {
        if (s.find(i) != s.end()) {
            cout << "1";
        } else {
            cout << "0";
        }
    }
    cout << endl;
   
    
    
}
