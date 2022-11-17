# Requirements

Implement two (malloc and free) library calls using the sbrk syscall and implement 
a simple allocation policy to do thread-safe allocation and free. Please also write 
a short paragraph explaining the policy you implemented, and how it works.


# Allocation policy

Firstly, we consider the heap composed of different size of memory blocks. Each block
store the meta information and also the data. When we do `malloc`, either there are some
available blocks and we use/split one of them to store the new data, either there is
no space or available blocks and then we increase the size of heap by creating new block.
When we do `free` and the given address is not NULL, then we find the allocated block and
set it as free, and we need to merge two connect free blocks into the same.

In this case, there are several problems that we need to solve.

1. How to distribute/find the approprate block?

First Fit or Best Fit ?

Here I choose the First Fit, which has lower overhead.

2. The data structure of each block ?

As we need to merge blocks, it is better that we are able to find the adjacent blocks.
So I choose to use double linked list to implement the block.

3. The Page size ?

4. Segmentations ?


You could find some detailed explanations in the next section [#Explanations](here).

# Explanations

I am going to solve this challenge in C and show how it works in the following sections.

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

- It allocates a continuous available memory (from HEAP), by using syscalls to obtain memory.
- The size of memory allocated is at least the given size
- It returns a pointer, pointing to the start address of the allocated memory
- If it is called multiple times, there should be no overlap among the allocated memories
- `realloc` and `free`
- as fast as possible

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


Firstly, we need to define a struct to contain the memory information allocated by `malloc`,
it is not exactly the given size. We need a double linked list to simulate it.











