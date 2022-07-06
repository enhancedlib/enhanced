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

#include <malloc.h>

#include "Enhanced/core/memory.h"

#include "Enhanced/core/defines.h"
#include "Enhanced/core/annotations.h"
#include "Enhanced/core/assert.h"
#include "Enhanced/core/types.h"

MustInspectResult RetRequiresRelease()
void* memoryAlloc(const Size size) {
    assert(size > 0);

    return malloc(size);
}

void memoryFree(void* const pointer) {
    if (pointer != null) {
        free(pointer);
    }
}

void memorySet(void* ptr, const Byte byte, const Size size) {
    assert(ptr != null), assert(size > 0);

    for (Size index = 0; index < size; ++ index) {
        ((Byte*) ptr)[index] = byte;
    }
}

void memoryCopy(void* destination, const void* const source, const Size size) {
    assert(destination != null), assert(source != null), assert(size > 0);

    Size countBlock = size / sizeof(qword);
    Size countByte = size % sizeof(qword);

    while ((countBlock--) > 0) {
        ((qword*) destination)[countBlock] = ((qword*) source)[countBlock];
    }

    while ((countByte--) > 0) {
        ((Byte*) destination)[countByte] = ((Byte*) source)[countByte];
    }
}
