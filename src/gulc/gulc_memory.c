#include "gulc/gulc_memory.h"
#include "gulc/gulc_verify.h"

#include <stdlib.h>
#include <string.h>

/**
 * @brief Safe memory related functions (basically safe wrappers for `malloc`, `realloc` and `free`)
 */

GULC_FN_IMPL(void*, SafeAlloc, size_t size)
{
    void* ptr = malloc(size);
    GULC_VERIFY(ptr != NULL, "Memory allocation failed!");
    return ptr;
}

GULC_FN_IMPL(void*, SafeAllocInit, size_t size, uint8_t value)
{
    void* ptr = GULC_NAME(SafeAlloc)(size);
    memset(ptr, value, size);
    return ptr;
}

GULC_FN_IMPL(void*, SafeRealloc, void* ptr, size_t newSize)
{
    void* newPtr = realloc(ptr, newSize);

    if(newPtr == NULL)
    {
        /**
         * this will not set the pointer in the calling function to NULL
         * but later verify will fail so its safe to do this
         */
        GULC_NAME(Free)(&ptr);
        /**
         * here we use newPtr != NULL instead of false for error logging purposes
         */
        GULC_VERIFY(newPtr != NULL, "Memory reallocation failed!");
    }

    return newPtr;
}

GULC_FN_IMPL(void, Free, void* ptr)
{
    if(ptr != NULL)
    {
        void** ptrP = (void**)ptr;
        free(*ptrP);
        *ptrP = NULL;
    }
}

GULC_FN_IMPL(void, Swap, void* a, void* b, size_t size)
{
    if(a == NULL || b == NULL || a == b || size == 0)
        return;

    uint8_t* aP = (uint8_t*)a;
    uint8_t* bP = (uint8_t*)b;
    uint8_t temp;

    while(size > 0)
    {
        temp = *aP;
        *aP = *bP;
        *bP = temp;

        ++aP, ++bP;
        --size;
    }
}

GULC_FN_IMPL(void, CopyMemory, const void* src, size_t srcSize, void* dst, size_t dstSize)
{
    if(src == NULL || srcSize == 0 || dst == NULL || dstSize == 0 || src == dst)
        return;
    
    uint8_t* srcP = (uint8_t*)src;
    uint8_t* dstP = (uint8_t*)dst;
    size_t copySize = (srcSize < dstSize) ? srcSize : dstSize;

    while(copySize > 0)
    {
        *dstP++ = *srcP++;
        --copySize;
    }
}