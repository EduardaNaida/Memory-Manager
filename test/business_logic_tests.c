#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "CUnit/Basic.h"

#include "../demo/ht_ll_refmem/iterator_refmem.h"

#include "../demo/business_logic.h" 
#include "../demo/generic_utils.h" 
#include "../src/refmem.h"

/// test only
struct warehouse
{
  ioopm_refmem_hash_table_t *merchendise;  // .key=name  .value=point_merch
  ioopm_refmem_hash_table_t *storage;      // .key=shelf .vale=merch_name
};

struct merch
{
    char *name;
    char *desc;
    float price;
    size_t stock;  // The summ of all quantitys in locs
    ioopm_refmem_list_t *locs;
};


int init_suite(void)
{
  return 0;
}

int clean_suite(void)
{
  return 0;
}

/// Test helper funktions
warehouse_t* non_empty_warehouse()
{
  warehouse_t *warehouse = create_warehouse();

  int str_size = 26;
  char *strings[26] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r",
    "s", "t", "u", "v", "w", "x", "y", "z"};
  for(int i = 0; i<str_size; ++i)
    {
      option_t add_success = add_merchandise(warehouse, ioopm_refmem_strdup(strings[i]), ioopm_refmem_strdup("desciption"), 9.9);
      CU_ASSERT(Successful(add_success));
      replenish(warehouse, strings[i], ioopm_refmem_strdup("shelf1"), 10);
      replenish(warehouse, strings[i], ioopm_refmem_strdup("shelf2"), 20);
      replenish(warehouse, strings[i], ioopm_refmem_strdup("shelf3"), 15);
    }
    
  return warehouse;
}

warehouse_t* non_empty_warehouse_with_items()
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
      
      //retain(strings[i]);
      
      
      //replenish(warehouse, strings[i], ioopm_refmem_strdup(shelves), 20);
      //replenish(warehouse, strings[i], ioopm_refmem_strdup("shelf3"), 15);
    }
  return warehouse;
}

shopping_cart_db_t *non_empty_cart_db(warehouse_t *warehouse)
{
  
  shopping_cart_db_t *cart_db = create_cart_db();
  ioopm_refmem_list_t *values = ioopm_refmem_hash_table_values(warehouse->merchendise);
  ioopm_refmem_list_iterator_t *iter_values = ioopm_refmem_list_iterator(values); //make an iterator

  char *username1 = ioopm_refmem_strdup("username1");
  //retain(username1);
  char *username2 = ioopm_refmem_strdup("username2");
  //retain(username2);
  char *username3 = ioopm_refmem_strdup("username3");
  //retain(username3);
  
  shopping_cart_t *cart1 = add_cart(cart_db, username1).value.pointer;
  shopping_cart_t *cart2 = add_cart(cart_db, username2).value.pointer;
  shopping_cart_t *cart3 = add_cart(cart_db, username3).value.pointer;

  do{
    merch_t *item = ioopm_refmem_iterator_current(iter_values).value.pointer; //item is null here, why?
    option_t add_success = add_to_cart(cart1, item, 1);
    CU_ASSERT_TRUE(Successful(add_success));
    
    option_t add_success2 = add_to_cart(cart2, item, 1);
    CU_ASSERT_TRUE(Successful(add_success2));
    
    option_t add_success3 = add_to_cart(cart3, item, 1);
    CU_ASSERT_TRUE(Successful(add_success3));
  }while(Successful(ioopm_refmem_iterator_next(iter_values)));
  
  
  
  // clean up
  ioopm_refmem_iterator_destroy(iter_values); //remove iterator  
  ioopm_refmem_linked_list_destroy(values); //remove list

  return cart_db;
}

