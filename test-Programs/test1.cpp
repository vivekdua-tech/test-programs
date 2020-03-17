//
//  test1.cpp
//  test-Programs
//
//  Created by vidua on 1/30/20.
//  Copyright © 2020 Vivek Dua. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <queue>




using namespace std;
class Person {
    
public:
    virtual void getdata() = 0;
    virtual void putdata() = 0;
};


class Professor : public Person {
    //  The class Professor should have two integer members: publications and cur_id. There will be //two member functions: getdata and putdata. The function getdata should get the input from the // user: the name, age and publications of the professor. The function putdata should print the
    // name, age, publications and the cur_id of the professor.
    
    string name = "";
    int age = 0;
    int publications = 0;
    int id;
    static int cur_id;
    
public:
    Professor () : id(++cur_id) {};
    
    void getdata() override {
        cin >> name;
        cin >> age;
        cin >> publications;
    }
    void putdata() override {
        cout << name << " ";
        cout << age << " ";
        cout << publications << " ";
        cout << id << endl;
    }
};

class Student : public Person {
    //   The class Student should have two data members: marks, which is an array of size  and cur_id. It has two member functions: getdata and putdata. The function getdata should get the input from the user: the name, age, and the marks of the student in subjects. The function putdata should print the name, age, sum of the marks and the cur_id of the student.
    
    int marks[6];
    string name;
    int age;
    int id;
    int sum = 0;
    static int cur_id;
    
public:
    Student () : id(++cur_id) {}
    
    void getdata() override {
        cin >> name;
        cin >> age;
        for (int i = 0; i < 6; i++) {
            cin >> marks[i];
            sum += marks[i];
        }
        
    }
    void putdata() override {
        cout << name << " ";
        cout << age << " ";
        cout << sum << " ";
        cout << id << endl;
    }
};

int Professor::cur_id = 0;
int Student::cur_id = 0;


class Solution {
public:
    
    vector<vector<int>> getgraph(int num, vector<vector<int>> pre) {
        vector<vector<int>> g(num, vector<int>());
        for (auto v : pre) {
            g[v[1]].push_back(v[0]);
        }
        return g;
    }
    
    vector<int> getIndegree(int num, vector<vector<int>> &pre) {
        vector<int> ideg(num, 0);
        for (auto edge : pre) {
            ideg[edge[0]]++;
        }
        return ideg;
    }
    
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        
        vector<vector<int>> graph = getgraph(numCourses, prerequisites);
        vector<int> ideg = getIndegree(numCourses, prerequisites);
        queue<int> bfsq;
        vector<int> order;
        int v = 0;
        vector<int> visited(numCourses, -1);
        for (int i = 0; i < ideg.size(); i++) {
            if (ideg[i] == 0) {
                bfsq.push(i);
            }
        }
        while (v < numCourses) {
            
            if (bfsq.empty()) {
                return vector<int>();
            }
            
            while(!bfsq.empty()) {
                int curr = bfsq.front();
                bfsq.pop();
                order.push_back(curr);
                
                
                vector<int> edges = graph[curr];
                for (auto dep : edges) {
                    if (!(--ideg[dep])) {
                        bfsq.push(dep);
                    }
                }
            }
        }
        
        return order;
        
    }
    
};



int main() {
    
    Professor p1, p2, p3;
    p1.putdata();
    p2.putdata();
    p3.putdata();
    
    Solution s;
    vector<vector<int>> preq = {{1,0},{2,0},{3,1},{3,2}};
    s.findOrder(4, preq);
    
    return 0;
}
