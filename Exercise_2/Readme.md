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


## Concurrent operations

To realise multithreading and ensure the thread safety, C++14 has started to offer `shared_mutex` to manage the shared
memory by readers-writer lock : one or multiple threads could read the resources but only one thread is allowed to write/
modify the resource.

The shared mutex is implemented as `std::shared_timed_mutex` from C++14, and for writing I use `std::unique_lock` from C++11
but for reading I use `std::shared_lock` from C++14.

## POSIX shm

POSIX shared memory buffer is the fastest approach of IPC communications.

```
shm_open (const char *name, int oflag, mode_t mode);
shm_unlink (const char *name);
```

*oflag : O_RDONLY or O_RDOWR, O_CREAT, O_EXCL*

### semaphore

The semaphore is used to synchronize data.
