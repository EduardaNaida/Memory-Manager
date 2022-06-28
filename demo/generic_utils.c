#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "generic_utils.h" 

//project
#include "../src/refmem.h"


typedef union { 
  int   int_value;
  float float_value;
  double double_value;
  char *string_value;
  char char_value;
} answer_t;



typedef bool(*check_func)(char *);
typedef answer_t(*convert_func)(char *);
extern char *strdup(const char *);



/// Helper functions

char *ioopm_refmem_strdup(char *str)
{
  size_t len = strlen(str);
  int lenght = len + 1;
  char *result = (char* ) allocate_array(lenght, sizeof(char), NULL);
  strncpy(result, str, len);
  
  //retain(result);
  return result;
}

static  bool is_number(char *str)
{
  int array_length = strlen(str);
  int start_i=0;
  
  if (array_length == 0)
    {
      return false;
    }
  else if (str[0] == '-' && array_length>1)
    {
      start_i = 1;
    }

  for (int i = start_i; i <= array_length-1; i++)
    {
      if (!isdigit(str[i]))
	{
	  return false;
	}
    }
  
  return true;
}


static bool is_float(char *str)
{
  int array_length = strlen(str);
  int dot_count = 0;
  int start_i=0;

  if (array_length == 0 || str[0] == '.' || str[array_length-1] == '.')
    {
      return false;
    }
  else if (str[0] == '-' && array_length>1)
    {
      start_i = 1;
    }
  
  for (int i = start_i; i <= array_length-1; i++)
    {
      if (str[i] == '.')
	{
	  dot_count = dot_count+1;
	}
      if ((!isdigit(str[i]) && str[i] != '.') || dot_count >=2)
	{
	  return false;
	}
    }
  return true;
}


// Global variable that can be change to have diffrent menu options
static char *menu_options = "AaRrDdQq";  // defult options
  
static bool is_menu_option(char *str)
{
  if (strlen(str) != 1)
    {
      return false;
    }

  int options = strlen(menu_options);//12;
  //char menu_options[13] = "AaRrDdQq";//"LlTtRrGgHhAa"; 
  char c = str[0];

  for (int i = 0; i < options; ++i)
    {
      if (c == menu_options[i])
	{
	  return true;
	}
    }
  return false;
}


static char to_upper_char(char *str)
{
  return toupper(str[0]);
}


/// Hjälpfunktion till ask_question_string
static bool not_empty(char *str)
{
  return strlen(str) > 0;
}


/// @brief Clear the buffer from multiple inputs  (helper funciton)
static  void clear_input_buffer()
{
  int c;
  do
    {
      c = getchar();
    }
  while (c != '\n' && c != EOF);
}


static int read_string(char *buf, int buf_siz)
{
  int i;
  char c;

  for (i=0; i < buf_siz; i++)
    {
      c = getchar();
      
      if(c == '\n' || c == EOF)
	{
	  break;
	}
      else if (i == (buf_siz-1))
	{
	  clear_input_buffer();
	}
      else
	{
	  buf[i]=c;
	}
    }

  buf[i] = '\0';  // end of string
  return i;
}

// helper function to float
static answer_t make_float(char *str)
{
  return (answer_t) { .float_value = atof(str) };
}


static answer_t ask_question(char *question, check_func check, convert_func convert)
{

  int buf_siz = 255;
  char buf[buf_siz];
  answer_t answer;
  int read = 0;
  
  while (read == 0) 
    {
      printf("%s\n", question);
      read = read_string(buf, buf_siz);
      if (check(buf))
	{
	  answer = convert(buf);
	  break;
	}
      else
	{
	  read = 0;
	  printf("not a valid input try again\n");
	}
    }
    
  return answer;
}



/// Public API functions


int ask_question_int(char *question)
{
  answer_t answer = ask_question(question, is_number, (convert_func) atoi);
  return answer.int_value; // svaret som ett heltal
}


char *ask_question_string(char *question)
{
  return ask_question(question, not_empty, (convert_func) ioopm_refmem_strdup).string_value;
}


float ask_question_float(char *question)
{
  return ask_question(question, is_float, make_float).float_value;
}

char ask_question_menu(char *question, char *menu_options_input)
{
  menu_options = menu_options_input;
  return ask_question(question, is_menu_option, (convert_func) to_upper_char).char_value;
}
