// io.h
// Riesenie IJC-DU2, priklad b), 20.4.2022
// Author: Andrej Smatana, FIT
// Prelozene: gcc 9.4.0
#ifndef IJC_PROJ2_IO_H
#define IJC_PROJ2_IO_H

#include <stdio.h>

/**
 * @brief Reads a word
 *
 * @param s buffer to store the word
 * @param max maximum number of characters to read
 * @param f file to read from
 *
 * @return number of characters read
 */
int read_word(char *s, int max, FILE *f);

#endif //IJC_PROJ2_IO_H
