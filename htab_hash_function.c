#include <stdlib.h>
#include <stdint.h>

#include "htab.h"
#include "htab_struct.h"

/**
 * @brief Hash function for the hash table
 * 
 * @param str string to store in hash table
 * 
 * @return size_t index of item in hash table
 */
size_t htab_hash_function(const char *str) {
    uint32_t h=0;     // integer has to be of 32 bits
    const unsigned char *p;

    for(p=(const unsigned char*)str; *p!='\0'; p++) {
        h = 65599*h + *p;
    }

    return h;
}