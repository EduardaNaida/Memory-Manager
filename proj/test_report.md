## Test report

Since this project consisted of both entirely new code, and reused a lot of code from previous assignments, there were multiple layers of testing going on. At the surface level, refmem.c was tested using CUnit (which is also used throughout the entire testing process). The tests were specific to the completely new functions, and tested each of them separately.

At the second level, the newly created interface from refmem.h was implemented into assignment 1, which is about hash tables and linked lists. This assignment was already rigorously tested in a blackbox style of testing. Simply put, the tests were swiftly rewritten using our own interface instead of calloc(), malloc() and free(). This level of testing also included proper memory testing using Valgrind (which was also used at the surface level, to make sure no memory leaks were possible anywhere).

Since the group in charge of this project worked very closely, regression testing was done manually each time new functionality was pushed, or significant restructuring was performed. During these meetings, the code was both merged, and tested using preexisting tests. For new functionality, new tests were required if the code was to be merged into the main branch - that is to say, any functionality-branch was to contain tests before merging them into the main branch.

Coverage in top level tests:
  Lines executed:89.36% of 94
  Branches executed:95.00% of 40
  Taken at least once:82.50% of 40
  Calls executed:86.21% of 29

Coverage in integration test business_logic:
  Lines executed:59.57% of 94
  Branches executed:70.00% of 40
  Taken at least once:55.00% of 40
  Calls executed:55.17% of 29
  
Coverage in integration test user_interface:
  Lines executed:70.21% of 94
  Branches executed:70.00% of 40
  Taken at least once:52.50% of 40
  Calls executed:68.97% of 29