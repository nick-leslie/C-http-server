//
// Created by nickl on 11/1/23.
//

#include <malloc.h>
#include <string.h>
#include "linkedList.h"


void pushString(struct stringLinkedList** head,char* string) {
    struct stringLinkedList* current = *head;
    struct stringLinkedList* new = malloc(sizeof(struct stringLinkedList));
    if(current != NULL) {
        while (current->next != NULL) {
            current = current->next;
        }
    }
    size_t len = strlen(string);
    new->next = NULL;
    new->data = malloc(sizeof(char) * len);
    new->len = len;
    memcpy(new->data,string,sizeof(char) * len);
    if(*head != NULL) {
        current->next = new;
    } else {
        *head = new;
        current = new;
    }
    printf("%s\n",current->data);
}

void freeLinkedList(struct stringLinkedList* head) {
    struct stringLinkedList* current = head;
    struct stringLinkedList* last = head;
    while (head->next != NULL) {
        current = head;
        while (current->next != NULL) {
            last = current;
            current = current->next;
        }
        free(current->data);
        free(current);
        last->next = NULL;
    }
    free(head->data);
    free(head);
}