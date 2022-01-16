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

#include "EnhancedBasic/generic/Allocator.h"

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/memory.h"

using EnhancedBasic::generic::Allocator0;

Size Allocator0::getSize0() const {
    return this->size;
}

void Allocator0::allocate0(Size newSize, Size sizeOfType) {
    this->size = newSize;
    this->space = memoryAlloc(newSize * sizeOfType);
}

void Allocator0::destroy0() {
    memoryFree(this->space);
}

void Allocator0::resize0(Size resize, Size sizeOfType) {
    this->size = resize;
    void *copy = memoryAlloc(resize * sizeOfType);
    memoryCopy(copy, this->space, this->size);
    memoryFree(this->space);
    this->space = copy;
}
