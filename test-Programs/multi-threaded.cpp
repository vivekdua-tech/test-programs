//
//  multi-threaded.cpp
//  test-Programs
//
//  Created by Vivek Dua on 4/9/18.
//  Copyright © 2018 Vivek Dua. All rights reserved.
//

#include <iostream>
#include <thread>
#include <mutex>


using namespace std;


// Implement a MT solution for FizzBuzz problem statement.
// Given a number n, print numbers from 1 to n, when the number if divisible by
// 3, print Fizz, when the number if divisible by 5, print buzz.
// When the number is divisible by both print FizzBuzz and when the number is any of those,
// just print the number. Use 4 different threads for four of these calculations.


// Implement a class which implements a 'run' where the number is incremented
// and each of the four thread operates on the number one by one and processes the
// logic independently.

class number {
private:
    
    int _n;
    std::mutex _mutex;
    
public:
    number(int n) : _n(n) {}
    
    
    void run (bool devby3, bool devby5) {
        std::unique_lock<std::mutex> lock(_mutex);
        static int current = 1;

        if (current > _n) {
            return;
        }
        if ((current % 3 == 0) == devby3 &&
            (current % 5 == 0) == devby5) {
            std::cout << "FizzBuzz" << std::endl;
        }

        if ((current % 3 == 0) == devby3) {
            std::cout << "Fizz" << std::endl;
        }
        if ((current % 5 == 0) == devby5) {
            std::cout << "Buzz" << std::endl;
        }
        current++;
    }
};


int main() {
    
    number *n1 = new number(15);
    
    std::thread T1(&number::run, n1, true, true);
    std::thread T2(&number::run, n1, true, false);
    std::thread T3(&number::run, n1, false, true);
    std::thread T4(&number::run, n1, false, false);
    
}