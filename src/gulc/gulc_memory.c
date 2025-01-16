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
    void* newPtr = realloc(ptr, newSize);
    GULC_VERIFY(newPtr != NULL, "Memory reallocation failed!");
    return newPtr;
}

GULC_FN_IMPL(void, Free, void* ptr)
{
    free(ptr);
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