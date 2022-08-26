
/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 *
 * Licensed under the Enhanced License, Version 0.5.4 (the "License").
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt
 *
 * UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING,
 * THE SOFTWARE IS ALWAYS PROVIDED "AS IS",
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#include "enhanced/basic/util/SharedPointer.h"

#include "enhanced/core/defines.h"
#include "enhanced/core/types.h"
#include "enhanced/core/annotations.h"

using enhanced::basic::generic_impl::util::SharedPointerImpl;

SharedPointerImpl::SharedPointerImpl(void* ptr, SharedPointerImpl::GenericOperator genericOperator) :
    pointer(ptr), referenceCount(new Size(1)), genericOperator(genericOperator) {}

SharedPointerImpl::SharedPointerImpl(const SharedPointerImpl& other) :
    pointer(other.pointer), referenceCount(other.referenceCount), genericOperator(other.genericOperator) {
    ++(*other.referenceCount);
}

SharedPointerImpl::~SharedPointerImpl() noexcept {
    release0();
}

void SharedPointerImpl::release0() noexcept {
    if ((--(*referenceCount)) == 0) {
        genericOperator.destroy(pointer);
        pointer = null;
        delete referenceCount;
    }
}

void SharedPointerImpl::assign0(void* value) noexcept {
    release0();
    referenceCount = new Size(1);
    pointer = value;
}

void SharedPointerImpl::assign0(const SharedPointerImpl& other) noexcept {
    release0();
    pointer = other.pointer;
    referenceCount = other.referenceCount;
    ++(*referenceCount);
}
