#pragma once

#include "common_refmem.h"

typedef struct list ioopm_refmem_list_t; /// Meta: struct definition goes in C file

/// FIXME: better comments here
/// @brief Creates a new empty list
/// @return an empty linked list
ioopm_refmem_list_t *ioopm_refmem_linked_list_create(ioopm_refmem_cmp_function compare);

/// @brief Tear down the linked list and return all its memory (but not the memory of the elements)
/// @param list the list to be destroyed
void ioopm_refmem_linked_list_destroy(ioopm_refmem_list_t *list);

/// @brief Insert at the end of a linked list in O(1) time
/// @param list the linked list that will be appended
/// @param value the value to be appended
void ioopm_refmem_linked_list_append(ioopm_refmem_list_t *list, elem_t value);

/// @brief Insert at the front of a linked list in O(1) time
/// @param list the linked list that will be prepended
/// @param value the value to be appended
void ioopm_refmem_linked_list_prepend(ioopm_refmem_list_t *list, elem_t value);

/// @brief Insert an element into a linked list in O(n) time.
/// The valid values of index are [0,n] for a list of n elements,
/// where 0 means before the first element and n means after
/// the last element.
/// @param list the linked list that will be extended
/// @param index the position in the list
/// @param value the value to be appended
int ioopm_refmem_linked_list_insert(ioopm_refmem_list_t *list, int index, elem_t value);

/// @brief Remove an element from a linked list in O(n) time.
/// The valid values of index are [0,n-1] for a list of n elements,
/// where 0 means the first element and n-1 means the last element.
/// @param list the linked list that will be extended
/// @param index the position in the list
/// @param value the value to be appended
/// @return the value returned (*)
option_t ioopm_refmem_linked_list_remove(ioopm_refmem_list_t *list, int index);

/// @brief Retrieve an element from a linked list in O(n) time.
/// The valid values of index are [0,n-1] for a list of n elements,
/// where 0 means the first element and n-1 means the last element.
/// @param list the linked list that will be extended
/// @param index the position in the list
/// @return the value at the given position
option_t ioopm_refmem_linked_list_get(ioopm_refmem_list_t *list, int index);

/// @brief Test if an element is in the list
/// @param list the linked list
/// @param element the element sought
/// @return true if element is in the list, else false
bool ioopm_refmem_linked_list_contains(ioopm_refmem_list_t *list, elem_t element);

/// @brief Lookup the number of elements in the linked list in O(1) time
/// @param list the linked list
/// @return the number of elements in the list
unsigned long ioopm_refmem_linked_list_size(ioopm_refmem_list_t *list);

/// @brief Test whether a list is empty or not
/// @param list the linked list
/// @return true if the number of elements int the list is 0, else false
bool ioopm_refmem_linked_list_is_empty(ioopm_refmem_list_t *list);

/// @brief Remove all elements from a linked list
/// @param list the linked list
void ioopm_refmem_linked_list_clear(ioopm_refmem_list_t *list);

/// @brief Test if a supplied property holds for all elements in a list.
/// The function returns as soon as the return value can be determined.
/// @param list the linked list
/// @param prop the property to be tested (function pointer)
/// @param extra an additional argument (may be NULL) that will be passed to all internal calls of prop
/// @return true if prop holds for all elements in the list, else false
bool ioopm_refmem_linked_list_all(ioopm_refmem_list_t *list, ioopm_refmem_predicate prop, void *extra);

/// @brief Test if a supplied property holds for any element in a list.
/// The function returns as soon as the return value can be determined.
/// @param list the linked list
/// @param prop the property to be tested
/// @param extra an additional argument (may be NULL) that will be passed to all internal calls of prop
/// @return true if prop holds for any elements in the list, else false
bool ioopm_refmem_linked_list_any(ioopm_refmem_list_t *list, ioopm_refmem_predicate prop, void *extra);

/// @brief Apply a supplied function to all elements in a list.
/// @param list the linked list
/// @param fun the function to be applied
/// @param extra an additional argument (may be NULL) that will be passed to all internal calls of fun
void ioopm_refmem_linked_apply_to_all(ioopm_refmem_list_t *list, ioopm_refmem_apply_function fun, void *extra);

