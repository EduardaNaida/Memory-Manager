#include "refmem.h"
#include "linked_list/linked_list.h"
#include "linked_list/common.h"
#include "hash_table/hash_table.h"
#include <string.h>
#include <stdio.h>
#include <limits.h>

// local global variables we need for the library
size_t cascade_limit = 50;
ioopm_list_t *garbage_collector;
ioopm_hash_table_t *pointer_memory;
int rec_depth = 0;
int bytes_cleaned = 0;
int req_amount = 0;

typedef struct {
    uint32_t refcount;
    size_t size;
    function1_t destructor;
} mem_header;

void deallocate(obj *ptr);

// we store the header in the memory space before the 'allocation' itself
mem_header* get_header(obj *ptr) {
    return (mem_header*)((uintptr_t)ptr - sizeof(mem_header));
}

// we store the header in the memory space before the 'allocation' itself
obj *get_obj(mem_header *hdr) {
    return (obj*)((uintptr_t)hdr + sizeof(mem_header));
}

size_t rc(obj* ptr) {
    return get_header(ptr)->refcount;
}

void default_destructor(obj* ptr) {
    // get start and end of allocation
    uintptr_t start = (uintptr_t) ptr;
    uintptr_t end = start + (get_header(ptr)->size - sizeof(mem_header));
    size_t ptr_size = sizeof(void*);

    if (start & (ptr_size - 1)) {
        start = (start + ptr_size) & ~(ptr_size - 1);
    }

    // scan the whole range of the allocation. If we find a pointer which matches with one of our known pointers
    // the pointer in question will be released.
    while ((start + ptr_size) <= end) { // ensure we have enough space to read a full pointer
        option_t lookup = ioopm_hash_table_lookup(pointer_memory, Epointer(*(void**)start)); //Borde nämna fel om en unsigned long eller uintptr matcher exakt
        if (lookup.success) {
            // valid pointer, release it.
            release(lookup.value.pointer);
        }
        start += ptr_size;
    }
}

// performs outstanding frees until min_bytes bytes has been free'd
void clean_amount(int min_bytes) {
    // make sure the garbage collector exists
    if (!garbage_collector) {
        garbage_collector = ioopm_linked_list_create(NULL);
    }
    
    // recursion depth of 0 means we are on the top level of the recursion, we are in the original call
    // we need to know this to be able to reset the recursion depth back to 0 at the end of this function
    // because that global is used in other functions.
    bool top_level = false;
    if(rec_depth == 0) {
        req_amount = min_bytes;
        bytes_cleaned = 0;
        top_level = true;
    }
    
    while(!ioopm_linked_list_is_empty(garbage_collector) && (rec_depth < cascade_limit || bytes_cleaned < req_amount)) {
        deallocate(ioopm_linked_list_remove(garbage_collector, 0).value.pointer);
    }
    
    // exiting from top level, make sure to reset recursion depth
    if(top_level) {
        rec_depth = 0;
    }
}

unsigned long pointer_hash(elem_t elem) {
    return (unsigned long) elem.pointer;
}


obj *allocate(size_t bytes, function1_t destructor) {
    size_t size = (sizeof(mem_header) + bytes);
    
    // perform cleanup of some outstanding frees if needed
    clean_amount(size);
    
    // make sure the hash table for all pointers exists
    if (!pointer_memory) {
        pointer_memory = ioopm_hash_table_create(pointer_hash, NULL);
    }
    
    mem_header *hdr = calloc(1, size);
    hdr->size = size;
    hdr->refcount = 0;
    hdr->destructor = destructor;
    
    
    // insert the pointer into our hash table so we can identify it later on if needed.
    void *ptr = get_obj(hdr); 
    ioopm_hash_table_insert(pointer_memory, Epointer(ptr), Epointer(ptr)); 
    return ptr;
}

obj *allocate_array(size_t elements, size_t elem_size, function1_t destructor) {
    return allocate(elements * elem_size, destructor);
}

void deallocate(obj *ptr) {
    // make sure we should continue our deallocation "chain"
    // ie. that we haven't reached our cascade limit.
    if (rec_depth >= cascade_limit && bytes_cleaned >= req_amount) {
        // make sure the garbage collector exists
        if(!garbage_collector) {
            garbage_collector = ioopm_linked_list_create(NULL);
        }
        // we reached our cascade limit and have to stop freeing
        // place the belated free into our garbage collector to free at a later time
        ioopm_linked_list_append(garbage_collector, Epointer(ptr));
        return;
    }
    
    // we are counting recursion depth as a way to count nested frees so we can handle it for cascade limit
    rec_depth++;
    mem_header *hdr = get_header(ptr);
    if (hdr->refcount != 0) {
        printf("references to this this instance still exists");
    }
    else {
        // increment the total bytes cleaned in the global since we need to keep track of this for cascade limit
        bytes_cleaned += hdr->size;
        if (hdr->destructor) {
            hdr->destructor(ptr);
        }
        ioopm_hash_table_remove(pointer_memory, Epointer(ptr));
        free(hdr);
    }
}

void retain(obj *ptr) {
    if (!ptr)
        return;
    
    mem_header *hdr = get_header(ptr);
    hdr->refcount++; 
}

void release(obj *ptr) {
    mem_header *hdr = get_header(ptr);
    if(ptr == NULL){
        //TODO: what sort of error handling do we use? 
        printf("pointer is null");
        return;
    }
    if(hdr->refcount > 0) {
        hdr->refcount--;
    }
    
    if(hdr->refcount == 0) {
        // make sure garbage collector exists
        if (!garbage_collector) {
            garbage_collector = ioopm_linked_list_create(NULL);
        }
        // add our current memory object to the garbage collector and use
        // clean amount to perform the proper free and cleanup for the object.
        ioopm_linked_list_append(garbage_collector, Epointer(ptr));
        clean_amount(0);
    }
    else if (hdr->refcount < 0) {
        // this implies wrong usage of the library.
        printf("Negative refcount detected for object %p", ptr);
    }
}

void set_cascade_limit(size_t size) {
    cascade_limit = size;
}

size_t get_cascade_limit() {
    return cascade_limit;
}

void cleanup() {
    // we call clean_amount with INT_MAX as min bytes, this ensurers that we will fully
    // clear out all outstanding frees in the garbage collector.
    clean_amount(INT_MAX);
}

void shutdown() {
    cleanup();
    ioopm_linked_list_destroy(garbage_collector); 
    ioopm_hash_table_destroy(pointer_memory);
    pointer_memory = NULL;
    garbage_collector = NULL;
}

