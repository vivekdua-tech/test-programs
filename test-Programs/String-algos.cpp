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


int main() {
    
    string wordlist = "Do..not..try..this";
    ReverseWords(wordlist, "..");
    return 0;
    
}
