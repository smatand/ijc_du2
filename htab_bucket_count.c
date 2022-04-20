// htab_bucket_count.c
// Riesenie IJC-DU2, priklad b), 20.4.2022
// Author: Andrej Smatana, FIT
// Prelozene: gcc 9.4.0
#include "htab_private.h"

size_t htab_bucket_count(const htab_t * t) {
	return t->arr_size;
}