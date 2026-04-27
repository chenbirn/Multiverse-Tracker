#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Defs.h"

typedef struct LinkedList *linked_list;

// create list
linked_list createLinkedList(FreeFunction freef, PrintFunction printf, EqualFunction partf);

// destroy list
status destroyList(linked_list);

// add value to list
status appendNode(linked_list, Element elem);

// remove value from list
status deleteNode(linked_list, Element elem);

// print all values in list
status displayList(linked_list);

// get value in list by index (starts from 1)
Element getDataByIndex(linked_list, int index);

//get size of list
int getLengthList(linked_list);

//search for a value in list
Element searchByKeyInList(linked_list, Element elem);

#endif //LINKEDLIST_H
