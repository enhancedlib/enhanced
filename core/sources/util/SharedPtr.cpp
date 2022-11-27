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

#include <enhanced/util/SharedPtr.h>

#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/Memory.h>

namespace enhancedInternal::util {
    SharedPtrImpl::SharedPtrImpl(void* ptr) :
        referenceCount(ptr != null ? new sizetype(1) : null), pointer(ptr), end(ptr) {}

    SharedPtrImpl::SharedPtrImpl(void* ptr, void* end) :
        referenceCount(ptr != null ? new sizetype(1) : null), pointer(ptr), end(end) {}

    SharedPtrImpl::SharedPtrImpl(const SharedPtrImpl& other) noexcept :
        referenceCount(other.referenceCount), pointer(other.pointer), end(other.end) {
        if (other.referenceCount != null) ++(*other.referenceCount);
    }

    SharedPtrImpl::SharedPtrImpl(SharedPtrImpl&& other) noexcept :
        referenceCount(other.referenceCount), pointer(other.pointer), end(other.end) {
        other.pointer = null;
        other.end = null;
        other.referenceCount = null;
    }

    func SharedPtrImpl::release0(OpDestroy opDestroy) const noexcept -> void {
        if (referenceCount != null && (--(*referenceCount)) == 0) {
            opDestroy(pointer, end);
            delete referenceCount;
            referenceCount = null;
        }
    }

    func SharedPtrImpl::assign0(const SharedPtrImpl& other, OpDestroy opDestroy) noexcept -> void {
        release0(opDestroy);

        pointer = other.pointer;
        end = other.end;
        referenceCount = other.referenceCount;

        if (referenceCount != null) ++(*referenceCount);
    }

    func SharedPtrImpl::assign0(SharedPtrImpl&& other, OpDestroy opDestroy) noexcept -> void {
        release0(opDestroy);

        pointer = other.pointer;
        end = other.end;
        referenceCount = other.referenceCount;

        other.pointer = null;
        other.end = null;
        other.referenceCount = null;
    }
}
