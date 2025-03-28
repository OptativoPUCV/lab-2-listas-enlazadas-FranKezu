#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List* list = (List*) malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;
    return list;
}

void * firstList(List * list) {
    if(list == NULL || list->head == NULL) return NULL;
    list->current = list->head;
    
    return list->current->data;
}

void * nextList(List * list) {
    if(list == NULL || list->current == NULL || list->current->next == NULL) return NULL;
    list->current = list->current->next;
    return list->current->data;
}

void * lastList(List * list) {
    while(list->current->next != NULL)
        list->current = list->current->next;

    return list->current->data;
}

void * prevList(List * list) {
    if(list == NULL || list->current == NULL || list->current->prev == NULL) return NULL;
    list->current = list->current->prev;

    return list->current->data;
}

void pushFront(List * list, void * data) {
    if(list == NULL) return;

    Node* new = createNode(data);
    if (new == NULL) return;

    if(list->head){
        new->next = list->head;
        list->head->prev = new;
    }
    else list->tail = new;
    
    list->head = new;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    if(list == NULL) return;

    Node* new = createNode(data);
    if (new == NULL) return;

    new->prev = list->current;

    if(list->current->next){
        new->next = list->current->next;
        list->current->next->prev = new;
    }
    else list->tail = new;

    list->current->next = new;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    if(list == NULL) return NULL;

    Node *left = list->current->prev;
    Node *right = list->current->next;
    void *data = list->current->data;

    if(left == NULL) list->head = right;
    else left->next = right;

    if(right == NULL) list->tail = left;
    else right->prev = left;

    free(list->current);
    list->current = right;

    return data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}