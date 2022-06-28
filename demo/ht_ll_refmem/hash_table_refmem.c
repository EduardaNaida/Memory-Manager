#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "linked_list_refmem.h"
#include "iterator_refmem.h"
#include "hash_table_refmem.h"
#include "../../src/refmem.h"

#define Initial_exponent 4
#define load_factor 0.75 
// INTERNAL TYPE DEFINITIONS:

typedef struct entry entry_t;

// STRUCT DEFINITIONS:

struct entry
{
  elem_t key;    // holds the key
  elem_t value;  // holds the value
  entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table
{
  ioopm_refmem_hash_function hash; 
  ioopm_refmem_cmp_function compare;
  size_t number_buckets;
  size_t size;
  size_t exponent;
  entry_t **buckets;
};


// STANDARD HASH FUNCTION:

static unsigned long elem_to_int(elem_t elem){
  return elem.integer;
}

// HELPER FUNCTIONS:

static int hash_function(ioopm_refmem_hash_table_t *ht, elem_t key){ 
  return (ht->hash(key)) % (ht->number_buckets); 
}

static entry_t *entry_create (elem_t key, elem_t value, entry_t *next) 
{
  entry_t *new_entry = allocate(sizeof(entry_t), NULL); //REFMEM: allocate
  retain(new_entry);
  new_entry->key = key;
  new_entry->value = value;
  new_entry->next = next;

  return new_entry;
}

static entry_t* entry_destroy(entry_t *entry) //REFMEM
{
  entry_t *next_entry = entry->next; 
  release(entry);
  return next_entry;
}

static entry_t **find_previous_entry_for_key(ioopm_refmem_cmp_function compare, entry_t **first_entry, elem_t key) 
{
  entry_t **tracer = first_entry;
  while (*tracer && compare((*tracer)->key, key) < 0)
  {
    tracer = &(*tracer)->next;
  }
  return tracer;
}

static bool check_predicate_for_all(ioopm_refmem_hash_table_t *ht, ioopm_refmem_predicate P, void *x, bool break_value, bool runout_value, bool invert_condition){
  for (int i = 0; i < ht->number_buckets; i++) {
    entry_t *entry = ht->buckets[i];
    while (entry){
      if (evaluate_predicate(P, entry->key, entry->value, x, invert_condition)){
        return break_value;
      }
    }
  }
  return runout_value;
}

//RESIZING STUFF 

static bool is_prime(size_t num){
  if (num <= 1){
    return false;
  }
  
  if (num % 2 == 0 && num > 2){
    return false;
  }
  size_t stop = floor(sqrt(num));
  for (int i = 3; i <= stop; i += 2){
    if (num % i == 0){
      return false;
    }
  }
  return true;
}

static size_t find_next_prime(size_t num){
  
  for (size_t i = num+1; i > 3; i++){
    if (is_prime(i)){
      return i;
    }
  }
  return num+1;   //if num is 1 or 2, just return num+1 (as 2 is a prime number and 3 is a prime number)
}

static void hash_table_rehash(ioopm_refmem_hash_table_t *ht, size_t old_num_buckets){
  for (int i = 0; i < old_num_buckets; i++){
    
    entry_t **entry = &ht->buckets[i];
    
    while (*entry){ 
      int new_hash = hash_function(ht, (*entry)->key);
      if (i != new_hash) {
        entry_t **prev_entry_next_ptr = find_previous_entry_for_key(ht->compare, &ht->buckets[new_hash], (*entry)->key);
        
        entry_t *next = (*entry)->next;
        (*entry)->next = (*prev_entry_next_ptr);
        (*prev_entry_next_ptr) = *entry;
        (*entry) = next; 
      }
      else{
        entry = &(*entry)->next;
      }
    }
  }
}

static void init_memory(ioopm_refmem_hash_table_t *ht, size_t old_num_buckets){
  for (int i = old_num_buckets; i < ht->number_buckets; i++) {
    ht->buckets[i] = NULL;
  }
}

static void hash_table_resize(ioopm_refmem_hash_table_t *ht){
  
  //find next prime number
  size_t old_buckets = ht->number_buckets;
  ht->exponent++;
  ht->number_buckets = find_next_prime((size_t) pow(2, ht->exponent));
  
  
  //entry_t **new_array = realloc(ht->buckets, sizeof(entry_t*) * ht->number_buckets); //TODO: REFMEM: VAD ?
  //entry_t **new_array = allocate_array(ht->buckets, sizeof(entry_t*) * ht->number_buckets);
  
  entry_t **new_array = allocate_array(ht->number_buckets, sizeof(entry_t*), NULL);
  memcpy(new_array, ht->buckets, sizeof(entry_t*) * old_buckets); //memcpy(dest, source, size)
  
  release(ht->buckets);
  ht->buckets = new_array;

  init_memory(ht, old_buckets);
  
  hash_table_rehash(ht, old_buckets); 
}

static bool hash_table_too_small(ioopm_refmem_hash_table_t *ht){
  return (load_factor < (ht->size/ht->number_buckets)); 
}

// PUBLIC API FUNCTIONS:

static void hash_table_destructor(obj *htt)   //REFMEM
{
  ioopm_refmem_hash_table_t *ht = (ioopm_refmem_hash_table_t *) htt;
  for (int i = 0; i < ht->number_buckets; i++) {
    entry_t *bucket = ht->buckets[i];
    while (bucket){
      bucket = entry_destroy(bucket);
    }
  }
  release(ht->buckets);
}

ioopm_refmem_hash_table_t *ioopm_refmem_hash_table_create(ioopm_refmem_hash_function hash_func, ioopm_refmem_cmp_function compare)
{
  ioopm_refmem_hash_table_t *ht = allocate(sizeof(ioopm_refmem_hash_table_t), hash_table_destructor); //REFMEM: allocate
  
  ht->size = 0;
  ht->exponent = Initial_exponent;
  ht->number_buckets = find_next_prime(pow(2, ht->exponent));
 
  
  //entry_t **buckets = calloc(ht->number_buckets, sizeof(entry_t *)); 
  entry_t **buckets = allocate_array(ht->number_buckets, sizeof(entry_t *), NULL); //TODO: REFMEM: allocate
  
  
  
  ht->buckets = buckets;
  
  ht->hash = hash_func ? hash_func : elem_to_int;
  ht->compare = compare ? compare : int_compare;
  
  return ht;
}


void ioopm_refmem_hash_table_destroy(ioopm_refmem_hash_table_t *ht)
{
  release(ht);
}


option_t ioopm_refmem_hash_table_lookup(ioopm_refmem_hash_table_t *ht, elem_t key) 
{
  unsigned long hash = hash_function(ht, key);
  entry_t **next = find_previous_entry_for_key(ht->compare, &(ht->buckets[hash]), key);

  if (*next && ht->compare((*next)->key, key) == 0)
  {
    return Success((*next)->value);
  }
  else
  {
    return Failure();
  }
}



option_t ioopm_refmem_hash_table_remove(ioopm_refmem_hash_table_t *ht, elem_t key)
{
  int hash = hash_function(ht, key);
  entry_t **tracer = find_previous_entry_for_key(ht->compare,&ht->buckets[hash], key);
  
  if (*tracer)
  {
    entry_t *removed_entry = (*tracer);
    (*tracer) = (*tracer)->next;
    elem_t value = removed_entry->value;
    entry_destroy(removed_entry); //REFMEM: release ?
    ht->size--;
    
    return Success(value); 
  }
  else
  {
    return Failure();
  }
}



void ioopm_refmem_hash_table_insert(ioopm_refmem_hash_table_t *ht, elem_t key, elem_t value) 
{
  if (hash_table_too_small(ht)){
    hash_table_resize(ht);
  }
  
  int hash = hash_function(ht, key);
  entry_t **entry = find_previous_entry_for_key(ht->compare, &(ht->buckets[hash]), key);

  if (*entry && ht->compare((*entry)->key, key) == 0)
  {
    (*entry)->value = value;
  }
  else
  {
    *entry = entry_create(key, value, *entry);
    ht->size++;
  }
}

size_t ioopm_refmem_hash_table_size (ioopm_refmem_hash_table_t *ht)
{
  return ht->size;
}



bool ioopm_refmem_hash_table_is_empty(ioopm_refmem_hash_table_t *ht)
{
  return ioopm_refmem_hash_table_size(ht) == 0;
}

void ioopm_refmem_hash_table_clear(ioopm_refmem_hash_table_t *ht)
{
  for (int i = 0; i < ht->number_buckets; i++)
  {
    entry_t *bucket = ht->buckets[i];
    ht->buckets[i] = NULL;
    while (bucket)
    {
      bucket = entry_destroy(bucket); //REFMEM: release inside
    }
  }
  ht->size = 0;
}

ioopm_refmem_list_t *ioopm_refmem_hash_table_keys(ioopm_refmem_hash_table_t *ht)
{
  ioopm_refmem_list_t *list = ioopm_refmem_linked_list_create(ht->compare);
  for (int i = 0; i < ht->number_buckets; i++)
  {
    entry_t *entry = ht->buckets[i];
    while(entry)
    {
      ioopm_refmem_linked_list_append(list, entry->key);
      entry = entry->next;
    }
  }
  return list;
}

ioopm_refmem_list_t *ioopm_refmem_hash_table_values(ioopm_refmem_hash_table_t *ht) 
{
  ioopm_refmem_list_t *list = ioopm_refmem_linked_list_create(ht->compare);
  for (int i = 0; i < ht->number_buckets; i++)
  {
    entry_t *entry = ht->buckets[i];
    while(entry)
    {
      ioopm_refmem_linked_list_append(list, entry->value); //Epointer(&entry->value)
      entry = entry->next; 
    }
  }
  return list;
}

bool ioopm_refmem_hash_table_has_key(ioopm_refmem_hash_table_t *ht, elem_t key) 
{
  return ioopm_refmem_hash_table_lookup(ht, key).success;
}

bool ioopm_refmem_hash_table_has_value(ioopm_refmem_hash_table_t *ht, elem_t value) 
{
  for (int i = 0; i < ht->number_buckets; i++)
  {
    entry_t *current_entry = ht->buckets[i];
    elem_t current_value;
    
    while (current_entry)
    {
      current_value = current_entry->value; 
      if (ht->compare(current_value, value) == 0)
      {
        return true;
      }
      current_entry = current_entry->next;
    }
  }
  return false;
}

bool ioopm_refmem_hash_table_all(ioopm_refmem_hash_table_t *ht, ioopm_refmem_predicate P, void *x) 
{
  bool is_non_empty = !ioopm_refmem_hash_table_is_empty(ht);
  return check_predicate_for_all(ht, P, x, false, is_non_empty, Inverted_predicate);
}


bool ioopm_refmem_hash_table_any(ioopm_refmem_hash_table_t *ht, ioopm_refmem_predicate P, void *x) 
{
  return check_predicate_for_all(ht, P, x, true, false, Predicate);
}

void ioopm_refmem_hash_table_apply_to_all(ioopm_refmem_hash_table_t *ht, ioopm_refmem_apply_function P, void *x) 
{

  for (int i = 0; i < ht->number_buckets; i++)
  {
    entry_t *entry = ht->buckets[i];
    while(entry)
    {
      P(entry->key, &entry->value, x);
      entry = entry->next; 
    }
  }
}


