//
//  hash.cpp
//  test-Programs
//
//  Created by Vivek Dua on 5/27/18.
//  Copyright © 2018 Vivek Dua. All rights reserved.
//

#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <map>

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

namespace std {
template <>
    class hash<pair<string,string>> {
    public:
        size_t operator() (const pair<string,string>& n) const {
            size_t key = std::hash<string>()(n.first) ^
            std::hash<string>()(n.second);
            return key;
        }
    };
}

// user defined maps

typedef struct _key {
    char macaddr[6];
    short vlan;
} key;

typedef struct _mac_value {
    char port;
} mac_value;

namespace std {
    template <>
    class less<key> {
    public:
        bool operator() (const key& k1, const key& k2) const {
            if (k1.macaddr[0] < k2.macaddr[0]) return true;
            if (k1.macaddr[1] < k2.macaddr[1]) return true;
            if (k1.macaddr[2] < k2.macaddr[2]) return true;
            if (k1.macaddr[3] < k2.macaddr[3]) return true;
            if (k1.macaddr[4] < k2.macaddr[4]) return true;
            if (k1.macaddr[5] < k2.macaddr[5]) return true;
            if (k1.vlan < k2.vlan) return true;
            return false;
        }
    };
}

map<key, mac_value> mactable;

int main () {
    node n(1, 23, "Vivek");
    cout << "hash of the node n is:" << std::hash<node>()(n);
    
    unordered_set<pair<string,string>> str_set;
    str_set.insert(pair<string,string>("Vivek", "pragati"));
    cout << " the size is" << str_set.size() << endl;
    
    key key1;
    key1.macaddr[0] = 0x00;
    key1.macaddr[0] = 0x01;
    key1.macaddr[0] = 0x02;
    key1.macaddr[0] = 0x03;
    key1.macaddr[0] = 0x04;
    key1.macaddr[0] = 0x05;
    key1.vlan = 0x40;
    mac_value value1;
    value1.port = 10;
    
    mactable.insert(pair<key, mac_value>(key1, value1));
    
}
