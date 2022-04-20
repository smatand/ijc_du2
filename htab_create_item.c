#include <stdlib.h>

#include "htab.h"
#include "htab_struct.h"

// initialize item
htab_item_t *htab_create_item(htab_key_t key) {
    htab_item_t *item = malloc(sizeof(htab_item_t));
    if (item == NULL) {
        return NULL;
    }
    htab_pair_t *pair = malloc(sizeof(htab_pair_t));
    if (pair == NULL) {
        free(item);
        return NULL;
    }

    // strlen(key) + 1 for '\0'
    char *string = malloc(strlen(key) + 1); // sizeof(char) is 1
    if (string == NULL) {
        free(pair);
        free(item);
        return NULL; // TODO: maybe add goto error
    }

    strcpy(string, key);
    pair->key = string;
    pair->value = 0;

    item->pair = pair;
    item->next = NULL;

    return item;
}
