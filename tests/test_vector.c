#include <gulc/gulc_vector.h>
#include <gulc/gulc_memory.h>
#include <gulc/gulc_verify.h>

#include <stdio.h>
#include <string.h>

char* StringDuplicate(const char* str)
{
    char* res = gulc_SafeAllocInit(sizeof(char) * (strlen(str) + 1), 0);

    size_t i = 0;
    
    while(*str != '\0')
        *(res + i++) = *str++;

    return res;
}

void StringDestructor(void* ptr)
{
    char* str = *(char**)ptr;
    printf("Destroying string: %s\n", str);
    gulc_Free(&str);
}

int main(void)
{
    const int numElements = 10;

    gulc_Vector* intVector = GULC_VECTOR_OF(int);
    gulc_Vector* stringVector = GULC_VECTOR_OF_DESTR(char*, &StringDestructor);

    for(int i = 0; i < numElements; i++)
        *(int*)gulc_VectorEmplace(&intVector) = i;
    
    GULC_VERIFY(intVector->length == numElements, "What? This value should be %d!", numElements);

    for(int i = 0; i < intVector->length; i++)
        GULC_VERIFY(GULC_VECTOR_AT(intVector, int, i) == i, "What? This value should be %d!", i);
    
    for(int i = 0; i < numElements; i++)
        gulc_VectorPopBack(&intVector);
    
    GULC_VERIFY(intVector->length == 0, "What? This value should be 0!");

    for(int i = 0; i < numElements; i++)
        *(char**)gulc_VectorEmplace(&stringVector) = StringDuplicate("Hello");
    
    GULC_VERIFY(stringVector->length == numElements, "What? This value should be %d!", numElements);
    
    for(int i = 0; i < stringVector->length; i++)
        GULC_VERIFY(strcmp(GULC_VECTOR_AT(stringVector, char*, i), "Hello") == 0, "What? This value should be 'Hello'!");

    gulc_VectorDestroy(&intVector);
    gulc_VectorDestroy(&stringVector);

    GULC_VERIFY(intVector == NULL && stringVector == NULL, "What? This value should be NULL!");

    return 0;
}