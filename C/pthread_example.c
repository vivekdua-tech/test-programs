//
//  pthread_example.c
//  test-Programs
//
//  Created by vidua on 4/4/20.
//  Copyright © 2020 Vivek Dua. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


void *foo(void *vargp) {
    int id;
    id = *((int*)vargp);
    
    printf("Thread %d\n", id);
    pthread_exit(0);
}
int main() {
    pthread_t tid[2];
    int i;
    for (i = 0; i < 2; i++)
        pthread_create(&tid[i], 0, foo, &i);
    pthread_join(tid[0], 0);
    pthread_join(tid[1], 0);
}
