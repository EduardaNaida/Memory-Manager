#include <stdlib.h>

#include "linked_list.h"
#include "iterator.h"

//DEFINITIONS:

#define Dummy_key (elem_t) {.pointer = NULL}

#define Open_bound (bool) {true}
#define Closed_bound (bool) {false}

// TYPES:

typedef struct link link_t;

// STRUCTURES:

struct link {
  elem_t element;
  link_t *next;
};

struct list {
  link_t *first;
  link_t *last;
  unsigned long size;
  ioopm_cmp_function compare;
};

struct iterator{
  link_t **first;
  link_t **current;
};

// HELPER FUNCTIONS:

// TODO: Ask if checking for allocation faliures is a requirement.
static link_t *create_link(elem_t elem, link_t *next){
  link_t *link = calloc(1, sizeof(link_t));
  link->element = elem;
  link->next = next;
  return link;
}

static link_t *destroy_link(link_t *link){
  link_t *next = link->next;
  free(link);
  return next;
}

static bool not_in_range(int num, int lower, int upper){
  return lower > num || num > upper;
}

/**
 * @brief Checks whether index is out of range or not
 * @param list the list to be indexed
 * @param index the index
 * @param whether or not the bound is open or not, I.E is the last position n or n-1
 * @return the result or inverted result of evaluationg prop on its arguments
*/
static bool index_out_of_range(ioopm_list_t *list, int index, bool is_open_bound){
  size_t size = ioopm_linked_list_size(list);
  return is_open_bound ? not_in_range(index, 0, size) : not_in_range(index, 0, size-1);
}

link_t **advance_to_index(link_t **tracer, int index){
  for (int i = 0; i < index; i++) {
    tracer = &(*tracer)->next;
  }
  return tracer;
}

/**
 * @breif evaluates a predicate on all elements in a list until it is true
 * @param list the list
 * @param prop the predicate
 * @param extra argument to predicate
 * @param break_value the value to return if the predicate holds for an element
 * @param runout_value the value to return if the predicate doesn't hold for any element
 * @param invert_condition when true checks for the inverse condition I.E. !prop 
*/
static bool check_predicate_for_all(ioopm_list_t *list, ioopm_predicate prop, void *extra, bool break_value, bool runout_value, bool invert_condition){
  link_t *tracer = list->first;
  while (tracer){
    if (evaluate_predicate(prop, Dummy_key, tracer->element, extra, invert_condition)){
      return break_value;
    }
    tracer = tracer->next;
  }
  return runout_value; 
}

// PUBLIC API:

ioopm_list_t *ioopm_linked_list_create(ioopm_cmp_function compare){
  ioopm_list_t *list = calloc(1, sizeof(ioopm_list_t));
  list->compare = compare ? compare : int_compare;
  return list;
}

void ioopm_linked_list_destroy(ioopm_list_t *list){
  link_t *cursor = list->first;
  while (cursor){
    cursor = destroy_link(cursor); 
  }
  free(list);
}

void ioopm_linked_list_append(ioopm_list_t *list, elem_t value){
  link_t *link = create_link(value, NULL);
  if (list->last){ // Do we have a last IE. is it empty?
    list->last->next = link;
  } else {
    list->first = link; // if empty first and last point to the same value
  }
  list->last = link; 
  list->size++;
}

void ioopm_linked_list_prepend(ioopm_list_t *list, elem_t value){
  link_t *link = create_link(value, NULL);
  if (list->first){
    link->next = list->first;
  } else {
    list->last = link;
  }
  list->first = link;
  list->size++;
}



int ioopm_linked_list_insert(ioopm_list_t *list, int index, elem_t value){
  if (index_out_of_range(list, index, Open_bound)){
    return 1;
  }
  
  link_t **tracer = advance_to_index(&(list->first), index);
  
  link_t *new_link = create_link(value, *tracer);
  *tracer = new_link;
  if (!(*tracer)->next){
    list->last = *tracer;
  }
  list->size++;
  return 0;
}


