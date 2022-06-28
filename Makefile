COMPILENAME = main.out
C_COMPILER = gcc
C_FLAGS = -ggdb -std=c11 -D_XOPEN_SOURCE=700
C_OBJECTS = refmem.o linked_list/linked_list.o linked_list/common.o
C_LINK_OPTIONS = -lm
SRC = src/refmem.o src/hash_table/hash_table.o src/linked_list/common.o src/linked_list/linked_list.o
SRCC = src/refmem.c src/hash_table/hash_table.c src/linked_list/common.c src/linked_list/linked_list.c
DEMO = demo/ht_ll_refmem/hash_table_refmem.o demo/ht_ll_refmem/linked_list_refmem.o demo/ht_ll_refmem/common_refmem.o demo/business_logic.o demo/generic_utils.o
DEMOC = demo/ht_ll_refmem/hash_table_refmem.c demo/ht_ll_refmem/linked_list_refmem.c demo/ht_ll_refmem/common_refmem.c demo/business_logic.c demo/generic_utils.c
UI = demo/user_interface.o

%.o: %.c
	$(C_COMPILER) $(C_FLAGS) $? -c -o $@

test/tests: $(SRC) test/Cunit.o
	$(C_COMPILER) $? -o $@ -g -lcunit $(C_LINK_OPTIONS)
	
test: test/tests
	./test/tests
	
memtest: test/tests
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test/tests

test/integration_business_logic: $(SRC) $(DEMO) test/business_logic_tests.o
	$(C_COMPILER) $^ -o $@ -g -lcunit $(C_LINK_OPTIONS)
	
business_logic_test: test/integration_business_logic
	./test/integration_business_logic
	
business_logic_memtest: test/integration_business_logic
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test/integration_business_logic

test/integration_user_interface: $(SRC) $(DEMO) $(UI) test/user_interface_tests.o
	$(C_COMPILER) $^ -o $@ -g -lcunit $(C_LINK_OPTIONS)
	
user_interface_test: test/integration_user_interface
	./test/integration_user_interface	
	
user_interface_memtest: test/integration_user_interface
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test/integration_user_interface

user_interface_testtxt: test/integration_user_interface
	./test/integration_user_interface < test/testtxt.txt

user_interface_memtesttxt: test/integration_user_interface
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test/integration_user_interface < test/testtxt.txt
	
test_gcov:
	$(C_COMPILER) $(SRCC) test/Cunit.c -fprofile-arcs -ftest-coverage $(C_LINK_OPTIONS) -lcunit $^ -o $@
	./test_gcov
	gcov -b -c refmem.c
	
business_test_gcov:
	$(C_COMPILER) $(SRCC) $(DEMOC) test/business_logic_tests.c -fprofile-arcs -ftest-coverage $(C_LINK_OPTIONS) -lcunit $^ -o $@
	./business_test_gcov
	gcov -b -c refmem.c
	
user_interface_gcov:
	$(C_COMPILER) $(SRCC) $(DEMOC) demo/user_interface.c test/user_interface_tests.c -fprofile-arcs -ftest-coverage $(C_LINK_OPTIONS) -lcunit $^ -o $@
	./user_interface_gcov < test/testtxt.txt
	gcov -b -c refmem.c

clean:
	rm *.gcov -f
	rm *.gcno -f
	rm *.gcda -f
	rm *.out -f
	rm *.o test_gcov business_test_gcov user_interface_gcov -f
	rm test/tests test/*.o test/integration_business_logic test/integration_user_interface -f
	rm demo/*.o demo/ht_ll_refmem/*.o -f
	rm src/linked_list/*.o -f
	rm src/hash_table/*.o -f
	rm src/*.o -f
