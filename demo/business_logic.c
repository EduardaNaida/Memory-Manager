#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

/// inlupp1
#include "ht_ll_refmem/iterator_refmem.h"

/// inlupp2 
#include "generic_utils.h"
//#include "generic_data_structures.h"
#include "business_logic.h"

//project
#include "../src/refmem.h"

struct merch
{
    char *name;
    char *desc;
    float price;
    size_t stock;  // The summ of all quantitys in locs
    ioopm_refmem_list_t *locs;
};

struct shelf
{
    char *shelf;
    size_t quantity;
};

struct shopping_cart 
{
  ioopm_refmem_hash_table_t *cart;  // .key=merch_name  .value=cart_item
  char *username_key; 
};

struct cart_item 
{
    char *name;
    float price;
    size_t quantity;
    merch_t *item;
};

struct warehouse
{  
  ioopm_refmem_hash_table_t *merchendise;  // .key=name  .value=point_merch
  ioopm_refmem_hash_table_t *storage;      // .key=shelf .value=merch_name
};


// HELPER FUNCTIONS:

static int eq_func_merch(elem_t a, elem_t b) // kompare key 
{
    return strcmp(a.pointer, b.pointer);
}

static int eq_func_storage(elem_t a, elem_t b) // kompare key 
{
    return strcmp(a.pointer, b.pointer);
}

static unsigned long string_knr_hash(const char *str)
{
  unsigned long result = 0;
  do
    {
      result = result * 31 + *str;
    }
  while (*++str != '\0');
  return result;
}

static unsigned long hash_function(elem_t word){
  return string_knr_hash(word.pointer);
}


static void remove_shelf(shelf_t *shelf_to_remove)
{
  if(shelf_to_remove && shelf_to_remove->shelf)
    //release(shelf_to_remove->shelf); // free strdup string
  
  release(shelf_to_remove);
}

static void destroy_location(ioopm_refmem_list_t *locs)
{
  if(locs)
  {
    ioopm_refmem_list_iterator_t *iter = ioopm_refmem_list_iterator(locs);
    
    do
    {
      shelf_t *shelf = ioopm_refmem_iterator_current(iter).value.pointer;
      remove_shelf(shelf);
    } while(Successful(ioopm_refmem_iterator_next(iter)));
    
    release(iter);
    release(locs);
  }
}

static option_t get_shelf(ioopm_refmem_list_t *locs, char *name_shelf)
{
  if(locs)
    {
      ioopm_refmem_list_iterator_t *iter = ioopm_refmem_list_iterator(locs);

      do{
	shelf_t *shelf = ioopm_refmem_iterator_current(iter).value.pointer;
	if(shelf && !strcmp(shelf->shelf, name_shelf))
    	{
    	  release(iter);
    	  return Success(Epointer(shelf));
    	}
      } while(Successful(ioopm_refmem_iterator_next(iter)));
      
      release(iter);
    }

  return Failure();
}

/*=================================================================
 *  Här har vi gjort ändringar  
 *=================================================================*/
 

  
void destructor_merch(obj *m){
  release(((merch_t*) m)->name);
  release(((merch_t*) m)->desc);
}

void destructor_cart(obj *c){
 release(((shopping_cart_t*) c)->cart);
 release(((shopping_cart_t*) c)->username_key);
}

void warehouse_destructor(obj *w)
{//destroyfunktionerna här
  release(((warehouse_t*) w)->merchendise); //TODO: crashes here
  release(((warehouse_t*) w)->storage);
}

void destructor_shelf(obj *s){
   release(((shelf_t*) s)->shelf);
}

void destructor_array(obj *a){
  return; //TODO
}

void cart_item_destructor(obj *c)
{
  release(((cart_item_t*) c)->name);
  release(((cart_item_t*) c)->item);
}

//Ändrad
static merch_t *create_merch(char *name, char *desc, float price, ioopm_refmem_list_t *locs)
{
    merch_t *new_merch = allocate(sizeof(merch_t), destructor_merch);
    
    *new_merch = (merch_t){
        .name=name,
        .desc=desc,
        .price=price,
	      .stock=0,
        .locs=locs
    };
    retain(name);
    retain(desc);
    retain(new_merch);
    retain(locs);
    return new_merch;
}

//icke ändrad

