#ifndef GULC_MEMORY_H__
#define GULC_MEMORY_H__

#include "gulc/gulc_common.h"

GULC_EXTERN_C_BEGIN

GULC_FN_DECLARE(void*, SafeAlloc, size_t size)
GULC_FN_DECLARE(void*, SafeAllocInit, size_t size, uint8_t value);
GULC_FN_DECLARE(void*, SafeRealloc, void* ptr, size_t newSize)
GULC_FN_DECLARE(void, Free, void* ptr)

GULC_FN_DECLARE(void, Swap, void* a, void* b, size_t size)

GULC_EXTERN_C_END

#endif // !GULC_MEMORY_H__