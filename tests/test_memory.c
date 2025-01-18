#include <gulc/gulc_memory.h>
#include <gulc/gulc_verify.h>

#include <stdio.h>

int main(void)
{
    int* data = (int*) gulc_SafeAlloc(sizeof(int));

    *data = 255;
    GULC_VERIFY(*data == 255, "What? This value should be 255!");

    data = gulc_SafeRealloc(data, sizeof(int) * 2);
    GULC_VERIFY(*data == 255, "What? This value should be 255!");

    gulc_Free(&data);

    int* data2 = (int*) gulc_SafeAllocInit(sizeof(int), 0);
    GULC_VERIFY(*data2 == 0, "What? This value should be 0!");

    gulc_Free(&data2);

    GULC_VERIFY(data == NULL && data2 == NULL, "These pointers should be NULL!");

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