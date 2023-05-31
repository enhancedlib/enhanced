/*
 * Copyright (C) 2023 Liu Baihao. All rights reserved.
 *
 * Licensed under the MIT License with the Distribution Exception.
 * You may not use this file except in compliance with the License.
 *
 * THIS FILE IS PART OF THE ENHANCED SOFTWARE, and IT ALWAYS
 * PROVIDES "AS IS" WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
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

        E_ANNOTATE(MayRequireRelease(release))
        Type* elements;

    public:
        using Element = Type;

        inline Array() noexcept : size(0), elements(nullptr) {}

        template <sizetype size>
        inline Array(wrap<const Type[size]>& elements) noexcept : size(size), elements(elements) {}

        inline Array(const Type* begin, const Type* end) noexcept : size(end - begin), elements(begin) {}

        inline explicit Array(sizetype size, const Type* elements) noexcept : size(size), elements(elements) {}

        E_INIT_LIST_CONSTRUCTOR(Array, Type)
        inline Array(InitializerList<Type> list) noexcept : size(list.getSize()), elements(util::removePtrConst(list.toArray())) {}

        inline Array(const Array& other) noexcept : size(other.size), elements(other.elements) {}

        inline Array(Array&& other) noexcept : size(other.size), elements(other.elements) {
            other.size = E_SIZE_TYPE_MAX;
            other.elements = nullptr;
        }

        E_ANNOTATE(RetNotIgnored)
        inline Type& operator[](sizetype index) const noexcept {
            return elements[index];
        }

        E_ANNOTATE(RetNotIgnored)
        inline sizetype getSize() const noexcept {
            return size;
        }

        E_ANNOTATE(RetNotIgnored)
        inline Type* raw() const noexcept {
            return elements;
        }

        inline void release() const noexcept {
            delete[] elements;
        }

        E_ANNOTATE(RetNotIgnored)
        inline Type* begin() const noexcept {
            return raw();
        }

        E_ANNOTATE(RetNotIgnored)
        inline Type* end() const noexcept {
            return elements + size;
        }

        E_ANNOTATE(RetNotIgnored)
        inline Array& operator=(const Array& other) noexcept {
            if (this == &other) return *this;

            size = other.size;
            elements = other.elements;

            return *this;
        }

        E_ANNOTATE(RetNotIgnored)
        inline Array& operator=(Array&& other) noexcept {
            if (this == &other) return *this;

            size = other.size;
            elements = other.elements;

            other.size = E_SIZE_TYPE_MAX;
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
    E_CORE_API void arrayFill(E_ANNOTATE(InOut) void* array, qword value, sizetype count, sizetype sizeOfType);

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
    E_CORE_API void arrayFillPtr(E_ANNOTATE(InOut) void* array, const void* valuePtr, sizetype count, sizetype sizeOfType);

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
    inline void arrayFill(E_ANNOTATE(InOut) Type* array, const Type& value, sizetype count) {
        if (array == nullptr) return;
        for (sizetype index = 0; index < count; ++index) {
            array[index] = value;
        }
    }

    template <typename Type>
    requires (!util::isClass<Type>)
    inline void arrayFill(E_ANNOTATE(InOut) Type* array, const Type& value, sizetype count) {
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
    E_CORE_API void arrayCopy(E_ANNOTATE(InOut) void* destination, const void* source, sizetype count, sizetype sizeOfType);


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
    void arrayCopy(E_ANNOTATE(InOut) Type* destination, const Type* source, sizetype count) {
        if (destination == nullptr || source == nullptr) return;
        for (sizetype index = 0; index < count; ++index) {
            destination[index] = source[index];
        }
    }

    template <typename Type>
    requires (!util::isClass<Type>)
    void arrayCopy(E_ANNOTATE(InOut) Type* destination, const Type* source, sizetype count) {
        arrayCopy(destination, source, count, sizeof(Type));
    }
}
