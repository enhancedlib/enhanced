/*
 * Copyright (C) 2021 Liu Baihao.
 * This product is licensed under Enhanced License.
 *
 * This copyright disclaimer is subject to change without notice.
 *
 * This software is a free software,
 * everyone can change, copy, publication, demonstrate, use, etc.
 *
 * If you change and publication this software,
 * must credit the original software source and author's name,
 * and include this copyright disclaimer and
 * the license of this software in your software.
 *
 * This software and documentation may provide
 * third-party content, product and other information.
 * I am not responsible for any loss or damage caused
 * by your access to or use of third-party content, products, etc.
 */

#ifndef ENHANCED_CORE_MEMORY_H
#define ENHANCED_CORE_MEMORY_H

#include "EnhancedCore/defines.h"
#include "EnhancedCore/annotations.h"
#include "EnhancedCore/types.h"

EXTERN_C_START

/*!
 * Allocates space in memory.
 *
 * @example memoryAlloc(100 * sizeof(int))
 *
 * @param size     The size to be allocated (unit: byte).
 * @return void*   A pointer to the newly allocated space.
 */
$RetRequiresRelease()
ENHANCED_CORE_API void *memoryAlloc(Size size);

/*!
 * Frees a memory space to which the pointer points.
 *
 * @example memoryFree(ptr)
 *
 * @param ptr A pointer.
 */
ENHANCED_CORE_API void memoryFree(void *ptr);

/*!
 * Sets a memory space of a pointer to the same value.
 *
 * @example memorySet(ptr, 0, 10 * sizeof(int))
 *
 * @param ptr    A pointer.
 * @param byte   A byte (range: 0 ~ 255).
 * @param size   The byte size of the pointer. (generally: "<memory size> * sizeof(<pointer type>)").
 */
ENHANCED_CORE_API void memorySet(void *ptr, Byte byte, Size size);

/*!
 * Copies a memory space.
 *
 * @example memoryCopy(source, target, 10 * sizeof(int))
 *
 * @param target   The target memory space.
 * @param source   A source pointer.
 * @param size     The byte size of the source pointer. (generally: "<memory size> * sizeof(<pointer type>)").
 */
ENHANCED_CORE_API void memoryCopy(void *target, void *source, Size size);

EXTERN_C_END

#endif // !ENHANCED_CORE_MEMORY_H
