#include <stdlib.h>

#include "htab_private.h"

htab_t *htab_init(size_t n) {
	if (n <= 0) {
		return NULL;
	}

	htab_t *t = malloc(sizeof(struct htab));

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
