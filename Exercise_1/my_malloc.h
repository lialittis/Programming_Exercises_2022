#ifndef __MY_MALLOC_H__
#define __MY_MALLOC_H__

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

#define ALIGNMENT 8				// could also be 4
#define META_SIZE sizeof(struct meta_header)	// meta header size in each memory block

#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~(ALIGNMENT-1))

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
	void* data;	/* pointing to data : 8 bytes */
};

p_header g_bot = NULL; // the global bottom pointer of heap <=> the base location


static inline p_header get_header(void* ptr_data){
	p_header ptr_header = (p_header)ptr_data - META_SIZE;
	return ptr_header;
}

/**
 * Find fit block (First Fit)
 * 
 * It uses First Fit to find a approprate block for new data
 * @param prev Pointer of previous block
 * @param size Data size
 * @return Pointer of found block
 */
p_header find_fit(p_header* prev, size_t size){
	p_header temp = g_bot; // start from g_bot
	while(temp) {
		if(temp->free_ && temp->size_ > size ) break;
		*prev = temp;
		temp = temp->next;
	}
	return temp;
}

/**
 * Split block
 *
 * It split the given block into two parts, with the given size data fitting into first part
 * @param parent_blk Pointer of the block to split
 * @param size Data size
 */
void split_block(p_header parent_blk, size_t size){
	if(!parent_blk) return;
	p_header child_blk;
	child_blk = (p_header)parent_blk->data + size; // new block, pointing to the free address after allocating
	child_blk->size_ = parent_blk->size_ - size - META_SIZE;
	child_blk->free_ = 1;
	child_blk->next = parent_blk->next;
	parent_blk->next->prev = child_blk;
	child_blk->prev = parent_blk;
	parent_blk->size_ = size;
	parent_blk->next = child_blk;
}

/**
 * Expand heap size
 *
 * It construct new block on the top of the current heap,
 * by sbrk increasing the break location
 * @param prev Pointer of previous block
 * @param size Data size
 * @return Pointer of found block
 */
p_header extend_heap(p_header prev, size_t size){
	p_header temp;
	temp = (p_header)sbrk(0); // get current break location
	if(sbrk(META_SIZE + size) == (void*)-1) // sbrk fails to increase break location
		return NULL;
	temp->prev = temp;
	temp->next = NULL;
	temp->size_ = size;
	temp->free_ = 0;
	temp->data = temp + META_SIZE;
	if(prev)
		prev->next = temp;
	return temp;
}


/**
 * Valid address in heap
 *
 * @param ptr Address of data to release
 * @return int Whether the address is valid
 */
int is_valid(void* ptr){
	if(g_bot && ptr){
		if((p_header)ptr > g_bot && ptr < sbrk(0) ){
			/* get header from data address */
			return ptr == (get_header(ptr))->data;
		}
	}
	return 0;
}

/**
 * Merge current and next one
 *
 * It merge two free blocks(acctually the headers), the current one and the next one
 * @param blk Current block
 * @return p_header Merged block
 */
p_header merge(p_header blk){
	if(blk->free_ && blk->next && blk->next->free_){
		p_header nxt = blk->next;
		blk->size_ += META_SIZE + nxt->size_;
		blk->next = nxt->next;
		if(blk->next)
			blk->next->prev = blk;
	}
	return blk;
}

/**
 * Malloc function
 *
 * @param size Data size
 * @return Pointer of data
 */
void* my_malloc(size_t size)
{
	p_header blk;
	size_t align_size = ALIGN(ALIGNMENT);
	// 1.check if the global bottom/base of heap is null
	if(g_bot){ // there are blocks existed
		p_header prev = g_bot;
		// 2. check if there is a available block
		if((blk = find_fit(&prev, align_size))){
			if(blk->size_ >= align_size + META_SIZE + 8) // condition to split the block
				split_block(blk,align_size);
			blk->free_ = 0;
		}else{ // apply a new memory
			blk = extend_heap(g_bot,align_size);
			if(!blk) return NULL; // fail
		}

	}else{ // apply a new memory
		blk = extend_heap(g_bot,align_size);
		if(!blk) return NULL; // fail
		g_bot = blk;
		printf("g_bot:%p\n",g_bot);
		printf("blk:%p\n",blk);
		printf("blk->data:%p\n",blk->data);
	}

	return blk + META_SIZE;
}

/**
 * Free function
 *
 * @param ptr Address to release
 */
void my_free(void* ptr){
	// 1. check the validation of the given address
	if(is_valid(ptr)){
		/* 2. find the current block, and set it as free*/
		p_header blk = get_header(ptr);
		blk->free_ = 1;
		
		/* 3. merge the adjacent free blocks */
		if(blk->prev && blk->prev->free_) // merge previous block
			blk = merge(blk->prev);
		
		if(blk->next) // try to merge next block
			blk = merge(blk);
		else{ // the block is the last block, the we reduce the heap size
			if(blk->prev)
				blk->prev->next = NULL; // reset the previous block
			else
				g_bot = NULL; // reset g_bot
			// 4. set the break location as blk
			brk(blk);
			// TODO : free has segmentation fault
			//printf("free %p successfully!\n",blk);
		}
	}	
}

#endif // __MY_MALLOC_H__
