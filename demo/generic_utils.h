#pragma once
#include <stdbool.h>

/**
 * @file linked_list.h
 * @author Lukas Nord, Anton Augustsson
 * @date 21 Sep 2020
 * @brief Lists, hashmaps, and more – if you need them. 
 *
 * @see http://wrigstad.com/ioopm/assignments/assignment2.html
 */

/// @brief Ask a question and receives int input
/// @param question for a input
/// @return only one of input
int ask_question_int(char *question);

/// @brief Ask a question and receives string
/// @param question for a input
/// @return only one of input
char *ask_question_string(char *question);

/// @brief Ask a question and receives float input
/// @param question for a input
/// @return only one of input
float ask_question_float(char *question);

/// @brief Ask a question and receives menu input
/// @param question for a input
/// @param the string of all upper and lower case carecter that is a valid menu option
/// @return only one of input
char ask_question_menu(char *question, char *menu_options_input);

char *ioopm_refmem_strdup(char *str);
