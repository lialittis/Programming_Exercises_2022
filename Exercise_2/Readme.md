# Requirements

Implement two programs in C/C++/Rust:

* Server program:

	- Initialize a hash table of given size (command line)
	- Support insertion of items in the hash table

	- Hash table collisions are resolved by maintaining a linked list for
	each bucket/entry in the hash
     	table

	- Supports concurrent operations (multithreading) to perform (insert,
     	read, delete operations on the hash table)

	- Use readers-writer lock to ensure safety of concurrent operations,
	try to optimize the granularity

	- Communicates with the client program using shared memory buffer (POSIX shm)

* Client program:
	- Enqueue requests/operations (insert, read a bucket, delete) to the
     	server (that will operate on the the hash table) via shared memory buffer (POSIX shm)

Please send us the code with a Makefile to compile and run the code.



