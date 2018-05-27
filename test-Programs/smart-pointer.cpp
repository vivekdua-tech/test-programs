//
//  smart-pointer.cpp
//  test-Programs
//
//  Created by Vivek Dua on 4/9/18.
//  Copyright © 2018 Vivek Dua. All rights reserved.
//

#include <iostream>


// An app defined smart pointer implementation

// Stores reference to the pointer of the underlying object.
// Stores total ref-count to the underlying object.

template<typename T>
class smartPointer {
protected:
    T *ref;
    size_t *ref_count;
    
    
    void remove() {
        --(*ref_count);
        if (*ref_count == 0) {
            delete ref;
            delete ref_count;
        }
    }
    
public:
    
    // Constructor : shared_ptr<string>(new string()) :
    smartPointer(T *ptr) {
        ref = ptr;
        ref_count = new size_t();
        *ref_count = 1;
    }
    
    
    // Copy constructor operator
    smartPointer(smartPointer<T> &sptr) {
        ref = sptr.ref;
        ref_count = sptr.ref_count;
        ++(*ref_count);
        
    }
    
    // Assignment operator
    // shared_ptr ptr1;
    // shared_ptr ptr2;
    // ptr1 = ptr2; // ref_count of ptr2 is decremented and ref_count of ptr1 is incremented.
    smartPointer<T> & operator=(smartPointer<T> &sptr) {
        ref = sptr.ref;
        ref_count = sptr.ref_count;
        ++(*ref_count);
        return *this;
    }
    
    ~smartPointer() {
        remove();
    }
    
    T*  get() {
        return ref;
    }
    
};
