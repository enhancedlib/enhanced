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

#include "enhanced/basic/util/Allocator.h"

#include "enhanced/core/defines.h"
#include "enhanced/core/types.h"
#include "enhanced/core/memory.h"

using enhanced::basic::generic_impl::util::Allocator0;

Size Allocator0::getSize0() const {
    return size;
}

void Allocator0::allocate0(Size newSize, Size sizeOfType) {
    size = newSize;
    space = operator new(size * sizeOfType);
}

void Allocator0::destroy0() {
    memoryFree(space);
}

void Allocator0::resize0(Size resize, Size sizeOfType) {
    size = resize;
    void* copy = operator new(resize * sizeOfType);
    memoryCopy(copy, space, size);
    operator delete(space);
    space = copy;
}
