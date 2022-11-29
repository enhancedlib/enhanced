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

#include <enhanced/Defines.h>
#include <enhanced/ExportCore.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/InitializerList.h>
#include <enhanced/util/Traits.h>

namespace enhanced {
    template <typename Type>
    class Array {
    private:
        sizetype size;

        Type* elements;

    public:
        template <sizetype size>
        Array(const Type (&elements)[size]) noexcept : size(size), elements(elements) {}

        explicit Array(sizetype size, const Type*& elements) noexcept : size(size), elements(elements) {}

        Array(InitializerList<Type> list) noexcept : size(initListSize(list)), elements(util::removePtrConst(initListToArray(list))) {}

        Array(const Array& other) noexcept : size(other.size), elements(other.elements) {}

        Array(Array&& other) noexcept : size(other.size), elements(other.elements) {
            other.size = INVALID_SIZE;
            other.elements = null;
        }

        $NoIgnoreReturn
        func operator[](sizetype index) const noexcept -> Type& {
            return elements[index];
        }

        $NoIgnoreReturn
        func getSize() const noexcept -> sizetype {
            return size;
        }

        func destroy() const noexcept -> void {
            delete[] elements;
        }

        func operator=(const Array& other) noexcept -> Array& {
            if (this == &other) return *this;

            size = other.size;
            elements = other.elements;

            return *this;
        }

        func operator=(Array&& other) noexcept -> Array& {
            if (this == &other) return *this;

            size = other.size;
            elements = other.elements;

            other.size = INVALID_SIZE;
            other.elements = null;

            return *this;
        }
    };

    /*!
     * Sets elements of an array to the same value. \n
     * For float types, use the pointer edition. \n
     * For struct/class types, use the template edition.
     *
     * @example arrayFill(str, 'a', 5, sizeof(char));
     * @example arrayFill(array, 0, 10, sizeof(int));
     *
     * @param array        An array.
     * @param value        A value (can be any integral type, includes "char").
     * @param count        The number of elements.
     * @param sizeOfType   The byte size of array type (generally: "sizeof(<array-type>)").
     */
    ENHANCED_CORE_API func arrayFill($InOut void* array, qword value, sizetype count, sizetype sizeOfType) -> void;

    /*!
     * Sets elements of an array to the same value (template edition).
     *
     * @example arrayFill(str, 'a', 5);
     * @example arrayFill(array, 0, 10);
     *
     * @param array        An array.
     * @param value        A value.
     * @param count        The number of elements.
     */
    template <typename Type>
    inline func arrayFill($InOut Type* array, const Type& value, sizetype count) -> void {
        for (sizetype index = 0; index < count; ++index) {
            array[index] = value;
        }
    }

    /*!
     * Sets elements of an array to the same value (pointer edition).
     *
     * @example float f = 10.0f; \n
     *          arrayFillPtr(array, &f, 10, sizeof(float));
     * @example double d = 5.0; \n
     *          arrayFillPtr(array, &d, 5, sizeof(double));
     *
     * @param array        An array.
     * @param count        The number of elements.
     * @param valuePtr     A pointer to the value.
     * @param sizeOfType   The byte size of array type (generally: "sizeof(<type>)").
     */
    ENHANCED_CORE_API func arrayFillPtr($InOut void* array, void* valuePtr, sizetype count, sizetype sizeOfType) -> void;

    /*!
     * Copies elements of an array to another array.
     *
     * @example arrayCopy(string, srcString, 50, sizeof(char));
     * @example arrayCopy(array, oldArray, 20, sizeof(int));
     *
     * @param destination   The destination array.
     * @param source        The source array.
     * @param count         The number of elements.
     * @param sizeOfType    The byte size of array type (generally: "sizeof(<type>)").
     */
    ENHANCED_CORE_API func arrayCopy($Out void* destination, const void* source, sizetype count, sizetype sizeOfType) -> void;
}
