# Requirements

Implement two (malloc and free) library calls using the sbrk syscall and implement 
a simple allocation policy to do thread-safe allocation and free. Please also write 
a short paragraph explaining the policy you implemented, and how it works.

# How to Compile \& Run

The new malloc and free functions are named `my_malloc` and `my_free` separately. 
They are implemented into a shared library `libmalloc.so`, to use these two library calls,
don't forget to to add a link to the compiler and a library path to the environment.

## Unit Tests

I also offer several unit tests which are able to call `my_malloc` and `my_free` functions.
Feel free to test them.

# Allocation policy

Firstly, we consider the heap as a space composed of different sizes of memory blocks. Each block
stores the meta information and also the data(payload). When we do `malloc`, either there 
are some available blocks and we use/split one of them to store the new data, either there 
is no space or available blocks and then we increase the size of the heap by creating a new block.
When we do `free` and the given address is not NULL, then we find the allocated block and
set it as free, and we need to merge two connect free blocks into the same.

This is one demonstration of one block. So the address of the header is actually the header of 
the block.

```
low                                             high
+++++++++++++++++++++++++++++++++++++++++++++++++++
+              |                                  +
+ header(meta) |            data(payload)         +
+              |                                  +
+++++++++++++++++++++++++++++++++++++++++++++++++++
```
In this case, several corresponding problems and my answers are listed below.

1. How to distribute/find the appropriate block?

There are multiple choices, e.g. First Fit, Best Fit, and Next Fit.
I choose *First Fit* since it is faster and we don't have to search the entire list every
time. And it is easy to implement. One of the key problems is that we need to take care of
small allocations, which is solved by splitting big blocks in my case.


2. The data structure of each header of blocks?

As we need to merge blocks, it is better that we are able to find the adjacent blocks.
So I choose to use a double-linked list to implement the header.

3. 64 bits or 32 bits?

In my case, I am using a 64bits machine, so the address is also 64 bits.
To ensure memory alignment, we should care about the size of the header and data and make
them a multiple of 8 bytes.


4. FIFO or LIFO?

when freeing or splitting blocks, we always try to keep the heap as small as possible, so 
the LIFO policy is used.

# Explanations

## Memory

This is a simplified illustration of memory management in Linux systems.

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

There are our key targets:

- It allocates a continuously available memory (from HEAP), by using syscalls to obtain memory
- The size of memory allocated is at least the given size
- It returns a pointer, pointing to the start address of the allocated memory
- If it is called multiple times, there should be no overlap among the allocated memories
- It should be executed as fast as possible

## sbrk\brk

In the heap, Linux uses a break pointer location to control the size of memory.
The memory that users could access is from the start address of the heap until the break location.
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

I use padding for the header structure to make it aligned to 8 bytes.

```
struct meta_header
{
	size_t size_;	/* data size : 8 bytes */
	int free_;	/* whether available : 4 bytes */
	int padding;	/* padding : 4 bytes */
	p_header prev;	/* pointing to previous block : 8 bytes */
	p_header next;	/* pointing to next block : 8 bytes */
	void* ptr_data;	/* pointing to data : 8 bytes */
	char data[1];	/* first byte of data : not counted in meta */
};
```

Note that, the last item is not counted as meta information, which is why the size of the meta is not exactly
the `sizeof(struct meta_header)`.

### First Fit

The policy is starting from the base location(bottom of the heap), once a free and big enough block is
found, we would take it as the allocated address for the current block. While there is one more step
to check: if *block size >=  (aligned)payload size + header size+ 8*, we split it into a perfect fit
block and a free block.

### Merge Free Blocks

In contrast with splitting, it is necessary to merge two adjacent free blocks. The policy is that 
once the user frees one block, the program would check its previous and next blocks' headers in order
and merge them if they are also free.

### Top of the heap

Once the operations meet the top of the heap, either malloc new space or free the top block, we should
always take care of the break location. Use `sbrk(increment size)` to create new space and `brk(ptr)`
to set the break location back to freed block address.













