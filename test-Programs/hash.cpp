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
    
    int  _a;
    short _b;
    string _str;
    
    node (int a, short b, string str) :
        _a(a), _b(b), _str(str) {}
    
    bool operator==(node& other) {
        return (_a == other._a &&
                _b == other._b &&
                _str == other._str);
    }
};


namespace  std {
    template <>
    class hash<node> {
    public:
        size_t operator()(const node& n) const {
            size_t key = std::hash<int>()(n._a) ^
                         std::hash<short>()(n._b) ^
                         std::hash<string>()(n._str);
            return key;
        }
    };
}



int main () {
    node n(1, 23, "Vivek");
    cout << "hash of the node n is:" << std::hash<node>()(n);
}
