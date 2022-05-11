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
#include <array>
#include <future>
#include <vector>
#include <map>


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
    std::array<std::condition_variable, 4> _cond;
    bool thread_1_done = false;
    bool thread_2_done = false;
    bool thread_3_done = false;
    bool thread_4_done = false;

    
public:
    number(int n) : _n(n) {}
    
    
    void run (int tname, bool devby3, bool devby5) {
        
        static int current = 1;

        while (current <= _n) {
            
            switch (tname) {
            case 1:
            {
                std::unique_lock<std::mutex> lock(_mutex);
                _cond[1].wait(lock, [this]() { return thread_3_done; });
                if ((current % 3 == 0) == devby3 &&
                    (current % 5 == 0) == devby5) {
                    std::cout << "Thread-1: " << current << "FizzBuzz" << std::endl;
                }
                thread_1_done = true;
                _cond[2].notify_one();
                break;
            }
            case 2:
            {
                std::unique_lock<std::mutex> lock(_mutex);
                if ((current % 3 == 0) == devby3) {
                    std::cout << "Thread-2: " << current << "Fizz" << std::endl;
                }
                thread_2_done = true;
                _cond[0].notify_one();
                break;
            }
            case 3:
            {
                std::unique_lock<std::mutex> lock(_mutex);
                _cond[0].wait(lock, [this]() { return thread_2_done; });
                if ((current % 5 == 0) == devby5) {
                    std::cout << "Thread-3: " << current << "Buzz" << std::endl;
                }
                thread_3_done = true;
                _cond[1].notify_one();
                break;
            }
            case 4:
            {
                std::unique_lock<std::mutex> lock(_mutex);
                _cond[2].wait(lock, [this](){ return thread_1_done; });
                if ((current % 3 == 0) == devby3 &&
                    (current % 5 == 0) == devby5) {
                    std::cout << "Thread-4: " << current << std::endl;
                }
                current++;
                break;
            }
            }
        }

    }
};

// use futures for single shot event communications

std::promise<int> _promise;

class react {
public:
    void run () {
        cout << "react called.." << endl;
    }
    react () {
        run();
    }
};

class detect {
public:
    int numThreads = 10;
    void run () {
        auto sf = _promise.get_future().share();
        std::vector<std::thread> tvec;
        
        for (int i = 0; i < numThreads; i++) {
            tvec.emplace_back([sf](){sf.wait(); react();});
        }
        _promise.set_value(1);
        
        for (auto &t : tvec) {
            if (t.joinable()) {
                t.join();
            }
        }
    }
    detect () {
        run();
    }
};


void func(std::promise<int> result_promise) noexcept
{
    result_promise.set_value(42);
}

int main() {
    
    number *n1 = new number(15);
    // std::thread t1(&object::run, object-ptr, args1, args2..);
    std::thread T1(&number::run, n1, 1, true, true);
    std::thread T2(&number::run, n1, 2, true, false);
    std::thread T3(&number::run, n1, 3, false, true);
    std::thread T4(&number::run, n1, 4, false, false);
    
    
    if (T1.joinable()) T1.join();
    if (T2.joinable()) T2.join();
    if (T3.joinable()) T3.join();
    if (T4.joinable()) T4.join();
    
    
    // Promise and future example
    detect();
    
    
    std::promise<int> result_promise;
    std::future<int> result_future = result_promise.get_future();
    std::thread t{func, std::move(result_promise)};
    int result = result_future.get();
    t.join();
}


// static singleton instances are inherently thread-safe.
// Just like singleton, if we want to make a function/non-static variable behave like singleton
// which is called once and is thread, use std::once_flag


// Just like static initialization of singleton class, we want logger to init the
// connection ONLY once. Without getting in mutex complexity, we can have once_flag which
// implicitly makes sure that class variable thread-safe..
//

class NetworkConnection;

class Logger {
    std::once_flag _once;
    NetworkConnection _conn;
    
    NetworkConnection& getConn() {
        std:call_once(_once, [&]() {
            _conn = NetworkConnection(defaultHost);
        });
        return *_conn;
    }
};


// Equivalent of pthread_rw_lock - Read/Write lock - Separate locks for read and writes
// std::shared_mutex
// mutable std::shared_mutex rw_;
// Can be used to to read or write locks

class ThreadSafeConfig {
    std::map<std::string, int> settings_;
    mutable  std::shared_mutex rw_;
    
    void set(const string& name, int value) {
        unique_lock<shared_mutex> lk(rw_); // Write Lock
        settings_.insert(name, value);
    }
    int get(const string& name) const {
        shared_lock<shared_mutex> lk(rw_); // Read lock
        return settings_.at(name);
    }
}



// C++11 Promise/Future - Single shot promise and future paradigm -
// async returns std::promise which can be called with get_future()
std::future<int> f1 = std::async(std::launch::async, []() {
    puts("Hello from thread A");
    return 1;
});

std::future<int> f2 = std::async(std::launch::async, []() {
    puts("Hello from thread B");
    return 1;
});

int result = f1.get() + f2.get();