/*
static merch_t *create_merch(char *name, char *desc, float price, ioopm_refmem_list_t *locs)
{
    merch_t *new_merch = calloc(1, sizeof(merch_t));
    
    *new_merch = (merch_t){
        .name=name,
        .desc=desc,
        .price=price,
	.stock=0,
        .locs=locs
    };
    
    return new_merch;
}
*/

static void print_shelf(shelf_t *shelf)
{
  printf("%s\n %zu\n", shelf->shelf, shelf->quantity);
}

option_t cart_lookup(shopping_cart_t *user_cart, char *item){
  return ioopm_refmem_hash_table_lookup(user_cart->cart, Epointer(item));
}

static option_t update_merch_name_in_storage(ioopm_refmem_hash_table_t *storage, char *old_name, char *new_name)
{
  ioopm_refmem_list_t *all_storage = ioopm_refmem_hash_table_keys(storage);
  ioopm_refmem_list_t *all_merchendise = ioopm_refmem_hash_table_values(storage);
  ioopm_refmem_list_iterator_t *iter1 = ioopm_refmem_list_iterator(all_storage);
  ioopm_refmem_list_iterator_t *iter2 = ioopm_refmem_list_iterator(all_merchendise);
  bool isEmpty = ioopm_refmem_linked_list_is_empty(all_merchendise);
  bool didChange = false;

  char *merch_namn;
  char *shelf_name;
  
  if(!isEmpty){
    do{
      merch_namn = ioopm_refmem_iterator_current(iter2).value.pointer;
      //retain(merch_name);
      shelf_name = ioopm_refmem_iterator_current(iter1).value.pointer;
      if(strcmp(merch_namn, old_name) == 0) {
        ioopm_refmem_hash_table_insert(storage,
  			      Epointer(shelf_name),
  			      Epointer(ioopm_refmem_strdup(new_name)));
  			
        //free(merch_namn);
       // release(merch_name);   //pga rad 2007
        release(merch_namn);    //pga namnbyte
        didChange = true;
        break;
      }
    } while(Successful(ioopm_refmem_iterator_next(iter1)) && Successful(ioopm_refmem_iterator_next(iter2)));
  }    

  release(all_storage);
  release(all_merchendise);
  release(iter1);
  release(iter2);
  
  if(didChange){
    return Success(Epointer(new_name));
  }
  else{
    return Failure();
  }
}

static bool shelf_exists(ioopm_refmem_hash_table_t *storage, char *shelf)
{
  return ioopm_refmem_hash_table_has_key(storage, Epointer(shelf));
}

static option_t remove_shelf_from_storage(ioopm_refmem_hash_table_t *storage, char *merch)
{
  ioopm_refmem_list_t *all_storage = ioopm_refmem_hash_table_keys(storage);
  ioopm_refmem_list_t *all_merchendise = ioopm_refmem_hash_table_values(storage);
  ioopm_refmem_list_iterator_t *iter1 = ioopm_refmem_list_iterator(all_storage);
  ioopm_refmem_list_iterator_t *iter2 = ioopm_refmem_list_iterator(all_merchendise);
  bool isEmpty = ioopm_refmem_linked_list_is_empty(all_merchendise);
  bool didRemove = false;
    
  char *shelf_namn;
  char *merch_namn;

  if(!isEmpty){
  do{
    shelf_namn = ioopm_refmem_iterator_current(iter1).value.pointer;   //ska vi retaina detta?
    merch_namn = ioopm_refmem_iterator_current(iter2).value.pointer;
    if(strcmp(merch_namn, merch) == 0){
      ioopm_refmem_hash_table_remove(storage, Epointer(shelf_namn));
      //free(shelf_namn);
      //free(merch_namn);
      release(shelf_namn);
      release(merch_namn);
      didRemove = true;
    }
  } while(Successful(ioopm_refmem_iterator_next(iter1)) && Successful(ioopm_refmem_iterator_next(iter2)));
  }
  
  release(all_storage);
  release(all_merchendise);
  release(iter1);
  release(iter2);

  if(didRemove)
    return Success(Epointer(merch));
  else
    return Failure();
}

