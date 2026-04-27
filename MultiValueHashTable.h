#ifndef MULTIVALUEHASHTABLE_H
#define MULTIVALUEHASHTABLE_H
#include "HashTable.h"
#include "Defs.h"

typedef struct multi_value_hash_table *MVhash;

// create MultiValueHashTable
MVhash createMultiValueHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue,
                          FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey, int hashSize, TransformIntoNumberFunction transformIntoNumber);
// destroy MultiValueHashTable
status destroyMultiValueHashTable(MVhash multiValueHashTable);

// add value to MultiValueHashTable by its key
status addToMultiValueHashTable(MVhash multiValueHashTable, Element key, Element value);

// search for elements related to key
Element lookupInMultiValueHashTable(MVhash multiValueHashTable, Element key);

// remove a value from MultiValueHashTable
status removeFromMultiValueHashTable(MVhash multiValueHashTable, Element key, Element value);

// print all values related to key
status displayMultiValueHashTable(MVhash multiValueHashTable, Element key);


#endif //MULTIVALUEHASHTABLE_H
