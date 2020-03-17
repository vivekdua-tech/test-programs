//
//  coderpad.cpp
//  test-Programs
//
//  Created by vidua on 2/25/20.
//  Copyright © 2020 Vivek Dua. All rights reserved.
//

#include <iostream>
#include <vector>
#include <memory>


using namespace std;

//
// Streams:
//
// [ 1, 4, 6, 8, 10, ... ]
// [ 2, 3, 6, 7, ... ]
// [ 5, 9, ... ]
// .....
//
// ------------------------
// [ 1, 2, 3, 4, 5, 6, 6, 7, 8, 9, 10, ... ]
//

// * Define interfaces for the streams.
// * Take N input streams containing sorted numbers and merge them into a single output
// stream that preserves the order.
//



template <typename T>
class MyIterator {
    
    vector<T> _vec;
    int       _currIndex = 0;
    
    void sort(vector<T>& vec1, vector<T>& vec2, vector<T>& result) {
        int i = 0;
        int j = 0;
        int k = 0;
        while (i < vec1.size() && j < vec2.size()) {
            if (vec1[i] < vec2[j]) {
                result[k++] = vec1[i++];
            } else if (vec1[i] > vec2[j]) {
                result[k++] = vec2[j++];
            } else {
                result[k++] = vec1[i++];
                result[k++] = vec2[j++];
            }
        }
    }
    
    void sort(vector<vector<T>>& vec, vector<T> &result) {
        vector<T> sorted;
        for (auto v : vec) {
            sort(v, sorted, result);
            sorted = result;
        }
    }
    
    MyIterator(vector<vector<T>> vec) {
        sort(vec, _vec);
    }
    
    T next() {
        if (_currIndex < _vec.size()) {
            return _vec[_currIndex++];
        }
    }
    
    bool hasNext() {
        if (_currIndex < _vec.size()) {
            return true;
        }
        return false;
    }
};




class Stream {
    
public:
    
    virtual int getfirst() = 0;
    virtual int get(int index)  = 0;
    virtual int getnext() = 0;
    virtual int size()    = 0;
    
    virtual void setfirst(int) = 0;
    virtual void setnext(int)  = 0;
    virtual void print() = 0;
    
};

using StreamPtr = shared_ptr<Stream>;

class intStream : public Stream {
public:
    vector<int> _vec;
    int         _currIndex;
    
    intStream(vector<int> v) : _vec(v) {}
    intStream() {}
    
    int getfirst() {
        _currIndex = 0;
        return _vec[0];
    }
    int get(int index) {
        if (index < _vec.size()) {
            _currIndex = index;
            return _vec[index];
        }
        return -1;
    }
    int getnext() {
        if (_currIndex < _vec.size()) {
            return _vec[_currIndex];
        }
        return -1;
    }
    void setfirst(int i) {
        _vec.push_back(i);
        _currIndex = 0;
        _currIndex++;
    }
    void setnext(int i) {
        _vec.push_back(i);
        _currIndex++;
    }
    int size() {
        return _vec.size();
    }
    void print() {
        for (auto i : _vec) {
            cout << " " << i;
        }
        cout << endl;
    }
};

shared_ptr<Stream> createStream() {
    return make_shared<intStream>();
}

shared_ptr<Stream> createStream(vector<int> v) {
    return make_shared<intStream>(v);
}

vector<StreamPtr> getStreams() {
    
    vector<int> v1 = {1, 4, 6, 8, 10};
    vector<int> v2 = {2, 3, 6, 7};
    vector<int> v3 = {5, 9};
    
    StreamPtr stream1 = createStream(v1);
    StreamPtr stream2 = createStream(v2);
    StreamPtr stream3 = createStream(v3);
    
    vector<StreamPtr> result;
    
    result.push_back(stream1);
    result.push_back(stream2);
    result.push_back(stream3);
    return result;
}

StreamPtr sortStream(StreamPtr first, StreamPtr second) {
    
    StreamPtr result = createStream();
    int i = 0;
    int j = 0;
    
    if (!first->size()) {
        return second;
    }
    
    if (!second->size()) {
        return first;
    }
    
    while ( i < first->size() && j < second->size() )
    {
        if (first->get(i) < second->get(j)) {
            result->setnext(first->get(i++));
        } else if (first->get(i) > second->get(j)) {
            result->setnext(second->get(j++));
        } else {
            result->setnext(first->get(i));
            result->setnext(second->get(j));
            i++;
            j++;
        }
    }
    if (i == first->size()) {
        while (j < second->size()) {
            result->setnext(second->get(j++));
        }
    } else if (j == second->size()) {
        while (i < first->size()) {
            result->setnext(first->get(i++));
        }
    }
    first = result;
    return first;
}


class Solution {
public:
    
    int longestLine(vector<vector<int>>& M) {
        int max_row = 0;
        int max_col = 0;
        int count_row = 0;
        int count_col = 0;
        vector<int> vec_sum(20000, 0);
        vector<int> vec_num(10000, 0);
        
        for (int i = 0; i < M.size(); i++) {
            for (int j = 0; j < M[i].size(); j++) {
                count_row += M[i][j];
                if (i == j) {
                    vec_num[i] += M[i][j];
                }
                vec_sum[i + j] = M[i][j];
            }
            max_row = count_row > max_row? count_row : max_row;
        }
        for (int j = 0; j < M[0].size(); j++) {
            for (int i = 0; i < M.size(); i++) {
                count_col += M[i][j];
            }
            max_col = count_col > max_col? count_col : max_col;
        }
        int max_diag = *max_element(vec_sum.begin(), vec_sum.end());
        int max_antidiag = *max_element(vec_num.begin(), vec_num.end());
        
        return max(max(max_diag, max_antidiag), max(max_col, max_row));
        
    }
};



                   
int main() {
                       
    vector<StreamPtr> streams = getStreams();
    int size = streams.size();
    StreamPtr result = createStream();
    for (int i = 0; i < size; i++) {
        result = sortStream(result, streams[i]);
    }
    result->print();
    
    Solution s;
    vector<int> v1 = {0,1,1,0};
    vector<int> v2 = {0,1,1,0};
    vector<int> v3 = {0,0,0,1};
    vector<vector<int>> vec = {v1, v2, v3};
    cout << " max is " << s.longestLine(vec);
    
    
    return 0;
}
