#ifndef GULC_MEMORY_H__
#define GULC_MEMORY_H__

#include "gulc/gulc_common.h"

GULC_EXTERN_C_BEGIN

/**
 * @brief Allocates memory and verifies that it was successful
 * 
 * @param size size of the memory to allocate (in bytes)
 * @return void* pointer to the allocated memory
 */
GULC_FN_DECLARE(void*, SafeAlloc, size_t size)

/**
 * @brief Allocates memory, verifies that it was successful and initializes it with a value
 * 
 * @param size size of the memory to allocate (in bytes)
 * @param value value to initialize the memory with
 * @return void* pointer to the allocated memory
 */
GULC_FN_DECLARE(void*, SafeAllocInit, size_t size, uint8_t value)

/**
 * @brief Reallocates memory and verifies that it was successful
 * 
 * @param ptr pointer to the memory to reallocate
 * @param newSize new size of the memory (in bytes)
 * @return void* pointer to the reallocated memory
 */
GULC_FN_DECLARE(void*, SafeRealloc, void* ptr, size_t newSize)

/**
 * @brief Frees memory and sets the pointer to NULL
 * 
 * @param ptr pointer to the previously allocated memory to free (Expected to be a pointer to a pointer)
 */
GULC_FN_DECLARE(void, Free, void* ptr)

/**
 * @brief Swaps the values of two memory regions
 * This is just the underlying implementation of the `GULC_SWAP` macro
 * 
 * @param a pointer to the first memory region
 * @param b pointer to the second memory region
 * @param size size of the memory regions
 */
GULC_FN_DECLARE(void, Swap, void* a, void* b, size_t size)

/**
 * @brief Copies memory from one location to another
 * If the sizes don't match, the smaller one will be used
 * 
 * @param src pointer to the source memory region
 * @param srcSize size of the source memory region (in bytes)
 * @param dst pointer to the destination memory region
 * @param dstSize size of the destination memory region (in bytes)
 */
GULC_FN_DECLARE(void, CopyMemory, const void* src, size_t srcSize, void* dst, size_t dstSize)

/**
 * @brief Swaps the values of two variables
 * If the sizes don't match, the smaller one will be used
 * 
 * @param a first variable
 * @param b second variable
 */
#define GULC_SWAP(a, b) GULC_NAME(Swap)(&a, &b, (sizeof(a) > sizeof(b) ? sizeof(b) : sizeof(a)))

/**
 * @brief Copies memory from one location to another (same size)
 * If you want to have more control over the sizes, use `CopyMemory` instead
 * 
 * @param src pointer to the source memory region
 * @param dst pointer to the destination memory region
 * @param size size of the memory regions (in bytes)
 */
#define GULC_MEM_ASSIGN(dst, src, size) GULC_NAME(CopyMemory)(src, size, dst, size)

GULC_EXTERN_C_END

#endif // !GULC_MEMORY_H__