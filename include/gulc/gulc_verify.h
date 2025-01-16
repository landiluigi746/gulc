#ifndef GULC_VERIFY_H__
#define GULC_VERIFY_H__

#include "gulc/gulc_common.h"

GULC_FN_DECLARE(void, Verify, int expr, const char* exprStr, const char* msg, ...)

#define GULC_VERIFY(expr, ...) GULC_PREFIX(Verify)(expr, #expr, __VA_ARGS__)

#endif // !GULC_VERIFY_H__