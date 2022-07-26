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
 * Allocates space in memory.
 *
 * @example memoryAlloc(100 * sizeof(int))
 *
 * @param size     The size to be allocated (unit: byte).
 * @return void*   A pointer to the newly allocated space.
 */
MustInspectResult Nullable RetRequiresRelease()
ENHANCED_CORE_API void* memoryAlloc(Size size);

/*!
 * Frees a memory space to which the pointer points.
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
 * @param size    The byte size of the pointer. (generally: "<memory size> * sizeof(<pointer type>)").
 */
ENHANCED_CORE_API void memorySet(void* ptr, byte aByte, Size size);

/*!
 * Copies a memory space.
 *
 * @example memoryCopy(source, destination, 10 * sizeof(int))
 *
 * @param destination   The target memory space.
 * @param source        A source pointer.
 * @param size          The byte size of the source pointer. (generally: "<count> * sizeof(<pointer type>)").
 */
ENHANCED_CORE_API void memoryCopy(void* destination, const void* source, Size size);

EXTERN_C_END
