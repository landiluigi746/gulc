#include <gulc/gulc_memory.h>
#include <gulc/gulc_verify.h>

#include <stdio.h>

int main(void)
{
    int* data = (int*) gulc_SafeAlloc(sizeof(int));

    *data = 255;
    printf("value stored at data (%p): %d\n", data, *data);

    data = gulc_SafeRealloc(data, 1);
    printf("value stored at data (%p): %d\n", data, *data);

    gulc_Free(data);

    int* data2 = (int*) gulc_SafeAllocInit(sizeof(int), 0);
    printf("value stored at data2 (%p): %d\n", data2, *data2);

    gulc_Free(data2);

    int a = 3;
    int b = 5;

    GULC_SWAP(a, b);
    GULC_VERIFY(a == 5 && b == 3, "Swap failed!");

    int* aP = &a;
    int* bP = &b;

    GULC_SWAP(aP, bP);
    GULC_VERIFY(aP == &b && bP == &a, "Swap failed!");
    GULC_SWAP(aP, bP);
    GULC_VERIFY(aP == &a && bP == &b, "Swap failed!");

    return 0;
}