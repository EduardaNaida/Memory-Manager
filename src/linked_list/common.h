#pragma once

#include <stdbool.h>

#define Eint(v)       (elem_t) {.integer = v}
#define Euint(v)      (elem_t) {.uinteger = v}
#define Ebool(v)      (elem_t) {.boolean = v}
#define Edouble(v)    (elem_t) {.decimal = v}
#define Efloat(v)     (elem_t) {.floating_point = v}
#define Epointer(v)   (elem_t) {.pointer = v}
#define Eulong(v)     (elem_t) {.ulong = v}

#define Success(v)      (option_t) { .success = true, .value = v }
#define Failure()       (option_t) { .success = false }
#define Successful(o)   (o.success == true)
#define Unsuccessful(o) (o.success == false)

#define Inverted_predicate (bool) {true}
#define Predicate (bool) {false}

typedef union elements {
    int integer;
    unsigned int uinteger;
    bool boolean;
    double decimal;
    float floating_point;
    void *pointer;
    unsigned long ulong;
} elem_t; 

typedef struct option
{
  const bool success;
  const elem_t value;
}option_t;

typedef bool (*ioopm_predicate)(elem_t key, elem_t value, void *extra);
typedef void (*ioopm_apply_function)(elem_t key, elem_t *value, void *extra);
typedef int(*ioopm_cmp_function)(elem_t a, elem_t b);



int int_compare(elem_t a, elem_t b);

/**
 * @brief Evaluates a predicate and optionally inverts its result
 * @param prop the predicate
 * @param key argument to predicate
 * @param value argument to predicate
 * @param extra argument to predicate
 * @param invert_condition wheter or not the condition should be inverted
 * @return the result or inverted result of evaluationg prop on its arguments
*/
bool evaluate_predicate(ioopm_predicate prop, elem_t key, elem_t value, void *extra, bool invert_condition);