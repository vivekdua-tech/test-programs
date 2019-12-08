//
//  function.cpp
//  test-Programs
//
//  Created by vidua on 12/6/19.
//  Copyright © 2019 Vivek Dua. All rights reserved.
//

#include <iostream>
#include <functional>
#include <vector>


using namespace std;

typedef function<int(int&, int&)> funcType;


int addition(int &x, int &y) {
    return x + y;
}

int substraction(int &x, int &y) {
    return x - y;
}

int main() {
    
    vector<funcType> fnVec;
    
    fnVec.push_back(addition);
    fnVec.push_back(substraction);
    
    int x = 3;
    int y = 2;
    
    for_each(fnVec.begin(), fnVec.end(), [&](funcType fn)
             { cout << "answer is:" << fn(x, y);});
}
