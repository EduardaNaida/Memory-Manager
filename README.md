# Project: Memory Manager

by
Lukas Nord

Max Sahlholm 

Anton Ohlsson

Eduarda Naida

Kimiya Rahimi Ata

Ludvig Westerholm


## Building: 

Use makefile to build tests. There is no main file to this program, only a header file to be imported into your own projects.
To tests use GCC as compiler and depends on CUnit.
To install CUnit & GCC on Ubuntu/Debian-based systems:
```
sudo apt-get install gcc libcunit1 libcunit1-dev
```
These are the various recommended tests to run
```
make memtest
make user_interface_memtesttxt
make business_logic_memtest
```

## Implementing interface:

The interface exports the functions retain() and release() which are the top level functions used to retain memory, or release an object. For allocation, this interface uses allocate() and allocate_array() to replace malloc() and calloc() respectively. Deallocate is a function explicitly used by the top level function release(). Do not use deallocate separately, instead, use release on an object that has no other references in the code.

If used correctly, interface will guarantee no invalid free's or trying to read NULL pointers.

## Use customized destructors

The functions allocate() and allocate_array() take a destructor as the third argument. If no destructor is wanted, use NULL in this field - the command will then function like malloc and calloc (with extra safeguards described above). If a customized destructor is needed, define it and use a pointer to this function as the third argument. If you are unsure how to make a destructor, a default destructor is included, which loops through structs, looking for already allocated object pointers (allocated using this interface), and deallocates these - with recursion occuring up to the cascade limit.

## Cascade limit

The cascade limit has the default value of 50. This can be changed during the runtime at any time by using the set_cascade_limit function. To get the current cascade limit get_cascade_limit can be used.
