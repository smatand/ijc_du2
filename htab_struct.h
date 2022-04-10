/** @brief Private structures */
#ifndef __HTAB_STRUCT_T__
#define __HTAB_STRUCT_T__

#include "htab.h"

/**
 * @brief Private structure for hash table item
 */
typedef struct htab_item {
    struct htab_pair pair;
    struct htab_item *next;
} htab_item_t;

/**
 * @brief Contains hash table items and other data
 */
typedef struct htab {
    size_t size;
    size_t arrSize;
    struct htab_item **arr;
} htab_t;

#endif // __HTAB_STRUCT_H__