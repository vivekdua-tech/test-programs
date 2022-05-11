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

// Use ^ and & to add two integers
// here XOR is a key as well because it's a sum of two integers in the binary form without
// taking carry into account. (x ^ y) = answer w/o carry
// carry=(x&y)<<1
// Keep doing the same bit operations till you get NO CARRY.



int getSum(int a, int b) {
    return b==0? a:getSum(a^b, (a&b)<<1); //be careful about the terminating condition;
}


/*******************************************************************************************
 
 
 Given a non-empty array of integers, every element appears twice except for one. Find that single one.
 
 Note:
 
 Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?
 
 Example 1:
 
 Input: [2,2,1]
 Output: 1
 Example 2:
 
 Input: [4,1,2,1,2]
 Output: 4
 
 Solution:
 
 Concept
 
 2 * (a + b + c) - (a + a + b + b + c) = c2∗(a+b+c)−(a+a+b+b+c)=c
 
 Concept
 
 If we take XOR of zero and some bit, it will return that bit
   a ^ 0 = a
 If we take XOR of two same bits, it will return 0
 a ^ a = 0
 a ^ b ^ a = b
 So we can XOR all bits together to find the unique number.
 
 public int singleNumber(int[] nums) {
 int a = 0;
 for (int i : nums) {
 a ^= i;
 }
 return a;
 }
 
 
 ********************************************************************/
 

#if 0

// Divide two integers w/o using division or multiplication
 
 List<Integer> doubles = new ArrayList<>();
 List<Integer> powersOfTwo = new ArrayList<>();

 int powerOfTwo = 1;

 /* Nothing too exciting here, we're just making a list of doubles of 1 and
  * the divisor. This is pretty much the same as Approach 2, except we're
  * actually storing the values this time. */
 while (divisor <= dividend) {
     powersOfTwo.add(powerOfTwo);
     doubles.add(divisor);
     powerOfTwo += powerOfTwo;
     divisor += divisor;
 }

 int quotient = 0;
 /* Go from largest double to smallest, checking if the current double fits.
  * into the remainder of the dividend */
 for (int i = doubles.size() - 1; i >= 0; i--) {
     if (doubles[i] <= dividend) {
         // If it does fit, add the current powerOfTwo to the quotient.
         quotient += powersOfTwo.get(i);
         // Update dividend to take into account the bit we've now removed.
         dividend -= doubles.get(i);
     }
 }

#endif // 0




#if 0


// Given an integer array nums where every element appears three times except for one, which appears exactly once. Find the single element and return it.
//

class Solution {
  public int singleNumber(int[] nums) {
    int seenOnce = 0, seenTwice = 0;

    for (int num : nums) {
      // first appearence:
      // add num to seen_once
      // don't add to seen_twice because of presence in seen_once

      // second appearance:
      // remove num from seen_once
      // add num to seen_twice

      // third appearance:
      // don't add to seen_once because of presence in seen_twice
      // remove num from seen_twice
      seenOnce = ~seenTwice & (seenOnce ^ num);
      seenTwice = ~seenOnce & (seenTwice ^ num);
    }

    return seenOnce;
  }
}

#endif



int main ()
{
    
    int m = 0x0a0a0a0a;
    // int n = 0xe;
    cout << "num bit set:" << numBitSet(m) << endl;
    return 0;
    // Insert N in M at bit posn X to Y ; X > Y
    // return insertNinM(m, n, 8, 4);
    
}





