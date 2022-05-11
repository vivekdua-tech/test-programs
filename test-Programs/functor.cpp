//
//  functor.cpp
//  test-Programs
//
//  Created by vivekdua on 4/2/22.
//  Copyright © 2022 Vivek Dua. All rights reserved.
//

#include <iostream>
#include <string>

using namespace std;


class A {
public:
    std::function<void(int, const string&)> _callback = nullptr;
    
    void foo(int i, const string& s) {
        if (_callback) {
            _callback(i, s);
        }
    }
};

class B {
public:
    A objA;
    
    void eventHandler(int i, const string& s) {
        cout << s << " : " << i << endl;
    }
    
    B() {
        // bind this class method to the callback of A
        auto aFunc = bind(&B::eventHandler, this, placeholders::_1, placeholders::_2);
        objA._callback = aFunc;
    }
    void doSomething(int i, const string& s) {
        objA.foo(i, s);
    }
};

int main() {
    B objB;
    objB.doSomething(100, "event Fired");
}
