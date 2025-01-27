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
    gulc_Vector* floatVector = GULC_VECTOR_OF_SIZED(float, numElements);

    GULC_VERIFY(intVector->length == 0 && stringVector->length == 0 && floatVector->length == 0, "What? These values should be 0!");
    GULC_VERIFY(intVector->capacity == 0 && stringVector->capacity == 0 && floatVector->capacity == numElements, "What? These values should be 0, 0 and %d!", numElements);

    // Int vector
    for(int i = 0; i < numElements; i++)
        *(int*)gulc_VectorEmplaceBack(&intVector) = i;
    
    GULC_VERIFY(intVector->length == numElements, "What? This value should be %d!", numElements);

    for(int i = 0; i < intVector->length; i++)
        GULC_VERIFY(GULC_VECTOR_AT(intVector, int, i) == i, "What? This value should be %d!", i);
    
    for(int i = 0; i < numElements; i++)
        gulc_VectorPopBack(&intVector);
    
    GULC_VERIFY(intVector->length == 0, "What? This value should be 0!");

    // String vector
    for(int i = 0; i < numElements; i++)
        *(char**)gulc_VectorEmplaceBack(&stringVector) = StringDuplicate("Hello");
    
    GULC_VERIFY(stringVector->length == numElements, "What? This value should be %d!", numElements);
    
    for(int i = 0; i < stringVector->length; i++)
        GULC_VERIFY(strcmp(GULC_VECTOR_AT(stringVector, char*, i), "Hello") == 0, "What? This value should be 'Hello'!");

    // Float vector
    for(int i = 0; i < numElements; i++)
        *(float*)gulc_VectorEmplaceBack(&floatVector) = (float)i * 0.5f;
    
    *(float*)gulc_VectorEmplace(&floatVector, 0) = 0.5f;

    GULC_VERIFY(floatVector->length == numElements + 1, "What? This value should be %d!", numElements + 1);

    GULC_VERIFY(GULC_VECTOR_AT(floatVector, float, 0) == 0.5f, "What? This value should be 0.5f!");

    for(int i = 1; i < floatVector->length; i++)
        GULC_VERIFY(GULC_VECTOR_AT(floatVector, float, i) == (float)(i - 1) * 0.5f, "What? This value should be %f!", (float)i * 0.5f);
    
    gulc_VectorErase(&floatVector, 0);
    gulc_VectorErase(&floatVector, floatVector->length - 1);

    GULC_VERIFY(floatVector->length == numElements - 1, "What? This value should be %d!", numElements);

    for(int i = 0; i < floatVector->length; i++)
        GULC_VERIFY(GULC_VECTOR_AT(floatVector, float, i) == (float)i * 0.5f, "What? This value should be %f!", (float)i * 0.5f);

    gulc_VectorDestroy(&intVector);
    gulc_VectorDestroy(&stringVector);
    gulc_VectorDestroy(&floatVector);

    GULC_VERIFY(intVector == NULL && stringVector == NULL, "What? This value should be NULL!");

    return 0;
}