shopping_cart_db_t *non_empty_cart_db_no_items(){
  
  shopping_cart_db_t *cart_db = create_cart_db();

  char *username1 = ioopm_refmem_strdup("username1");
  char *username2 = ioopm_refmem_strdup("username2");
  char *username3 = ioopm_refmem_strdup("username3");
  
  add_cart(cart_db, username1);
  add_cart(cart_db, username2);
  add_cart(cart_db, username3);

  return cart_db;
  
}

/// Tests

void test_create_destroy()
{
  warehouse_t *warehouse = create_warehouse();
  shopping_cart_db_t *cart_db = non_empty_cart_db_no_items(warehouse);
  CU_ASSERT_PTR_NOT_NULL(warehouse);
  destroy_warehouse(cart_db, warehouse);
  destroy_cart_db(cart_db);
}


void test_add_remove_merchandise()
{
  warehouse_t *warehouse = create_warehouse();
  
  shopping_cart_db_t *cart_db =non_empty_cart_db_no_items(warehouse);
  
  option_t add_success = add_merchandise(warehouse, ioopm_refmem_strdup("name"), ioopm_refmem_strdup("desciption"), 9.9);
  CU_ASSERT(Successful(add_success));
  //list_merchandise(warehouse);

  option_t add_unsuccessful = add_merchandise(warehouse, ioopm_refmem_strdup("name"), ioopm_refmem_strdup("other"), 10);
  CU_ASSERT(Unsuccessful(add_unsuccessful));

  char *strdup_name = ioopm_refmem_strdup("name");
  retain(strdup_name);
  option_t remove_success = remove_merchandise(cart_db, warehouse, strdup_name);
  CU_ASSERT(Successful(remove_success));
  release(strdup_name);

  destroy_warehouse(cart_db, warehouse);
  destroy_cart_db(cart_db);
}

void test_edit_merchandise()
{
  warehouse_t *warehouse = create_warehouse();
  shopping_cart_db_t *cart_db = create_cart_db();
  option_t add_success = add_merchandise(warehouse, ioopm_refmem_strdup("name"), ioopm_refmem_strdup("desciption"), 9.9);
  CU_ASSERT(Successful(add_success));

  // edit existing
  char *strdup_name = ioopm_refmem_strdup("name");
  retain(strdup_name);
  char *strdup_wrong_name = ioopm_refmem_strdup("wrong_name");
  retain(strdup_wrong_name);
  option_t edit_success1 = edit_merchandise(warehouse, cart_db, strdup_name, ioopm_refmem_strdup("new_name"), ioopm_refmem_strdup("new_desciption"), 9.9);
  CU_ASSERT(Successful(edit_success1));
  option_t edit_success2 = edit_merchandise(warehouse, cart_db, strdup_wrong_name, ioopm_refmem_strdup("new_name"), ioopm_refmem_strdup("new_desciption"), 8);
  CU_ASSERT(Unsuccessful(edit_success2));
  //list_merchandise(warehouse);
  CU_ASSERT(ioopm_refmem_hash_table_lookup(warehouse->merchendise, Epointer("new_name")).success);
    
  option_t remove_success3 = remove_merchandise(cart_db, warehouse, strdup_name);
  CU_ASSERT(Unsuccessful(remove_success3));
  option_t remove_success4 = remove_merchandise(cart_db, warehouse, "new_name");
  CU_ASSERT(Successful(remove_success4));
  release(strdup_name);
  release(strdup_wrong_name);
  
  destroy_warehouse(cart_db, warehouse);
  destroy_cart_db(cart_db);
}

/* needs another test func
void test_edit_merch_in_carts()
{
  warehouse_t *warehouse = non_empty_warehouse_with_items();
  shopping_cart_db_t *cart_db = non_empty_cart_db();
  
  edit_merchandise(warehouse, cart_db, strdup("a"), strdup("hej"), strdup("desc"), 55)
  
  shopping_cart_t *shopping_cart1 = ioopm_refmem_hash_table_lookup(cart_db, Epointer("username1")).value.pointer;
  shopping_cart_t *shopping_cart2 = ioopm_refmem_hash_table_lookup(cart_db, Epointer("username2")).value.pointer;
  
  ioopm_refmem_hash_table_t *cart1 = get_cart(shopping_cart1);
  ioopm_refmem_hash_table_t *cart2 = get_cart(shopping_cart2);
  
  
  destroy_warehouse(cart_db, warehouse);
  destroy_cart_db(cart_db);
  
}*/

