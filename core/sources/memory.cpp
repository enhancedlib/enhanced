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

#include <enhanced/core/memory.h>

#include <enhanced/core/defines.h>
#include <enhanced/core/types.h>
#include <enhanced/core/exception/MemoryAllocationError.h>

using enhanced::core::memoryAlloc;
using enhanced::core::memoryFree;
using enhanced::core::exception::MemoryAllocationError;

void* operator new(Size size) {
    void* space = memoryAlloc(size);
    if (space == null) {
        throw MemoryAllocationError("Cannot allocate memory");
    }
    return space;
}

void operator delete(void* pointer) noexcept {
    memoryFree(pointer);
}

void* operator new[](Size size) {
    return operator new(size);
}

void operator delete[](void* pointer) noexcept {
    operator delete(pointer);
}
