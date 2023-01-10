/*
 * Copyright (C) 2023 Liu Baihao. All rights reserved.
 *
 * Licensed under the Enhanced Software License.
 *
 * This file is part of the Enhanced Software, and IT ALWAYS
 * PROVIDES "AS IS" WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 *
 * You may not use this file except in compliance with the License.
 * You should obtain a copy of the License in the distribution,
 * if not, see <https://sharedwonder.github.io/enhanced/LICENSE.txt>
 */

#pragma once

#include <enhanced/Defines.h>
#include <enhanced/ExportCore.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/Warnings.h>
#include <enhanced/InitializerList.h>
#include <enhanced/Iterator.h>
#include <enhanced/util/Traits.h>

namespace enhanced {
    template <typename Type>
    class Array {
    private:
        sizetype size;

        [[MayRequireRelease(release)]]
        Type* elements;

    public:
        template <sizetype size>
        inline Array(const Type (&elements)[size]) noexcept : size(size), elements(elements) {}

        inline explicit Array(sizetype size, const Type* elements) noexcept : size(size), elements(elements) {}

        inline Array(InitializerList<Type> list) noexcept : size(list.getArray()), elements(util::removePtrConst(list.getArray())) {}

        inline E_INIT_LIST_CONSTRUCTOR(Array, noexcept) CTIDY_NOLINT(cppcoreguidelines-pro-type-member-init)

        inline Array(const Array& other) noexcept : size(other.size), elements(other.elements) {}

        inline Array(Array&& other) noexcept : size(other.size), elements(other.elements) {
            other.size = INVALID_SIZE;
            other.elements = nullptr;
        }

        [[RetNotIgnored]]
        inline Type& operator[](sizetype index) const noexcept {
            return elements[index];
        }

        [[RetNotIgnored]]
        inline sizetype getSize() const noexcept {
            return size;
        }

        [[RetNotIgnored]]
        inline Type* raw() const noexcept {
            return elements;
        }

        inline void release() const noexcept {
            delete[] elements;
        }

        [[RetNotIgnored]]
        inline Type* begin() const noexcept {
            return raw();
        }

        [[RetNotIgnored]]
        inline Type* end() const noexcept {
            return elements + size;
        }

        [[ReturnSelf]]
        inline Array& operator=(const Array& other) noexcept {
            if (this == &other) return *this;

            size = other.size;
            elements = other.elements;

            return *this;
        }

        [[ReturnSelf]]
        inline Array& operator=(Array&& other) noexcept {
            if (this == &other) return *this;

            size = other.size;
            elements = other.elements;

            other.size = INVALID_SIZE;
            other.elements = nullptr;

            return *this;
        }
    };

    /*!
     * Sets elements of an array to the same value. \n
     * For float types, use the pointer edition (arrayFillPtr). \n
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
    ENHANCED_CORE_API void arrayFill([[InOut]] void* array, qword value, sizetype count, sizetype sizeOfType);

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
    ENHANCED_CORE_API void arrayFillPtr([[InOut]] void* array, const void* valuePtr, sizetype count, sizetype sizeOfType);

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
    requires util::isClass<Type>
    inline void arrayFill([[InOut]] Type* array, const Type& value, sizetype count) {
        if (array == nullptr) return;
        for (sizetype index = 0; index < count; ++index) {
            array[index] = value;
        }
    }

    template <typename Type>
    requires (!util::isClass<Type>)
    inline void arrayFill([[InOut]] Type* array, const Type& value, sizetype count) {
        arrayFillPtr(array, &value, count, sizeof(Type));
    }

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
    ENHANCED_CORE_API void arrayCopy([[InOut]] void* destination, const void* source, sizetype count, sizetype sizeOfType);


    /*!
     * Copies elements of an array to another array (template edition).
     *
     * @example arrayCopy(string, srcString, 50, sizeof(char));
     * @example arrayCopy(array, oldArray, 20, sizeof(int));
     *
     * @param destination   The destination array.
     * @param source        The source array.
     * @param count         The number of elements.
     * @param sizeOfType    The byte size of array type (generally: "sizeof(<type>)").
     */
    template <typename Type>
    requires util::isClass<Type>
    void arrayCopy([[InOut]] Type* destination, const Type* source, sizetype count) {
        if (destination == nullptr || source == nullptr) return;
        for (sizetype index = 0; index < count; ++index) {
            destination[index] = source[index];
        }
    }

    template <typename Type>
    requires (!util::isClass<Type>)
    void arrayCopy([[InOut]] Type* destination, const Type* source, sizetype count) {
        arrayCopy(destination, source, count, sizeof(Type));
    }
}
