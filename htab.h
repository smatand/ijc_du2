/** 
 * @brief Hash table library (public domain)
 */

#ifndef __HTAB_H__
#define __HTAB_H__

#include <string.h>
#include <stdbool.h>

struct htab;   
typedef struct htab htab_t;

typedef const char * htab_key_t;
typedef int htab_value_t;

/**
 * @struct htab_item
 * 
 * details of hash table item
 */
typedef struct htab_pair {
    htab_key_t    key; 
    htab_value_t  value;  
} htab_pair_t;

/**
 * @brief Hash function for the hash table
 * 
 * @param str string to store in hash table
 * 
 * @return size_t index of item in hash table
 */
size_t htab_hash_function(htab_key_t str);

/**
 * @brief Initialize new hash table
 * 
 * @param n size of hash table
 * 
 * @return htab_t* pointer to the new hash table
 */
htab_t *htab_init(size_t n); 

/**
 * @brief Return current number of records [(key, data), next]
 * 
 * @param t hash table to get size from
 * @return size_t size
 */
size_t htab_size(const htab_t * t);  

/**
 * @brief Return pointer array size [number of items]
 * 
 * @param t hash table to get size from
 * 
 * @return size_t size
 */
size_t htab_bucket_count(const htab_t * t);

/**
 * @brief Resize the hash table
 * 
 * @param t hash table to resize
 * @param newn new size of the hash table
 */
void htab_resize(htab_t *t, size_t newn);

/**
 * @brief Find item in the hash table
 * 
 * @param t table to search
 * @param key key to find
 * @return htab_pair_t* pointer to the item
 */
htab_pair_t * htab_find(htab_t * t, htab_key_t key);

/**
 * @brief Look for item with key or add
 * 
 * @param t table to search
 * @param key key to find or to add
 * @return htab_pair_t* pointer to the item
 */
htab_pair_t * htab_lookup_add(htab_t * t, htab_key_t key);

/**
 * @brief Erase the item from the hash table
 * 
 * @param t table from which the item is
 * @param key key of the item to erase
 * @return true success
 * @return false item with key wasn't found
 */
bool htab_erase(htab_t * t, htab_key_t key);

/**
 * @brief Process all items in the table and call the function f
 * 
 * @param t table to process
 * @param f function to call
 */
void htab_for_each(const htab_t * t, void (*f)(htab_pair_t *data));

/**
 * @brief Clear the table
 * 
 * @param t table to clear
 */
void htab_clear(htab_t * t);

/**
 * @brief Free the dynamically allocated memory for table
 * 
 * @param t table to free
 */
void htab_free(htab_t * t);

#endif // __HTAB_H__
