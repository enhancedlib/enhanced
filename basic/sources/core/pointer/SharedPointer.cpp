/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 * This software is licensed under Enhanced License.
 *
 * This copyright notice is subject to change without notice.
 *
 * This software is a free software, everyone can change,
 * copy, publication, demonstrate, use, etc.
 *
 * This software and documentation may provide
 * third-party content, product and other information.
 * The Licensor is not responsible for any loss or damage
 * caused by your access to or use of third-party content, products, etc.
 *
 * For any loss or damage caused by this software,
 * the licensor may provide possible solutions,
 * but it does not mean that the licensor will definitely solve the problem.
 * In no event shall the licensor be liable for any claims,
 * damages or other liabilities.
 *
 * You should see a copy of Enhanced License in this software, if not, visit
 * <https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt>
 */

#include "Enhanced/basic/core/pointer/SharedPointer.h"

#include "Enhanced/core/defines.h"
#include "Enhanced/core/types.h"
#include "Enhanced/core/annotations.h"

using EnhancedGenericImpl::basic::core::pointer::SharedPointerImpl;

SharedPointerImpl::SharedPointerImpl(void* ptr, SharedPointerImpl::GenericOperator genericOperator) :
    pointer(ptr), referenceCount(new Size(1)), genericOperator(genericOperator) {}

SharedPointerImpl::SharedPointerImpl(const SharedPointerImpl& other) :
    pointer(other.pointer), referenceCount(other.referenceCount), genericOperator(other.genericOperator) {
    ++ (*other.referenceCount);
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
    ++ (*referenceCount);
}
