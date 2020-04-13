//
//  addrmatch.cpp
//  test-Programs
//
//  Created by vidua on 3/19/20 at 02:50PM.
//  Copyright © 2020 Vivek Dua. All rights reserved.
//

#include <iostream>
#include <string>
#include <algorithm>


using namespace std;

#define ADDRMASK(n) \
    (~(0xFFFFFFFF >> (n)))


class v4addr_match {
    
private:
    int _addr;
    int _len;

public:
    
    int fromdotteddecimal(string v4addr) {
        int result = 0;
        int index = 3;
        string remstr = v4addr;
        string strbyte;
        size_t pos = v4addr.find(".");
        while (pos != string::npos && index > 0) {
            strbyte = remstr.substr(0, pos);
            remstr = remstr.substr(pos+1);
            if (std::all_of(strbyte.begin(), strbyte.end(), [&](char c){ return isdigit(c); }) == false) {
                return false;
            }
            int byte = atoi(strbyte.c_str());
            result |= (byte << (8 * index--));
            pos = remstr.find(".");
        }
        if (pos != string::npos || index > 0) {
            return -1;
        } else if (!remstr.empty()) {
            if (std::all_of(remstr.begin(), remstr.end(), [&](char c){ return isdigit(c); }) == false) {
                return false;
            }
            int byte = atoi(remstr.c_str());
            result |= byte;
        }
        return result;
    }
    
    
    bool parse_validate (string cidr_addr) {
        // should have 3 dots and a slash for len
        // no non-numeric chars
        int result = 0;
        int index = 3;
        size_t pos = cidr_addr.find("/");
        if (pos == string::npos) {
            return false;
        }
        string addrstr = cidr_addr.substr(0, pos);
        string lenstr = cidr_addr.substr(pos+1);
        pos = addrstr.find(".");
        string remstr = addrstr;
        string strbyte;
        while (pos != string::npos && index > 0) {
            strbyte = remstr.substr(0, pos);
            remstr = remstr.substr(pos+1);
            if (std::all_of(strbyte.begin(), strbyte.end(), [&](char c){ return isdigit(c); }) == false) {
                return false;
            }
            int byte = atoi(strbyte.c_str());
            result |= byte << (8 * index--);
            pos = remstr.find(".");
        }
        if (pos != string::npos || index > 0) {
            return false;
        } else if (!remstr.empty()) {
            if (std::all_of(remstr.begin(), remstr.end(), [&](char c){ return isdigit(c); }) == false) {
                return false;
            }
            int byte = atoi(remstr.c_str());
            result |= byte;
        }
        if (!std::all_of(lenstr.begin(), lenstr.end(), [&](char c){ return isdigit(c); })) {
            return false;
        }
        _addr = result;
        _len = atoi(lenstr.c_str());
        return true;
    }
    
    bool set_v4addr (string cidr_addr) {
        return parse_validate(cidr_addr);
    }
    
    // 10.10.10.10 matches 10.10.10.10/24
    bool match (string v4addr) {
        int addr = fromdotteddecimal(v4addr);
        int addrmask = _addr & ADDRMASK(_len);
        int inputmask = addr & ADDRMASK(_len);
        return (addrmask == inputmask);
    }
};

int main() {
    
    v4addr_match addr_match;
    string addr = "10.10.10.2";
    string cidr = "10.10.10.10/24";
    
    if (addr_match.parse_validate(cidr) == false) {
        cout << "addr/mask parse validation failed" << endl;
        return 0;
    }
    if (addr_match.match(addr)) {
        cout << addr << " matched" << endl;
    } else {
        cout << addr << " not matched" << endl;
    }
    return 0;
}
