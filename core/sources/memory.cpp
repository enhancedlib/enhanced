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

    $MustInspectResult $RetNullable $SuccessIf(return != nullptr) $Allocator $RetRestrict
    void* memoryAlloc(sizetype size) {
        if (size == 0) return nullptr;

        return malloc(size);
    }

    void memoryFree(void* pointer) {
        free(pointer);
    }

    void memorySet(void* ptr, byte aByte, sizetype size) {
        if (ptr == nullptr || size == 0) return;

        for (sizetype index = 0; index < size; ++index) {
            ((byte*) ptr)[index] = aByte;
        }
    }

    void memoryCopy(void* destination, const void* source, sizetype size) {
        if (destination == nullptr || source == nullptr || size == 0) return;

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

using enhanced::NothrowRef;
using enhanced::nothrow;

// TODO

$RetNotNull $Allocator
void* operator new(sizetype size) {
    void* space = memoryAlloc(size);
    if (space == nullptr) {
        throw MemoryAllocationError("Cannot allocate memory");
    }
    return space;
}

$RetNotNull $Allocator
void* operator new[](sizetype size) {
    return operator new(size);
}

$RetNullable $SuccessIf(return != nullptr) $Allocator $RetRestrict
void* operator new(sizetype size, enhanced::NothrowRef) noexcept {
    return memoryAlloc(size);
}

$RetNullable $SuccessIf(return != nullptr) $Allocator $RetRestrict
void* operator new[](sizetype size, enhanced::NothrowRef) noexcept {
    return operator new(size, nothrow);
}

GCC_WARNING_PUSH_AND_DISABLE("-Wsized-deallocation")

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
