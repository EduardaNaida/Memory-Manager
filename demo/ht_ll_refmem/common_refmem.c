#include "common_refmem.h"

int refmem_int_compare(elem_t a, elem_t b){
  return a.integer - b.integer;
}

bool refmem_evaluate_predicate(ioopm_refmem_predicate prop, elem_t key, elem_t value, void *extra, bool invert_condition){
  return invert_condition ? !prop(key, value, extra) : prop(key, value, extra);
}
