#include "LinkedList.h"
#include "KeyValuePair.h"

// Node Structure
typedef struct Node {
    Element elem;
    struct Node *next;
} *node;

//LinkedList structure
struct LinkedList {
    int size;
    node head;
    FreeFunction freeElement;
    PrintFunction printElement;
    EqualFunction partElement;
};

//create linked list
linked_list createLinkedList(FreeFunction freef, PrintFunction printf, EqualFunction partf) {
    linked_list lst = malloc(sizeof(struct LinkedList));
    if (lst == NULL) {
        return NULL;
    }
    lst->size = 0;
    lst->head = NULL;
    lst->freeElement = freef;
    lst->printElement = printf;
    lst->partElement = partf;
    return lst;
}

//create node
node createNode(Element elem) {
    node pNode = malloc(sizeof(struct Node));
    pNode->elem = elem;
    pNode->next = NULL;
    return pNode;
}

//destroy list
status destroyList(linked_list lst) {
    // check valid input
    if (lst == NULL) {
        return failure;
    }
    node del = lst->head;
    while (del != NULL) {
        node temp = del->next;
        lst->freeElement(del->elem);
        free(del);
        del = temp;
    }
    free(lst);
    return success;
}

//add node to list
status appendNode(linked_list lst, Element elem) {
    // check valid input
    if (elem == NULL || lst == NULL) {
        return failure;
    }
    node new_node = createNode(elem);
    if (new_node == NULL) {
        return failure;
    }
    if (lst->size == 0) {
        lst->head = new_node;
        lst->size++;
        return success;
    }
    node temp = lst->head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_node;
    lst->size++;
    return success;
}

//help function to check if element is in linked list
status check_elem(linked_list lst, Element elem) {
    if (elem == NULL || lst == NULL) {
        return failure;
    }
    node curr = lst->head;
    while (curr != NULL) {
        if (curr->elem == elem) {
            return success;
        }
        curr = curr->next;
    }
    return failure;
}

//delete node from list
status deleteNode(linked_list lst, Element elem) {
    if (elem == NULL || lst == NULL) {
        return failure;
    }
    if (check_elem(lst, elem) == failure) {
        return failure;
    }
    if (lst->head->elem == elem) {
        node del = lst->head;
        lst->head = lst->head->next;
        lst->freeElement(del->elem);
        free(del);
        lst->size--;
        return success;
    }
    node temp1 = lst->head;
    node temp2 = lst->head->next;
    while (temp2->elem != elem) {
        temp1 = temp2;
        temp2 = temp2->next;
    }
    temp1->next = temp2->next;
    lst->freeElement(temp2->elem);
    free(temp2);
    lst->size--;
    return success;
}

//print all values in list
status displayList(linked_list lst) {
    if (lst == NULL) {
        return failure;
    }
    node curr = lst->head;
    while (curr != NULL) {
        lst->printElement(curr->elem);
        curr = curr->next;
    }
    return success;
}

//get value by index in list (starts from 1)
Element getDataByIndex(linked_list lst, int index) {
    if (lst == NULL || index <= 0 || index > lst->size) {
        return NULL;
    }
    node curr = lst->head;
    for (int i = 1; i < index; i++) {
        curr = curr->next;
    }
    return curr->elem;
}

// get size of list
int getLengthList(linked_list lst) {
    if (lst == NULL) {
        return 0;
    }
    return lst->size;
}

//search for an element in list
Element searchByKeyInList(linked_list lst, Element elem) {
    if (lst == NULL) {
        return NULL;
    }
    node curr = lst->head;
    while (curr != NULL) {
        if (lst->partElement(curr->elem, elem)) {
            return curr->elem;
        }
        curr = curr->next;
    }
    return NULL;
}
