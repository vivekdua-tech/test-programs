//
//  dynamic-progamming.cpp
//  test-Programs
//
//  Created by Vivek Dua on 4/7/18.
//  Copyright © 2018 Vivek Dua. All rights reserved.
//

#include <iostream>
#include <map>


using namespace std;

// Given an infinite number of coins of 25cents, 15cents, 10cents, 5cents, and 1cents, write a code to calculate
// the number of ways of representing n cents.

// Recursion, keep reducing by each coin and when we reach n equal to {25, 15, 10, 5, 1} increment the associated
// number by one. When we reach zero, increment the number of ways by one.


class way {
    
public:
    
    int q;
    int f;
    int d;
    int n;
    int c;
    
    bool operator <(const way& x) const {
        if (q < x.q) return true;
        if (f < x.f) return true;
        if (d < x.d) return true;
        if (n < x.n) return true;
        if (c < x.c) return true;
        
        return false;
    }
    
};


void count (int n, way pway, map<way, int> &wayMap) {
    
    
    way  currentWay = pway;
    
    if (n == 0) {
        if (wayMap.find(pway) == wayMap.end()) {
            // add it now
            wayMap.insert(pair<way, int>(pway, 1));
        }
        return;
    }

    if (n >= 1) {
        // 1-cent added
        currentWay.c++;
        count(n-1, currentWay, wayMap);
    }
    
    if (n >= 5) {
        // 5-cent added
        currentWay.n++;
        count(n-5, currentWay, wayMap);
    }
    
    if (n >= 10) {
        currentWay.d++;
        count(n-10, currentWay, wayMap);
    }
                          
    if (n >= 15) {
        currentWay.f++;
        count(n-15, currentWay, wayMap);
    }
    
    if (n >= 25) {
        currentWay.q++;
        count(n-25, currentWay, wayMap);
    }
    
}

int main() {
    
    map<way, int> waysMap;
    
    way currentWay;
    
    count(15, currentWay, waysMap);
    
    cout << "Number of ways.." << waysMap.size();
    
}


