#include <stdlib.h>
#include <string.h>

#include "htab_private.h"

void htab_clear(htab_t * t) {
	// iterate through all buckets and clear them
	for (size_t i = 0; i < t->arr_size; i++) {
		// clear bucket
		htab_list_t *list = t->arr[i]; // used as current list

		// start clearing lists from the beginning
		while (list != NULL) {
			htab_list_t *next = list->next; // for list
			free((char *) list->pair.key);
			free(list);
			list = next;
		}

		t->arr[i] = NULL;
	}
	t->size = 0;
	t->arr_size = 0;
	free(t->arr);

	return;
}

