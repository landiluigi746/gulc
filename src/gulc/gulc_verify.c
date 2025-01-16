#include "gulc/gulc_verify.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

GULC_FN_IMPL(void, Verify, int expr, const char* exprStr, const char* msg, ...)
{
    if(!expr)
    {
        va_list args;
        va_start(args, msg);

        fprintf(stderr, "Test failed (%s)!\nError message: ", exprStr);
        vfprintf(stderr, msg, args);

        va_end(args);
        
        getchar();
        abort();
    }
}