static bool shelf_exists_for_other_merch(warehouse_t *warehouse, char *name, char *name_shelf)
{
  option_t shelf_exists_other = ioopm_refmem_hash_table_lookup(warehouse->storage, Epointer(name_shelf));

  if(Successful(shelf_exists_other))
    {
      char *existing_merch_name = shelf_exists_other.value.pointer;
      if(strcmp(existing_merch_name, name) != 0)
    	  return true;
    }

  return false;
}

static option_t uppdate_quantity(shelf_t *shelf, merch_t *merch, char *name_shelf, int change_quantity)
{
  if(change_quantity <-(int)shelf->quantity) // Dont allow negativ quantity
    return Failure();
  
  shelf->quantity += change_quantity;
  merch->stock    += change_quantity;
      
  if(shelf->quantity == 0){ //if we remove all items from a shelf
    int index = 0;
    ioopm_refmem_list_iterator_t *locs_iter = ioopm_refmem_list_iterator(merch->locs);
    
    do{
      shelf_t *shelf = ioopm_refmem_iterator_current(locs_iter).value.pointer;
      if(shelf->shelf == name_shelf)
	    ioopm_refmem_linked_list_remove(merch->locs, index);
      index++;
    }while(Successful(ioopm_refmem_iterator_next(locs_iter)));
    
    release(locs_iter);
  }

  return Success(Epointer(shelf));
}

static option_t new_shelf_in_warehouse(warehouse_t *warehouse, merch_t *merch, char *name, char *name_shelf, int change_quantity)
{
  if(change_quantity < 0){  // Dont allow new shelf with negativ quantity
    release(name_shelf);
    return Failure();
  }
  
  // storage update
  ioopm_refmem_hash_table_insert(warehouse->storage, Epointer(ioopm_refmem_strdup(name_shelf)), Epointer(ioopm_refmem_strdup(name)));

  // Insert new shelf
  shelf_t *new_shelf = create_shelf(name_shelf, change_quantity);
  ioopm_refmem_linked_list_prepend(merch->locs, Epointer(new_shelf));
  merch->stock += change_quantity;
  
  return Success(Epointer(new_shelf));

}

/*
ioopm_refmem_hash_table *get_cart(shopping_cart_t *shopping_cart){
  return shopping_cart->cart;
}*/

// Checkout

static size_t replenish_for_checkout(warehouse_t *warehouse, size_t quantity_left, shelf_t *shelf, char *merch_name)
{
  if(quantity_left < shelf->quantity){
      replenish(warehouse, merch_name, ioopm_refmem_strdup(shelf->shelf), -quantity_left);
      quantity_left = 0;
  }
  else{
      size_t shelf_quantity = shelf->quantity;
      replenish(warehouse, merch_name, ioopm_refmem_strdup(shelf->shelf), -shelf->quantity);
      quantity_left -= shelf_quantity;
  }
  
  return quantity_left;
}

static void uppdate_merch_in_warehouse_for_checkout(warehouse_t *warehouse, cart_item_t *cart_item)
{
  // Stop ff there dosent exist a cart item
  if(cart_item == NULL)
    return;
  
  // Find merch
  merch_t *merch = ioopm_refmem_hash_table_lookup(warehouse->merchendise, Epointer(cart_item->name)).value.pointer;

  // create iter
  ioopm_refmem_list_iterator_t *iter_shelf = ioopm_refmem_list_iterator(merch->locs);
  shelf_t *shelf;
  size_t quantity_left = cart_item->quantity;
  
  // iterate over all shelfs in locs
  do{
    shelf = ioopm_refmem_iterator_current(iter_shelf).value.pointer;
    quantity_left = replenish_for_checkout(warehouse, quantity_left, shelf, merch->name);
  }while(Successful(ioopm_refmem_iterator_next(iter_shelf)) && quantity_left > 0);

  // Clean up
  release(iter_shelf);
}

// O(1) check if there is enough in stock for cheakout
static bool enough_quantity(warehouse_t *warehouse, cart_item_t *cart_item)
{
  if(cart_item == NULL)
    return true;
    
  // Find merch
  option_t find_merch_success = ioopm_refmem_hash_table_lookup(warehouse->merchendise, Epointer(cart_item->name));
  if(Unsuccessful(find_merch_success))
    return false;
  
  merch_t *merch = find_merch_success.value.pointer;
  
  if(cart_item->quantity <= merch->stock)
    return true;
  else
    {
      printf("Low in stock for %s\n", cart_item->name);
      return false;
    }
}

