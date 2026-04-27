#include "KeyValuePair.h"

//KeyValuePair structure
struct KeyValuePair {
    Element key;
    Element value;
    FreeFunction freeKey;
    FreeFunction freeValue;
    PrintFunction printKey;
    PrintFunction printValue;
    EqualFunction equalKey;
};

//create KeyValuePair
key_value_pair createKeyValuePair(Element key, Element value, FreeFunction freeKey, FreeFunction freeValue, PrintFunction printKey, PrintFunction printValue, EqualFunction equalKey) {
    if (key == NULL || value == NULL) {
        return NULL;
    }
    key_value_pair KVpair = malloc(sizeof(struct KeyValuePair));
    if (KVpair == NULL) {
        return NULL;
    }
    KVpair->key = key;
    KVpair->value = value;
    KVpair->freeKey = freeKey;
    KVpair->freeValue = freeValue;
    KVpair->printKey = printKey;
    KVpair->printValue = printValue;
    KVpair->equalKey = equalKey;
    return KVpair;
}

//destroy KeyValuePair
status destroyKeyValuePair(key_value_pair KVpair) {
    if (KVpair == NULL) {
        return failure;
    }
    KVpair->freeKey(KVpair->key);
    KVpair->freeValue(KVpair->value);
    free(KVpair);
    return success;
}

//print value
status displayValue(key_value_pair KVpair) {
    if (KVpair == NULL) {
        return failure;
    }
    KVpair->printValue(KVpair->value);
    return success;
}

//print key
status displayKey(key_value_pair KVpair) {
    if (KVpair == NULL) {
        return failure;
    }
    KVpair->printKey(KVpair->key);
    return success;
}

//get value
Element getValue(key_value_pair KVpair) {
    if (KVpair == NULL) {
        return NULL;
    }
    return KVpair->value;
}

//get key
Element getKey(key_value_pair KVpair) {
    if (KVpair == NULL) {
        return NULL;
    }
    return KVpair->key;
}

// check if the given key is equal to the KeyPairValue key
bool isEqualKey(key_value_pair KVpair, Element key) {
    if (KVpair == NULL || key == NULL) {
        return false;
    }
    return KVpair->equalKey(key, KVpair->key);
}