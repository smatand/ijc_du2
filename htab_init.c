#include <stdlib.h>

#include "htab.h"
#include "htab_struct.h"

/**
 * @brief Initialize new hash table
 * 
 * @param n size of hash table
 * 
 * @return htab_t* pointer to the new hash table
 */
htab_t *htab_init(size_t n) {
    if (n <= 0) {
        return NULL;
    }

    htab_t* t = malloc(sizeof(htab_t) + n * sizeof(htab_item_t*));

    if (t == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < n; i++) {
        t->arr[i] = NULL;
    }
    t->arrSize = n;
    t->size = 0;

    return t;
}