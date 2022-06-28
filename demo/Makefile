inlupp2:
	echo "hello"

C_COMPILER     := gcc
C_OPTIONS      := -ggdb -Wall -std=c11
C_LINK_OPTIONS := -lm 
CUNIT_LINK     := -lcunit -D_XOPEN_SOURCE=700

clean:
	rm ht_ll_refmem/*.o -f *.o *.gcov *.gcno vgcore.* *.gcda inlupp2 generic_utils-tests generic_data_structure_tests user_interface_tests business_logic_tests

%.o:  %.c ht_ll_refmem/%.c
	$(C_COMPILER) $(C_OPTIONS) $? -c $(CUNIT_LINK)


main: main.o user_interface.o generic_utils.o business_logic.o hash_table.o linked_list.o common.o ../refmem.o
	$(C_COMPILER) $^ -o $@ $(CUNIT_LINK)

run: main
	./main

business_logic_tests: ../refmem.o business_logic_tests.o business_logic.o ht_ll_refmem/hash_table_refmem.o ht_ll_refmem/linked_list_refmem.o ht_ll_refmem/common_refmem.o 
	$(C_COMPILER) $? -o $@ $(C_LINK_OPTIONS) $(CUNIT_LINK)

user_interface_tests: ../refmem.o user_interface_tests.o user_interface.o generic_utils.o business_logic.o ht_ll_refmem/hash_table_refmem.o ht_ll_refmem/linked_list_refmem.o ht_ll_refmem/common_refmem.o 	
	$(C_COMPILER) $^ -o $@ $(C_LINK_OPTIONS) $(CUNIT_LINK)

test: business_logic_tests
	./business_logic_tests

memtest: business_logic_tests
	valgrind --leak-check=full ./business_logic_tests

user_memtest: user_interface_tests
	valgrind --leak-check=full ./user_interface_tests

