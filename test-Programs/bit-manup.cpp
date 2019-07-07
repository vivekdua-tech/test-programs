//
//  bit-manup.cpp
//  test-Programs
//
//  Created by Vivek Dua on 4/24/18.
//  Copyright © 2018 Vivek Dua. All rights reserved.
//

#include <iostream>
#include <math.h>


using namespace std;


#define MASK(N) \
    ((0x1 << N) - 1)

// FLEXMASK(X, Y) -> 00001111100000 x and y bit posn have 1's.
#define FLEXMASK(X, Y) \
    (MASK((X)) ^ MASK((Y)))

#define INVERSEFLEXMASK(X, Y) ~FLEXMASK((X), (Y))

// Clear bits X to Y in M
#define CLEARBITS(M, X, Y)   \
    ((M) & INVERSEFLEXMASK((X), (Y)))

// left shift by Y bits
#define LSHIFT(N, Y) \
    ((N) << (Y))

//Insert N in M at bit posn X to Y
#define INSERTVALUE(M, N, X, Y) \
     CLEARBITS(M, X, Y) | LSHIFT(N, Y)

int insertNinM(int m, int n, int x, int y) {
    
    cout << "mask(4): " << hex << MASK(4) << endl;
    
    int flex = FLEXMASK(4, 8);
    cout << "Flexmask(2, 7): " << hex << flex << endl;
    
    int result = INSERTVALUE(m, n, x, y);
    
    int clear = CLEARBITS(m, x, y);
    
    int ls = LSHIFT(n, y);
    
    cout << "clear is:" << hex << clear << endl;
    
    cout << "ls is:" << hex << ls << endl;
    
    cout << "Value is" << hex << result << endl;
    
    return 0;
    
}

// Write a function to determine the number of bits you would need to flip to convert integer A to integer B.
// This seemingly complex problem is actually rather straightforward.To approach this, ask yourself how you would
// figure out which bits in two numbers are different. Simple: with an XOR.

int numBitSet(int n) {
    int count = 0;
    for (int i = n; i != 0; i &= i - 1) {
        count++;
    }
    return count;
}
// a function to determine the number of bits you would need to flip to convert integer A to integer B.
int numBitSwapRequired(int m, int n) {
    return numBitSet(m ^ n);
}

int main ()
{
    
    int m = 0x0a0a0a0a;
    // int n = 0xe;
    cout << "num bit set:" << numBitSet(m) << endl;
    return 0;
    // Insert N in M at bit posn X to Y ; X > Y
    // return insertNinM(m, n, 8, 4);
    
}





