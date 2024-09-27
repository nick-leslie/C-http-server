//
// Created by nickl on 11/1/23.
//

#include <stddef.h>

#ifndef SERVER_LINKEDLIST_H
#define SERVER_LINKEDLIST_H

#endif //SERVER_LINKEDLIST_H
struct stringLinkedList{
    char* data;
    size_t len;
    struct stringLinkedList* next;
};

void pushString(struct stringLinkedList** head,char* string);

void freeLinkedList(struct stringLinkedList* head);