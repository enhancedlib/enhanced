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

#include <malloc.h>

#include <enhanced/core/memory.h>

#include <enhanced/core/defines.h>
#include <enhanced/core/types.h>
#include <enhanced/core/exceptions/MemoryAllocationError.h>

using enhanced::core::memoryAlloc;
using enhanced::core::memoryFree;
using enhanced::core::exceptions::MemoryAllocationError;

namespace enhanced::core {
    $(MustInspectResult RetNullable RetRequiresRelease)
    func memoryAlloc(sizetype size) -> void* {
        if (size == 0) return null;

        return malloc(size);
    }

    func memoryFree(void* pointer) -> void {
        free(pointer);
    }

    func memorySet(void* ptr, byte aByte, sizetype size) -> void {
        if (ptr == null || size == 0) return;

        for (sizetype index = 0; index < size; ++index) {
            ((byte*) ptr)[index] = aByte;
        }
    }

    func memoryCopy(void* destination, const void* source, sizetype size) -> void {
        if (destination == null || source == null || size == 0) return;

        sizetype countBlock = size / sizeof(qword);
        sizetype countByte = size % sizeof(qword);

        for (sizetype index = 0; index < countBlock; ++index) {
            ((qword*) destination)[index] = ((qword*) source)[index];
        }

        for (sizetype index = size - countByte; index < size; ++index) {
            ((byte*) destination)[index] = ((byte*) source)[index];
        }
    }
}

$(RetRequiresRelease)
func operator new(sizetype size) -> void* {
    void* space = memoryAlloc(size);
    if (space == null) {
        throw MemoryAllocationError("Cannot allocate memory");
    }
    return space;
}

func operator delete(void* pointer) noexcept -> void {
    memoryFree(pointer);
}

$(RetRequiresRelease)
func operator new[](sizetype size) -> void* {
    return operator new(size);
}

func operator delete[](void* pointer) noexcept -> void {
    operator delete(pointer);
}
