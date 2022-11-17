# Requirements

Implement two programs in C/C++/Rust:

* Server program:

	- Initialize a hash table of given size (command line)

	- Support insertion of items in the hash table
	
	- Hash table collisions are resolved by maintaining a linked list for each bucket/entry in the hash table
	
	- Supports concurrent operations (multithreading) to perform (insert, read, delete operations on the hash table)

	- Use readers-writer lock to ensure safety of concurrent operations,try to optimize the granularity

	- Communicates with the client program using shared memory buffer (POSIX shm)

* Client program:
	- Enqueue requests/operations (insert, read a bucket, delete) to the server (that will operate on the the hash 
	table) via shared memory buffer (POSIX shm)

Please send us the code with a Makefile to compile and run the code.


# Solution

The exercise is solved in C++. The key points are:

1. Implementation of a hash table, with insertion and using linked list to resolve collisions
2. Concurrent operations
3. readers-write lock
4. shared memory buffer


## Hash Table

### Hash Function

For the hash function, I choose the typical hashing approach by division.

```
Hash(key) = key mod p
```

,where p is a prime least than the size of hash table.

In my case, I simply use size of hash table as p.
And the key doesn't have to be a number, so I convert it into string and then into ascii value:

```
Hash(key) = (..(key[0]*37 + key[1])*37 + ... + k[p-1])*37
```


### Collision Resolution

To resolve the collisions, the exercise asks to implement a linked list for each bucket/entry in the hash table.

For keys with same result from hash function, we always update the new comer as the head of the linked list.




