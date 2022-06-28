#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "CUnit/Basic.h"
#include "../src/refmem.h"


int init_suite(void)
{
  return 0;
}

int clean_suite(void)
{
  return 0;
}

int des_counter = 0;

struct cell
{
  struct cell *cell;
  int i;
  char *string;
};

typedef struct cell cell_t;

void cell_destructor(obj *c)
{
  if (((cell_t*) c)->cell != NULL) {
    release(((cell_t*) c)->cell);
  }
}

void try_allocate()
{
  size_t bytes = sizeof(cell_t);
  function1_t destructor = cell_destructor;
  cell_t *ptr = allocate(bytes ,destructor);

  ptr->i = 30;
  ptr->string = "foo";
  uint32_t ref = 0;
  
  CU_ASSERT_EQUAL("foo", ptr->string);
  
  CU_ASSERT_EQUAL(rc(ptr),ref); 
  retain(ptr);
  release(ptr);
}

void try_deallocate()
{
  size_t bytes = sizeof(cell_t);
  function1_t destructor = cell_destructor;
  cell_t *ptr = allocate(bytes, destructor);
  ptr->i = 30;
  ptr->string = "foo";
  retain(ptr);
  release(ptr);
}

void try_retain()
{
    size_t bytes = sizeof(cell_t);
    function1_t destructor = cell_destructor;
    
    cell_t *obj = allocate(bytes, destructor);
    uint32_t ref = 0;
    CU_ASSERT_EQUAL(rc(obj), ref); //0 - 0
    
    retain(obj); //1
    CU_ASSERT_NOT_EQUAL(rc(obj), ref); //1 - 0
    
    ref = 1;
    CU_ASSERT_EQUAL(rc(obj), ref);
    
    retain(obj); //2
    retain(obj); //3
    retain(obj); //4
    
    ref = 4;
    CU_ASSERT_EQUAL(rc(obj), ref);
    
    release(obj); //4
    release(obj); //3
    release(obj); //2
    release(obj); //1
    
}

void try_release()
{
    size_t bytes = sizeof(cell_t);
    function1_t destructor = cell_destructor;
    cell_t *ptr = allocate(bytes, destructor);
    ptr->i = 30;
    ptr->string = "foo";
    uint32_t ref = 0;
    
    CU_ASSERT_EQUAL(rc(ptr), ref); 
    retain(ptr); //2
    retain(ptr); //3
    retain(ptr); //4
    release(ptr);
    ref = 2;
    CU_ASSERT_EQUAL(rc(ptr), ref); 
    release(ptr);
    ref = 1;
    CU_ASSERT_EQUAL(rc(ptr), ref); 
    release(ptr);
    obj *null = NULL;
    release(null);
}

void try_rc()
{
    size_t bytes = sizeof(cell_t*);
    function1_t destructor = cell_destructor;
    
    cell_t *ptr = allocate(bytes, destructor);
    uint32_t ref = 0;
    size_t refcounter = rc(ptr);
    
    CU_ASSERT_EQUAL(ref, refcounter);
    
    retain(ptr); //1
    retain(ptr); //2
    retain(ptr); //3
    
    refcounter = rc(ptr);
    CU_ASSERT_NOT_EQUAL(ref, refcounter)
    
    ref = 3;
    
    CU_ASSERT_EQUAL(ref, refcounter);
    
    release(ptr);       //2
    release(ptr);       //1
    release(ptr);       //0
}

void try_destructor()
{
  size_t bytes = sizeof(cell_t);
  function1_t destructor = cell_destructor;
  cell_t *cell1 = allocate(bytes, destructor);
  retain(cell1);
  
  cell1->cell = allocate(bytes, destructor);
  cell_t *cell2 = cell1->cell;
  retain(cell2);
  retain(cell2);
  
  cell2->cell = allocate(bytes, destructor);
  retain(cell2->cell);
  
  uint32_t ref = 2;
  size_t refcounter = rc(cell2);
  CU_ASSERT_EQUAL(ref, refcounter);
  
  release(cell1);
  
  ref = 1;
  refcounter = rc(cell2);
  CU_ASSERT_EQUAL(ref, refcounter);
  
  release(cell2);
}

void try_allocate_array()
{
  size_t bytes = sizeof(int);
  int *array = allocate_array(10, bytes, NULL);
  retain(array);
  release(array);
  CU_ASSERT(true);
}

void cell_destructor2(obj *c)
{
  if (((cell_t*) c)->cell != NULL) {
    release(((cell_t*) c)->cell);
  }
  des_counter += 1;
}


