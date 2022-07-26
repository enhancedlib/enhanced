/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 *
 * This software is licensed under Enhanced License.
 * You may not use this file except in compliance with the License.
 * You should see a copy of Enhanced License in this software, if not, visit
 * <https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt>
 *
 * The Software is always provided "AS IS",
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 *
 */

#include <malloc.h>

#include "enhanced/core/memory.h"

#include "enhanced/core/defines.h"
#include "enhanced/core/types.h"
#include "enhanced/core/annotations.h"
#include "enhanced/core/assert.h"
#include "enhanced/core/types.h"

MustInspectResult Nullable RetRequiresRelease()
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

    while (countBlock-- > 0) {
        ((qword*) destination)[countBlock] = ((qword*) source)[countBlock];
    }

    while (countByte-- > 0) {
        ((byte*) destination)[countByte] = ((byte*) source)[countByte];
    }
}