void test_replenish()
{
  warehouse_t *warehouse = create_warehouse();
  shopping_cart_db_t *cart_db = non_empty_cart_db_no_items(warehouse);
  option_t add_success = add_merchandise(warehouse, ioopm_refmem_strdup("name"), ioopm_refmem_strdup("desciption"), 9.9);
  CU_ASSERT(Successful(add_success));

  char *strdup_name = ioopm_refmem_strdup("name");
  retain(strdup_name);
  /// Test inizial replenish
  option_t replenish_success1 = replenish(warehouse, strdup_name, ioopm_refmem_strdup("A32"), 100);
  CU_ASSERT(Successful(replenish_success1));
  //show_stock(warehouse, "name");

  // Test invalid init valuez
  option_t replenish_success2 = replenish(warehouse, strdup_name, ioopm_refmem_strdup("B12"), -2);
  CU_ASSERT(Unsuccessful(replenish_success2));
    
  /// Test replensish multiple shelfs and 
  option_t replenish_success3 = replenish(warehouse, strdup_name, ioopm_refmem_strdup("B12"), 2);
  CU_ASSERT(Successful(replenish_success3));
  //show_stock(warehouse, "name");
  
  /// Test uppdating with replenish
  option_t replenish_success4 = replenish(warehouse, strdup_name, ioopm_refmem_strdup("A32"), -99);
  CU_ASSERT(Successful(replenish_success4));
  //show_stock(warehouse, "name");

  /// Test replensish to mutch
  option_t replenish_success5 = replenish(warehouse, strdup_name, ioopm_refmem_strdup("A32"), -2);
  CU_ASSERT(Unsuccessful(replenish_success5));
  //show_stock(warehouse, "name");
  
  option_t replenish_success8 = replenish(warehouse, strdup_name, ioopm_refmem_strdup("A32"), 100);
  CU_ASSERT(Successful(replenish_success8));
  //show_stock(warehouse, "name");
  
  /// Test replenish non existing merche
  char *strdup_invalid_name = "invalid_name";
  option_t replenish_success6 = replenish(warehouse, strdup_invalid_name, ioopm_refmem_strdup("A32"), 90);
  CU_ASSERT(Unsuccessful(replenish_success6));
  //show_stock(warehouse, "name");  
  
  option_t remove_success7 = remove_merchandise(cart_db, warehouse, strdup_name); // Chould not be needed
  CU_ASSERT(Successful(remove_success7));
  release(strdup_name);
  
  destroy_warehouse(cart_db, warehouse);
  destroy_cart_db(cart_db);
}

void test_show()
{
  warehouse_t *warehouse = create_warehouse();
  shopping_cart_db_t *cart_db = non_empty_cart_db_no_items();
  option_t add_success = add_merchandise(warehouse, ioopm_refmem_strdup("name"), ioopm_refmem_strdup("desciption"), 9.9);
  CU_ASSERT(Successful(add_success));
  show_stock(warehouse, "name");
 
   destroy_warehouse(cart_db, warehouse);
   destroy_cart_db(cart_db);
}
  
void test_large_warehouse()
{
  warehouse_t *warehouse = non_empty_warehouse_with_items();
  shopping_cart_db_t *cart_db =non_empty_cart_db(warehouse);
  
  //list_merchandise(warehouse);

  destroy_warehouse(cart_db, warehouse);
  destroy_cart_db(cart_db);
}

