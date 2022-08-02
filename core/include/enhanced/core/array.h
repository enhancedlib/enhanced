/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 *
 * This software is licensed under Enhanced License.
 * You may not use this file except in compliance with the License.
 * You should see a copy of Enhanced License in this software, if not, visit
 * <https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt>
 *
 * The Software is always provided "AS IS",
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#pragma once

#include "defines.h"
#include "export.h"
#include "types.h"
#include "annotations.h"

EXTERN_C_START

/*!
 * Creates a new array.
 *
 * @param length          The count of the original array.
 * @param sizeOfType      The byte size of array type (generally: "sizeof(<array type>)").
 */
RetRequiresRelease
ENHANCED_CORE_API void* arrayNew(Size length, Size sizeOfType);

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
 * @param value           A value (can be any integer type, includes "char").
 * @param sizeOfType      The byte size of array type (generally: "sizeof(<array type>)").
 */
ENHANCED_CORE_API void arraySetInt(Out void* array, Size count, int64 value, Size sizeOfType);

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
ENHANCED_CORE_API void arraySet(Out void* array, Size count, void* address, Size sizeOfType);

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
ENHANCED_CORE_API void arrayCopy(Out void* destArray, void* srcArray, Size count, Size sizeOfType);

EXTERN_C_END
