#pragma once
#include <stdint.h>
#include <stdlib.h>

typedef void obj;
typedef void(*function1_t)(obj *);

/**
 * @brief increases reference count for an allocation
 *
 * @param ptr pointer to the allocation returned from allocate or allocate_array
 */
void retain(obj* ptr);

/**
 * @brief decreases reference count for an allocation
 *
 * When calling release on an allocation with a reference count of 1 the allocation 
 * will have its destructor called and its memory freed.
 *
 * @param ptr allocation returned from allocate or allocate_array
 */
void release(obj* ptr);

/**
 * @brief returns the reference count of an allocation
 * 
 * @param ptr allocation returned from allocate or allocate_array
 * @return the reference count
 */
size_t rc(obj* ptr);


/**
 * @brief default destructor which can be useful for some datatypes
 *
 * The default destructor will scan the allocation looking for other valid allocations
 * and then also release those
 *
 * @param ptr allocation returned from allocate or allocate_array
 */
void default_destructor(obj* ptr);

/**
 * @brief creates an allocation of arbitrary size
 *
 * @param bytes size of allocation (in bytes) to creates
 * @param destructor destructor function called when the allocation is free'd
 */
obj *allocate(size_t bytes, function1_t destructor);

/**
 * @brief creates an allocation of arbitrary size array
 *
 * @param elements amount of elements in the array
 * @param elem_size size of each element (in bytes)
 * @param destructor destructor function called when the allocation is free'd
 */
obj *allocate_array(size_t elements, size_t elem_size, function1_t destructor);

/**
 * @brief Sets the cascade limit for the library
 *
 * The cascade limit determines how many 'nested' free's a deallocation can perform, the outstanding
 * frees will be done later on when allocating a new buffer, or forcefully when cleanup is called.
 *
 * @param limit new cascade limit
 */
void set_cascade_limit(size_t);

/**
 * @brief Gets the current cascade limit
 *
 * The cascade limit determines how many 'nested' free's a deallocation can perform, the outstanding
 * frees will be done later on when allocating a new buffer, or forcefully when cleanup is called.
 *
 * @return current cascade limit
 */
size_t get_cascade_limit();

/**
 * @brief Cleans up all outstanding free's which has been queued up because of the cascade limit
 */
void cleanup();

/**
 * @brief Shuts down the library. Calls cleanup and then cleans up everything else the library needed to work. Called once at the end of the program.
 */
void shutdown();

