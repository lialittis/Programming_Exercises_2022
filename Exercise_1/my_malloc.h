#ifndef __MY_MALLOC_H__
#define __MY_MALLOC_H__

#include <sys/types.h>
#include <unistd.h>

#define ALIGNMENT 8				// could also be 4
#define META_SIZE (sizeof(struct meta_header)-ALIGNMENT)	// meta header size in each memory block

#define ALIGN(size) ((size + (ALIGNMENT-1)) & ~(ALIGNMENT-1))

typedef struct meta_header* p_header;

/**
 * meta header of each memory block
 * 
 * It is a structure of double linked list and contains meta information and data pointer
 */
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

/**
 * Malloc function
 *
 * @param size Data size
 * @return Pointer of data
 */
void* my_malloc(size_t size);

/**
 * Free function
 *
 * @param ptr Address to release
 */
void my_free(void* ptr);

#endif // __MY_MALLOC_H__

