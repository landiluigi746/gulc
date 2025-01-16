#include "gulc/gulc_memory.h"
#include "gulc/gulc_verify.h"

#include <stdlib.h>

GULC_FN_IMPL(void*, SafeAlloc, size_t size)
{
    void* ptr = malloc(size);
    GULC_VERIFY(ptr != NULL, "Memory allocation failed!");
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