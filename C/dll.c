//
//  dll.c
//  test-Programs
//
//  Created by vivekdua on 5/4/22.
//  Copyright © 2022 Vivek Dua. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// DLL

typedef struct _node {
    void *data;
    int size;
    struct _node *prev;
    struct _node *next;
} node;

typedef struct _dll {
    node *head;
    node *tail;
    int maxsize;
} dll;


dll* dll_init(int maxsize);
void insert(dll* dll, void *data, int datasize);
void delete(dll *dll, void *data, int datasize);
//void *find(dll *dll, void *data, int datasize);

dll* dll_init(int maxsize) {
    if (!maxsize) return NULL;
    
    dll *pDll = (dll *)malloc(sizeof(dll));
    pDll->maxsize = maxsize;
    pDll->head = NULL;
    pDll->tail = NULL;
    return pDll;
}

void display(dll *dll) {
    
    if (!dll) {
        printf("\n no elements..");
        return;
    }
    
    node *temp = dll->head;
    
    while(temp) {
        
        void *pdata = temp->data;
        switch(temp->size) {
            case sizeof(int):
            {
                int *p = (int *)pdata;
                printf("\n %d ", *p);
                break;
            }
            case sizeof(short):
            {
                short *s = (short *)pdata;
                printf("\n %hu", *s);
                break;
            }
            case sizeof(char):
            {
                char *c = (char *)pdata;
                printf("\n %hu", *c);
                break;
            }
        }
        temp = temp->next;
    }
}

void insert(dll *dll, void *data, int datasize) {
    if (!datasize || !data) return;
    
    node* pnode = (node *) malloc(sizeof(node));
    
    pnode->prev = NULL;
    pnode->next = NULL;
    pnode->data = (void *)malloc(datasize);
    memcpy(pnode->data, data, datasize);
    pnode->size = datasize;
    
    if (dll->tail) {
        dll->tail->next = pnode;
        pnode->prev = dll->tail;
        dll->tail = pnode;
    } else {
        dll->tail = pnode;
        dll->head = pnode;
    }
}


void delete(dll *dll, void *data, int datasize) {
    // compare data and remove the node
    if (!data || !datasize) return;
    
    node *temp = dll->head;
    while(temp) {
        if (!memcmp(temp->data, data, datasize)) {
            // found it
            node *prev = temp->prev;
            node *next = temp->next;
            if (prev) {
                prev->next = next;
            }
            if (next) {
                next->prev = prev;
            }
            if (temp == dll->head) {
                dll->head = temp->next;
                if (temp->next) {
                    temp->next->prev = NULL;
                }
            }
            free(temp->data);
            free(temp);
            return;
        }
        temp = temp->next;
    }
    
}


int main() {
    
    int i = 10;
    short j = 4;
    char k = 6;
    
    dll* pdll = dll_init(10);
    insert(pdll, &i, sizeof(i));
    insert(pdll, &j, sizeof(j));
    insert(pdll, &k, sizeof(k));
    display(pdll);
    delete(pdll, &i, sizeof(i));
    delete(pdll, &k, sizeof(k));
    delete(pdll, &j, sizeof(j));
    free(pdll);
    display(pdll);
    
}



