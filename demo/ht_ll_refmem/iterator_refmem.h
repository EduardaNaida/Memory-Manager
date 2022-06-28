#pragma once

#include <stdbool.h>
#include <stddef.h>

#include "linked_list_refmem.h"
#include "common_refmem.h"

typedef struct iterator ioopm_refmem_list_iterator_t;

/// @brief Create an iterator for a given list
/// @param the list to be iterated over
/// @return an iteration positioned at the start of list
ioopm_refmem_list_iterator_t *ioopm_refmem_list_iterator(ioopm_refmem_list_t *list);

/// @brief Checks if there are more elements to iterate over
/// @param iter the iterator
/// @return true if
bool ioopm_refmem_iterator_has_next(ioopm_refmem_list_iterator_t *iter);

/// @brief Step the iterator forward one step
/// @param iter the iterator
/// @return the next element
option_t ioopm_refmem_iterator_next(ioopm_refmem_list_iterator_t *iter);

/// @brief Remove the current element from the underlying list
/// @param iter the iterator
/// @return the removed element
option_t ioopm_refmem_iterator_remove(ioopm_refmem_list_iterator_t *iter);

/// @brief Insert a new element into the underlying list making the current element it's next
/// @param iter the iterator
/// @param element the element to be inserted
void ioopm_refmem_iterator_insert(ioopm_refmem_list_iterator_t *iter, elem_t element);

/// @brief Reposition the iterator at the start of the underlying list
/// @param iter the iterator
void ioopm_refmem_iterator_reset(ioopm_refmem_list_iterator_t *iter);

/// @brief Return the current element from the underlying list
/// @param iter the iterator
/// @return the current element
option_t ioopm_refmem_iterator_current(ioopm_refmem_list_iterator_t *iter);

/// @brief Destroy the iterator and return its resources
/// @param iter the iterator
void ioopm_refmem_iterator_destroy(ioopm_refmem_list_iterator_t *iter);
