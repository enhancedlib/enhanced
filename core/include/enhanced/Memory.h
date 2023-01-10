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
#include <enhanced/util/Traits.h>

namespace enhanced {
    using Nothrow = std::nothrow_t;
    using NothrowRef = const std::nothrow_t&;

    extern const Nothrow nothrow;

    template <typename Type>
    [[RetNotIgnored]]
    inline constexpr Type* addressOf(Type& value) noexcept {
        return __builtin_addressof(value);
    }

    template <typename Type>
    constexpr const Type* addressOf(const Type&&) {
        static_assert(!util::testValid<Type>, "Cannot get address of a temporary expression");
    }

    /*!
     * Allocates space in memory. \n
     *
     * @example memoryAlloc(100 * sizeof(int))
     *
     * @param size     The size to be allocated (unit: byte).
     * @return void*   A pointer to the newly allocated space.
     */
    [[MustInspectResult, RetNullable, SuccessIf("return != nullptr"), RetRequiresRelease]]
    ENHANCED_CORE_API ALLOCATOR RET_RESTRICT void* memoryAlloc(sizetype size);

    /*!
     * Frees a memory space to which the pointer points. \n
     *
     * @example memoryFree(pointer)
     *
     * @param pointer A pointer.
     */
    ENHANCED_CORE_API void memoryFree(void* pointer);

    /*!
     * Sets a memory space of a pointer to the same value.
     *
     * @example memorySet(pointer, 0, 10 * sizeof(int))
     *
     * @param ptr     A pointer.
     * @param aByte   A byte (range: 0 ~ 255).
     * @param size    The byte size of the pointer. (generally: "<memory size> * sizeof(<type>)").
     */
    ENHANCED_CORE_API void memorySet(void* ptr, byte aByte, sizetype size);

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
