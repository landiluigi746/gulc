#ifndef GULC_COMMON_H__
#define GULC_COMMON_H__

#ifndef GULC_API
#define GULC_API // extern implicit by default
#endif // !GULC_API

/**
 * gulc tries to emulate C++'s namespace system by using prepocessor macros.
 * This means that everything in the library is prefixed with `gulc_` unless
 * `GULC_NO_PREFIX` is defined.
 */
#ifdef GULC_NO_PREFIX
#define GULC_PREFIX(x) x
#else
#define GULC_PREFIX(x) gulc_ ##x
#endif // GULC_NO_PREFIX

/**
 * Helper macros for declaring and defining functions
 * 
 * @param ret return type
 * @param name function name
 * @param ... function parameters
 */
#ifndef GULC_FN_DECLARE
#define GULC_FN_DECLARE(ret, name, ...) GULC_API ret GULC_PREFIX(name)(__VA_ARGS__);
#endif // !GULC_FN_DECLARE

#ifndef GULC_FN_IMPL
#define GULC_FN_IMPL(ret, name, ...) ret GULC_PREFIX(name)(__VA_ARGS__)
#endif // !GULC_FN_IMPL

/**
 * Helper macros for declaring gulc functions with extern "C" linkage in C++
 */
#ifdef __cplusplus
#define GULC_EXTERN_C_BEGIN extern "C" {
#define GULC_EXTERN_C_END }
#else
#define GULC_EXTERN_C_BEGIN
#define GULC_EXTERN_C_END
#endif // __cplusplus

GULC_EXTERN_C_BEGIN

#include <stdint.h>
#include <stddef.h>

GULC_EXTERN_C_END

#endif // !GULC_COMMON_H__