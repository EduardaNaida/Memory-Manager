#pragma once

#include <stdbool.h>
#include "../linked_list/common.h"
#include "../linked_list/linked_list.h"
/**
 * @file hash_table.h
 * @author Lukas Nord, Oskar Pettersson Löfstedt
 * @date 10 Oct 2020
 * @brief Simple hash table that maps integer keys to string values.
 *
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 *
 * @see http://wrigstad.com/ioopm19/assignments/assignment1.html
 */
typedef unsigned long(*ioopm_hash_function)(elem_t);

typedef struct hash_table ioopm_hash_table_t;

/// @brief Create a new hash table
/// @return A new empty hash table
ioopm_hash_table_t *ioopm_hash_table_create(ioopm_hash_function hash, ioopm_cmp_function compare);

/// @brief Delete a hash table and free its memory
/// @param ht a hash table to be deleted
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht);

/// @brief add key => value entry in hash table ht
/// @param ht hash table operated upon
/// @param key key to insert
/// @param value value to insert
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, elem_t, elem_t);

/// @brief lookup value for key in hash table ht
/// @param ht hash table operated upon
/// @param key key to lookup
/// @return the value mapped to by key (FIXME: incomplete)
option_t ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key);

/// @brief remove any mapping from key to a value
/// @param ht hash table operated upon
/// @param key key to remove
/// @return the value mapped to by key (FIXME: incomplete)
option_t ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t key);

//@brief check if hash table is empty
//@param ht hash table operated upon
//@return whether or not ht is empty
bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht);

//@brief calculate size of hashtable
//@param ht hash table operated upon
//@return the number of entries in the hash table
size_t ioopm_hash_table_size (ioopm_hash_table_t *ht);

//@brief removes the entires in the hash tables but preserves buckets
//@param ht hash table operated upon
void ioopm_hash_table_clear(ioopm_hash_table_t *ht);

//@brief creates a linked list of all the keys in the hash table
//@param ht hash table opreated upon
//@return a linked list with all the keys in the list
ioopm_list_t *ioopm_hash_table_keys (ioopm_hash_table_t *ht);

//@brief creates a linked list of all values in the hash table
//@param ht hash table operated upon
//@return linked list with pointers to all the values in ht
ioopm_list_t *ioopm_hash_table_values (ioopm_hash_table_t *ht);

//@brief checks whether hash table contains a specific key
//@param ht hash table operated upon
//@param key the key to look for
//@return whether or not hash table ht contains key key
bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, elem_t key);

//@brief checks whether hash table contains a specific value
//@param ht hash table operated upon
//@param value the value to query about
//@return whether or not hash table ht contains value value
bool ioopm_hash_table_has_value(ioopm_hash_table_t *ht, elem_t value);

//@brief checks whether all entries in a hash table satisfies a specific predicate
//@param ht hash table operated upon
//@param P predicate to be examined
//@param x void pointer for extra usability if extraction without return is needed
//@return whether or not all entries in hash table ht satisfies predicate P
bool ioopm_hash_table_all(ioopm_hash_table_t *ht, ioopm_predicate P, void *x); //TODO: skriv om för elem_t format på key och value

//@brief checks whether any entry in a hash table satisfies a specific predicate
//@param ht hash table operated upon
//@param P predicate to be examined
//@param x void pointer for extra usability if extraction without return is needed
//@return whether or not any entry in hash table ht satisfies predicate P
bool ioopm_hash_table_any(ioopm_hash_table_t *ht, ioopm_predicate P, void *x); //TODO: skriv om för elem_t format på key och value

//@brief applies a function to all values in a hash table
//@param ht hash table operated upon
//@param P function to be executed for each value
//@param x void pointed for extra usability or exctraction without return
void ioopm_hash_table_apply_to_all(ioopm_hash_table_t *ht, ioopm_apply_function P, void *x); //TODO: skriv om för elem_t blabla