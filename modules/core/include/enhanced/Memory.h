/*
 * This file is part of Enhanced Framework.
 *
 * Copyright (C) 2023 sharedwonder (Liu Baihao). All rights reserved.
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
 *    distribution of the Software, except for distributing modified versions and
 *    products that use the Software.
 *
 * 5. If you use this Software in your product, you shall indicate it.
 *
 * 6. Neither the name of the author nor the names of its contributors may
 *    be used to endorse or promote products derived from the Software.
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

#include <new> // std::nothrow_t, std::align_val_t

#include <enhanced/Defines.h>
#include <enhanced/CoreAPI.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/TraitInterface.h>
#include <enhanced/Traits.h>

namespace enhanced {
    using Nothrow = std::nothrow_t;
    using NothrowRef = const std::nothrow_t&;

    extern const Nothrow nothrow;

    E_TRAIT_INTERFACE()
    class Swappable {
    E_CLASS_HEADER
        E_TRAIT_INTERFACE_METHOD(swap, void, (const E_TRAIT_INTERFACE_IMPL_CLASS&))

    E_CLASS_BODY
        using Type = E_TRAIT_INTERFACE_IMPL_CLASS;
    };

    template <typename Type>
    E_RET_NO_DISCARD()
    inline constexpr Type* addressOf(Type& value) noexcept {
        return __builtin_addressof(value);
    }

    template <typename Type>
    constexpr const Type* addressOf(const Type&&) {
        static_assert(!testValid<Type>, "Cannot get address of a literal");
    }

    template <typename Type>
    inline constexpr void swap(Type&& first, Type&& second)
        noexcept(noexcept(isNothrowConstructible<Type> && isNothrowMoveAssignable<Type>)) {
        Type&& temp = first;
        first = second;
        second = temp;
    }

    template <typename Type>
    requires isBaseOf<Swappable<Type>, Type>
    inline constexpr void swap(Type&& first, Type&& second) noexcept(noexcept(first.swap(second))) {
        first.swap(second);
    }

    /*!
     * Allocates space in memory. \n
     *
     * @example allocate(100 * sizeof(int))
     *
     * @param size     The size to be allocated (unit: byte).
     * @return void*   A pointer to the newly allocated space.
     */
    E_RET_INSPECT() E_NULLABLE() E_RET_NEED_RELEASE()
    E_API(core) E_ALLOCATOR E_RET_RESTRICT void* allocate(sizetype size);

    /*!
     * Frees a memory space to which the pointer points. \n
     *
     * @example release(pointer)
     *
     * @param pointer A pointer.
     */
    E_API(core) void release(void* pointer);

    /*!
     * Sets a memory space of a pointer to the same value.
     *
     * @example memoryFill(pointer, 0, 10 * sizeof(int))
     *
     * @param ptr     A pointer.
     * @param aByte   A byte (range: 0 ~ 255).
     * @param size    The byte size of the pointer. (generally: "<memory size> * sizeof(<type>)").
     */
    E_API(core) void memoryFill(void* ptr, byte aByte, sizetype size);

    /*!
     * Copies a memory space.
     *
     * @example memoryCopy(destination, source, 10 * sizeof(int))
     *
     * @param destination   The target memory space.
     * @param source        A source pointer.
     * @param size          The byte size of the source pointer. (generally: "<count> * sizeof(<type>)").
     */
    E_API(core) void memoryCopy(void* destination, const void* source, sizetype size);
}
