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

#include <malloc.h>

#include <enhanced/Memory.h>

#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/Warnings.h>
#include <enhanced/exceptions/MemoryAllocationError.h>

using enhanced::allocate;
using enhanced::release;
using enhanced::exceptions::MemoryAllocationError;

namespace enhanced {
    const Nothrow nothrow {};

    E_ANNOTATE(MustInspectResult, RetNullable, SuccessIf("return != nullptr"), RetRequiresRelease)
    ALLOCATOR RET_RESTRICT void* allocate(sizetype size) {
        if (size == 0) return nullptr;

        return malloc(size);
    }

    void release(void* pointer) {
        free(pointer);
    }

    void memoryFill(void* ptr, byte aByte, sizetype size) {
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

E_ANNOTATE(RetNotNull)
ALLOCATOR void* operator new(enhanced::sizetype size) {
    void* space = allocate(size);
    if (space == nullptr) {
        throw MemoryAllocationError("Cannot allocate memory");
    }
    return space;
}

E_ANNOTATE(RetNotNull)
ALLOCATOR void* operator new[](enhanced::sizetype size) {
    return operator new(size);
}

E_ANNOTATE(MustInspectResult, RetNullable, SuccessIf("return != nullptr"), RetRequiresRelease)
ALLOCATOR RET_RESTRICT void* operator new(enhanced::sizetype size, enhanced::NothrowRef) noexcept {
    return allocate(size);
}

E_ANNOTATE(MustInspectResult, RetNullable, SuccessIf("return != nullptr"), RetRequiresRelease)
ALLOCATOR RET_RESTRICT void* operator new[](enhanced::sizetype size, enhanced::NothrowRef) noexcept {
    return operator new(size, nothrow);
}

GCC_WARNING_PAD("-Wsized-deallocation")

void operator delete(void* block) noexcept {
    release(block);
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
