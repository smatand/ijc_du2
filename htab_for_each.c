// htab_for_each.c
// Riesenie IJC-DU2, priklad b), 20.4.2022
// Author: Andrej Smatana, FIT
// Prelozene: gcc 9.4.0
#include "htab_private.h"

void htab_for_each(const htab_t * t, void (*f)(htab_pair_t *data)) {
	for (size_t i = 0; i < t->arr_size; i++) {
		htab_list_t *list = t->arr[i];

		while (list != NULL) {
			(*f)(&list->pair);
			list = list->next;
		}
	}

	return;
}