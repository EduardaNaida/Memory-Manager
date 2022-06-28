#include <stdio.h>
#include <stdlib.h>

/// inlupp1

/// inlupp2
#include "user_interface.h"

//project
#include "../src/refmem.h"

// Admin warehouse functions
static void print_admin_menu()
{
  printf("\n\n"
	 "[-------------- Main --------------]"
	 "\n\n"
	 "  [A]dd merch\n"
	 "  [R]emove merch\n"
	 "  Show [W]arehouse\n"
	 "  Show [L]ocations\n"
	 "  [E]dit merch\n"
	 "  Replenish [M]erch\n"
	 "  [Q]uit\n\n");
}

static void print_function_name(char *string)
{
   printf( "\n"
	   "[------- %s -------]\n", string);
}
  
void quit_admin(warehouse_t *warehouse)
{
    printf("\n\n Exiting the program....\n");
}


void admin_add_merch_to_warehouse(warehouse_t *warehouse)
{
  print_function_name("Adding merch");
  
  char *merch_name  = ask_question_string("Name of merchendise:        ");
  char *description = ask_question_string("Description of merchendise: ");
  float price       =  ask_question_float("The price of merchendise:   "); 

  option_t success = add_merchandise(warehouse, merch_name, description, price);
  
  if(Successful(success))
    puts("Merchandise was added successfully");
  else
    puts("Merchandise was added unsuccessfully ");
  
}


void admin_remove_merch_from_warehouse(warehouse_t *warehouse, shopping_cart_db_t *cart_db)
{
  print_function_name("Removing merch");
  
  char *merch_name  = ask_question_string("Name of merchendise: ");  //check if dosent exist
  option_t success = remove_merchandise(cart_db, warehouse, merch_name);
    
  if(Successful(success))
    puts("Merchandise was removed successfully");
  else
    puts("Merchandise was not removed.");

  release(merch_name);
}


void admin_show_warehouse(warehouse_t *warehouse)
{
  print_function_name("Show warehouse");
  list_merchandise(warehouse);
}

//PRINTING NUMBERS ETC LAND
/*
char **extract_to_array(elem_t key, elem_t *value, void *extra){
  static int index = 0;
  elem_t *array = extra;
  array[index] = *value;
  index++;
}
*/
/*void get_array_from_warehouse(warehouse_t *warehouse){
  
  ioopm_hash_table_ht *ht = warehouse -> merchendise; //might not work, might have to have this in other file? 
  ioopm_linked_list_t *list_of_merch = ioopm_hash_table_keys(ht);
  int size = ioopm_linked_list_size(list);
  
  char *array[size];
  ioopm_linked_apply_to_all(list, extract_to_array, array);

  ioopm_linked_list_destroy(list_of_merch);
  return array;
}*/

//END OF PRINTING NUMBER ETC LAND

void admin_show_location(warehouse_t *warehouse)
{
  print_function_name("Show location");
  
  char *merch_name  = ask_question_string("Name of merchendise: ");
  show_stock(warehouse, merch_name);

  // clean up
  release(merch_name);
}


void admin_edit_merch(warehouse_t *warehouse, shopping_cart_db_t *cart_db)
{
  print_function_name("Edit merch");
  
  char *merch_name  = ask_question_string("Name of merchendise:      ");
  char *new_name    = ask_question_string("New name of merchendise:  ");
  char *new_desc    = ask_question_string("New desciption:           ");
  float new_price   =  ask_question_float("The price of merchendise: ");
  
  option_t success = edit_merchandise(warehouse, cart_db, merch_name, new_name, new_desc, new_price);;

  if(Successful(success))
    puts("Merchandise was edited successfully");
  else
    puts("Merchandise was edited unsuccessfully ");

  // clean up
  release(merch_name);
}

void admin_replenish(warehouse_t *warehouse)
{
  print_function_name("Replenish");
  
  char *merch_name    = ask_question_string("Name of merchendise:    ");
  char *shelf_name    = ask_question_string("The shelf to store in:  ");
  int change_quantity =    ask_question_int("The delta quantity:     ");
  
  option_t success = replenish(warehouse, merch_name, shelf_name, change_quantity);

  if(Successful(success))
    puts("Merchandise was Replenish successfully");
  else
    puts("Merchandise was Replenish unsuccessfully ");

  // clean up
  release(merch_name);
}



