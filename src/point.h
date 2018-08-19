#ifndef POINT_H
#define POINT_H

#include "side.h"

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/** @file point.h */

typedef struct point point;

point* point_new(size_t, size_t, direction);

void point_free(point**);

size_t point_getRow(point*);

size_t point_getColumn(point*);

direction point_getSide(point*);


typedef struct ListNode ListNode;

ListNode* ListNode_new(point*);

void ListNode_free(ListNode**);

void ListNode_setNext(ListNode*, ListNode*);

ListNode* ListNode_getNext(const ListNode*);

point* ListNode_getPoint(const ListNode*);

void ListNode_setPoint(ListNode*, point*);


typedef struct List List;

List* List_new(void);

void List_free(List**);

void List_addFirst(List*, point*);

void List_insertAt(List*, point*, int);

void List_addLast(List*, point*);

void List_removeFirst(List*);

void List_removeAt(List*, int);

void List_removeLast(List*);

ListNode* List_getNodeAt(List*, int);

point* List_getPoint(List*, int);

int List_getSize(List*);

int List_count(List*);

bool List_hasPoint(List*, size_t, size_t, direction);

#endif
