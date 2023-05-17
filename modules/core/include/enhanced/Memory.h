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

#include <new> // std::nothrow_t, std::align_val_t

#include <enhanced/Defines.h>
#include <enhanced/ExportCore.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/util/Traits.h>

namespace enhanced {
    using Nothrow = std::nothrow_t;
    using NothrowRef = const std::nothrow_t&;

    extern const Nothrow nothrow;

    template <typename Type>
    struct Swappable {
        static_assert(util::isVoidType<decltype(Type::swap())>);
    };

    template <typename Type>
    E_ANNOTATE(RetNotIgnored)
    inline constexpr Type* addressOf(Type& value) noexcept {
        return __builtin_addressof(value);
    }

    template <typename Type>
    constexpr const Type* addressOf(const Type&&) {
        static_assert(!util::assume<Type>, "Cannot get address of a literal");
    }

    template <typename Type>
    inline constexpr void swap(Type&& first, Type&& second)
        noexcept(noexcept(util::isNothrowConstructible<Type> && util::isNothrowMoveAssignable<Type>)) {
        Type&& temp = first;
        first = second;
        second = temp;
    }

    template <typename Type>
    requires util::isBaseOf<Swappable<Type>, Type>
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
    E_ANNOTATE(MustInspectResult, RetNullable, SuccessIf("return != nullptr"), RetRequiresRelease)
    ENHANCED_CORE_API ALLOCATOR RET_RESTRICT void* allocate(sizetype size);

    /*!
     * Frees a memory space to which the pointer points. \n
     *
     * @example release(pointer)
     *
     * @param pointer A pointer.
     */
    ENHANCED_CORE_API void release(void* pointer);

    /*!
     * Sets a memory space of a pointer to the same value.
     *
     * @example memoryFill(pointer, 0, 10 * sizeof(int))
     *
     * @param ptr     A pointer.
     * @param aByte   A byte (range: 0 ~ 255).
     * @param size    The byte size of the pointer. (generally: "<memory size> * sizeof(<type>)").
     */
    ENHANCED_CORE_API void memoryFill(void* ptr, byte aByte, sizetype size);

    /*!
     * Copies a memory space.
     *
     * @example memoryCopy(destination, source, 10 * sizeof(int))
     *
     * @param destination   The target memory space.
     * @param source        A source pointer.
     * @param size          The byte size of the source pointer. (generally: "<count> * sizeof(<type>)").
     */
    ENHANCED_CORE_API void memoryCopy(void* destination, const void* source, sizetype size);
}
