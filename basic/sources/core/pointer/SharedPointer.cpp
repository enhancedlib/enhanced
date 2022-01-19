/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 * This software is licensed under Enhanced License.
 *
 * This copyright disclaimer is subject to change without notice.
 *
 * This software is a free software,
 * everyone can change, copy, publication, demonstrate, use, etc.
 *
 * If you change and publication this software,
 * must credit the original software source and author's name,
 * and include this copyright disclaimer and
 * the license of this software in your software.
 *
 * This software and documentation may provide
 * third-party content, product and other information.
 * I am not responsible for any loss or damage caused
 * by your access to or use of third-party content, products, etc.
 */

#include "EnhancedBasic/core/pointer/SharedPointer.h"

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/annotations.h"

using EnhancedBasic::core::pointer::SharedPointer0;

SharedPointer0::SharedPointer0(void *ptr, SharedPointer0::GenericsOperator genericsOperator) :
    pointer(ptr), referenceCount(new Size(1)), genericsOperator(genericsOperator) {}

SharedPointer0::SharedPointer0(const SharedPointer0 &other) :
    pointer(other.pointer), referenceCount(other.referenceCount), genericsOperator(other.genericsOperator) {
    ++ (*other.referenceCount);
}

SharedPointer0::~SharedPointer0() noexcept {
    this->release0();
}

void SharedPointer0::release0() noexcept {
    if ((-- (*this->referenceCount)) == 0) {
        this->genericsOperator.destroy(this->pointer);
        this->pointer = null;
        delete this->referenceCount;
    }
}

void SharedPointer0::assign0(void *value) noexcept {
    this->release0();
    this->referenceCount = new Size(1);
    this->pointer = value;
}

void SharedPointer0::assign0(const SharedPointer0 &other) noexcept {
    this->release0();
    this->pointer = other.pointer;
    this->referenceCount = other.referenceCount;
    ++ (*this->referenceCount);
}
