// htab_resize.c
// Riesenie IJC-DU2, priklad b), 20.4.2022
// Author: Andrej Smatana, FIT
// Prelozene: gcc 9.4.0
#include <stdlib.h>
#include <string.h>

#include "htab_private.h"

void htab_resize(htab_t *t, size_t newn) {
	if (newn <= 0) {
		return;
	}

	htab_t *newt = htab_init(t->arr_size);
	if (newt == NULL) {
		goto newtAllocationError;
	}

	for (size_t i = 0; i < newt->arr_size; i++) {
		newt->arr[i] = t->arr[i];

		t->arr[i] = NULL;
	}

	htab_clear(t);

	t->arr_size = newn;
	t->arr = calloc(sizeof(htab_list_t *) * newn, 1);
	if (t->arr == NULL) {
		goto allocationError;
	}

	for (size_t i = 0; i < newt->arr_size; i++) {
		htab_list_t *list = newt->arr[i];

		while (list != NULL) {
			htab_pair_t * addedList = htab_lookup_add(t, list->pair.key);
			if (addedList == NULL) {
				goto allocationError;
			}
			addedList->value = list->pair.value;

			list = list->next;
		}
	}

	htab_free(newt);
	return;

allocationError:
	htab_free(newt);
newtAllocationError:
	htab_free(t);
	exit(1);
}