void test_storage()
{
  warehouse_t *warehouse = non_empty_warehouse_with_items();
  shopping_cart_db_t *cart_db = non_empty_cart_db_no_items();
 
  char *merch_name = ioopm_refmem_strdup("sixCha");
  retain(merch_name);
  char *new_merch_name = ioopm_refmem_strdup("sevChar");
  retain(new_merch_name);
  char *shelf_name = ioopm_refmem_strdup("A25");
  retain(shelf_name);
  char *merch_name2 = ioopm_refmem_strdup("somRadnomNameThatIsValif");
  retain(merch_name2);
  char *new_merch_name2 = ioopm_refmem_strdup("SomNewRadnfomName");
  retain(new_merch_name2);
  char *shelf_name2 = ioopm_refmem_strdup("C30");
  retain(shelf_name2);
 
  option_t success_add = add_merchandise(warehouse, ioopm_refmem_strdup(merch_name), ioopm_refmem_strdup("desciption"), 2);
  CU_ASSERT(Successful(success_add));  
  option_t success_replenish = replenish(warehouse, merch_name, ioopm_refmem_strdup(shelf_name), 100);
  CU_ASSERT(Successful(success_replenish));

  /// Test update storage name when updating merch name
  option_t edit_success = edit_merchandise(warehouse, cart_db, merch_name, ioopm_refmem_strdup(new_merch_name), ioopm_refmem_strdup("new_desciption"), 10);
  CU_ASSERT(Successful(edit_success));
  CU_ASSERT(strcmp((char *)ioopm_refmem_hash_table_lookup(warehouse->storage, Epointer(shelf_name)).value.pointer
	   , new_merch_name) == 0);

  /// Test edit two items
  option_t success_add2 = add_merchandise(warehouse, ioopm_refmem_strdup(merch_name2), ioopm_refmem_strdup("desciption_other"), 2);
  CU_ASSERT(Successful(success_add2));  
  option_t success_replenish2 = replenish(warehouse, merch_name2, ioopm_refmem_strdup(shelf_name2), 100);
  CU_ASSERT(Successful(success_replenish2));
  option_t edit_success2 = edit_merchandise(warehouse, cart_db, merch_name2, ioopm_refmem_strdup(new_merch_name2), ioopm_refmem_strdup("new_desciption"), 10);
  CU_ASSERT(Successful(edit_success2));
  
  /// Test remove shelf when remove merch
  char *strdupname = ioopm_refmem_strdup(new_merch_name);
  char *strdupshelf = ioopm_refmem_strdup(shelf_name);
  option_t success_remove = remove_merchandise(cart_db, warehouse, strdupname);
  CU_ASSERT(Successful(success_remove));
  CU_ASSERT(!ioopm_refmem_hash_table_lookup(warehouse->storage, Epointer(strdupshelf)).success);
  
  release(strdupname);
  release(strdupshelf);
  release(merch_name);
  release(new_merch_name);
  release(shelf_name);
  release(merch_name2);
  release(new_merch_name2);
  release(shelf_name2);
  

  destroy_warehouse(cart_db, warehouse);
  destroy_cart_db(cart_db);
}

