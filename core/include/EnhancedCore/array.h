/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 * This software is licensed under Enhanced License.
 *
 * This copyright notice is subject to change without notice.
 *
 * This software is a free software, everyone can change,
 * copy, publication, demonstrate, use, etc.
 *
 * This software and documentation may provide
 * third-party content, product and other information.
 * The authors or copyright holders be not responsible for any loss or damage
 * caused by your access to or use of third-party content, products, etc.
 *
 * For any loss or damage caused by This software,
 * the authors or copyright holders may provide possible solutions,
 * but it does not mean that the authors or copyright holders
 * will definitely solve the problem.
 * In no event shall the author or copyright
 * owner be liable for any claims, damages or other liabilities.
 *
 * You should see the Enhanced License in this software, if not, visit
 * <https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt>
 */

#ifndef ENHANCED_CORE_ARRAY_H
#define ENHANCED_CORE_ARRAY_H

#include "EnhancedCore/defines.h"
#include "EnhancedCore/export.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/annotations.h"

EXTERN_C_START

/*!
 * Creates a new array.
 *
 * @param length          The count of the original array.
 * @param sizeOfType      The byte size of array type (generally: "sizeof(<array type>)").
 */
$RetRequiresRelease()
ENHANCED_CORE_API void *arrayNew(Size length, Size sizeOfType);

/*!
 * Sets all the value of an array to the same value.
 *
 * @example arraySetInt(str, 5, 'a', sizeof(char));
 * @example arraySetInt(array, 10, 0, sizeof(int));
 *
 * For float and struct type, use arraySet.
 *
 * @param array           An array (essentially a pointer).
 * @param count           The number of elements of the array (the count of the array).
 * @param value           A value (can be any type).
 * @param sizeOfType      The byte size of array type (generally: "sizeof(<array type>)").
 */
ENHANCED_CORE_API void arraySetInt(void *array, Size count, int64 value, Size sizeOfType);

/*!
 * Sets all the value of an array to the same value.
 *
 * @example struct A a = {0, 1}; \n
 *          arraySet(array, 5, &a, sizeof(A));
 * @example float f = 10.0f; \n
 *          arraySet(array, 10, &f, sizeof(float));
 *
 * @param array           An array (essentially a pointer).
 * @param count           The number of elements of the array (the count of the array).
 * @param address         An address.
 * @param sizeOfType      The byte size of array type (generally: "sizeof(<array type>)").
 */
ENHANCED_CORE_API void arraySet(void *array, Size count, void *address, Size sizeOfType);

/*!
 * Copies an array to a new array of the same count.
 *
 * @example arrayCopy(string, srcString, 50, sizeof(char))
 * @example arrayCopy(array, oldArray, 20, sizeof(int))
 *
 * @param destArray      The target array (or the new pointer).
 * @param srcArray       An array (or a pointer).
 * @param count          The count of the original array.
 * @param sizeOfType     The byte size of array type (generally: "sizeof(<array type>)").
 */
ENHANCED_CORE_API void arrayCopy(void *destArray, void *srcArray, Size count, Size sizeOfType);

EXTERN_C_END

#endif // !ENHANCED_CORE_ARRAY_H
