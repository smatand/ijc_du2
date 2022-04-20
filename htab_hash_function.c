// htab_hash_function.c
// Riesenie IJC-DU2, priklad b), 20.4.2022
// Author: Andrej Smatana, FIT
// Prelozene: gcc 9.4.0
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "htab_private.h"

#ifndef HASH_TEST

// function copy-pasted from
// http://www.cse.yorku.ca/~oz/hash.html - variant sdbm
size_t htab_hash_function(const char *str) {
    uint32_t h=0;     // integer has to be of 32 bits
    const unsigned char *p;

    for(p=(const unsigned char*)str; *p!='\0'; p++) {
        h = 65599*h + *p;
    }

    return h;
}

#endif

#ifdef HASH_TEST

size_t htab_hash_function(const char *str) {
    static int flag = 0;
    if (flag == 0) {
        flag = 1;
        printf("Own hash_function used\n");
    }

    uint32_t h=853;     // integer has to be of 32 bits
    const unsigned char *p;
	
    for(p=(const unsigned char*)str; *p!='\0'; p++) {
        h = (h << 2) + 28841*h + *p;
    }
	
    return h;
} 

#endif