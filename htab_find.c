#include <string.h>

#include "htab_private.h"

htab_pair_t * htab_find(htab_t * t, htab_key_t key) {
	size_t hash = htab_hash_function(key) % t->arr_size;
	htab_list_t * list = t->arr[hash];

	// iterate through the linked list
	while (list != NULL) {
		// check if the key matches
		if (!strcmp(list->pair.key, key)) {
			return &list->pair; // return the found pair
		}

		list = list->next;
	}

	return NULL; // otherwise return NULL
}