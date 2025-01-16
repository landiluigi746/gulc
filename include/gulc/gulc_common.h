#ifndef GULC_COMMON_H__
#define GULC_COMMON_H__

#ifndef GULC_API
#define GULC_API // extern implicit by default
#endif // !GULC_API

#ifdef GULC_NO_PREFIX
#define GULC_PREFIX(x) x
#else
#define GULC_PREFIX(x) gulc_ ##x
#endif // GULC_NO_PREFIX

#ifndef GULC_FN_DECLARE
#define GULC_FN_DECLARE(ret, name, ...) GULC_API ret GULC_PREFIX(name)(__VA_ARGS__);
#endif // !GULC_FN_DECLARE

#ifndef GULC_FN_IMPL
#define GULC_FN_IMPL(ret, name, ...) ret GULC_PREFIX(name)(__VA_ARGS__)
#endif // !GULC_FN_IMPL

#ifdef __cplusplus
#define GULC_EXTERN_C_BEGIN extern "C" {
#define GULC_EXTERN_C_END }
#else
#define GULC_EXTERN_C_BEGIN
#define GULC_EXTERN_C_END
#endif // __cplusplus

#include <stdint.h>
#include <stddef.h>

#endif // !GULC_COMMON_H__