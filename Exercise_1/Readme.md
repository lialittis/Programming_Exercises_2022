# Requirements

Implement two (malloc and free) library calls using the sbrk syscall and implement 
a simple allocation policy to do thread-safe allocation and free. Please also write 
a short paragraph explaining the policy you implemented, and how it works.


# Allocation policy

Firstly, we consider the heap composed of different size of memory blocks. Each block
store the meta information and also the data(payload). When we do `malloc`, either there 
are some available blocks and we use/split one of them to store the new data, either there 
is no space or available blocks and then we increase the size of heap by creating new block.
When we do `free` and the given address is not NULL, then we find the allocated block and
set it as free, and we need to merge two connect free blocks into the same.


This is one demostration of one block. So the address of header is actually the header of 
the block.

```
low                                             high
+++++++++++++++++++++++++++++++++++++++++++++++++++
+              |                                  +
+ header(meta) |            data(payload)         +
+              |                                  +
+++++++++++++++++++++++++++++++++++++++++++++++++++
```

In this case, there are several problems that we need to solve.

1. How to distribute/find the approprate block?

There are multiple choices, e.g. First Fit, Best Fit and Next Fit.
I choose *First Fit*, since it is faster and we don't have to search the entire list every
time. And it is easy to implement. One of the key problem is that we need to take care of
small allocations, by spliting big block in my case.


2. The data structure of each header of blocks?

As we need to merge blocks, it is better that we are able to find the adjacent blocks.
So I choose to use double linked list to implement the header.

3. 64 bits or 32 bits?

In my case, I am using a 64bits machine, so the address is also in 64 bits.
To ensure the memory alignment, we should care about the size of header and data and make
them be the multiple of 8 bytes.

4. FIFO or LIFO ?

when freeing or spliting blocks, we always try to keep the heap as small as possible, so 
the LIFO policy is used.

# Explanations

## Memory

This is a simplified illustration of memory management in Linux system.

```
++++++++++++++++++++++++++++++++++++   High address
++                                ++
++                            ||  ++
++             STACK          ||  ++
++                            \/  ++
++                                ++
++--------------------------------++
++                                ++
++                            /\  ++
++             HEAP           ||  ++  <--- (malloc, free)
++                            ||  ++
++                                ++
++++++++++++++++++++++++++++++++++++
++                                ++
++                                ++
++              BBS               ++
++                                ++
++                                ++
++++++++++++++++++++++++++++++++++++
++                                ++
++                                ++
++             DATA               ++
++                                ++
++                                ++
++++++++++++++++++++++++++++++++++++
++                                ++
++                                ++
++             CODE               ++
++                                ++
++                                ++
++++++++++++++++++++++++++++++++++++   Low address
```


## malloc

According to the C standard library, here is the declaration of malloc:

```C
void *malloc(size_t size);
```

There is our key targets:

- It allocates a continuous available memory (from HEAP), by using syscalls to obtain memory
- The size of memory allocated is at least the given size
- It returns a pointer, pointing to the start address of the allocated memory
- If it is called multiple times, there should be no overlap among the allocated memories
- It should be executed as fast as possible

## sbrk\brk

In heap, Linux uses a break pointer location to control the size of memory.
The memory that users could access is from the start address of heap until the break location.
And `brk` and `sbrk` are two syscalls that we could use to operate the break pointer.

```C
int brk(void *addr);
void *sbrk(intptr_t increment);
```

Both sbrk and brk increase memory by increment linearly. So the release would be from back to 
forward.

## Implementation

Firstly, we need to define a struct to contain the header, which is actually memory information(meta) 
allocated by `malloc`, it is not exactly the given size. We need a double linked list to simulate it.

```
struct meta_header
{
	size_t size_;	/* data size : 8 bytes */
	int free_;	/* whether available : 4 bytes */
	int padding;	/* padding : 4 bytes */
	p_header prev;	/* pointing to previous block : 8 bytes */
	p_header next;	/* pointing to next block : 8 bytes */
	void* data;	/* pointing to data : 8 bytes */
};
```














