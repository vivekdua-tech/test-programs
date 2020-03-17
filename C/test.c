//
//  test.c
//  test-Programs
//
//  Created by vidua on 10/18/19.
//  Copyright © 2019 Vivek Dua. All rights reserved.
//

#include "test.h"


// pointers to functions

int sum (int a, int b) {
    return a + b;
}

typedef int (*func_ptr_type)(int a, int b);






// Write a program to print all lines which are greater than 80 chars
int main() {
    
    char *line = NULL;
    size_t linesz = 0;
    size_t read = 0;
    
    // test pointer to char arrays
    char *cptr[] = {"Manan", "Ananya", "Pragati"};
    
    
    printf("%s %s %s\n", cptr[0], cptr[1], cptr[2]);
    /****
    while((read = getline(&line, &linesz, stdin)) != EOF) {
        // if size more than 80 print it
        if (read > 20) {
            printf("line-size: %ld\n", linesz);
            printf("read: %ld\n", read);
            printf("%s", line);
        }
    }
    // int no = atoi("789");
    // printf("%d", no);
    free(line);
    ****/
    
    func_ptr_type fp;
    fp = sum;
    
    printf("\n calling FP as sum %d", (*fp)(2, 3));
    
}
