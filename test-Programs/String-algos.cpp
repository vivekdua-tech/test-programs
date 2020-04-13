//
//  String-algos.cpp
//  test-Programs
//
//  Created by Vivek Dua on 4/6/18.
//  Copyright © 2018 Vivek Dua. All rights reserved.
//

#include <iostream>
#include <string>
#include <stack>
#include <map>
#include <vector>
#include <unordered_map>


using namespace std;
// Reverse words in the string.

// "Do not try this." should get printed as "this. try not Do"

// Use find() to get to the first delimiter pos. Then substr() to get to the
// first instance of the word w/o the de-limiter. Erase the charaters till the
// pos of the delimiter


void ReverseWords (string wordList, string delimiter)
{

    size_t pos = wordList.find(delimiter);
    stack<string> strStack;

    while (pos != std::string::npos) {
        string word = wordList.substr(0, pos);
        strStack.push(word);
        wordList.erase(0, pos + delimiter.length());
        pos = wordList.find(delimiter);
    }
    if (!wordList.empty()) {
        strStack.push(wordList);
    }
    while (!strStack.empty()) {
        cout << strStack.top();
        if (strStack.size() > 1) {
            cout << delimiter;
        }
        strStack.pop();
    }
}

void printPermute (string str, string result) {
    
    // string is empty - print the answer
    if (!str.length()) {
        // print and return
        cout << result << endl;
        return;
    }
    
    for (int i = 0; i < str.length(); i++) {
        char ch = str.at(i);
        // Get the rest of the string
        string ros = str.substr(0, i) + str.substr(i + 1);
        //recursive call
        printPermute(ros, result + ch);
    }
}

// Sort a string

void sortString (string &str) {
    sort(str.begin(), str.end());
    cout << str << endl;
}

// One string is permutation of the other

bool isPermuatation (string &str1, string& str2) {
    if (str1.length() != str2.length()) {
        return false;
    }
    sort(str1.begin(), str1.end());
    sort(str2.begin(), str2.end());
    if (str1 == str2) {
        return true;
    }
    return false;
}

// One string is permutation of the other
bool isPermutation ( string& str1, string& str2) {
    if (str1.length() != str2.length()) {
        return false;
    }
    vector<int> freq(128, 0);
    // count the chars
    for (auto s : str1) {
        freq[s - 'a'] ++;
    }
    for (auto s : str2) {
        if (freq[s - 'a'] == 0) {
            return false;
        }
        freq[s - 'a'] --;
    }
    return true;
}

// Replace all spaces with the char string '%20'

void replaceSpaces (string& str) {
    size_t pos = -1;
    while ((pos = str.find(' ', pos + 1)) != std::string::npos) {
        str.replace(pos, 1, "%20");
    }
}

// Remove leading and trailing whitespaces including all non-alphabetic chars
const string NON_ALPHABETIC_CHARS = " \n\r\t\f\v";

std::string trim (string& str) {
    // left and right trim
    size_t start = str.find_first_not_of(NON_ALPHABETIC_CHARS);
    str = (start == string::npos) ? "" : str.substr(start);
    
    size_t end = str.find_last_not_of(NON_ALPHABETIC_CHARS);
    str = (end == string::npos)? "" : str.substr(0, end + 1);
    
    return str;
}

// Strings - One edit away
// Let the input strings be s1 and s2 and lengths of input
// strings be m and n respectively.

// 1) If difference between m an n is more than 1,
// return false.
// 2) Initialize count of edits as 0.
// 3) Start traversing both strings from first character.
//     a) If current characters don't match, then
//        (i)   Increment count of edits
//        (ii)  If count becomes more than 1, return false
//        (iii) If length of one string is more, then only
//              possible  edit is to remove a character.
//             Therefore, move ahead in larger string.
//        (iv)  If length is same, then only possible edit
//              is to  change a character. Therefore, move
//              ahead in both strings.
//      b) Else, move ahead in both strings.




/*****************************************************************
   Longest non-repeating substr
   abcaddfd
   output = 3 for 'abc'
 


 int lengthOfLongestSubstring(string s) {
     vector<int> dict(256, -1);
     int maxLen = 0, start = -1;
     for (int i = 0; i != s.length(); i++) {
         if (dict[s[i]] > start)
             start = dict[s[i]];
         dict[s[i]] = i;
         maxLen = max(maxLen, i - start);
     }
     return maxLen;
 }
 ****************************************************************/

vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>&> anamap;
    vector<vector<string>> res;
    for (auto s: strs) {
        string tempstr = s;
        sort(tempstr.begin(), tempstr.end());
        auto it = anamap.find(tempstr);
        anamap[tempstr].push_back(s);
    }
    for (auto p : anamap) {
        res.push_back(p.second);
    }
    return res;
}


int lengthOfLongestSubstring(string s) {
    vector<int> dict(256, -1);
    int maxLen = 0, start = -1;
    for (int i = 0; i != s.length(); i++) {
        if (dict[s[i]] > start)
            start = dict[s[i]];
        dict[s[i]] = i;
        maxLen = max(maxLen, i - start);
    }
    return maxLen;
}

class Solution {
public:
    
    string removeslashatend(string path) {
        string res = path;
        while (res[res.length() - 1] == '/' && res.length() != 1) {
            res = res.substr(0, res.length() -1);
        }
        return res;
    }
    
    string removedotdotslash(string path) {
        size_t pos = 0;
        while ((pos = path.find("/..")) != string::npos) {
            path.erase(pos, 3);
        }
        return path;
    }
    
    string removedoubleslash(string path) {
        size_t pos = 0;
        while((pos = path.find("//")) != string::npos) {
            path.erase(pos, 1);
        }
        return path;
    }
    
    string simplifyPath(string path) {
        string result = path;
        result = removedotdotslash(result);
        result = removedoubleslash(result);
        result = removeslashatend(result);
        return result;
    }
};

int main() {
    
    string wordlist = "Do..not..try..this";
    ReverseWords(wordlist, "..");
    // printPermute("AABC", "");
    string str = "John Smith Sr";
    replaceSpaces(str);
    cout << str << endl;
    string str1 = "   John Smith  ";
    trim(str1);
    cout << str1 << endl;
    
    Solution s;
    cout << "result is: " << s.simplifyPath("/a/../../b/../c//.//");
    cout << "int is:" << round(3.71) << " " <<  round(3.41) << endl;
    
    return 0;
}
