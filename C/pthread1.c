//
//  pthread.c
//  test-Programs
//
//  Created by vidua on 11/20/19.
//  Copyright © 2019 Vivek Dua. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

long long sum = 0;


// thread function
void* sum_runner(void *arg) {
    long long *limit_ptr = (long long *)arg;
    long long limit = *limit_ptr;
    
    for (long long i = 0; i <= limit; i++) {
        sum += i;
    }
    pthread_exit(&sum);
}

char* getString() {
    char message[] = "Hello World!";
    char *msg = malloc(100);
    strcpy(msg, message);
    return msg;
}


int main (int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage: %s <num>\n", argv[0]);
        exit(-1);
    }
    long long limit = atoll(argv[1]);
    long long *s = NULL;
    //thread id
    pthread_t tid;
    
    //create attributes
    pthread_attr_t attr;
    
    pthread_attr_init(&attr);
    
    pthread_create(&tid, &attr, sum_runner, &limit);
    
    // wait till we join
    pthread_join(tid, (void **)&s);
    printf("Sum is %lld\n", *s);
    
    printf("\n %s", getString());
}
