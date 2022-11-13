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

#include <enhanced/core/util/SharedPtr.h>

#include <enhanced/core/defines.h>
#include <enhanced/core/types.h>
#include <enhanced/core/annotations.h>
#include <enhanced/core/memory.h>

using enhanced_internal::core::util::SharedPtrImpl;

SharedPtrImpl::SharedPtrImpl(void* ptr, GenericOperator genericOperator) :
    referenceCount(ptr != null ? new sizetype(1) : null), pointer(ptr), genericOperator(genericOperator) {}

SharedPtrImpl::SharedPtrImpl(const SharedPtrImpl& other) noexcept :
    referenceCount(other.referenceCount), pointer(other.pointer), genericOperator(other.genericOperator) {
    if (other.referenceCount != null) ++(*other.referenceCount);
}

SharedPtrImpl::SharedPtrImpl(SharedPtrImpl&& other) noexcept :
    referenceCount(other.referenceCount), pointer(other.pointer), genericOperator(other.genericOperator) {
    other.pointer = null;
    other.referenceCount = null;
}

SharedPtrImpl::~SharedPtrImpl() noexcept {
    release0();
}

func SharedPtrImpl::release0() noexcept -> void {
    if (referenceCount != null && (--(*referenceCount)) == 0) {
        genericOperator.destroy(pointer);
        pointer = null;
        delete referenceCount;
    }
}

func SharedPtrImpl::assign0(const SharedPtrImpl& other) noexcept -> void {
    release0();
    pointer = other.pointer;
    referenceCount = other.referenceCount;
    ++(*referenceCount);
}

func SharedPtrImpl::assign0(SharedPtrImpl&& other) noexcept -> void {
    release0();
    pointer = other.pointer;
    referenceCount = other.referenceCount;

    other.pointer = null;
    other.referenceCount = null;
}
