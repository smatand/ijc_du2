#include <stdlib.h>
#include <string.h>

#include "htab_private.h"

#define AVG_LEN_MAX 7

htab_pair_t * htab_lookup_add(htab_t * t, htab_key_t key) {
	htab_pair_t * pair = htab_find(t, key);

	// in case the key is not found, add it
	if (pair == NULL) {
		size_t hash = htab_hash_function(key) % t->arr_size;

		// allocate memory for the pair
		htab_list_t * listToInsert = calloc(sizeof(htab_list_t), 1);
		if (listToInsert == NULL) {
			return NULL;
		}

		// allocate memory for the key in the pair
		size_t keyLen = strlen(key);
		listToInsert->pair.key = calloc(keyLen + 1, 1);
		if (listToInsert->pair.key == NULL) {
			free(listToInsert);
			return NULL;
		}

		// copy the key to the pair and set the value to 0
		memcpy((char *)listToInsert->pair.key, key, keyLen + 1);
		listToInsert->pair.value = 0;
		listToInsert->next = NULL;

		if (t->arr[hash] == NULL) {
			t->arr[hash] = listToInsert;
		} else {
			// insert the new pair at the end
			htab_list_t * last = t->arr[hash];
			while (last->next != NULL) {
				last = last->next;
			}
			last->next = listToInsert;
		}

		t->size++;

		// check if the table needs to be resized
		if (t->size / t->arr_size > AVG_LEN_MAX) {
			htab_resize(t, t->arr_size * 2);
		}

		return &(listToInsert->pair);
	} else {
		return pair; // the pair is already in the table
	}
}