option_t ioopm_linked_list_remove(ioopm_list_t *list, int index){
  if (index_out_of_range(list, index, Closed_bound) || ioopm_linked_list_is_empty(list)){
    return Failure();
  }
  
  link_t **tracer = advance_to_index(&(list->first), index);

  link_t *removed = *tracer; //extract
  *tracer = (*tracer)->next; //unlink
  if (!(*tracer)){
    list->last = *tracer;
  }
  elem_t elem = removed->element; // get element
  destroy_link(removed); // destroy link
  
  list->size--;
  return Success(elem); 
}

option_t ioopm_linked_list_get(ioopm_list_t *list, int index){
  if (index_out_of_range(list, index, Closed_bound) || ioopm_linked_list_is_empty(list)){
    return Failure();
  }
  
  link_t **tracer = advance_to_index(&list->first, index);
  
  elem_t elem = (*tracer)->element;
  return Success(elem);
}

bool ioopm_linked_list_contains(ioopm_list_t *list, elem_t element){
  link_t *tracer = list->first;
  ioopm_cmp_function compare = list->compare;
  while(tracer){
    if (compare(tracer->element, element) == 0){
      return true;
    }
    tracer = tracer->next;
  }
  return false;
}


unsigned long ioopm_linked_list_size(ioopm_list_t *list){
  return list->size;
}

bool ioopm_linked_list_is_empty(ioopm_list_t *list){
  return ioopm_linked_list_size(list) == 0;
}


//TODO: Should this fail silently? Return an integer for failurestates?
void ioopm_linked_list_clear(ioopm_list_t *list){
  link_t *cursor = list->first;
  while (cursor){
    cursor = destroy_link(cursor); 
  }
  list->first = NULL;
  list->last = NULL;
  list->size = 0;
}

bool ioopm_linked_list_all(ioopm_list_t *list, ioopm_predicate prop, void *extra){
  bool list_non_empty = !ioopm_linked_list_is_empty(list);
  return check_predicate_for_all(list, prop, extra, false, list_non_empty, Inverted_predicate);
}

bool ioopm_linked_list_any(ioopm_list_t *list, ioopm_predicate prop, void *extra){
  return check_predicate_for_all(list, prop, extra, true, false, Predicate);
}

void ioopm_linked_apply_to_all(ioopm_list_t *list, ioopm_apply_function fun, void *extra){
  link_t *tracer = list->first;
  while (tracer){
    fun(Dummy_key, &tracer->element, extra);
    tracer = tracer->next;
  }
}

// ITERATOR API: 

ioopm_list_iterator_t *ioopm_list_iterator(ioopm_list_t *list){
  ioopm_list_iterator_t *iter = calloc(1, sizeof(ioopm_list_iterator_t));
  iter->first = &list->first;
  iter->current = &list->first;
  return iter;
}

bool ioopm_iterator_has_next(ioopm_list_iterator_t *iter){
  if (*iter->current){
    return (*iter->current)->next ? true : false;
  }
  return false;
}

option_t ioopm_iterator_next(ioopm_list_iterator_t *iter){
  if (ioopm_iterator_has_next(iter)){
    iter->current = &(*iter->current)->next;
    return Success((*iter->current)->element);
  }
  return Failure(); 
}

option_t ioopm_iterator_remove(ioopm_list_iterator_t *iter){
  link_t *removed = *iter->current;
  if (removed) {
    elem_t result = removed->element; 
    *iter->current = destroy_link(removed);
    return Success(result);
  } else {
    return Failure();
  }
}

void ioopm_iterator_insert(ioopm_list_iterator_t *iter, elem_t element){
  link_t *new_link = create_link(element, *iter->current);
  *iter->current = new_link;
}

void ioopm_iterator_reset(ioopm_list_iterator_t *iter){
  iter->current = &(*iter->first); 
}

option_t ioopm_iterator_current(ioopm_list_iterator_t *iter){
  return *iter->current ? Success((*iter->current)->element) : Failure(); 
}

void ioopm_iterator_destroy(ioopm_list_iterator_t *iter){
  free(iter);
}