static bool cart_can_be_checkout(warehouse_t *warehouse, shopping_cart_t *shopping_cart)
{
  ioopm_refmem_list_t *all_cart_items = ioopm_refmem_hash_table_values(shopping_cart->cart);
  ioopm_refmem_list_iterator_t *iter_cart_items = ioopm_refmem_list_iterator(all_cart_items);
  cart_item_t *cart_items;
  bool success = true;
  
  do{
    cart_items = ioopm_refmem_iterator_current(iter_cart_items).value.pointer;
    success = success && enough_quantity(warehouse, cart_items);
  }while(Successful(ioopm_refmem_iterator_next(iter_cart_items)) && success);

  release(all_cart_items);
  release(iter_cart_items);
  return success;
}



static shopping_cart_t *create_cart(char *username)
{
    ioopm_refmem_hash_table_t *cart = ioopm_refmem_hash_table_create(hash_function, eq_func_merch);     
    shopping_cart_t *new_cart = allocate(sizeof(shopping_cart_t), destructor_cart);
    
    *new_cart = (shopping_cart_t){
        .username_key = username, 
        .cart = cart,
    };
    retain(new_cart);
    retain(username);
    retain(cart);
    return new_cart; 
}



// PUBLIC API FUNCTIONS:

warehouse_t *create_warehouse()
{
  warehouse_t *warehouse = allocate(sizeof(warehouse_t), warehouse_destructor);
   
  ioopm_refmem_hash_table_t *merchendise = ioopm_refmem_hash_table_create(hash_function, eq_func_merch);
  ioopm_refmem_hash_table_t *storage = ioopm_refmem_hash_table_create(hash_function, eq_func_storage);
 
  warehouse->merchendise = merchendise;
  warehouse->storage = storage;
  retain(warehouse);
  retain(merchendise);
  retain(storage);
  return warehouse;
}


void destroy_warehouse(shopping_cart_db_t *cart_db, warehouse_t *warehouse) 
{
  ioopm_refmem_list_t *all_merchendise = ioopm_refmem_hash_table_values(warehouse->merchendise);
  ioopm_refmem_list_iterator_t *iter = ioopm_refmem_list_iterator(all_merchendise);
  merch_t *merch_to_remove;
  do{
    merch_to_remove = ioopm_refmem_iterator_current(iter).value.pointer;
    if(merch_to_remove){
      remove_merchandise(cart_db, warehouse, merch_to_remove->name);
      }; 
  } while(Successful(ioopm_refmem_iterator_next(iter)));

  // remove both ht
  //release(warehouse->storage);
  //release(warehouse->merchendise);
  release(warehouse);
  // remove temperary variables
  release(all_merchendise);
  release(iter);
  // remove warehouse
  //release(warehouse);
}



shelf_t *create_shelf(char *shelf, size_t quantity)
{
  shelf_t *new_shelf = allocate(sizeof(shelf_t), destructor_shelf);

  *new_shelf = (shelf_t){
    .shelf=shelf,
    .quantity=quantity
  };
  
  retain(new_shelf);
  retain(shelf);
  return new_shelf;
}


/// Public functions

option_t add_merchandise(warehouse_t *warehouse, char *name, char *desc, float price)
{
  if(warehouse->merchendise && !ioopm_refmem_hash_table_has_key(warehouse->merchendise, Epointer(name)))
    {
      // create merchendise
      ioopm_refmem_list_t *locs = ioopm_refmem_linked_list_create(eq_func_merch);
      merch_t *new_merch = create_merch(name, desc, price, locs);
    
      // insert it in warehouse    //.key=name .value=new_merch
      ioopm_refmem_hash_table_insert(warehouse->merchendise, Epointer(name), Epointer(new_merch));

      return Success(Epointer(new_merch));
    }

  //free(name);
  //free(desc);
  release(name);
  release(desc);
  
  
  return Failure();
}


