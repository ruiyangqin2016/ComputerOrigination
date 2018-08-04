/*
 * CS 2110 Summer 2018
 * Author: Ruiyang Qin
 */

/* we need this for uintptr_t */
#include <stdint.h>
/* we need this for memcpy/memset */
#include <string.h>
/* we need this to print out stuff*/
#include <stdio.h>
/* we need this for my_sbrk */
#include "my_sbrk.h"
/* we need this for the metadata_t struct and my_malloc_err enum definitions */
#include "my_malloc.h"

/* Here are a few helper methods that you may find useful to implement!
 *
 * Oh and a quick tip, while loops are your best friend for going through
 * the free lists
 */

/* Inserts a block into the size list. 
 * Make sure to handle adding to an empty size list!
 */
static void insert_size_list(metadata_t *block_to_insert);

/* Inserts a block into the address list. 
 * Make sure to handle adding to an empty address list!
 */
static void insert_address_list(metadata_t *block_to_insert);

/* Removes a block from the size list. 
 * Make sure to handle removing from the head and tail, 
 * and dont forget to null out the metadata of the removed block! 
 */
static void remove_size_list(metadata_t *block_to_remove);

/* Removes a block from the address list.  
 * Make sure to handle removing from the head and tail, 
 * and dont forget to null out the metadata of the removed block! 
 */
static void remove_address_list(metadata_t *block_to_remove);

/* Checks for merges, performing the merge if needed.
 *
 * There are multiple ways to check for merges, but here's one way:
 * Traverse through the whole address list, and check to see if each node needs
 * to merge with it's neighbor. If it does, merge and check to see if that
 * newly merged node can be merged again. If it doesn't need to merge
 * simply move on to the next node!
 */
// static void merge_helper();

/* Calculates the canary value, given the pointer to the block */
static unsigned long calculate_canary(void *ptr_to_block);

/* Sets the beginning and end canaries for the given block */
static void set_canary(metadata_t *block);

/* Declare other helper methods here. Make sure they are marked as static! */


/* Our freelist structure - our freelist is represented as two doubly linked lists
 * the address_list orders the free blocks in ascending address
 * the size_list orders the free blocks by size
 */

metadata_t *address_list;
metadata_t *size_list;

metadata_t *remain;
/* Set on every invocation of my_malloc()/my_free()/my_realloc()/
 * my_calloc() to indicate success or the type of failure. See
 * the definition of the my_malloc_err enum in my_malloc.h for details.
 * Similar to errno(3).
 */
enum my_malloc_err my_malloc_errno;

/* MALLOC
 * See my_malloc.h for documentation
 */
