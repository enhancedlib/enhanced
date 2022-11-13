/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 *
 * Licensed under the Enhanced Software License.
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://sharedwonder.github.io/enhanced/LICENSE.txt
 *
 * UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING,
 * THE SOFTWARE IS ALWAYS PROVIDED "AS IS",
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#pragma once

#include <enhanced/core/defines.h>
#include <enhanced/core/types.h>
#include <enhanced/core/annotations.h>

namespace enhanced::core {
    /*!
    * Sets elements of an array to the same value. \n
    * \n
    * For float and struct type, use arrayFillPtr.
    *
    * @example arrayFill(str, 'a', 5, sizeof(char));
    * @example arrayFill(array, 0, 10, sizeof(int));
    *
    * @param array        An array.
    * @param value        A value (can be any integral type, includes "char").
    * @param count        The number of elements.
    * @param sizeOfType   The byte size of array type (generally: "sizeof(<array-type>)").
    */
    ENHANCED_CORE_API func arrayFill($(InOut) void* array, qword value, sizetype count, sizetype sizeOfType) -> void;

    /*!
    * Sets elements of an array to the same value (use a pointer).
    *
    * @example struct A a = {0, 1}; \n
    *          arrayFillPtr(array, &a, 5, sizeof(A));
    * @example float f = 10.0f; \n
    *          arrayFillPtr(array, &f, 10, sizeof(float));
    *
    * @param array        An array.
    * @param count        The number of elements.
    * @param valuePtr     A pointer to the value.
    * @param sizeOfType   The byte size of array type (generally: "sizeof(<type>)").
    */
    ENHANCED_CORE_API func arrayFillPtr($(InOut) void* array, void* valuePtr, sizetype count, sizetype sizeOfType) -> void;

    /*!
    * Copies elements of an array to another array.
    *
    * @example arrayCopy(string, srcString, 50, sizeof(char))
    * @example arrayCopy(array, oldArray, 20, sizeof(int))
    *
    * @param destination   The destination array.
    * @param source        The source array.
    * @param count         The number of elements.
    * @param sizeOfType    The byte size of array type (generally: "sizeof(<type>)").
    */
    ENHANCED_CORE_API func arrayCopy($(Out) void* destination, const void* source, sizetype count, sizetype sizeOfType) -> void;
}