void test_list_storage()
{
  warehouse_t *warehouse = create_warehouse();
  shopping_cart_db_t *cart_db = non_empty_cart_db_no_items();
  
  char *first = ioopm_refmem_strdup("first");
  char *second = ioopm_refmem_strdup("secon");
  char *tird = ioopm_refmem_strdup("tird");
  char *fourth = ioopm_refmem_strdup("fourth");
  
  retain(first);
  retain(second);
  retain(tird);
  retain(fourth);
       
  int str_size = 26;
  char *strings[26] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r",
    "s", "t", "u", "v", "w", "x", "y", "z"};

  option_t successa = add_merchandise(warehouse, ioopm_refmem_strdup(first), ioopm_refmem_strdup("desciption"), 9.9);
  CU_ASSERT(Successful(successa));
  option_t successb = add_merchandise(warehouse, ioopm_refmem_strdup(second), ioopm_refmem_strdup("desciption"), 9.9);
  CU_ASSERT(Successful(successb));
  option_t successc = add_merchandise(warehouse, ioopm_refmem_strdup(tird), ioopm_refmem_strdup("desciption"), 100);
  CU_ASSERT(Successful(successc));
  option_t successd = add_merchandise(warehouse, ioopm_refmem_strdup(fourth), ioopm_refmem_strdup("desciption"), 23.9);
  CU_ASSERT(Successful(successd));
  
  //list_merchandise(warehouse);
  
  for(int i = 0; i<str_size/4; ++i)  
    {
      option_t success1 = replenish(warehouse, first, ioopm_refmem_strdup(strings[i*4]), i+1);
      CU_ASSERT(Successful(success1));
      option_t success2 = replenish(warehouse, second, ioopm_refmem_strdup(strings[i*4+1]), i+1);
      CU_ASSERT(Successful(success2));
      option_t success3 = replenish(warehouse, tird, ioopm_refmem_strdup(strings[i*4+2]), i+1);
      CU_ASSERT(Successful(success3));
      option_t success4 = replenish(warehouse, fourth, ioopm_refmem_strdup(strings[i*4+3]), i+1);
      CU_ASSERT(Successful(success4));
    }
  
  //list_storage(warehouse); 

  release(first);
  release(second);
  release(tird);
  release(fourth);
  
  destroy_warehouse(cart_db, warehouse);
  destroy_cart_db(cart_db);
  
}

void test_create_destroy_cart() 
{
  //warehouse_t *warehouse = non_empty_warehouse();
  shopping_cart_db_t *cart_db = create_cart_db();
  CU_ASSERT_PTR_NOT_NULL(cart_db);

  /// Test add cart to system
  option_t add_success = add_cart(cart_db, ioopm_refmem_strdup("username"));
  CU_ASSERT_TRUE(Successful(add_success));
  //show_cart(cart_db, "username");
  
  char *strdupUser = ioopm_refmem_strdup("username");
  retain(strdupUser);
  option_t remove_success = remove_cart(cart_db, strdupUser);
  CU_ASSERT_TRUE(Successful(remove_success));
  //show_cart(cart_db, "username");
  
  // clean up
  release(strdupUser);
  destroy_cart_db(cart_db);
  //destroy_warehouse(warehouse);
}


void test_add_and_remove_items_from_cart()
{
  
  warehouse_t *warehouse = non_empty_warehouse_with_items();
  shopping_cart_db_t *cart_db = create_cart_db();
  
  merch_t *item1 = ioopm_refmem_hash_table_lookup(warehouse->merchendise, Epointer("a")).value.pointer;

  // Test add remove
  option_t add_success = add_cart(cart_db, ioopm_refmem_strdup("username"));
  CU_ASSERT_TRUE(Successful(add_success));
  shopping_cart_t *cart = add_success.value.pointer;
  option_t add_to_success = add_to_cart(cart, item1, 1);
  CU_ASSERT_TRUE(Successful(add_to_success));
  CU_ASSERT_TRUE(add_to_success.value.integer == 1); //option_t returns .success=true and .value=1 if we manage to add a new item

  char *cart_item_name = ioopm_refmem_strdup("a");
  retain(cart_item_name);
  option_t remove_success = remove_from_cart(cart, cart_item_name, 1);
  CU_ASSERT_TRUE(Successful(remove_success));

  // Test remove that dosent exist
  option_t remove_success_again = remove_from_cart(cart, cart_item_name, 1);  
  CU_ASSERT_FALSE(Successful(remove_success_again));

  // Test new item
  merch_t *item2 = ioopm_refmem_hash_table_lookup(warehouse->merchendise, Epointer("b")).value.pointer;
  option_t add_success2 = add_to_cart(cart, item2, 1);
  CU_ASSERT_TRUE(Successful(add_success2));

  // Test adding 2 items
  add_to_cart(cart, item1, 1);
  option_t add_success3 = add_to_cart(cart, item1, 1);
  CU_ASSERT_TRUE(add_success3.value.integer == 2);

  // Test remove cart
  char *strdupUser = ioopm_refmem_strdup("username");
  retain(strdupUser);
  remove_cart(cart_db, strdupUser);

  // Final cleanup
  release(cart_item_name);
  release(strdupUser);
  destroy_warehouse(cart_db, warehouse);
  destroy_cart_db(cart_db);
}

