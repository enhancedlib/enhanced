/*
 * This file is part of Enhanced Framework.
 *
 * Copyright (C) 2023 Liu Baihao (sharedwonder). All rights reserved.
 *
 * Permission is hereby granted, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software,
 * including without limitation the rights to use, copy, modify, merge,
 * distribute. Unless you have obtained permission from the copyright holders,
 * subject to the following restrictions:
 *
 * 1. The above copyright notice and this permission notice shall be included in
 *    all copies of the Software and modified versions.
 *
 * 2. You may not misrepresent the source of the Software, and you may not claim
 *    that you wrote the original version.
 *
 * 3. You may not misrepresent the modified version as the original version.
 *
 * 4. You may not charge any fees or receive other compensation for the
 *    distribution of the Software, excluding distribution of modified versions
 *    and products using the Software.
 *
 * 5. If you use this Software in your product, you shall indicate it.
 *
 * 6. Neither the name of the author nor the names of its contributors may
 *    be used to endorse or promote products derived from the Software
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#include <enhanced/Defines.h>
#include <enhanced/ExportCore.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/Warnings.h>
#include <enhanced/Traits.h>
#include <enhanced/InitializerList.h>
#include <enhanced/Iterator.h>

namespace enhanced {
    template <typename Type>
    class Array {
        E_CLASS(Array)

    E_CLASS_BODY
    private:
        sizetype size;

        E_RELEASE_FUNC(release)
        Type* elements;

    public:
        using Element = Type;

        inline Array() noexcept : size(0), elements(nullptr) {}

        template <sizetype size>
        inline Array(wrap<const Type[size]>& elements) noexcept : size(size), elements(elements) {}

        inline Array(const Type* begin, const Type* end) noexcept : size(end - begin), elements(begin) {}

        inline explicit Array(sizetype size, const Type* elements) noexcept : size(size), elements(elements) {}

        E_INIT_LIST_CONSTRUCTOR(Array, Type)
        inline Array(InitializerList<Type> list) noexcept : size(list.getSize()), elements(removePtrConst(list.toArray())) {}

        inline Array(const Array& other) noexcept : size(other.size), elements(other.elements) {}

        inline Array(Array&& other) noexcept : size(other.size), elements(other.elements) {
            other.size = E_SIZE_TYPE_MAX;
            other.elements = nullptr;
        }

        E_RET_NO_DISCARD()
        inline Type& operator[](sizetype index) const noexcept {
            return elements[index];
        }

        E_RET_NO_DISCARD()
        inline sizetype getSize() const noexcept {
            return size;
        }

        E_RET_NO_DISCARD()
        inline Type* raw() const noexcept {
            return elements;
        }

        inline void release() const noexcept {
            delete[] elements;
        }

        E_RET_NO_DISCARD()
        inline Type* begin() const noexcept {
            return raw();
        }

        E_RET_NO_DISCARD()
        inline Type* end() const noexcept {
            return elements + size;
        }

        E_RET_NO_DISCARD()
        inline Array& operator=(const Array& other) noexcept {
            if (this == &other) return *this;

            size = other.size;
            elements = other.elements;

            return *this;
        }

        E_RET_NO_DISCARD()
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
     * For class/struct types, use the template edition.
     *
     * @example arrayFill(str, 'a', 5, sizeof(char));
     * @example arrayFill(array, 0, 10, sizeof(int));
     *
     * @param array        An array.
     * @param value        A value (can be any integral type, includes "char").
     * @param count        The number of elements.
     * @param sizeOfType   The byte size of array type (generally: "sizeof(<array-type>)").
     */
    E_CORE_API void arrayFill(E_IN_OUT() void* array, qword value, sizetype count, sizetype sizeOfType);

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
    E_CORE_API void arrayFillPtr(E_IN_OUT() void* array, const void* valuePtr, sizetype count, sizetype sizeOfType);

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
    requires isClass<Type>
    inline void arrayFill(E_IN_OUT() Type* array, const Type& value, sizetype count) {
        if (array == nullptr) return;
        for (sizetype index = 0; index < count; ++index) {
            array[index] = value;
        }
    }

    template <typename Type>
    requires (!isClass<Type>)
    inline void arrayFill(E_IN_OUT() Type* array, const Type& value, sizetype count) {
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
    E_CORE_API void arrayCopy(E_IN_OUT() void* destination, const void* source, sizetype count, sizetype sizeOfType);


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
    requires isClass<Type>
    void arrayCopy(E_IN_OUT() Type* destination, const Type* source, sizetype count) {
        if (destination == nullptr || source == nullptr) return;
        for (sizetype index = 0; index < count; ++index) {
            destination[index] = source[index];
        }
    }

    template <typename Type>
    requires (!isClass<Type>)
    void arrayCopy(E_IN_OUT() Type* destination, const Type* source, sizetype count) {
        arrayCopy(destination, source, count, sizeof(Type));
    }
}
