//
//  bit-manup.c
//  test-Programs
//
//  Created by vidua on 10/18/19.
//  Copyright © 2019 Vivek Dua. All rights reserved.
//

#include <stdio.h>


// 6.1 Write a function setbits(x,p,n,y) that returns x with the n bits that begin at position p set to the rightmost n bits of y,
// leaving the other bits unchanged.

// n bits set
#define bits(n) (0x1 << (n)) - 1

// 0x00001111 ^ 0x00000011 = 0x00001100
// mask(4) ^ mask(2) = mask(2,3)
// mask(m) ^ mask(n) = mask(m-1, n)
// mask(m+1) ^ mask(n) = mask(bit-posn-m, bit-posn-n)


// set bits at bit posn x to bit posn y
#define mask(m, n)  (bits((m)+1) ^ bits((n)))

#define setbits(x, p, n, y) ((x) | mask((y), (p)))
#define invertbits(x, p, n, y) ((x) ^ mask((y), (p)))

int main() {
    
    int x = 0x10000001;
    int y = x;
    // 6.1
    x = setbits(x, 2, 3, 4);
    // 6.2
    y = invertbits(x, 2, 3, 4);
    printf("0x%x", x);
    printf("0x%x", y);
}

// Write a function invert(x,p,n) that returns x with the n bits that begin at position p inverted (i.e., 1 changed into
// 0 and vice versa), leaving the others unchanged

// Write a function rightrot(x,n) that returns the value of the integer x rotated to the right by n bit positions.

unsigned rightrot(unsigned x, unsigned n)
{
    while (n > 0) {
        if ((x & 1) == 1)
        x = (x >> 1) | ~(~0U >> 1);
        else
        x = (x >> 1);
        n--;
    }
    return x;
}

/*  Reverses string s[] in place  */

void reverse(char s[]) {
    int c, i, j;
    for ( i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}


void itoa(int n, char s[]) {
    int i, sign;
    
    if (( sign = n) < 0) {
        n = -n;
    }
    i = 0;
    do { /* generate digits in reverse order */
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    if (sign < 0) {
        s[i+=] = '-';
    }
    s[i] = '\0';
    reverse(s);
}

/*  Stores a string representation of integer n
in s[], using a numerical base of b. Will handle
up to base-36 before we run out of digits to use.  */

void itob(int n, char s[], int b) {
    static char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int i, sign;
    
    if ( b < 2 || b > 36 ) {
        fprintf(stderr, "EX3_5: Cannot support base %d\n", b);
        exit(-1);
    }
    
    if ((sign = n) < 0)
    n = -n;
    i = 0;
    do {
        s[i++] = digits[n % b];
    } while ((n /= b) > 0);
    if (sign < 0)
    s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}


