#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "CUnit/Basic.h"

/// inlupp1

/// inlupp2 
#include "../demo/user_interface.h"
#include "../src/refmem.h"


int init_suite(void)
{
  return 0;
}

int clean_suite(void)
{
  return 0;
}

// TEST FUNCTIONS
/*
warehouse_t* non_empty_warehouse()
{
  warehouse_t *warehouse = create_warehouse();

  int str_size = 26;
  char *strings[26] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r",
    "s", "t", "u", "v", "w", "x", "y", "z"};
  for(int i = 0; i<str_size; ++i)
    {
      add_merchandise(warehouse, strdup(strings[i]), strdup("desciption"), 9.9);

      replenish(warehouse, strings[i], strdup("shelf1"), 10);

      replenish(warehouse, strings[i], strdup("shelf2"), 20);

      replenish(warehouse, strings[i], strdup("shelf3"), 15);

    }
    
  return warehouse;
}*/

warehouse_t* non_empty_warehouse()
{
  warehouse_t *warehouse = create_warehouse();

  int str_size = 5;
  char *strings[5] = {"a", "b", "c", "d", "e"};
    
  char *shelves[15] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15"};
  for(int i = 0; i<str_size; ++i)
    {
      option_t add_success = add_merchandise(warehouse, ioopm_refmem_strdup(strings[i]), ioopm_refmem_strdup("desciption"), 9.9);
      CU_ASSERT(Successful(add_success));
      option_t replenish_success1 = replenish(warehouse, strings[i], ioopm_refmem_strdup(shelves[i]), 10); //this doesnt replenish after first loop?..
      CU_ASSERT(Successful(replenish_success1));
      //replenish(warehouse, strings[i], strdup(shelves), 20);
      //replenish(warehouse, strings[i], strdup("shelf3"), 15);
    }
  return warehouse;
}


void test_admin()
{
  // Commet out when you whant to run the otherone
  //warehouse_t *warehouse = non_empty_warehouse();
  //admin_menu(warehouse);
}


void test_user()
{
  // Commet out when you whant to run the otherone
  shopping_cart_db_t *cart_db = create_cart_db();
  warehouse_t *warehouse = non_empty_warehouse();
  menu(warehouse, cart_db);
  //while(true){
  //  admin_menu(warehouse, cart_db);
  //  user_menu(warehouse, cart_db);
  //}
}


int main()
{
  CU_pSuite test_suite1 = NULL;

  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  test_suite1 = CU_add_suite("Iterator Tests", init_suite, clean_suite);
  if (NULL == test_suite1)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  if (
      (NULL == CU_add_test(test_suite1, "Admin Testing", test_admin)) ||
      (NULL == CU_add_test(test_suite1, "User Testing ", test_user)) 
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
