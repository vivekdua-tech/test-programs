//
//  hash.cpp
//  test-Programs
//
//  Created by Vivek Dua on 5/27/18.
//  Copyright © 2018 Vivek Dua. All rights reserved.
//

#include <iostream>
#include <string>

// User defined hash implementation


using namespace std;

class node {
    
public:
    
    int a;
    short b;
    string str;
    
    bool operator==(node& other) {
        return (a == other.a &&
                b == other.b &&
                str == other.str);
    }
};


namespace  std {
    template <>
    class hash<node> {
    public:
        size_t operator()(const node& n) const {
            size_t key = std::hash<int>()(n.a) ^
                         std::hash<short>()(n.b) ^
                         std::hash<string>()(n.str);
            return key;
        }
    };
}
