#include "MultiValueHashTable.h"

// structure of MultiValueHashTable
struct multi_value_hash_table {
    CopyFunction copyKey;
    FreeFunction freeKey;
    PrintFunction printKey;
    CopyFunction copyValue;
    FreeFunction freeValue;
    PrintFunction printValue;
    EqualFunction equalKey;
    TransformIntoNumberFunction transformIntoNumber;
    int hashSize;
    hashTable ht;
};

//create MultiValueHashTable
MVhash createMultiValueHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey,
                                 CopyFunction copyValue,
                                 FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey, int hashSize,
                                 TransformIntoNumberFunction transformIntoNumber) {
    MVhash mv_hash = malloc(sizeof(struct multi_value_hash_table));
    if (mv_hash == NULL) {
        return NULL;
    }
    mv_hash->ht = createHashTable(copyKey, freeKey, printKey, copyValue, (FreeFunction)destroyList, (PrintFunction)displayList, equalKey,
                                  transformIntoNumber, hashSize);
    if (mv_hash->ht == NULL) {
        return NULL;
    }
    mv_hash->copyKey = copyKey;
    mv_hash->freeKey = freeKey;
    mv_hash->printKey = printKey;
    mv_hash->copyValue = copyValue;
    mv_hash->freeValue = freeValue;
    mv_hash->printValue = printValue;
    mv_hash->equalKey = equalKey;
    mv_hash->transformIntoNumber = transformIntoNumber;
    mv_hash->hashSize = hashSize;
    return mv_hash;
}

//destroy MultiValueHashTable
status destroyMultiValueHashTable(MVhash mv_hash) {
    if (mv_hash == NULL) {
        return failure;
    }
    destroyHashTable(mv_hash->ht);
    free(mv_hash);
    return success;
}

// add to MultiValueHashTable (a list with values related to key)
status addToMultiValueHashTable(MVhash mv_hash, Element key, Element value) {
    if (mv_hash == NULL || key == NULL || value == NULL) {
        return failure;
    }
    linked_list KeyList = lookupInMultiValueHashTable(mv_hash, key);
    if (KeyList == NULL) {
        if (addToHashTable(mv_hash->ht, mv_hash->copyKey(key), createLinkedList(mv_hash->freeValue, mv_hash->printValue, mv_hash->equalKey)) == failure) {
            destroyList(KeyList);
            return failure;
        }
    }
    linked_list KeyList2 = lookupInMultiValueHashTable(mv_hash, key);
    if (appendNode(KeyList2, mv_hash->copyValue(value)) == failure) {
        return failure;
    }
    return success;
}

//search for a list that is related to the given key
Element lookupInMultiValueHashTable(MVhash mv_hash, Element key) {
    if (mv_hash == NULL || key == NULL) {
        return NULL;
    }
    linked_list KeyList = lookupInHashTable(mv_hash->ht, key);
    if (KeyList == NULL) {
        return NULL;
    }
    return KeyList;
}

//removes a value from the table
status removeFromMultiValueHashTable(MVhash mv_hash, Element key, Element value) {
    if (mv_hash == NULL || key == NULL || value == NULL) {
        return failure;
    }
    linked_list KeyInChain = lookupInHashTable(mv_hash->ht, key);
    if (KeyInChain == NULL) {
        return failure;
    }
    deleteNode(KeyInChain, searchByKeyInList(KeyInChain, value));
    if (getLengthList(KeyInChain) == 0) {
        removeFromHashTable(mv_hash->ht, key);
    }
    return success;
}

// print all values related to the given key
status displayMultiValueHashTable(MVhash mv_hash, Element key) {
    if (mv_hash == NULL || key == NULL) {
        return failure;
    }
    linked_list ListInChain = lookupInMultiValueHashTable(mv_hash, key);
    if (ListInChain == NULL) {
        return failure;
    }
    mv_hash->printKey(key);
    displayList(ListInChain);
    return success;
}
