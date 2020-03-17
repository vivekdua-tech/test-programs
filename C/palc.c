//
//  palc.c
//  test-Programs
//
//  Created by vidua on 3/12/20.
//  Copyright © 2020 Vivek Dua. All rights reserved.
//

#include "palc.h"


void swap (int *a, int *b) {
    if (!a || !b) return;
    int temp = *a;
    *a = *b;
    *b = temp;
}

int endian() {
    int a = 0x01020304;
    char *c = (char *)&a;
    return c[0] == 0x01 ? 1 : 0;
}

struct student {
    
    int id;
    
    char name[0x20];
    
};


struct student *student_init(int id, char *name)

{
    struct student *ptemp = (struct student *)my_calloc(1, sizeof(struct student));
    assert(ptemp);
    ptemp->id = id;
    strncpy(ptemp->name, name, 0x20);
    return ptemp;
}



void process_student_info(struct student *p) {
    
    if(p) {
        
        printf("student name: %s, id:%d\n", p->name, p->id);
        
    }
    
}



int main(int argc, char *argv[])

{
    
    struct student *p = student_init(1, "John Smith");
    
    process_student_info(p);
    
    return 0;
    
}

