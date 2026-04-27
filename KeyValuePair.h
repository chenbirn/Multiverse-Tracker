#ifndef KEYVALUEPAIR_H
#define KEYVALUEPAIR_H
#include "Defs.h"

typedef struct KeyValuePair* key_value_pair;

//create KeyPairValue
key_value_pair createKeyValuePair(Element key, Element value, FreeFunction freeKey, FreeFunction freeValue, PrintFunction printKey, PrintFunction printValue, EqualFunction equalKey);

//destroy KeyValuePair
status destroyKeyValuePair(key_value_pair KVpair);

//print value
status displayValue(key_value_pair KVpair);

//print key
status displayKey(key_value_pair KVpair);

//get value
Element getValue(key_value_pair KVpair);

//get key
Element getKey(key_value_pair KVpair);

// check if the given key is equal to the KeyPairValue key
bool isEqualKey(key_value_pair KVpair, Element key);

#endif //KEYVALUEPAIR_H
