#ifndef GULC_VECTOR_H__
#define GULC_VECTOR_H__

#include "gulc/gulc_common.h"

GULC_EXTERN_C_BEGIN

/**
 * @brief Function type for vector element destructors
 * 
 * @param element pointer to the element
 */
GULC_PTR_FN_DECLARE(VectorElementDestructor, void, void*)

// Just an alias for convenience in implementation
typedef GULC_NAME(VectorElementDestructor) gulc_TypeVectorElemDestr;

/**
 * @brief gulc Vector type
 * It's kind of like std::vector in certain ways, providing
 * a resizable array of elements of a certain size (in bytes)
 * with an optional destructor for each element
 */
GULC_TYPE_DECLARE(
    Vector,
    struct
    {
        const size_t length;
        const size_t capacity;
        uint8_t data[];
    }
)

typedef GULC_NAME(Vector) gulc_TypeVector;

/**
 * @brief Creates a new vector with given elementSize, capacity and elementDestructor
 * 
 * @param elementSize size of each element (in bytes)
 * @param capacity initial capacity of the vector
 * @param elementDestructor pointer to the element destructor function
 * 
 * @return pointer to the created vector
 */
GULC_FN_DECLARE(gulc_TypeVector*, VectorCreate, size_t elementSize, size_t capacity, gulc_TypeVectorElemDestr elementDestructor)

/**
 * @brief Destroys the vector, its elements, frees the memory, setting its pointer to NULL
 * 
 * @param vectorP pointer to the vector (pointer to pointer)
 * 
 * @note If the vector is null, an error is thrown
 */
GULC_FN_DECLARE(void, VectorDestroy, gulc_TypeVector** vectorP)

/**
 * @brief Emplaces a new element at the end of the vector
 * 
 * @param vectorP pointer to the vector (pointer to pointer)
 * 
 * @return pointer to the emplaced element
 * 
 * @note If the vector is null, an error is thrown
 */
GULC_FN_DECLARE(void*, VectorEmplaceBack, gulc_TypeVector** vectorP)

/**
 * @brief Removes the last element from the vector
 * 
 * @param vectorP pointer to the vector (pointer to pointer)
 * 
 * @note If the vector is null, an error is thrown
 */
GULC_FN_DECLARE(void, VectorPopBack, gulc_TypeVector** vectorP)

/**
 * @brief Emplaces a new element at the given index of the vector
 * 
 * @param vectorP pointer to the vector (pointer to pointer)
 * @param index index to emplace the element at
 * 
 * @return pointer to the emplaced element
 * 
 * @note If the vector is null, an error is thrown
 */
GULC_FN_DECLARE(void*, VectorEmplace, gulc_TypeVector** vectorP, size_t index)

/**
 * @brief Removes the element at the given index of the vector
 * 
 * @param vectorP pointer to the vector (pointer to pointer)
 * @param index index of the element to remove
 * 
 * @note If the vector is null, an error is thrown
 * @note If the index is out of bounds, an error is thrown
 */
GULC_FN_DECLARE(void, VectorErase, gulc_TypeVector** vectorP, size_t index)

/**
 * @brief Creates a new vector of given type
 */
#define GULC_VECTOR_OF(type) GULC_NAME(VectorCreate)(sizeof(type), 0, NULL)

/**
 * @brief Creates a new vector of given type with destructor
 */
#define GULC_VECTOR_OF_DESTR(type, destructor) GULC_NAME(VectorCreate)(sizeof(type), 0, destructor)

/**
 * @brief Creates a new vector of given type with given capacity
 */
#define GULC_VECTOR_OF_SIZED(type, cap) GULC_NAME(VectorCreate)(sizeof(type), cap, NULL)

/**
 * @brief Creates a new vector of given type with given capacity and destructor
 */
#define GULC_VECTOR_OF_SIZED_DESTR(type, cap, destructor) GULC_NAME(VectorCreate)(sizeof(type), cap, destructor)

/**
 * @brief Returns the element at given index of a vector
 */
#define GULC_VECTOR_AT(vec, type, i) (((type*)(vec)->data)[i])

GULC_EXTERN_C_END

#endif // !GULC_VECTOR_H__