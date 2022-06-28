#pragma once

#include <stdbool.h>

/// inlupp1

/// inlupp2
#include "generic_utils.h"
#include "business_logic.h"


/**
 * @file user_interface.h
 * @author Lukas Nord, Anton Augustsson
 * @date 21 Sep 2020
 * @brief Lists, hashmaps, and more – if you need them. 
 *
 * @see http://wrigstad.com/ioopm/assignments/assignment2.html
 */


/// one chould have a user sign in "ask for name so it dosent have to ener it every time"
/// @brief user add to cart
void user_add_to_cart(warehouse_t *warehouse, shopping_cart_t *user_cart);

/// @brief remove item from cart
void user_remove_from_cart(warehouse_t *warehouse, shopping_cart_t *user_cart);

/// @brief user cheackut
void user_checkout(warehouse_t *warehouse, shopping_cart_db_t *cart_db, char *username);

/// @brief user display cart  with total sum and so on
void user_show_cart();


/// @brief allows admin to enter in merch and saves it to warehouse
/// @param A hash table that stores pointer to merchendise and one for storage
void admin_add_merch_to_warehouse(warehouse_t *warehouse);

/// @brief allows admin to enter name of merch to remove from warehouse
/// @param A hash table that stores pointer to merchendise and one for storage
void admin_remove_merch_from_warehouse(warehouse_t *warehouse, shopping_cart_db_t *cart_db);

/// @brief allows admin to view all merchendise in warehouse
/// @param A hash table that stores pointer to merchendise and one for storage
void admin_show_warehouse(warehouse_t *warehouse);

/// @brief allows admin to enter name of merch to view all added location
/// @param A hash table that stores pointer to merchendise and one for storage
void admin_show_location(warehouse_t *warehouse);

/// @brief allows admin to edit merch
/// @param A hash table that stores pointer to merchendise and one for storage
void admin_edit_merch(warehouse_t *warehouse, shopping_cart_db_t *cart_db);

/// @brief allows admin to add modify the storage of the warehouse
/// @param A hash table that stores pointer to merchendise and one for storage
void admin_replenish(warehouse_t *warehouse);


/// @brief Return allocated warehouse recorses and quits program
/// @param A hash table that stores pointer to merchendise and one for storage
void quit_admin(warehouse_t *warehouse);

/// @brief Quits program
/// @param A hash table that stores pointer to merchendise and one for storage
void quit_user(warehouse_t *warehouse, shopping_cart_db_t *cart_db, char *user_name);

/// @brief Allowes the admin to eddit.
/// @param A hash table that stores pointer to merchendise and one for storage
void admin_menu(warehouse_t *warehouse, shopping_cart_db_t *cart_db);

/// @brief Allowes the user to eddit.
/// @param A hash table that stores pointer to merchendise and one for storage
/// @param A hash table that stores all carts
void user_menu(warehouse_t *warehouse, shopping_cart_db_t *cart_db, shopping_cart_t *user_cart, char *username); 

/// @brief Event loop for manipulating cart and warehouse
/// @param warehouse A struct of 2 hash-tables containing merch and locations
/// @param cart_db The database of user carts
void menu(warehouse_t *warehouse, shopping_cart_db_t *cart_db);

/// @brief Exits the menu event loop
/// @param warehouse A struct of 2 hash-tables containing merch and locations
/// @param cart_db The database of user carts
void quit_program(warehouse_t *warehouse, shopping_cart_db_t *cart_db);