void *my_malloc(size_t size) {
	my_malloc_errno = NO_ERROR;
	if (size == 0) {
		return NULL;
	}
	unsigned long real_size = size + TOTAL_METADATA_SIZE;
	if (real_size > SBRK_SIZE) {
		my_malloc_errno = SINGLE_REQUEST_TOO_LARGE;
		return NULL;
	}

	// allocating the smallest chunk of memory
	if (size_list == NULL) {
		metadata_t *temp = (metadata_t *)my_sbrk(SBRK_SIZE);
		if (temp == NULL) {
		my_malloc_errno = OUT_OF_MEMORY;
		return NULL;
		}
		temp->canary = calculate_canary(temp);
		temp->size = SBRK_SIZE;
		temp->next_addr = NULL;
		temp->prev_addr = NULL;
		temp->prev_size = NULL;
		temp->next_size = NULL;
		my_malloc_errno = NO_ERROR;

		if (temp == NULL) {
			my_malloc_errno = OUT_OF_MEMORY;
			return NULL;
		}
		size_list = temp;
		address_list = temp;
	}


	metadata_t *minPtrSizeFit = NULL;
	metadata_t *minPtrSizeOver = NULL;
	metadata_t *current = size_list;
	while (current != NULL) { 
		if (current->size == real_size) {
			minPtrSizeFit = current;
			break;
		}
		if (current->size > real_size) {
			if (current->size - real_size >= MIN_BLOCK_SIZE) {
				minPtrSizeOver = current;
				break;
			}
		}
		current = current->next_size;
	}
	/*
	 * no need to split
	 */
	if (minPtrSizeFit != NULL) {
		set_canary(minPtrSizeFit);
		remove_size_list(minPtrSizeFit);
		remove_address_list(minPtrSizeFit);
		minPtrSizeFit++;
		return minPtrSizeFit;
	} else if (minPtrSizeOver != NULL) {
		if (minPtrSizeOver->next_size == NULL && minPtrSizeOver->prev_size == NULL) {
			if (minPtrSizeOver->size - real_size >= MIN_BLOCK_SIZE) {
				remain = (metadata_t *)((uintptr_t)minPtrSizeOver + (char *)(minPtrSizeOver->size - real_size));
				remain->size = real_size;
				set_canary(remain);
				minPtrSizeOver->size = minPtrSizeOver->size - real_size;
				set_canary(minPtrSizeOver);
				insert_address_list(minPtrSizeOver);
				insert_size_list(minPtrSizeOver);
				remain++;
				return remain;
			} else {
				remove_size_list(minPtrSizeOver);
				remove_address_list(minPtrSizeOver);
				minPtrSizeOver++;
				return minPtrSizeOver;
			}
		} else {
			remove_size_list(minPtrSizeOver);
			remain = (metadata_t *)((uintptr_t)minPtrSizeOver + (minPtrSizeOver -> size - real_size));
			remain -> size = real_size;
			set_canary(remain);
			minPtrSizeOver -> size = minPtrSizeOver -> size - real_size;
			set_canary(minPtrSizeOver);
			insert_size_list(minPtrSizeOver);
			remain++;
			return remain;
		}
	} else {
		metadata_t *temp = (metadata_t *)my_sbrk(SBRK_SIZE);
		if (temp == NULL) {
			my_malloc_errno = OUT_OF_MEMORY;
			return NULL;
		}
		temp->canary = calculate_canary(temp);
		temp->size = SBRK_SIZE;
		temp->next_addr = NULL;
		temp->prev_addr = NULL;
		temp->prev_size = NULL;
		temp->next_size = NULL;
		my_malloc_errno = NO_ERROR;

		if (temp == NULL) {
			my_malloc_errno = OUT_OF_MEMORY;
			return NULL;
		}
		minPtrSizeOver = temp;

		current = address_list;
		while (current != NULL) {
			if (current -> next_addr == NULL) {
				break;
			} 
			current = current -> next_addr;
		}
		if ((metadata_t *)((uintptr_t)current + current -> size) == minPtrSizeOver) {
			current -> size += minPtrSizeOver -> size;
			remove_size_list(current);
			remain = (metadata_t *)((uintptr_t)current + (current->size - real_size));
			current -> size -= real_size;
			set_canary(current);
			remain->size = real_size;
			set_canary(remain);
			remain++;
			insert_size_list(current);
			return remain;
		} else {
			remain = (metadata_t *)((uintptr_t)minPtrSizeOver + (minPtrSizeOver->size - real_size));
			remain->size = real_size;
			set_canary(remain);
			minPtrSizeOver->size = minPtrSizeOver->size - real_size;
			set_canary(minPtrSizeOver);
			insert_size_list(minPtrSizeOver);
			insert_address_list(minPtrSizeOver);
			remain++;
			return remain;
		}
	}	
}

/* FREE
 * See my_malloc.h for documentation
 */
void my_free(void *ptr) {
	// UNUSED_PARAMETER(ptr);
	my_malloc_errno = NO_ERROR;
	if (ptr == NULL) {
		return;
	}
	metadata_t *currentPtr = (metadata_t *)ptr;
	currentPtr--;
	if (currentPtr->canary != *((unsigned long *)((uint8_t *)currentPtr + currentPtr->size - sizeof(unsigned long)))) {
		my_malloc_errno = CANARY_CORRUPTED;
		return;
	}
	if (address_list != NULL) {
		metadata_t *current = address_list;
		while (current != NULL) {
			if (current -> next_addr != NULL) {

				if (current > currentPtr) {
					if ((metadata_t *)((uintptr_t)currentPtr + (char *)currentPtr->size) == current) {
						remove_address_list(current);
						remove_size_list(current);
						currentPtr -> size += current -> size;
						set_canary(currentPtr);
						insert_size_list(currentPtr);
						insert_address_list(currentPtr);
						return;
					}
					insert_address_list(currentPtr);
					insert_size_list(currentPtr);
					return;
				}

				if (current < currentPtr && current -> next_addr > currentPtr) {
					if ((metadata_t *)((uintptr_t)current + (char *)current->size) == currentPtr 
						&& (metadata_t *)((uintptr_t)currentPtr + (char *)currentPtr->size) != current -> next_addr) {
						remove_size_list(current);
						current -> size += currentPtr -> size;
						set_canary(current);
						insert_size_list(current);
						return;
					}
					if ((metadata_t *)((uintptr_t)currentPtr + (char *)currentPtr->size) == current -> next_addr 
						&& (metadata_t *)((uintptr_t)current + (char *)current->size) != currentPtr) {
						currentPtr -> size += current -> next_addr -> size;
						set_canary(currentPtr);
						remove_size_list(current -> next_addr);
						remove_address_list(current -> next_addr);
						insert_size_list(currentPtr);
						insert_address_list(currentPtr);
						return;
					}
					if (((metadata_t *)((uintptr_t)current + (char *)current->size) == currentPtr) 
						&& ((metadata_t *)((uintptr_t)currentPtr + (char *)currentPtr->size) == current -> next_addr)) {
						current -> size += (currentPtr -> size + current -> next_addr -> size);
						set_canary(current);
						remove_size_list(current -> next_addr);
						remove_address_list(current -> next_addr);
						remove_size_list(current);
						insert_size_list(current);
						return;
					} else {
						insert_address_list(currentPtr);
						insert_size_list(currentPtr);
						return;
					}
				} 
				current = current -> next_addr;
			} else {
				if (current < currentPtr) {
					remove_size_list(current);
					current -> size += currentPtr -> size;
					set_canary(current);
					insert_size_list(current);
					return;
				}
			}
		}
	} else {
		size_list = currentPtr;
		address_list = currentPtr;
	}
}

