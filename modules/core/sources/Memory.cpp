/*
 * Copyright (C) 2023 Liu Baihao. All rights reserved.
 *
 * Licensed under the MIT License with "Fairness" Exception.
 *
 * You may not use this file except in compliance with the License.
 *
 * This file is part of The Enhanced Software, and IT ALWAYS
 * PROVIDES "AS IS" WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#include "enhanced/Annotations.h"
#include <malloc.h>

#include <enhanced/Memory.h>

#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/Warnings.h>
#include <enhanced/exceptions/MemoryAllocationError.h>

using enhanced::memoryAlloc;
using enhanced::memoryFree;
using enhanced::exceptions::MemoryAllocationError;

namespace enhanced {
    const Nothrow nothrow {};

    [[MustInspectResult, RetNullable, SuccessIf("return != nullptr"), RetRequiresRelease]]
    ALLOCATOR RET_RESTRICT void* memoryAlloc(sizetype size) {
        if (size == 0) return nullptr;

        return malloc(size);
    }

    void memoryFree(void* pointer) {
        free(pointer);
    }

    void memorySet(void* ptr, byte aByte, sizetype size) {
    #ifndef COMPILER_MSVC
        __builtin_memset(ptr, aByte, size);
    #else
        if (ptr == nullptr || size == 0) return;

        for (sizetype index = 0; index < size; ++index) {
            ((byte*) ptr)[index] = aByte;
        }
    #endif
    }

    void memoryCopy(void* destination, const void* source, sizetype size) {
    #ifndef COMPILER_MSVC
        __builtin_memcpy(destination, source, size);
    #else
        if (destination == nullptr || source == nullptr || size == 0) return;

        sizetype countBlock = size / sizeof(qword);
        sizetype countByte = size % sizeof(qword);

        for (sizetype index = 0; index < countBlock; ++index) {
            ((qword*) destination)[index] = ((qword*) source)[index];
        }

        for (sizetype index = size - countByte; index < size; ++index) {
            ((byte*) destination)[index] = ((byte*) source)[index];
        }
    #endif
    }
}

using enhanced::NothrowRef;
using enhanced::nothrow;

// TODO

[[RetNotNull]]
ALLOCATOR void* operator new(sizetype size) {
    void* space = memoryAlloc(size);
    if (space == nullptr) {
        throw MemoryAllocationError("Cannot allocate memory");
    }
    return space;
}

[[RetNotNull]]
ALLOCATOR void* operator new[](sizetype size) {
    return operator new(size);
}

[[MustInspectResult, RetNullable, SuccessIf("return != nullptr"), RetRequiresRelease]]
ALLOCATOR RET_RESTRICT void* operator new(sizetype size, enhanced::NothrowRef) noexcept {
    return memoryAlloc(size);
}

[[MustInspectResult, RetNullable, SuccessIf("return != nullptr"), RetRequiresRelease]]
ALLOCATOR RET_RESTRICT void* operator new[](sizetype size, enhanced::NothrowRef) noexcept {
    return operator new(size, nothrow);
}

GCC_WARNING_PAD("-Wsized-deallocation")

void operator delete(void* block) noexcept {
    memoryFree(block);
}

void operator delete[](void* block) noexcept {
    operator delete(block);
}

void operator delete(void* block, enhanced::NothrowRef) noexcept {
    operator delete(block);
}

void operator delete[](void* block, enhanced::NothrowRef) noexcept {
    operator delete(block);
}

GCC_WARNING_POP
