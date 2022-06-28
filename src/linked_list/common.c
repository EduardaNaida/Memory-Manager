#include "common.h"

int int_compare(elem_t a, elem_t b){
  return a.integer - b.integer;
}

bool evaluate_predicate(ioopm_predicate prop, elem_t key, elem_t value, void *extra, bool invert_condition){
  return invert_condition ? !prop(key, value, extra) : prop(key, value, extra);
}
