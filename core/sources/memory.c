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

#include <malloc.h>

#include "enhanced/core/memory.h"

#include "enhanced/core/defines.h"
#include "enhanced/core/types.h"
#include "enhanced/core/annotations.h"
#include "enhanced/core/assert.h"
#include "enhanced/core/types.h"

MustInspectResult Nullable RetRequiresRelease
void* memoryAlloc(const Size size) {
    assert(size > 0);

    return malloc(size);
}

void memoryFree(void* const pointer) {
    if (pointer != null) {
        free(pointer);
    }
}

void memorySet(void* ptr, const byte aByte, const Size size) {
    assert(ptr != null), assert(size > 0);

    for (Size index = 0; index < size; ++index) {
        ((byte*) ptr)[index] = aByte;
    }
}

void memoryCopy(void* destination, const void* const source, const Size size) {
    assert(destination != null), assert(source != null), assert(size > 0);

    Size countBlock = size / sizeof(qword);
    Size countByte = size % sizeof(qword);

    for (Size index = 0; index < countBlock; ++index) {
        ((qword*) destination)[index] = ((qword*) source)[index];
    }

    for (Size index = size - countByte; index < size; ++index) {
        ((byte*) destination)[index] = ((byte*) source)[index];
    }
}
