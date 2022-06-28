This program creates a way of counting references to each object stored in memory. 
This allows a specific object to only be fully released from memory when the reference counter allows for it,
I.E. when there is no other pointer to that object in the programs scope.
This also entails that each and every object that would normally be stored in memory by either a malloc or a calloc, 
will now have to be stored instead using the new interface; retain().
Furthermore, to free an object, the used would have to call release(). 

The purpose of such an implementation is to ease the burden of manual memory management in C.
In this implementation of memory allocation, a guard is implemented
to make sure that no user can release a segment of memory that is referenced somewhere else in the same program.
If properly implemented and used, this guarantees that no use of release() can cause a segmentation error. 

In addition to the added safeguards of memory management, 
the new interface also allows for more efficient memory allocation.
As per the project specifications, a garbage collector has been implemented. 
This garbage collector stores any object that is no longer referenced in the program,
but has yet to been released due to a cascade limit - 
a limit to how many object can be released in succession from a single call of release().
The remaining objects are then stored in this global garbage collection, 
and released at a later time, either when there is another call to release()
that leaves room for additional memory freeing according to the cascade limit,
or when there is a call for memory allocation 
(in which case, the memory management guarantees to free at least as much space from the garbage collector to make sure the allocation is possible).