cell_t *create_cells() 
{
  size_t bytes = sizeof(cell_t);
  function1_t destructor = cell_destructor2;  //Global dest variabel
  cell_t *cell1 = allocate(bytes, destructor);
  retain(cell1);
  
  cell1->cell = allocate(bytes, destructor);
  cell_t *cell2 = cell1->cell;
  retain(cell2);
  
  cell2->cell = allocate(bytes, destructor);
  retain(cell2->cell);
  return cell1;
}

void try_cascade_limit()
{ 
  set_cascade_limit(3);
  cell_t *cell13 = create_cells();
  cell13->cell->cell->cell = create_cells();
  cell_t *cell23 = cell13->cell->cell->cell;
  cell23->cell->cell->cell = create_cells();
  
  release(cell13);
  CU_ASSERT(des_counter == 3);
  cell_t *cell35 = create_cells(); //Three allocates in create_cells == 3xCascade limit max removal
  cell35->cell->cell->cell = create_cells();
  release(cell35);
  CU_ASSERT(des_counter == 12);
  set_cascade_limit(1);
  
  void **test_disregard_cascade_limit = allocate_array(10, sizeof(void *), NULL);
  CU_ASSERT(des_counter == 15);
  release(test_disregard_cascade_limit);

}

struct spec1
{
  char a;
  int i;
  char b;
  cell_t *cell;
};

typedef struct spec1 spec1_t;

spec1_t* create_spec1(char a, int i, char b, cell_t *cell)
{
  size_t bytes = sizeof(spec1_t);
  spec1_t *special1 = allocate(bytes, default_destructor);
  retain(special1);
  special1->a = a;
  special1->i = i;
  special1->b = b;
  special1->cell = cell;
  return special1;
}

typedef struct spec2 spec2_t;

struct spec2
{
  spec1_t *spec11;
  char a;
  unsigned long l;
  spec2_t *spec22;
  char b;
  int *ints;
};

spec2_t* create_spec2(spec1_t *spec11, char a, unsigned long l, spec2_t *spec22, char b, int *ints)
{
  size_t bytes = sizeof(spec2_t);
  spec2_t *special2 = allocate(bytes, default_destructor);
  retain(special2);
  special2->spec11 = spec11;
  special2->a = a;
  special2->l = l;
  special2->spec22 = spec22;
  special2->b = b;
  special2->ints = ints;
  return special2;
}
//int int
void try_default_destructor()
{ 
  //Works as further testing of cascade_limit since it is currently 1
  spec1_t *spec11 = create_spec1('a', 612341263, 'b', create_cells());
  spec1_t *spec12 = create_spec1('c', 567345345, 'd', create_cells());
  spec1_t *spec13 = create_spec1('e', 1234123, 'f', create_cells());
  spec1_t *spec14 = create_spec1('g', 657536745, 'h', create_cells());

  int *b = allocate_array(4, sizeof(int), default_destructor);
  retain(b);
  int *c = allocate_array(2, sizeof(int), default_destructor);
  retain(c);
  retain(c);
  int *d = allocate_array(2, sizeof(int), default_destructor);
  retain(d);
  spec2_t *spec21 = create_spec2(spec11, 'l', 0, NULL, 't', b);
  spec2_t *spec22 = create_spec2(NULL, 'g', 18446744003709051615ul, spec21, 'r', NULL);
  spec2_t *spec23 = create_spec2(spec12, 'g', 0, spec22, 'r', NULL);
  retain(spec23);
  spec2_t *spec24 = create_spec2(spec13, 'g', 18335744073700000000ul, spec23, 'r', c);
  spec2_t *spec25 = create_spec2(spec14, 'g', 44073709551615ul, spec24, 'r', d);
  release(spec25);
  
  CU_ASSERT_EQUAL(spec23->a, 'g');
  release(spec23);
  release(c);
}

//TODO: Test shutdown ?

int main()
{
    CU_pSuite memtest_suite = NULL;
    
    if (CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();

    memtest_suite = CU_add_suite("Testing of ", init_suite, clean_suite);
    
    if (NULL == memtest_suite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if(
        (NULL == CU_add_test(memtest_suite, "Test allocate ",       try_allocate))        ||
        (NULL == CU_add_test(memtest_suite, "Test deallocate",      try_deallocate))      ||             
        (NULL == CU_add_test(memtest_suite, "Test retain",          try_retain))          ||             
        (NULL == CU_add_test(memtest_suite, "Test release",         try_release))         ||     
        (NULL == CU_add_test(memtest_suite, "Test destructor",      try_destructor))      ||
        (NULL == CU_add_test(memtest_suite, "Test allocate_array",  try_allocate_array))  ||
        (NULL == CU_add_test(memtest_suite, "Test cascade_limit",  try_cascade_limit))    ||
        (NULL == CU_add_test(memtest_suite, "Test default_destructor",try_default_destructor))
        
    )
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    shutdown();
    return CU_get_error();
}
