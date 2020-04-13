//
//  list.cpp
//  test-Programs
//
//  Created by Vivek Dua on 5/7/18.
//  Copyright © 2018 Vivek Dua. All rights reserved.
//

#include <iostream>


struct node {
    struct node *next;
    int data;
};


struct linkledList {
    node *head;
};


void insert( linkledList list, node *insert)
{
    
    node *temp = list->head;
    node *prev = NULL;
    
    // insert at the head if the data is less than the head.
    if (temp->data > insert->data) {
        insert->next = head;
        head = insert;
    } else {
        while (temp != NULL) {
        
            if (insert->data >= temp->data) {
                temp->next = insert;
                if (prev) {
                   prev->next = insert;
                }
            }
            prev = temp;
            temp = temp->next;
         }
    }
    
    
}
