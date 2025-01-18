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
    void* ptr = gulc_SafeAlloc(size);
    memset(ptr, value, size);
    return ptr;
}

GULC_FN_IMPL(void*, SafeRealloc, void* ptr, size_t newSize)
{
    GULC_VERIFY(ptr != NULL, "Memory reallocation failed (passed pointer is NULL)!");

    void* newPtr = realloc(ptr, newSize);

    if(newPtr == NULL)
    {
        /**
         * this will not set the pointer in the calling function to NULL
         * but later verify will fail so its safe to do this
         */
        gulc_Free(&ptr);
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