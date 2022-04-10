#include <stdlib.h>

#include "htab.h"

/**
 * @brief Free all items in hash table
 * 
 * @param t table to be freed
 */
void htab_free(htab_t *t) {
    htab_clear(t);

    free(t);
}