static void insert_size_list(metadata_t *block_to_insert) {
	if (size_list == NULL) { // create the first element
		size_list = block_to_insert;
	}else if (size_list == block_to_insert) {
		size_list = block_to_insert;

	} else {
		metadata_t *current = size_list;
		if (current->size >= block_to_insert->size) {
			block_to_insert -> next_size = current;
			current -> prev_size = block_to_insert;
			size_list = block_to_insert;
		} else {
			while (current->size < block_to_insert->size) {
				if (current->next_size == NULL) {
					current->next_size = block_to_insert;
					block_to_insert->prev_size = current;
					return;
				} else {
					current = current->next_size;
				}
			}
			current->prev_size->next_size = block_to_insert;
			block_to_insert->prev_size = current->prev_size;
			block_to_insert->next_size = current;
			current->prev_size = block_to_insert;
		}

	}
}

static void insert_address_list(metadata_t *block_to_insert) {
	if (address_list == NULL) { // create the first element
		address_list = block_to_insert;
	}else if (address_list == block_to_insert) {
		address_list = block_to_insert;

	} else {
		metadata_t *current = address_list;
		if (current > block_to_insert) {
			block_to_insert -> next_addr = current;
			current -> prev_addr = block_to_insert;
			address_list = block_to_insert;
		} else {
			while (current < block_to_insert) {
				if (current->next_addr == NULL) {
					current->next_addr = block_to_insert;
					block_to_insert->prev_addr = current;
					return;
				} else {
					current = current->next_addr;
				}
			}
			current->prev_addr->next_addr = block_to_insert;
			block_to_insert->prev_addr = current->prev_addr;
			block_to_insert->next_addr = current;
			current->prev_addr = block_to_insert;
		}
	}
}

static void remove_size_list(metadata_t *block_to_remove) {
	if (size_list == NULL) {
		return;
	} else {
		metadata_t *current = block_to_remove;
		if (block_to_remove == size_list) {
			current = current -> next_size;
			if (block_to_remove -> next_size != NULL) {
				block_to_remove -> next_size -> prev_size = NULL;
				block_to_remove -> next_size = NULL;
			}
			size_list = current;
			return;
		}
		if (block_to_remove->prev_size == NULL && block_to_remove->next_size != NULL) {
			block_to_remove->next_size->prev_size = NULL;
			block_to_remove->next_size = NULL;
			return;
		}
		if (block_to_remove->next_size == NULL && block_to_remove->prev_size != NULL) {
			block_to_remove->prev_size->next_size = NULL;
			block_to_remove->prev_size = NULL;
			return;
		}
		if (block_to_remove->next_size != NULL && block_to_remove->prev_size != NULL) {
			block_to_remove->prev_size->next_size = block_to_remove->next_size;
			block_to_remove->next_size->prev_size = block_to_remove->prev_size;
			block_to_remove->prev_size = NULL;
			block_to_remove->next_size = NULL;
			return;
		}
	}
}

static void remove_address_list(metadata_t *block_to_remove) {
	if (address_list == NULL) {
		return;
	} else {
		metadata_t *current = block_to_remove;
		if (block_to_remove == address_list) {
			current = current -> next_addr;
			if (block_to_remove -> next_addr != NULL) {
				block_to_remove -> next_addr -> prev_addr = NULL;
				block_to_remove -> next_addr = NULL;
			}
			address_list = current;
			return;
		} 
		if (current->prev_addr == NULL && current->next_addr != NULL) {
			current -> next_addr -> prev_addr = NULL;
			current -> next_addr = NULL;
			return;
		} 
		if (current->next_addr == NULL && current->prev_addr != NULL) {
			current -> prev_addr -> next_addr = NULL;
			current -> prev_addr = NULL;
			return;
		} 
		if (current->next_addr != NULL && current->prev_addr != NULL) {
			current -> prev_addr->next_addr = current -> next_addr;
			current -> next_addr->prev_addr = current -> prev_addr;
			current -> next_addr = NULL;
			current -> prev_addr = NULL;
			return;
		}
	}
}

static unsigned long calculate_canary(void *ptr_to_block) {
	unsigned long canary = ((uintptr_t)ptr_to_block ^ CANARY_MAGIC_NUMBER) + 1;
	return canary;
}

static void set_canary(metadata_t *block) {
	unsigned long c = calculate_canary(block);
	block->canary = c;
	*((unsigned long *)((uint8_t *)block + block->size - sizeof(unsigned long))) = c;
}