void list_merchandise(warehouse_t *warehouse)
{
  ioopm_refmem_list_t *all_merchendise = ioopm_refmem_hash_table_values(warehouse->merchendise);
  ioopm_refmem_list_iterator_t *iter = ioopm_refmem_list_iterator(all_merchendise);
  int row = 1; 
  
  merch_t *merch = ioopm_refmem_iterator_current(iter).value.pointer;
  if(merch)  //no dummy entry
    {
      printf("%d. %s, \n", row, merch->name);
      ++row;
    }
  
  while(ioopm_refmem_iterator_has_next(iter))
    {
      printf("%d. %s\n", row, ((merch_t *)ioopm_refmem_iterator_next(iter).value.pointer)->name);
      ++row;
    }
  
  release(all_merchendise);
  release(iter);
}


char **list_merchandise_with_array(warehouse_t *warehouse)
{
  ioopm_refmem_list_t *all_merchendise = ioopm_refmem_hash_table_values(warehouse->merchendise);
  ioopm_refmem_list_iterator_t *iter = ioopm_refmem_list_iterator(all_merchendise);
  int no_strings = ioopm_refmem_linked_list_size(all_merchendise);
  //char **array = calloc(no_strings, sizeof(char *));
  char **array = allocate_array(no_strings, sizeof(char *), destructor_array);

  int row = 1; 
  merch_t *merch;
  
  do{
    merch = ioopm_refmem_iterator_current(iter).value.pointer;
    printf("%d. %s, \n", row, merch->name);
    array[row-1] = merch->name;
    ++row;
  } while(Successful(ioopm_refmem_iterator_next(iter)));

  
  release(all_merchendise);
  release(iter);
  
  return array;
}


option_t remove_merchandise(shopping_cart_db_t *cart_db, warehouse_t *warehouse, char *name)
{   
  option_t merch_exists = ioopm_refmem_hash_table_lookup(warehouse->merchendise, Epointer(name));
  
  if(Successful(merch_exists))
    {
      merch_t *merch = merch_exists.value.pointer;
      int size = ioopm_refmem_hash_table_size(cart_db);
      
      if(size > 0){
        ioopm_refmem_list_t *carts = ioopm_refmem_hash_table_values(cart_db);
        ioopm_refmem_list_iterator_t *iter_carts = ioopm_refmem_list_iterator(carts);
        
        do{
          shopping_cart_t *cart = ioopm_refmem_iterator_current(iter_carts).value.pointer;
          option_t item_exists = ioopm_refmem_hash_table_lookup(cart->cart, Epointer(name));
          if(Successful(item_exists)){
	    cart_item_t *item = item_exists.value.pointer;
	    remove_from_cart(cart, merch->name, item->quantity); 
          }
        } while(Successful(ioopm_refmem_iterator_next(iter_carts)));
	
        release(iter_carts);
        release(carts);
      }
      
      
      char *strname = name;
      destroy_location(merch->locs);
      
      ioopm_refmem_hash_table_remove(warehouse->merchendise, Epointer(strname));
      
      // storage update
      remove_shelf_from_storage(warehouse->storage, name);


      //free(merch->name); // free strdup string
      //free(merch->desc); // free strdup string
      //free(merch);
      release(merch);
      
      return Success(Epointer(strname));
    }
  
  return Failure(); // if merch dosent exist
}

option_t update_cart_items(shopping_cart_db_t *cart_db, char *name, char *new_name, float new_price, merch_t *merch){
  int size = ioopm_refmem_hash_table_size(cart_db);
  
  if(size > 0){
    int no_carts_changed = 0;
    ioopm_refmem_list_t *carts = ioopm_refmem_hash_table_values(cart_db);
    ioopm_refmem_list_iterator_t *iter_carts = ioopm_refmem_list_iterator(carts);
    
    do{
      shopping_cart_t *cart = ioopm_refmem_iterator_current(iter_carts).value.pointer;
      option_t item_exists = ioopm_refmem_hash_table_lookup(cart->cart, Epointer(name));
      if(Successful(item_exists)){
        cart_item_t *item = item_exists.value.pointer;
        if(strcmp(name, new_name) != 0){
          char *old_name = item->name;
          size_t old_quantity = item->quantity;
          add_to_cart(cart, merch, old_quantity); 
          remove_from_cart(cart, old_name, old_quantity);
          no_carts_changed++;
        }
        else if(new_price != item->price){
          item->price = new_price;
          no_carts_changed++;
        }
      }
    } while(Successful(ioopm_refmem_iterator_next(iter_carts)));
    
    release(iter_carts);
    release(carts);
    
    return Success(Eint(no_carts_changed));
  }
  else
    return Failure();
}

