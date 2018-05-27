//
//  bit-manup.cpp
//  test-Programs
//
//  Created by Vivek Dua on 4/24/18.
//  Copyright © 2018 Vivek Dua. All rights reserved.
//

#include <iostream>

using namespace std;


#define MASK(N) \
    ~(~0 << N)

// FLEXMASK(X, Y) -> 00001111100000 x and y bit posn have 1's.
#define FLEXMASK(X, Y) \
    MASK((X)) ^ MASK((Y))

#define INVERSEFLEXMASK(X, Y) ~FLEXMASK((X), (Y))

//Insert M in N at bit posn X to Y
#define INSERTVALUE(M, N, X, Y) \
    (((M) & INVERSEFLEXMASK((X), (Y))) |  (((N) << (Y))))


int main ()
{
    
    cout << "mask(2): " << hex <<
    MASK(2);
    
    int flex = FLEXMASK(2, 5);
    cout << "Flexmask(2, 5): " << hex << flex;
    
#if 0
    
    int m = 0x0a0a0a0a;
    int n = 0xe;
    
    int result = INSERTVALUE(m, n, 8, 5);
    
    
    int mask = FLEXMASK(8, 5);
    
    cout << "flex mask is" << hex <<
    mask << endl;
    
    int invmask = INVERSEFLEXMASK(8, 5);
    
    
    cout << "inverse flex mask is" << hex <<
    invmask << endl;
    
    int value1 = m & invmask;
    
    cout << "value1 is : " << hex << value1 << endl;
    
    int value2 = n << 5;
    
    cout << "value2 is : " << hex << value2 << endl;
    
    
    int value3 = value1 | value2;
    
    cout << " OR of value1 and value2 is" << hex <<
    value3 << endl;
    
    
    cout << "Value is" << hex << result << endl;
#endif
    
}



