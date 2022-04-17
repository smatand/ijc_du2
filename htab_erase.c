#include "htab_private.h"

#define AVG_LEN_MIN 20

bool htab_erase(htab_t * t, htab_key_t key) {
	size_t hash = htab_hash_function(key) % t->arr_size;
	htab_list_t * list = t->arr[hash];

	while (list != NULL) {
		if (!strcmp(list->pair.key, key)) {
			htab_list_t * listToRemove = list;

			// check whether it isn't the 1st list in the array
			if (list->next == NULL && t->arr[hash]->next == NULL) {
				free((char *) t->arr[hash]->pair.key);
				free(t->arr[hash]);

				t->arr[hash] = NULL;
				t->size--;
				return true;
			}

			// if the list isn't the last one in the linked list, then we still may iterate through the list
			if (list->next != NULL) {
				list = list->next;
			}

			free((char *)listToRemove->pair.key);
			free(listToRemove);

			t->size--;
			// check if the table is too small
			if (t->size / t->arr_size < AVG_LEN_MIN) {
				htab_resize(t, t->arr_size / 2);
			}

			return true;
		}
		list = list->next;
	}

	return false;
}