option_t edit_merchandise(warehouse_t *warehouse, shopping_cart_db_t *cart_db, char *name, char *new_name, char *new_desc, float new_price)
{    
  option_t merch_exists = ioopm_refmem_hash_table_lookup(warehouse->merchendise, Epointer(name));
  option_t new_merch_exists = ioopm_refmem_hash_table_lookup(warehouse->merchendise, Epointer(new_name));
  
  if(Successful(merch_exists) && Unsuccessful(new_merch_exists))
    {
      merch_t *merch = merch_exists.value.pointer;
      char *remove_name = merch->name; // free strdup string
      char *remove_desc = merch->desc; // free strdup string
      merch->name = new_name;
      retain(new_name);
      merch->desc = new_desc;
      retain(new_desc);
      merch->price = new_price;

      // Change key
      ioopm_refmem_hash_table_insert(warehouse->merchendise, Epointer(new_name), Epointer(merch));
      ioopm_refmem_hash_table_remove(warehouse->merchendise, Epointer(name));
      
      // update storage
      update_merch_name_in_storage(warehouse->storage, name, new_name);
      
      //update cart items to reflect new information
      update_cart_items(cart_db, name, new_name, new_price, merch);
      
      release(remove_name);
      release(remove_desc);
      //free(remove_name);
      //free(remove_desc);

      return Success(Epointer(name));
    }
  else
    {
      
      release(new_name);
      release(new_desc);
      //free(new_name);
      //free(new_desc);
    }

  return Failure();
}


void show_stock(warehouse_t *warehouse, char* name)
{
  option_t merch_exists = ioopm_refmem_hash_table_lookup(warehouse->merchendise, Epointer(name));

  if(Successful(merch_exists))
    {
      merch_t *merch = merch_exists.value.pointer;
      ioopm_refmem_list_iterator_t *iter = ioopm_refmem_list_iterator(merch->locs);
      shelf_t *shelf;
      
      do{
	shelf = ioopm_refmem_iterator_current(iter).value.pointer;
	if(shelf)
	  print_shelf(shelf);
      } while(Successful(ioopm_refmem_iterator_next(iter)));
      
      release(iter);
    }
}


option_t replenish(warehouse_t *warehouse, char *name, char *name_shelf, int change_quantity)
{
  option_t merch_exists = ioopm_refmem_hash_table_lookup(warehouse->merchendise, Epointer(name));

  if(Unsuccessful(merch_exists) || shelf_exists_for_other_merch(warehouse, name, name_shelf))
    {
      release(name_shelf);
      //free(name_shelf);
      return Failure();
    }
     
  merch_t *merch = merch_exists.value.pointer;  
  option_t shelf_success = get_shelf(merch->locs, name_shelf);

  if(shelf_exists(warehouse->storage, name_shelf) && Successful(shelf_success))
    {
      shelf_t *shelf = shelf_success.value.pointer;
      //free(name_shelf); // so we dont have duble names
      release(name_shelf);
      return uppdate_quantity(shelf, merch, name_shelf, change_quantity);
    }
  //RETAIN HÄR?
  return new_shelf_in_warehouse(warehouse, merch, name, name_shelf, change_quantity);
}


void list_storage(warehouse_t *warehouse)
{
  ioopm_refmem_list_t *all_storage = ioopm_refmem_hash_table_keys(warehouse->storage);
  ioopm_refmem_list_iterator_t *iter = ioopm_refmem_list_iterator(all_storage);

  char *shelf_name;
  char *merch;
  
  do{
    shelf_name = ioopm_refmem_iterator_current(iter).value.pointer;
    merch = ioopm_refmem_hash_table_lookup(warehouse->storage, Epointer(shelf_name)).value.pointer;
    printf("Shelf: %s\n %s, \n",
	 shelf_name,
	 merch);
  } while(Successful(ioopm_refmem_iterator_next(iter)));

  release(all_storage);
  release(iter);
}


option_t get_merch(warehouse_t *warehouse, char *merch_name)
{
  option_t success = ioopm_refmem_hash_table_lookup(warehouse->merchendise, Epointer(merch_name));
  if(Successful(success))
    return Success(Epointer(success.value.pointer));
    
  return Failure();
}



