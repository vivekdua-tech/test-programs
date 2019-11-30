//
//  pthread2.c
//  test-Programs
//
//  Created by vidua on 11/25/19.
//  Copyright © 2019 Vivek Dua. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>

// counting up and counting down threads - one counts up and the other counts down

int sum = 0;

#define NUM_LOOPS 10000000

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// thread function
void* counting_thread(void *arg) {
    int offset = *((int *)arg);
    
    for (int i = 0; i < NUM_LOOPS; i++) {
        pthread_mutex_lock(&mutex);
        // critical section
        sum += offset;
        // critical section
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}


int main (int argc, char *argv[])
{
    if (argc < 1) {
        printf("Usage: %s <num>\n", argv[0]);
        exit(-1);
    }
    struct timeval tv;
    time_t prevtime;
    gettimeofday(&tv, NULL);
    prevtime = tv.tv_sec;
    
    //thread id
    pthread_t tid1;
    int offset1 = 1;
    pthread_create(&tid1, NULL, counting_thread, &offset1);
    
    pthread_t tid2;
    int offset2 = -1;
    pthread_create(&tid2, NULL, counting_thread, &offset2);

    // wait till we join
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    
    gettimeofday(&tv, NULL);
    time_t newtime = tv.tv_sec;
    printf("Sum is %d and the elasped time:%ld\n", sum, newtime - prevtime);
    
}
