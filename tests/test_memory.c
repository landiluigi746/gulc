#include <gulc/gulc_memory.h>

#include <stdio.h>

int main(void)
{
    int* data = (int*) gulc_SafeAlloc(sizeof(int));

    *data = 255;
    printf("value stored at data (%p): %d\n", data, *data);

    data = gulc_SafeRealloc(data, 1);
    printf("value stored at data (%p): %d\n", data, *data);

    gulc_Free(data);

    return 0;
}