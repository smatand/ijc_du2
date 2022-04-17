#ifndef _HTAB_PRIVATE_H
#define _HTAB_PRIVATE_H

#include <stdlib.h>
#include "htab.h"

/**
 * @struct htab
 * @brief Hash table structure
 */
struct htab {
	size_t size;
	size_t arr_size;
	struct htab_list **arr;
};

/**
 * @struct htab_list
 * @brief Hash table list structure
 */
struct htab_list {
	struct htab_pair pair; // (key, value)
	struct htab_list *next; // next item in the same bucket
};

typedef struct htab_list htab_list_t;

#endif // _HTAB_PRIVATE_H