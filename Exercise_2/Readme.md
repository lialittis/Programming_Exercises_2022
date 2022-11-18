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

# How to Compile \& Run

## Config

Langurage Version : \>C++14

Compiler Version : g++ 9.4.0

**NOTE** The HashTable is a template class, here the server and client is only prepared for `HashTable<int,int>` type.

**TODO** Make server and client could manipulate different types of HashTable.

## Compiling

```
make
```

## Execute

1. Run Server Firstly

There is one argument : size of hash table.

```
./server 20
```

2. Run Client and Send Request

```
./client
```


Once the client program is executed successfully, follow the instructions to send requests to server.
There are three type of requests : `I` for `Insert`, `R` for `Read`, `D` for `Delete`.

For example:

```
Your Request:(I/R/D):
I
The entry:(key value)
2 3
```

I also offer one toy client that is able to run directly.


```
bash toy_client.sh
```

## Unit Tests

I wrote two unit tests for this exercise.

`hash_test.cpp` is the program testing the basic functionalities of the hash table;
`threads_test.cpp` is the program testing the operators in multiple threads.

A Makefile is given to compile the testing porgrams.

# Explanations

The exercise is solved in C++. The goals are:

1. Implementation of a hash table, with insert/read/delete functions and using linked list to resolve collisions
2. Concurrent operations and readers-write lock
3. Implementation of POSIX shared memory buffer communication.


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
but for reading I use `std::shared_lock` from C++14. Thus, for writer operators, e.g. `insert`, `delete`, `clear`, unique 
lock is used; for reader operator `get`, shared lock is used.


## POSIX shm

POSIX shared memory buffer is the fastest approach of IPC communications.

### Shared Memory 

```
template <class Key, class Value>
struct SharedMem{
	int flag;		/* whether reading is successful */
	int count;		/* number of requests */
	sem_t sem_s;		/* first semaphore */
	sem_t sem_c;		/* second semaphore */
	size_t hash_operation;	/* operation type */
	Key key;		/* key */
	Value val;		/* value */
};

typedef SharedMem<int,int> ShmIntInt;
```

### semaphore

The semaphore is necessary for synchronize data in shared memory buffer.
Here I used two semaphores to control the mutex lock between the server and the client.





