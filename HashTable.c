#include "HashTable.h"

// HashTable stracture
struct hashTable_s {
    CopyFunction copyKey;
    FreeFunction freeKey;
    PrintFunction printKey;
    CopyFunction copyValue;
    FreeFunction freeValue;
    PrintFunction printValue;
    EqualFunction equalKey;
    TransformIntoNumberFunction transformIntoNumber;
    int hashNumber;
    linked_list *list;
};

//create HashTable
hashTable createHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue,
                          FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey,
                          TransformIntoNumberFunction transformIntoNumber, int hashNumber) {
    hashTable ht = malloc(sizeof(struct hashTable_s));
    if (ht == NULL) {
        return NULL;
    }
    ht->copyKey = copyKey;
    ht->freeKey = freeKey;
    ht->printKey = printKey;
    ht->copyValue = copyValue;
    ht->freeValue = freeValue;
    ht->printValue = printValue;
    ht->equalKey = equalKey;
    ht->transformIntoNumber = transformIntoNumber;
    ht->hashNumber = hashNumber;
    ht->list = (linked_list *) calloc(hashNumber, sizeof(linked_list));
    if (ht->list == NULL) {
        free(ht);
        return NULL;
    }
    return ht;
}

//destroy HashTable
status destroyHashTable(hashTable ht) {
    if (ht == NULL) {
        return failure;
    }
    for (int i = 0; i < ht->hashNumber; i++) {
        destroyList(ht->list[i]);
        ht->list[i] = NULL;
    }
    free(ht->list);
    ht->list = NULL;
    free(ht);
    return success;
}

// add a value related to key to HashTable
status addToHashTable(hashTable ht, Element key, Element value) {
    if (ht == NULL || key == NULL || value == NULL) {
        return failure;
    }
    if (lookupInHashTable(ht, key) == NULL) {
        key_value_pair new_pair = createKeyValuePair(key, value, ht->freeKey, ht->freeValue,
                                                     ht->printKey, ht->printValue, ht->equalKey);
        if (new_pair == NULL) {
            return failure;
        }
        int keyVal = ht->transformIntoNumber(getKey(new_pair));
        int idx = keyVal % ht->hashNumber;
        if (ht->list[idx] == NULL) {
            linked_list new_list = createLinkedList((FreeFunction)destroyKeyValuePair, (PrintFunction)displayValue, (EqualFunction)isEqualKey);
            ht->list[idx] = new_list;
        }
        appendNode(ht->list[idx], new_pair);
        return success;
    }
    return failure;
}

// search value that is related to given key
Element lookupInHashTable(hashTable ht, Element key) {
    if (ht == NULL || key == NULL) {
        return NULL;
    }
    int keyVal = ht->transformIntoNumber(key);
    int idx = keyVal % ht->hashNumber;
    if (ht->list[idx] == NULL) {
        return NULL;
    } else {
        for (int i = 1; i <= getLengthList(ht->list[idx]); i++) {
            key_value_pair key_element = getDataByIndex(ht->list[idx], i);
            if (isEqualKey(key_element, key)) {
                return getValue(getDataByIndex(ht->list[idx], i));
            }
        }
    }
    return NULL;
}

// remove value from HashTable
status removeFromHashTable(hashTable ht, Element key) {
    if (ht == NULL || key == NULL) {
        return failure;
    }
    int keyVal = ht->transformIntoNumber(key);
    int idx = keyVal % ht->hashNumber;
    if (ht->list[idx] == NULL) {
        return failure;
    } else {
        key_value_pair del = searchByKeyInList(ht->list[idx], key);
        deleteNode(ht->list[idx], del);
        return success;
    }
}

// display all keys and values in HashTable
status displayHashElements(hashTable ht) {
    if (ht == NULL) {
        return failure;
    }
    for (int i = 0; i < ht->hashNumber; i++) {
        if (ht->list[i] != NULL) {
            for (int j = 1; j <= getLengthList(ht->list[i]); j++) {
                key_value_pair d_pair = getDataByIndex(ht->list[i], j);
                if (d_pair != NULL) {
                    displayKey(d_pair);
                    displayValue(d_pair);
                }
            }
        }
    }
    return success;
}
