#include <string.h>

#include "htab_private.h"

void htab_resize(htab_t *t, size_t newn) {
	if (newn <= 0) {
		return;
	}

	htab_t *newt = htab_init(t->arr_size);

	for (size_t i = 0; i < newt->arr_size; i++) {
		newt->arr[i] = t->arr[i];

		t->arr[i] = NULL;
	}

	htab_clear(t);

	t->arr_size = newn;
	t->arr = calloc(sizeof(htab_list_t *) * newn, 1);

	for (size_t i = 0; i < newt->arr_size; i++) {
		htab_list_t *list = newt->arr[i];

		while (list != NULL) {
			htab_pair_t * addedList = htab_lookup_add(t, list->pair.key);
			addedList->value = list->pair.value;

			list = list->next;
		}
	}

	htab_free(newt);
}
