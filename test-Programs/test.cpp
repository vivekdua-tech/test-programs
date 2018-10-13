//
//  test.cpp
//  test-Programs
//
//  Created by vidua on 9/24/18.
//  Copyright © 2018 Vivek Dua. All rights reserved.
//

#include <iostream>
#include <string>
#include <unordered_map>



using namespace std;

unordered_map<string,string> mapStr;
int getIndex(string s) {
    
    for (int index = 0; index < s.length() - 1; index++) {
        if (s[index] != s[index + 1]) {
            return index;
        }
    }
    return -1;
}

string shortStr(string s) {
    string origStr = s;
    auto it = mapStr.find(s);
    if (it != mapStr.end()) {
        return it->second;
    }
    if (s.length() == 1) {
        return s;
    }
    int index = getIndex(s);
    while (index != -1) {
        string firstHalf = s.substr(getIndex(s), 2);
        string shortFirstHalf = shortStr(firstHalf);
        s.replace(getIndex(s), 2, shortFirstHalf);
        if ((it = mapStr.find(s)) != mapStr.end()) {
            // stash it if s > 3
            //if (origStr.length() >= 3) {
            //    mapStr.insert(pair<string, string>(origStr, it->second));
            //}
            return it->second;
        }
        index = getIndex(s);
    }
    return s;
}


// Complete the stringReduction function below.
int stringReduction(string s) {
    
    
    return shortStr(s).length();
}

int main()
{
    mapStr.insert(pair<string, string>(string("ab"), string("c")));
    mapStr.insert(pair<string, string>(string("ac"), string("b")));
    mapStr.insert(pair<string, string>(string("ba"), string("c")));
    mapStr.insert(pair<string, string>(string("bc"), string("a")));
    mapStr.insert(pair<string, string>(string("ca"), string("b")));
    mapStr.insert(pair<string, string>(string("cb"), string("a")));
    
    string s = "accbaacabbbaacabcbcaccaabcbccbacbcbaabacacababcaacbcccbaccacaabcbaaccbcabccbccbcbbcba";
        
    int result = stringReduction(s);
    cout << " Result: " << result << endl;
    
    return 0;
}