void admin_menu(warehouse_t *warehouse, shopping_cart_db_t *cart_db)
{
  while (true)
    {
      print_admin_menu();
      char answer = ask_question_menu("Enter option: ", "AaRrWwLlEeMmQq");
      
      if (answer=='A')
	admin_add_merch_to_warehouse(warehouse);
      else if (answer=='R')
	admin_remove_merch_from_warehouse(warehouse, cart_db);
      else if (answer=='W')
	admin_show_warehouse(warehouse);
      else if (answer=='L')
	admin_show_location(warehouse);
      else if (answer=='E')
	admin_edit_merch(warehouse, cart_db);
      else if (answer=='M')
	admin_replenish(warehouse);
      else{
	quit_admin(warehouse);
	return;
      }
    } 
}

// Cart functions

static void print_user_menu()
{
  printf("\n\n"
	 "[-------------- Main --------------]"
	 "\n\n"
	 "[A]dd cart item\n"
	 "[R]emove cart item \n"
	 "[D]isplay cart\n"
	 "[Q]uit\n");
}


void quit_user(warehouse_t *warehouse, shopping_cart_db_t *cart_db, char *username)
{
    printf("Exiting the program....\n");
    user_checkout(warehouse, cart_db, username);
}

void user_add_to_cart(warehouse_t *warehouse, shopping_cart_t *user_cart)
{
  print_function_name("Add to cart");
  char **array = list_merchandise_with_array(warehouse);
  
  int merch_number =    ask_question_int("What item do you want to add? (by number):       ");
  
  if(0 < merch_number && merch_number <= (int)sizeof(array)){
  int quantity  =    ask_question_int("The delta quantity:       ");
  char *merch_name = array[merch_number-1];
  option_t success  = get_merch(warehouse, merch_name);

  if(Successful(success))
  {
    merch_t *item = success.value.pointer;
    option_t add_success = add_to_cart(user_cart, item, quantity);
    if(Successful(add_success)){
      puts("Merchandise was added successfully");
    }
    else{
      puts("Invalid quantity, try again");
    }
  }
  else
    printf("There is no item named %s.\n", merch_name);
  }
  
  // clean up
  release(array);
}

void user_remove_from_cart(warehouse_t *warehouse, shopping_cart_t *user_cart)
{
  print_function_name("Add to cart");
  show_cart(user_cart);
  
  char *merch_name    = ask_question_string("Name of merchendise:    ");
  int remove_quantity =    ask_question_int("The delta quantity:     ");
  option_t success    = cart_lookup(user_cart, merch_name);
  
  if(Successful(success))
  {
    remove_from_cart(user_cart, merch_name, (unsigned int)remove_quantity);
    printf("You removed %d of item %s.\n",remove_quantity, merch_name);
  }
  else
    printf("There is no item named %s. \n", merch_name);
    
  // clean up
  release(merch_name);
}

void user_checkout(warehouse_t *warehouse, shopping_cart_db_t *cart_db, char *username)
{
  print_function_name("Checkout");
  option_t success = checkout(warehouse, cart_db, username);
  
  if(Successful(success))
    puts("You have checkout yout cart");
  else
    puts("You checkout unsuccessfully");
}


void user_show_cart(shopping_cart_t *user_cart)
{
  print_function_name("Cart");
  show_cart(user_cart);
}


void user_menu(warehouse_t *warehouse, shopping_cart_db_t *cart_db, shopping_cart_t *user_cart, char *username)
{
    while (true)
    {
      print_user_menu();
      char answer = ask_question_menu("Enter option: ", "AaRrCcDdQq");
      
      if (answer=='A')
	user_add_to_cart(warehouse, user_cart);	      
      else if (answer=='R')
        user_remove_from_cart(warehouse, user_cart);
      else if (answer=='C')
        user_checkout(warehouse, cart_db, username);
      else if (answer=='D')
	user_show_cart(user_cart);
      else if (answer=='Q')
	return;
    } 
}

void quit_program(warehouse_t *warehouse, shopping_cart_db_t *cart_db){
  destroy_warehouse(cart_db, warehouse);
  destroy_cart_db(cart_db);
}

void print_menu(){
  printf("\n\n"
	 "[-------------- Main --------------]"
	 "\n\n"
	 "[A]dmin\n"
	 "[U]ser \n"
	 "[C]heck \n"
	 "[Q]uit\n");
  
}
void menu(warehouse_t *warehouse, shopping_cart_db_t *cart_db)
{
    char *username = ask_question_string("Enter username:    ");
    
    shopping_cart_t *user_cart = add_cart(cart_db, username).value.pointer;

    while (true)
    {
      print_menu();
      char answer = ask_question_menu("Enter option: ", "AaUuCcQq");
      
      if (answer=='A')
	admin_menu(warehouse, cart_db);
      else if (answer=='U')
        user_menu(warehouse, cart_db, user_cart, username);
      else if (answer=='C')
        quit_user(warehouse, cart_db, username); //chekout          
      else if (answer=='Q')
      {
	quit_program(warehouse, cart_db);
	return;
      }
    } 
}