void add_multiple_to_cart(){
  
  //Create warehouse, cart_db, and cart. 
  warehouse_t *warehouse = non_empty_warehouse();
  shopping_cart_db_t *cart_db = create_cart_db();
  option_t add_success = add_cart(cart_db, ioopm_refmem_strdup("username"));
  shopping_cart_t *cart = add_success.value.pointer;
  
  //Fetch and add 3 of 1 item
  merch_t *item1 = ioopm_refmem_hash_table_lookup(warehouse->merchendise, Epointer("a")).value.pointer;
  option_t add_3_success = add_to_cart(cart, item1, 3);
  CU_ASSERT_TRUE(Successful(add_3_success));
  
  //Remove those 3 items
  option_t remove_3_success = (remove_from_cart(cart, item1->name, 3));
  CU_ASSERT_TRUE(Successful(remove_3_success));
  option_t remove_3_again = (remove_from_cart(cart, item1->name, 3));
  CU_ASSERT_FALSE(Successful(remove_3_again));
  
  // Test remove cart
  char *strdupUser = ioopm_refmem_strdup("username");
  retain(strdupUser);
  remove_cart(cart_db, strdupUser);

  // Final cleanup
  destroy_warehouse(cart_db, warehouse);
  destroy_cart_db(cart_db);
  release(strdupUser);
}

void test_many_items_in_cart(){
  
  warehouse_t *warehouse = non_empty_warehouse_with_items();  
  shopping_cart_db_t *cart_db = non_empty_cart_db(warehouse);

  destroy_warehouse(cart_db, warehouse);
  destroy_cart_db(cart_db);
}

void test_checkout_cart(){
  warehouse_t *warehouse = non_empty_warehouse_with_items();  
  shopping_cart_db_t *cart_db = non_empty_cart_db(warehouse);

  // Test checkout cart with no items
  char *username2 = ioopm_refmem_strdup("username2");
  retain(username2);
  option_t checkout_success1 = checkout(warehouse, cart_db, username2);
  CU_ASSERT_TRUE(Successful(checkout_success1));
  release(username2);

  // Test checkout cart with many items
  char *username1 = ioopm_refmem_strdup("username1");
  retain(username1);
  option_t checkout_success2 = checkout(warehouse, cart_db, username1);
  CU_ASSERT_TRUE(Successful(checkout_success2));
  release(username1);

  // Test checkout non existing cart
  char *invalid_username = ioopm_refmem_strdup("invalid username");
  retain(invalid_username);
  option_t checkout_success3 = checkout(warehouse, cart_db, invalid_username);
  CU_ASSERT_FALSE(Successful(checkout_success3));
  release(invalid_username);

  // Test if warehouse is updated when cart is cheackut
  option_t success = add_merchandise(warehouse, ioopm_refmem_strdup("cat"), ioopm_refmem_strdup("desciption"), 9.9);
  merch_t *item1 =  success.value.pointer;
  replenish(warehouse, "cat", ioopm_refmem_strdup("shelfA"), 1);

  option_t add_success1 = add_cart(cart_db, ioopm_refmem_strdup("us"));
  CU_ASSERT_TRUE(Successful(add_success1));
  option_t add_to_success = add_to_cart(add_success1.value.pointer, item1, 1);
  CU_ASSERT_TRUE(Successful(add_to_success));

  option_t add_success2 = add_cart(cart_db, ioopm_refmem_strdup("usA"));
  CU_ASSERT_TRUE(Successful(add_success2));
  option_t add_to_success2 = add_to_cart(add_success2.value.pointer, item1, 1);
  CU_ASSERT_TRUE(Successful(add_to_success2));

  CU_ASSERT_TRUE(item1->stock==1);
  char *us = ioopm_refmem_strdup("us");
  retain(us);
  option_t checkout_success4 = checkout(warehouse, cart_db, us);
  CU_ASSERT_TRUE(Successful(checkout_success4));
  release(us);
  
  CU_ASSERT_TRUE(item1->stock==0);
  char *usA = ioopm_refmem_strdup("usA");
  retain(usA);
  option_t checkout_success5 = checkout(warehouse, cart_db, usA);
  printf(" ");
  CU_ASSERT_FALSE(Successful(checkout_success5));
  release(usA);
  
  // Cleanup
  destroy_warehouse(cart_db, warehouse);
  destroy_cart_db(cart_db); //invalid read of size 8 från föregående rads free
}

