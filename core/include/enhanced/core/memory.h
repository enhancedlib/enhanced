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
    * Allocates space in memory. \n
    *
    * Note: For C++, use 'new' keyword as well.
    *
    * @example memoryAlloc(100 * sizeof(int))
    *
    * @param size     The size to be allocated (unit: byte).
    * @return void*   A pointer to the newly allocated space.
    */
    $(MustInspectResult RetNullable RetRequiresRelease)
    ENHANCED_CORE_API func memoryAlloc(sizetype size) -> void*;

    /*!
    * Frees a memory space to which the pointer points. \n
    *
    * Note: For C++, use 'delete' keyword as well.
    *
    * @example memoryFree(pointer)
    *
    * @param pointer A pointer.
    */
    ENHANCED_CORE_API func memoryFree(void* pointer) -> void;

    /*!
    * Sets a memory space of a pointer to the same value.
    *
    * @example memorySet(pointer, 0, 10 * sizeof(int))
    *
    * @param ptr     A pointer.
    * @param aByte   A byte (range: 0 ~ 255).
    * @param size    The byte size of the pointer. (generally: "<memory size> * sizeof(<type>)").
    */
    ENHANCED_CORE_API func memorySet(void* ptr, byte aByte, sizetype size) -> void;

    /*!
    * Copies a memory space.
    *
    * @example memoryCopy(destination, source, 10 * sizeof(int))
    *
    * @param destination   The target memory space.
    * @param source        A source pointer.
    * @param size          The byte size of the source pointer. (generally: "<count> * sizeof(<type>)").
    */
    ENHANCED_CORE_API func memoryCopy(void* destination, const void* source, sizetype size) -> void;
}

$(RetRequiresRelease)
func operator new(sizetype size) -> void*;

func operator delete(void* pointer) noexcept -> void;

$(RetRequiresRelease)
func operator new[](sizetype size) -> void*;

func operator delete[](void* pointer) noexcept -> void;
