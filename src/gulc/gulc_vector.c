#include "gulc/gulc_vector.h"
#include "gulc/gulc_memory.h"
#include "gulc/gulc_verify.h"

typedef struct
{
    size_t elementSize;
    gulc_TypeVectorElemDestr elementDestructor;
    size_t length;
    size_t capacity;
    uint8_t data[];
} gulc_VectorImpl;

#define TO_GULC_VECTOR_IMPL(vec) ((gulc_VectorImpl*)((vec) + 1) - 1)
#define TO_GULC_VECTOR(vec) ((gulc_TypeVector*)((vec) + 1) - 1)
#define VECTOR_IMPL_AT(vec, i) ((vec)->data + (vec)->elementSize * (i))

static void VectorGrow(gulc_VectorImpl** vector)
{
    (*vector)->capacity = ((*vector)->capacity == 0) ? 1 : (*vector)->capacity * 2;
    *vector = GULC_NAME(SafeRealloc)(*vector, sizeof(**vector) + (*vector)->elementSize * (*vector)->capacity);
}

GULC_FN_IMPL(gulc_TypeVector*, VectorCreate, size_t elementSize, size_t capacity, gulc_TypeVectorElemDestr elementDestructor)
{
    GULC_VERIFY(elementSize != 0, "A vector's element size can't be 0!");

    gulc_VectorImpl* vector = GULC_NAME(SafeAlloc)(sizeof(*vector) + elementSize * capacity);

    vector->elementSize = elementSize;
    vector->elementDestructor = elementDestructor;
    vector->length = 0;
    vector->capacity = capacity;

    return TO_GULC_VECTOR(vector);
}

GULC_FN_IMPL(void, VectorDestroy, gulc_TypeVector** vectorP)
{
    if(vectorP == NULL || *vectorP == NULL)
        return;
    
    gulc_VectorImpl* vec = TO_GULC_VECTOR_IMPL(*vectorP);
    
    GULC_NAME(VectorClear)(vectorP);

    GULC_NAME(Free)(&vec);
    *vectorP = NULL;
}


GULC_FN_IMPL(void*, VectorEmplaceBack, gulc_TypeVector** vectorP)
{
    GULC_VERIFY(vectorP != NULL && *vectorP != NULL, "Can't push on a null vector");
    
    gulc_VectorImpl* vec = TO_GULC_VECTOR_IMPL(*vectorP);

    if(vec->length == vec->capacity)
    {
        VectorGrow(&vec);
        *vectorP = TO_GULC_VECTOR(vec);
    }

    return VECTOR_IMPL_AT(vec, (vec->length)++);
}

GULC_FN_IMPL(void, VectorPopBack, gulc_TypeVector** vectorP)
{
    GULC_VERIFY(vectorP != NULL && *vectorP != NULL, "Can't pop from a null vector");

    gulc_VectorImpl* vec = TO_GULC_VECTOR_IMPL(*vectorP);

    if(vec->length > 0)
    {
        --(vec->length);
        if(vec->elementDestructor != NULL)
            vec->elementDestructor(VECTOR_IMPL_AT(vec, vec->length));
    }
}

GULC_FN_IMPL(void*, VectorEmplace, gulc_TypeVector** vectorP, size_t index)
{
    GULC_VERIFY(vectorP != NULL && *vectorP != NULL, "Can't pop from a null vector");

    gulc_VectorImpl* vec = TO_GULC_VECTOR_IMPL(*vectorP);

    if(vec->length == vec->capacity)
    {
        VectorGrow(&vec);
        *vectorP = TO_GULC_VECTOR(vec);
    }

    size_t i;

    for(i = vec->length; i > 0; --i)
        GULC_MEM_ASSIGN(VECTOR_IMPL_AT(vec, i), VECTOR_IMPL_AT(vec, (i - 1)), vec->elementSize);
    
    ++(vec->length);
    return VECTOR_IMPL_AT(vec, i);
}

GULC_FN_IMPL(void, VectorErase, gulc_TypeVector** vectorP, size_t index)
{
    GULC_VERIFY(vectorP != NULL && *vectorP != NULL, "Can't pop from a null vector");

    gulc_VectorImpl* vec = TO_GULC_VECTOR_IMPL(*vectorP);

    GULC_VERIFY(index < vec->length, "Can't erase an element out of bounds of a vector");

    if(vec->length > 0)
    {
        for(size_t i = index; i < vec->length; ++i)
            GULC_MEM_ASSIGN(VECTOR_IMPL_AT(vec, i), VECTOR_IMPL_AT(vec, (i + 1)), vec->elementSize);
        
        --(vec->length);
    }
}

GULC_FN_IMPL(void, VectorResize, gulc_TypeVector** vectorP, size_t newSize)
{
    GULC_VERIFY(vectorP != NULL && *vectorP != NULL, "Can't resize a null vector");

    gulc_VectorImpl* vec = TO_GULC_VECTOR_IMPL(*vectorP);

    if(newSize < vec->length)
    {
        if(vec->elementDestructor != NULL)
        {
            for(size_t i = newSize; i < vec->length; ++i)
                vec->elementDestructor(VECTOR_IMPL_AT(vec, i));
        }

        vec->length = newSize;
    }

    if(newSize != vec->capacity)
    {
        vec->capacity = newSize;
        vec = GULC_NAME(SafeRealloc)(vec, sizeof(*vec) + newSize * vec->elementSize);
        *vectorP = TO_GULC_VECTOR(vec);
    }
}

GULC_FN_IMPL(void, VectorClear, gulc_TypeVector** vectorP)
{
    GULC_VERIFY(vectorP != NULL && *vectorP != NULL, "Can't pop from a null vector");

    gulc_VectorImpl* vec = TO_GULC_VECTOR_IMPL(*vectorP);

    if(vec->elementDestructor != NULL)
    {
        for(size_t i = 0; i < vec->length; ++i)
            vec->elementDestructor(VECTOR_IMPL_AT(vec, i));
    }

    vec->length = 0;
}

GULC_FN_IMPL(void, VectorShrinkToFit, gulc_TypeVector** vectorP)
{
    GULC_VERIFY(vectorP != NULL && *vectorP != NULL, "Can't pop from a null vector");

    gulc_VectorImpl* vec = TO_GULC_VECTOR_IMPL(*vectorP);

    if(vec->length != vec->capacity)
        GULC_NAME(VectorResize)(vectorP, vec->length);
}