void test_checkout_multiple_carts(){
  
  warehouse_t *warehouse = non_empty_warehouse_with_items();
  shopping_cart_db_t *cart_db = non_empty_cart_db_no_items();
  
  char *username1 = ioopm_refmem_strdup("username1");
  retain(username1);
  option_t checkout_success1 = checkout(warehouse, cart_db, username1);
  CU_ASSERT_TRUE(Successful(checkout_success1));
  release(username1);

  char *username2 = ioopm_refmem_strdup("username2");
  retain(username2);
  option_t checkout_success2 = checkout(warehouse, cart_db, username2);
  CU_ASSERT_TRUE(Successful(checkout_success2));
  release(username2);
  
  char *username3 = ioopm_refmem_strdup("username3");
  retain(username3);
  option_t checkout_success3 = checkout(warehouse, cart_db, username3);
  CU_ASSERT_TRUE(Successful(checkout_success3));
  release(username3);
  
  destroy_warehouse(cart_db, warehouse);
  destroy_cart_db(cart_db);
}


int main()
{
  CU_pSuite test_suite1 = NULL;

  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  test_suite1 = CU_add_suite("Business Logic Tests", init_suite, clean_suite);
  if (NULL == test_suite1)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  if (
      (NULL == CU_add_test(test_suite1, "Create and destroy          ", test_create_destroy)) ||
      (NULL == CU_add_test(test_suite1, "Add and remove merch        ", test_add_remove_merchandise)) ||
      (NULL == CU_add_test(test_suite1, "Edit merch                  ", test_edit_merchandise)) ||
      (NULL == CU_add_test(test_suite1, "Replenish merch             ", test_replenish)) ||
      (NULL == CU_add_test(test_suite1, "Large warehouse             ", test_large_warehouse)) ||
      (NULL == CU_add_test(test_suite1, "Show warehouse locs         ", test_show)) ||
      (NULL == CU_add_test(test_suite1, "Storage tests               ", test_storage)) || 
      (NULL == CU_add_test(test_suite1, "Show storage                ", test_list_storage)) ||
      (NULL == CU_add_test(test_suite1, "Creat and destory cart db   ", test_create_destroy_cart)) ||
      (NULL == CU_add_test(test_suite1, "Add and remove items to cart", test_add_and_remove_items_from_cart)) ||
      (NULL == CU_add_test(test_suite1, "Many items in cart          ", test_many_items_in_cart)) ||
      (NULL == CU_add_test(test_suite1, "Checkout cart               ", test_checkout_cart))|| 
      (NULL == CU_add_test(test_suite1, "Add multiple to cart        ", add_multiple_to_cart)) ||
      (NULL == CU_add_test(test_suite1, "Checkout multiple carts     ", test_checkout_multiple_carts))
      
     )
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}
