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
 * Short hand for `GULC_PREFIX(name)`
*/
#ifndef GULC_NAME
#define GULC_NAME(name) GULC_PREFIX(name)
#endif // !GULC_NAME

/**
 * Helper macros for declaring and defining functions
 * 
 * @param ret return type
 * @param name function name
 * @param ... function parameters
 */
#ifndef GULC_FN_DECLARE
#define GULC_FN_DECLARE(ret, name, ...) GULC_API ret GULC_NAME(name)(__VA_ARGS__);
#endif // !GULC_FN_DECLARE

#ifndef GULC_FN_IMPL
#define GULC_FN_IMPL(ret, name, ...) ret GULC_NAME(name)(__VA_ARGS__)
#endif // !GULC_FN_IMPL

/**
 * Helper macro for typdeffing types (simple typedefs)
 * Use GULC_PTR_FN_DECLARE instead if you want to type a pointer to function type
*/
#ifndef GULC_TYPE_DECLARE
#define GULC_TYPE_DECLARE(name, type) typedef type GULC_NAME(name);
#endif // !GULC_TYPE_DECLARE

/**
 * Helper macro for typedeffing pointers to function types
 */
#ifndef GULC_PTR_FN_DECLARE
#define GULC_PTR_FN_DECLARE(name, ret, ...) typedef ret (*GULC_NAME(name))(__VA_ARGS__);
#endif // !GULC_PTR_FN_DECLARE

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