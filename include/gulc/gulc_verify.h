#ifndef GULC_VERIFY_H__
#define GULC_VERIFY_H__

#include "gulc/gulc_common.h"

GULC_EXTERN_C_BEGIN

GULC_FN_DECLARE(void, Verify, int expr, const char* exprStr, const char* msg, ...)

/**
 * @brief Verify that an expression is true. Works similary to assert but
 * doesn't print the file (and line) where the assertion failed.
 * Also allows you to print custom error messages with printf-like formatting.
 * 
 * @param expr expression to verify
 * @param ... formatted message and (optional) arguments to print
 * @note It outputs the error message to stderr
 */
#define GULC_VERIFY(expr, ...) GULC_PREFIX(Verify)(expr, #expr, __VA_ARGS__)

GULC_EXTERN_C_END

#endif // !GULC_VERIFY_H__