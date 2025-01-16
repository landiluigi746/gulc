#ifndef GULC_MEMORY_H__
#define GULC_MEMORY_H__

#include "gulc/gulc_common.h"

GULC_FN_DECLARE(void*, SafeAlloc, size_t size)
GULC_FN_DECLARE(void*, SafeRealloc, void* ptr, size_t newSize)
GULC_FN_DECLARE(void, Free, void* ptr)

#endif // !GULC_MEMORY_H__