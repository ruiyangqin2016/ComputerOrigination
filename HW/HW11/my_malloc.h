#ifndef __MY_MALLOC_H__
#define __MY_MALLOC_H__

/* DO NOT MODIFY THIS FILE!
   Keep your changes in my_malloc.c.

   Any helper functions you add to my_malloc.c must be static, so if you
   write prototypes for them, those (static) prototypes should go in
   my_malloc.c as well. */

/* we need this for the size_t typedef */
#include <stddef.h>
/* we need this for the uint8_t typedef */
#include <stdint.h>

/* You *MUST* use this macro when calling my_sbrk to allocate the
 * appropriate size. Failure to do so may result in an incorrect
 * grading!
 */
#define SBRK_SIZE 2048

/* This is the size of the metadata struct and canary footer in bytes */
#define TOTAL_METADATA_SIZE (sizeof(metadata_t) + sizeof(unsigned long))

/* This is the minimum size of a block in bytes, where it can
 * store the metadata, canary footer, and at least 1 byte of data
 */
#define MIN_BLOCK_SIZE (TOTAL_METADATA_SIZE + 1)

/* Used in canary calcuations. See the "Block Allocation" section of the
 * homework PDF for details.
 */
#define CANARY_MAGIC_NUMBER 0xE629

/* Feel free to delete all uses of this once you've implemented all
 * the functions */
#define UNUSED_PARAMETER(param) (void)(param)

/* Our metadata structure for use in the freelist.
 * you *MUST NOT* change this definition unless specified
 * in an official assignment update by the TAs.
 */
typedef struct metadata {
    struct metadata *prev_addr;
    struct metadata *next_addr;
    struct metadata *prev_size;
    struct metadata *next_size;
    unsigned long size; // size of the whole block in number of bytes
    unsigned long canary;
} metadata_t;

/* This is your error enum. The three
 * different types of errors for this homework are explained below.
 * If ANY function has a case where one of the errors described could
 * occur, it must set ERRNO to the appropriate enum.
 * In the case where a single request is too large and
 * the request results in an out of memory error as well, the
 * SINGLE_REQUEST_TOO_LARGE should take precedence. If any of the three
 * functions complete successfully, the error code should be set to
 * NO_ERROR. */
enum my_malloc_err {
    NO_ERROR,
    OUT_OF_MEMORY,
    SINGLE_REQUEST_TOO_LARGE,
    CANARY_CORRUPTED
};

extern enum my_malloc_err my_malloc_errno;

/* MALLOC
 *
 * this function should allocate a block that is big enough to hold the
 * specified size (bytes), and that is all. if there is not a block that is
 * able to satisfy the request, then you should attempt to grab more heap space
 * with a call to my_sbrk. if this succeeds, then you should continue as
 * normal. If it fails (by returning NULL), then you should return NULL.
 */
void *my_malloc(size_t size);

/* FREE
 *
 * this function should free the block of memory, merging it with the block in
 * memory to its right and left if possible. If ptr is NULL, no operation is
 * performed.
 */
void my_free(void *ptr);

#endif /* __MY_MALLOC_H__ */
