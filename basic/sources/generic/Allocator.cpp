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
    this->space = operator new(newSize * sizeOfType);
}

void Allocator0::destroy0() {
    memoryFree(this->space);
}

void Allocator0::resize0(Size resize, Size sizeOfType) {
    this->size = resize;
    void *copy = operator new(resize * sizeOfType);
    memoryCopy(copy, this->space, this->size);
    operator delete(this->space);
    this->space = copy;
}
