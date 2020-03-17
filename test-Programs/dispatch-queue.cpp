//
//  dispatch-queue.cpp
//  test-Programs
//
//  Created by vidua on 3/17/20.
//  Copyright © 2020 Vivek Dua. All rights reserved.
//

#include <stdio.h>


/***************************************************************************************************************
 
 Implementing an Asynchronous Dispatch Queue
 Updated: 20190910
 
 Previously, I introduced the concept of dispatch queues. Here’s a quick review of what a dispatch queue is, in case you haven’t read the previous article: The dispatcher contains multiple generic-use threads and a work queue. Threads can dispatch single functional operations to run asynchronously on the dispatch work threads.
 
 Apple is encouraging its app developers to move away from threads and to instead utilize central dispatch queues to run asynchronous processing. To quote Apple on the advantages of using dispatch queues instead of threads:
 
 It reduces the memory penalty your application pays for storing thread stacks in the application’s memory space.
 It eliminates the code needed to create and configure your threads.
 It eliminates the code needed to manage and schedule work on threads.
 It simplifies the code you have to write.
 These benefits are pretty real and tangible. As we saw in “The Problem With Threads”, threading introduces nondeterminism into our system. By controlling our threading models using concurrent and serial dispatch queues, we gain a better grasp on the nondeterminism of our system.
 
 The dispatch queue concept simplifies many of the threading scenarios encountered in embedded programming. Often, I just need to run small simple tasks asynchronously without blocking the primary thread. This results in spawning numerous threads with single small purposes:
 
 When the user presses a button, update the drawing on the screen
 When charging is complete, change LEDs and notify the system
 When recording starts, turn on an LED and start drawing the elapsed record time on the screen
 These simple steps can run on any generic thread. These trivial operations don’t require the overhead of explicit thread management, excessive context switching, and higher potential for other threading errors.
 
 Let’s see how we can implement an asynchronous dispatch queue of our own with C++11.
 
 Table of Contents:
 
 std::function Refresher
 A Queue of Functions
 Allocating Queue Threads
 Making Our Dispatch Queue Thread-Safe
 Dispatch Thread Handler
 How do I know when to run?
 Exiting
 Putting it all Together
 What if I haven’t ported std::thread or std::condition_variable?
 Further Reading
 std::function refresher
 As we saw last week with callbacks, std::function is a useful C++11 feature for capturing Callable objects. As a refresher:
 
 Instances of std::function can store, copy, and invoke any Callable target — functions, lambda expressions, bind expressions, or other function objects, as well as pointers to member functions and pointers to data members.
 
 For this example, we will prototype our function objects as:
 
 typedef std::function<void(void)> fp_t;
 A queue of functions
 The primary purpose of using a dispatch queue is to provide a first-in, first-out processing model.
 
 C++ luckily provides us a simple std::queue type which we can use for this purpose:
 
 std::queue<fp_t> q_;
 To add to the queue we push:
 
 q_.push(op);
 And to get the next item:
 
 auto op = q_.front(); //get the front item
 q_.pop(); //and pop it from the queue
 Allocating Queue Threads
 Our goal is to make our dispatch queue generic enough that we can change the number of threads for each queue we create. This allows us to create concurrent queues that allow generic tasks to run in parallel, as well as serial queues that only utilize one thread to protect a resource.
 
 C++11 provides a generic thread type: std::thread. Using std::vector, we can manage as many std::thread objects as we need:
 
 std::vector<std::thread> threads_;
 When constructing our dispatch queue, we can specify the number of threads desired. Then our constructor does the work of creating the required number of std::thread objects in our std::vector container.
 
 dispatch_queue(std::string name, size_t thread_cnt = 1) :
 name_{std::move(name)}, threads_(thread_cnt)
 {
 for(size_t i = 0; i < threads_.size(); i++)
 {
 //Initialize each thread object
 threads_[i] = std::thread(
 &dispatch_queue::dispatch_thread_handler, this);
 }
 }
 Making Our Dispatch Queue Thread-Safe
 Our dispatch queue is a shared resource in two potential directions:
 
 Any thread can add work to the queue
 The queue may have multiple threads which remove work from the queue for processing
 To make sure we implement this safely, we must rely on a locking mechanism. Luckily, C++11 also provides std::mutex:
 
 std::mutex lock_;
 The queue itself is the critical piece, so lock around queue modifications.
 
 Dispatch Thread Handler
 The dispatch queue worker thread handler should be a simple one. Its requirements are:
 
 Wait until there is something to run
 Pop that item from the queue
 Run the item
 Check whether I need to quit, if not: wait again
 How do I know when to run?
 Once we understand our requirements for the worker threads, we encounter a question: how do I know that there’s something to execute without keeping these threads awake?
 
 At this point, it may not surprise you to learn that C++11 also provides us a tool for this: std::condition_variable.
 
 std::condition_variable cv_;
 By pairing a condition variable with our std::mutex, we can let our threads sleep whenever there is no work to do. We wake them up again when there is data in the queue:
 
 std::unique_lock<std::mutex> lock(lock_);
 q_.push(op);
 
 // Manual unlocking is done before notifying, to avoid waking up
 // the waiting thread only to block again (see notify_one for details)
 lock.unlock();
 cv_.notify_all();
 In our worker thread, we wait until there is a new data notification. Upon waking, the thread will take the lock, get an item from the queue, and resume operation.
 
 void dispatch_queue::dispatch_thread_handler(void)
 {
 std::unique_lock<std::mutex> lock(lock_);
 
 do {
 //Wait until we have data
 cv_.wait(lock, [this]{
 return (q_.size());
 });
 
 //after wait, we own the lock
 if(q_.size())
 {
 auto op = std::move(q_.front());
 q_.pop();
 
 //unlock now that we're done messing with the queue
 lock.unlock();
 
 op();
 
 lock.lock();
 }
 } while (1);
 }
 It’s worth noting that condition variable’s wait function requires a lock. If the thread is waiting for data, it will release the mutex and only re-lock when notified and ready to run. This is why we lock at the end of the while loop.
 
 Exiting
 The next question is: how do I know when to stop running and exit?
 
 The simplest way is to add an exit_ or active_ boolean flag. When instructed to stop() or when destructing the queue, you can set this flag and wait for all threads to finish any work-in-progress.
 
 dispatch_queue::~dispatch_queue()
 {
 // Signal to dispatch threads that it's time to wrap up
 quit_ = true;
 cv_.notify_all();
 
 // Wait for threads to finish their work before we exit
 for(size_t i = 0; i < threads_.size(); i++)
 {
 if(threads_[i].joinable())
 {
 threads_[i].join();
 }
 }
 }
 Your worker thread can also add the exit signal to the condition variable wait:
 
 cv_.wait(lock, [this]{
 return (q_.size() || quit_);
 });
 And use the following while structure:
 
 do {
 // ...
 } while(!quit_);
 Putting it all Together
 I’ve added an example dispatch queue implementation on GitHub. Check it out!
 
 Don’t forget to compile with -std=c++11.

***************************************************************************************************************/
