//
//  heap.cpp
//  test-Programs
//
//  Created by Vivek Dua on 5/28/18.
//  Copyright © 2018 Vivek Dua. All rights reserved.
//

#include <iostream>
#include <queue>
#include <map>
#include <algorithm>



// min_heap and max_heap :
//     min or max element at the root of the Binary tree.
//     Insertion and extract_min are two methods supported.
//     Insertion is done by inserting at the bottommost right sub-tree element and then bubble up the
//     the node by following the min.max criteria: root.data < root.left.data and root.data < root.right.data
//     Extract-min: remove the root node and replace it with the rightmost node element. Bubble down the
//                  nodes following the property.

// in C++ , heap STL is priority_queue<> :

// max-heap: priority_queue<int>
// min-heap: priority_queue<int, vector<int>, greater<int>>

using namespace std;

// User defined class, Point
class Point
{
    int x;
    int y;
public:
    Point(int _x, int _y)
    {
        x = _x;
        y = _y;
    }
    int getX() const { return x; }
    int getY() const { return y; }
};

// To compare two points
class myComparator
{
public:
    int operator() (const Point& p1, const Point& p2)
    {
        return p1.getX() > p2.getX();
    }
};


// Given N candies of different type, mary has to given N/2 of them to her sister such that she has
// left with it maximum number of different types of candies. N is even. What is the max type she can have
// T = [5, 6, 7, 7, 7, 8, 9, 8]
// 8/2 she has to give 4 so she can give 7, 7, 8, 9. she can then have 5, 6, 7, 8,

unsigned maxdifftype (vector<int> &T) {
   // Put the elements in Set
    //  and then return min(set.size(), N/2);
    return 0;
}


// Driver code
int main ()
{
    // Creates a Min heap of points (order by x coordinate)
    priority_queue <Point, vector<Point>, myComparator > pq;
    
    // Insert points into the min heap
    pq.push(Point(10, 2));
    pq.push(Point(2, 1));
    pq.push(Point(1, 5));
    
    // One by one extract items from min heap
    while (pq.empty() == false)
    {
        Point p = pq.top();
        cout << "(" << p.getX() << ", " << p.getY() << ")";
        cout << endl;
        pq.pop();
    }
    
    vector<int> vec = {5, 6, 7, 7, 7, 8, 8, 9, 7, 7, 7, 8};
    
    cout << "maxdiff type is:" << maxdifftype(vec);
    
    return 0;
}