// Cart Funcktions


cart_item_t *create_cart_item(char *name, float price, size_t quantity, merch_t *item)
{
  cart_item_t *cart_item = allocate(sizeof(cart_item_t), cart_item_destructor);
  char *item_name = ioopm_refmem_strdup(name); 
  //char *item_name = allocate(sizeof(char*), NULL);

  *cart_item = (cart_item_t){
    .name=item_name, 
    .price=item->price,
    .quantity=quantity,
    .item=item,
  };
  retain(cart_item);
  retain(item_name); //pga strdup inge ref count
  retain(item);


  return cart_item;
}


option_t add_to_cart(shopping_cart_t *shopping_cart, merch_t *item, size_t add_quantity)
{
  if(item){
    option_t lookup_item = ioopm_refmem_hash_table_lookup(shopping_cart->cart, Epointer(item->name));
    if (Successful(lookup_item)){
      cart_item_t *cart_item = lookup_item.value.pointer;
      if(item->stock >= add_quantity+cart_item->quantity){
        cart_item->quantity += add_quantity; 
        return Success(Eint(cart_item->quantity));
      }
      else{
        return Failure();
      }
    }
    else{
      if(item->stock >= add_quantity){
      cart_item_t *cart_item = create_cart_item(item->name, item->price, add_quantity, item);
      ioopm_refmem_hash_table_insert(shopping_cart->cart, Epointer(cart_item->name), Epointer(cart_item));
      return Success(Eint(add_quantity)); 
      }
      else{
        printf("There is not enough stock to add %zu of this item", add_quantity);
        return Failure();
      }
    }
  }
  return Failure();
}



option_t remove_from_cart(shopping_cart_t *shopping_cart, char *name, unsigned int remove_quantity)
{
    option_t lookup_item = ioopm_refmem_hash_table_lookup(shopping_cart->cart, Epointer(name));
    
    if (Successful(lookup_item)){
      cart_item_t *cart_item = lookup_item.value.pointer;
      
      if(cart_item->quantity <= remove_quantity){
        ioopm_refmem_hash_table_remove(shopping_cart->cart, Epointer(name));
        //free(cart_item->name);
        //free(cart_item);
        release(cart_item);
        return Success(Epointer("h"));
      }
      
      else{
        for (unsigned int i = 0; i < remove_quantity; i++ ){
        cart_item->quantity--;
        }
        return Success(Eint(cart_item->quantity));
      }
    }
    return Failure();
}


option_t remove_cart(shopping_cart_db_t *cart_db, char *username)
{
  option_t lookup_result = ioopm_refmem_hash_table_lookup(cart_db, Epointer(username));
  
  if(Successful(lookup_result))
  {
    shopping_cart_t *right_cart = lookup_result.value.pointer; 
    ioopm_refmem_list_t *cart_values = ioopm_refmem_hash_table_values(right_cart->cart); // make a list of everything in cart
    bool isEmpty = ioopm_refmem_linked_list_is_empty(cart_values); //size variable for if statements


  if(!isEmpty){ // remove shopping cart items
    ioopm_refmem_list_iterator_t *cart_iter = ioopm_refmem_list_iterator(cart_values); //make an iterator

    do{
       cart_item_t *current_item = ioopm_refmem_iterator_current(cart_iter).value.pointer;
       remove_from_cart(right_cart, current_item->name, current_item->quantity);
      }while(Successful(ioopm_refmem_iterator_next(cart_iter)));

     release(cart_iter); //remove iterator
   }

  // Remove shoping cart   
 // release(right_cart->cart); //ALWAYS FREE THE CART ETC, also jump to this instant if size is 0 
   
  ioopm_refmem_hash_table_remove(cart_db, Epointer(username));
  // free(right_cart->username_key);
  // free(right_cart);
  // release(right_cart->username_key);
   release(right_cart);
   release(cart_values); //remove list
   return Success(Epointer(username));
  }
  return Failure();
}


