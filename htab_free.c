// htab_free.c
// Riesenie IJC-DU2, priklad b), 20.4.2022
// Author: Andrej Smatana, FIT
// Prelozene: gcc 9.4.0
#include <stdlib.h>

#include "htab_private.h"

void htab_free(htab_t * t) {
	if (t == NULL) {
		return;
	}

	htab_clear(t);
	free(t);
}

