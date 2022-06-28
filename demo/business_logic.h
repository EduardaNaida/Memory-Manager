#pragma once

#include <stdbool.h>
#include <stddef.h>

#include "ht_ll_refmem/hash_table_refmem.h"

//project


/**
 * @file business_logic.h
 * @author Lukas Nord, Anton Augustsson
 * @date 21 Sep 2020
 * @brief All non-user interface logic that concerns the system, 
 * e.g. shopping carts, merchandise, adding and removing items from the “database” 
 * (most of which will delegate to e.g. the hash table library), etc.
 *
 * @see http://wrigstad.com/ioopm/assignments/assignment2.html
 */
/**
 * @file hash_table.h
 * @author Lukas Nord, Oskar Pettersson Löfstedt
 * @date 10 Oct 2020
 * @brief Simple hash table that maps integer keys to string values.
 *
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 *
 * @see http://wrigstad.com/ioopm19/assignments/assignment1.html
 */
typedef struct warehouse warehouse_t;

typedef struct merch merch_t;
typedef struct shelf shelf_t;

typedef struct shopping_cart shopping_cart_t;
typedef struct hash_table shopping_cart_db_t;
typedef struct cart_item cart_item_t;


/// @brief Creates a new warehouse with a ht merchendise and a ht storage
/// @return new warehouse
warehouse_t *create_warehouse();

/// @brief Frees all alocated memory from warehouse
/// @param warehouse warehouse operated upon
void destroy_warehouse(shopping_cart_db_t *cart_db, warehouse_t *warehouse);

/// @brief Creates a new shelf
/// @return new shelf in merch location in warehouse
shelf_t *create_shelf(char *shelf, size_t quantity);

/// @brief This adds a new merch to the warehouse with a name (string), description (string), and price (integer).
/// @param A hash table that stores pointer to merchendise and one for storage
/// @param the name of the merchendise
/// @Param the desciption of the merchendise
/// @param the price of the merchendise
/// @return a new merch if there dose not existing a merch with the same name
option_t add_merchandise(warehouse_t *warehouse, char *name, char *desciption, float price);

/// @brief list all merchendise in the warehouse
/// @param A hash table that stores pointer to merchendise and one for storage
void list_merchandise(warehouse_t *warehouse);
char **list_merchandise_with_array(warehouse_t *warehouse);

/// @brief Removes an item completely from the warehouse, including all its stock
/// @param A hash table that stores pointer to merchendise and one for storage
/// @param the name of the merchendise
/// @return success status with value as name
option_t remove_merchandise(shopping_cart_db_t *cart_db, warehouse_t *warehouse, char *name);

/// @brief Allows changing the name, description and price of a merch (dosent effect stock)
/// new name that is equal another is not allowed
/// @param A hash table that stores pointer to merchendise and one for storage
/// @param the name of the merchendise
/// @param new name for merchendise
/// @param new description for merchendise
/// @param new prise for merchendise
/// @return success status with value as name
option_t edit_merchandise(warehouse_t *warehouse, shopping_cart_db_t *cart_db, char *name, char *new_name, char *new_desc, float new_price);

/// @brief List all the storage locations for a particular merch
/// @param data stucture (ht)
/// @param name (merchandise)
void show_stock(warehouse_t *warehouse, char* name);

/// @brief Increases the stock of a merch by at least one (of an existing or non existing storage)
/// if the quantity is set to 0 then the shelf whill be removed
/// @param A hash table that stores pointer to merchendise and one for storage
/// @param existing name for merchendise
/// @param the name of the shelf
/// @param the quantaty that will be added to the existing one (if change_quantity> then 0)
/// @return success status with value as name
option_t replenish(warehouse_t *warehouse, char *name, char *name_shelf, int change_quantity);

/// @brief List all the storage locations and what merch is stored there
/// @param A hash table that stores pointer to merchendise and one for storage
void list_storage(warehouse_t *warehouse);

/// @brief A lookup function for merch in warehouse
/// @param A hash table that stores pointer to merchendise and one for storage
/// @param the name merch of the merchendise you wish to find
/// @return merchindeise
option_t get_merch(warehouse_t *warehouse, char *merch_name);


/// @brief Creates a new shopping cart data base
/// @return new shopping cart
shopping_cart_db_t *create_cart_db();

/// @brief Creates a new shopping cart data base
/// @return new shopping cart
void destroy_cart_db(shopping_cart_db_t *cart_db);

/// @brief Adds a new shopping cart in carts database.
/// @param data stucture (ht)
/// @param customer
/// @return new shopping cart
option_t add_cart(shopping_cart_db_t *cart_db, char *username);

/// @brief Removes a shopping cart from the system.
/// @param data stucture (ht)
/// @param customer
option_t remove_cart(shopping_cart_db_t *cart_db, char *username);

/// @brief Adds some quantity of a merch to a specific shopping cart.
/// @param data stucture (ht)
/// @param customer
/// @return shopping cart with it's new merchandise 
option_t add_to_cart(shopping_cart_t *shopping_cart, merch_t *item, size_t add_quantity);

/// @brief Removes zero or more items of some merch from a particular cart.
/// @param data stucture (ht)
/// @param customer
option_t remove_from_cart(shopping_cart_t *shopping_cart, char *item, unsigned int remove_quantity);

/// @brief Calculate the cost of a shopping cart
/// @param data stucture (ht)
/// @param customer
option_t calculate_cost();

/// @brief Allows the user to view cart
/// @param data stucture (ht)
/// @param customer
void show_cart(shopping_cart_t *user_cart);

/// @brief Decrease the stock for the merches in the cart and Remove the shopping cart from the syste.
/// @param data stucture (ht)
/// @param customer
option_t checkout(warehouse_t *warehouse, shopping_cart_db_t *cart_db, char *username);

/// @brief Returns option_t containing success if item is in cart
/// @param user_cart is the cart looked in
/// @item is a string of the nameo f hte item
option_t cart_lookup(shopping_cart_t *user_cart, char *item);
