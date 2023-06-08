/*
 * This file is part of Enhanced Framework.
 *
 * Copyright (C) 2023 Liu Baihao (sharedwonder). All rights reserved.
 *
 * Permission is hereby granted, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software,
 * including without limitation the rights to use, copy, modify, merge,
 * distribute, subject to the following restrictions:
 *
 * 1. The above copyright notice and this permission notice shall be included in
 *    all copies of the Software and modified versions.
 *
 * 2. You may not charge any fees or receive other compensation for the
 *    distribution of the Software.
 *
 * 3. You may not misrepresent the source of the Software, and you may not claim
 *    that you wrote the original version.
 *
 * 4. If you use this Software in your product, you should indicate the it in
 *    the product documentation.
 *
 * Unless you have obtained the written consent of the copyright holders,
 * you may not break these restrictions.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
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
    E_ALLOCATOR E_RET_RESTRICT void* allocate(sizetype size) {
        if (size == 0) return nullptr;

        return malloc(size);
    }

    void release(void* pointer) {
        free(pointer);
    }

    void memoryFill(void* ptr, byte aByte, sizetype size) {
    #ifndef E_SM_COMPILER_MSVC
        __builtin_memset(ptr, aByte, size);
    #else
        if (ptr == nullptr || size == 0) return;

        for (sizetype index = 0; index < size; ++index) {
            ((byte*) ptr)[index] = aByte;
        }
    #endif
    }

    void memoryCopy(void* destination, const void* source, sizetype size) {
    #ifndef E_SM_COMPILER_MSVC
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
E_ALLOCATOR void* operator new(enhanced::sizetype size) {
    void* space = allocate(size);
    if (space == nullptr) {
        throw MemoryAllocationError("Cannot allocate memory");
    }
    return space;
}

E_ANNOTATE(RetNotNull)
E_ALLOCATOR void* operator new[](enhanced::sizetype size) {
    return operator new(size);
}

E_ANNOTATE(MustInspectResult, RetNullable, SuccessIf("return != nullptr"), RetRequiresRelease)
E_ALLOCATOR E_RET_RESTRICT void* operator new(enhanced::sizetype size, enhanced::NothrowRef) noexcept {
    return allocate(size);
}

E_ANNOTATE(MustInspectResult, RetNullable, SuccessIf("return != nullptr"), RetRequiresRelease)
E_ALLOCATOR E_RET_RESTRICT void* operator new[](enhanced::sizetype size, enhanced::NothrowRef) noexcept {
    return operator new(size, nothrow);
}

E_GCC_WARNING_PAD("-Wsized-deallocation")

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

E_GCC_WARNING_POP
