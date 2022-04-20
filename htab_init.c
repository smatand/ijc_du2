// htab_init.c
// Riesenie IJC-DU2, priklad b), 20.4.2022
// Author: Andrej Smatana, FIT
// Prelozene: gcc 9.4.0
#include <stdlib.h>

#include "htab_private.h"

htab_t *htab_init(size_t n) {
	if (n <= 0) {
		return NULL;
	}

	htab_t *t = calloc(sizeof(struct htab), 1);

	if (t == NULL) {
		return NULL;
	}

	t->arr = calloc(sizeof(struct htab_list) * n, 1);
	if (t->arr == NULL) {
		free(t);
		return NULL;
	}

	t->arr_size = n;
	t->size = 0;

	return t;
}
