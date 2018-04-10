//
//  thread.cpp
//  test-Programs
//
//  Created by Vivek Dua on 4/7/18.
//  Copyright © 2018 Vivek Dua. All rights reserved.
//

#include <iostream>
#include <deque>
#include <thread>


using namespace std;

// Thread-safe DE queue
//

template <typename T>
class concurrentQueue
{
    
    
private:
    std::deque<T> _queue;
    std::mutex    _mutex;
    std::condition_variable _cond;
    
    
public:
    void push (T const& data) {
        std::unique_lock<std::mutex> lock(_mutex);
        _queue.push_back(data);
        lock.unlock();
        _cond.notify_one();
    }
    
    bool isEmpty () {
        return _queue.empty();
    }
    
    void pop (T& popped_value) {
        std::unique_lock<std::mutex> lock(_mutex);
        _cond.wait(lock, [this] { return !_queue.empty(); } );
        popped_value = _queue.back();
        cout << "popped value is " << popped_value;
        _queue.pop_back();
        
    }
};

class producer {
    
public:
    
    void run(concurrentQueue<int> &queue) {
        queue.push(10);
        queue.push(20);
        queue.push(30);
    }
};

class consumer {
    
public:
    
    void run(concurrentQueue<int> &queue) {
        int value;
        queue.pop(value);
        cout << "value is " << value;
        queue.pop(value);
        cout << "value is " << value;
        queue.pop(value);
        cout << "value is " << value;
    }
};



int main() {
    
    concurrentQueue<int> queue;
    
    std::thread t1(&producer::run, producer(), queue);
    std::thread t2(&consumer::run, consumer(), queue);
    
    if (t1.joinable()) t1.join();
    if (t2.joinable()) t2.join();
    
    return 0;
}
