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

#include <enhanced/util/SharedPtr.h>

#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/Memory.h>

using enhanced::sizetype;

namespace enhancedInternal::util {
    SharedPtrImpl::SharedPtrImpl(void* ptr) : referenceCount(ptr != nullptr ? new sizetype(1) : nullptr), pointer(ptr), end(ptr) {}

    SharedPtrImpl::SharedPtrImpl(void* ptr, void* end) : referenceCount(ptr != nullptr ? new sizetype(1) : nullptr), pointer(ptr), end(end) {}

    SharedPtrImpl::SharedPtrImpl(const SharedPtrImpl& other) noexcept :
        referenceCount(other.referenceCount), pointer(other.pointer), end(other.end) {
        if (other.referenceCount != nullptr) ++(*other.referenceCount);
    }

    SharedPtrImpl::SharedPtrImpl(SharedPtrImpl&& other) noexcept :
        referenceCount(other.referenceCount), pointer(other.pointer), end(other.end) {
        other.pointer = nullptr;
        other.end = nullptr;
        other.referenceCount = nullptr;
    }

    void SharedPtrImpl::release0(OpDestroy opDestroy) const noexcept {
        if (referenceCount != nullptr && (--(*referenceCount)) == 0) {
            opDestroy(pointer, end);
            delete referenceCount;
            referenceCount = nullptr;
        }
    }

    void SharedPtrImpl::assign0(const SharedPtrImpl& other, OpDestroy opDestroy) noexcept {
        release0(opDestroy);

        pointer = other.pointer;
        end = other.end;
        referenceCount = other.referenceCount;

        if (referenceCount != nullptr) ++(*referenceCount);
    }

    void SharedPtrImpl::assign0(SharedPtrImpl&& other, OpDestroy opDestroy) noexcept {
        release0(opDestroy);

        pointer = other.pointer;
        end = other.end;
        referenceCount = other.referenceCount;

        other.pointer = nullptr;
        other.end = nullptr;
        other.referenceCount = nullptr;
    }
}