void destroy_cart_db(shopping_cart_db_t *cart_db)
{
  if(ioopm_refmem_hash_table_size(cart_db) > 0){
   ioopm_refmem_list_t *values = ioopm_refmem_hash_table_values(cart_db);
  

   if(!ioopm_refmem_linked_list_is_empty(values)){
     ioopm_refmem_list_iterator_t *value_iter = ioopm_refmem_list_iterator(values);

     do{ 
       shopping_cart_t *cart = ioopm_refmem_iterator_current(value_iter).value.pointer;
       remove_cart(cart_db, cart->username_key);
     } while(Successful(ioopm_refmem_iterator_next(value_iter)));

     release(value_iter);
   }

   release(values); //remove list
   release(cart_db);
  }
  else{
    release(cart_db);
  }
}

option_t add_cart(shopping_cart_db_t *cart_db, char *username)
{
  option_t success = ioopm_refmem_hash_table_lookup(cart_db, Epointer(username));
  if(Successful(success))
    return Failure();
    
  shopping_cart_t *cart = create_cart(username);
  ioopm_refmem_hash_table_insert(cart_db, Epointer(cart->username_key), Epointer(cart));
  return Success(Epointer(cart));
}

option_t calculate_cost(shopping_cart_t *shopping_cart) //only returns success if cart contains at least 1 item.
{
    ioopm_refmem_list_t *values = ioopm_refmem_hash_table_values(shopping_cart->cart);
    bool isEmpty = ioopm_refmem_linked_list_is_empty(values);

    if(!isEmpty){ //only enter this if at least 1 item guaranteed
    
      ioopm_refmem_list_iterator_t *value_iter = ioopm_refmem_list_iterator(values);
      float acc_price = 0;
      
      do{ 
        cart_item_t *cart_item = ioopm_refmem_iterator_current(value_iter).value.pointer;
        float tmp_price = cart_item->price * cart_item->quantity;
        acc_price += tmp_price; 
        } while(Successful(ioopm_refmem_iterator_next(value_iter)));
      
      release(value_iter);
      release(values);
      return (Success(Efloat(acc_price)));
    }
    else{
    release(values);
    return Failure();
    }
}


option_t checkout(warehouse_t *warehouse, shopping_cart_db_t *cart_db, char *username)
{
  // Find the shopping cart
  option_t find_cart_success = ioopm_refmem_hash_table_lookup(cart_db, Epointer(username));
  if(Unsuccessful(find_cart_success))
    return Failure();
  
  shopping_cart_t *shopping_cart =  find_cart_success.value.pointer;
  
  // If cart can not be checkout, do not even try
  if(!cart_can_be_checkout(warehouse, shopping_cart))
      return Failure();
  
  // create iter
  ioopm_refmem_list_t *all_cart_items = ioopm_refmem_hash_table_values(shopping_cart->cart);
  ioopm_refmem_list_iterator_t *iter_cart_items = ioopm_refmem_list_iterator(all_cart_items);
  cart_item_t *cart_item;

  // iterate over all cart items
  do{
    cart_item = ioopm_refmem_iterator_current(iter_cart_items).value.pointer;
    uppdate_merch_in_warehouse_for_checkout(warehouse, cart_item);
  } while(Successful(ioopm_refmem_iterator_next(iter_cart_items)));

  // Clean up
  release(all_cart_items);
  release(iter_cart_items);
  remove_cart(cart_db, username);
  
  return Success(Epointer(username));
}


shopping_cart_db_t *create_cart_db()
{  
  return ioopm_refmem_hash_table_create(hash_function, eq_func_merch);
}

void show_cart(shopping_cart_t *shopping_cart)
{
    ioopm_refmem_list_t *cart_items = ioopm_refmem_hash_table_values(shopping_cart->cart);
    int cart_size = ioopm_refmem_linked_list_size(cart_items);

    //special cases= 1, 0 and more. 
    
    if(cart_size >= 1){
      ioopm_refmem_list_iterator_t *items_iter = ioopm_refmem_list_iterator(cart_items);
      int line_counter = 1; 
      
      do{
        cart_item_t *item = ioopm_refmem_iterator_current(items_iter).value.pointer;
        printf("\n %d. %s, Quantity: %zu, Price per: %f", line_counter, item->name, item->quantity, item->price); 
        line_counter++;
      }while(Successful(ioopm_refmem_iterator_next(items_iter)));
      release(items_iter);
      }

    
    
    release(cart_items);
    
    printf("\n_________________________________\n\n");
}
