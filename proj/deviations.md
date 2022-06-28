DEVIATIONS

In order to test the program by implementation, the group rewrote all functions of the assignment 1 hash table and linked list.
This was a great way to test whether or not the new interface worked in a similar enough way to the standard library of allocation and memory freeing functions.
Since there was already proper tests written for hash table and linked list, implementation was relatively simple.
However, the new interface had no equivalent of a realloc() function, which was used when a hash table grew in size.
The group decided that rewriting the code within hash table was preferable rather than exporting another function that had not been part of the project specifications.
Thus, the problem was solved by first allocating the space needed for a hash table to expand,
and then copying the memory from the previous hashtable into that slot. 
Finally, the old hash table was freed using release().

During the implementation of our memory management into the assignment 2 program (simulating a simple web-store),
there was an annoying bug discovered when trying to use the new memory allocation system. 
Since the implementation of the memory handling system used the original hash table and linked list files from assignment 1,
there was a collision between these functions, and the rewritten functions that were used in the web-store.
Initially, the issue seemed to be caused by some file leaking information about the old hash table and linked list versions. 
However, after many hours of searching, no such leak was found. Another remedy was to stage the compilation of the files so as to separate the two versions of ht and linked list. 
This did not make any difference. The problem was ultimately solved by renaming all of the rewritten assignment 1 functions.

At the later stage of the project, the group decided to implement a bitmap in order to save some space when saving the addresses of all allocated objects.
During the implementation of this feature, there were a few bugs discovered in the base program, 
and a decision was made to spend time fixing these bugs instead of implementing the bitmap - which in essence was more of an optimization rather than a functionality feature.
Even though it would have been nice to have a bitmap, which marginally would reduce memory used,
the group unanimously decided that functionality was more important than optimization.
