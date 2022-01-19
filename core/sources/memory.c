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

#include "EnhancedCore/memory.h"

#include "EnhancedCore/defines.h"
#include "EnhancedCore/annotations.h"
#include "EnhancedCore/assert.h"
#include "EnhancedCore/types.h"

#include <malloc.h>

$RetRequiresRelease()
void *memoryAlloc(const Size size) {
    assert(size > 0);

    return malloc(size);
}

void memoryFree(void *const pointer) {
    if (pointer != null) {
        free(pointer);
    }
}

void memorySet(void *ptr, const Byte byte, const Size size) {
    assert(ptr != null), assert(size > 0);

    for (Size index = 0; index < size; ++ index) {
        ((Byte *) ptr)[index] = byte;
    }
}

void memoryCopy(void *destination, const void *const source, const Size size) {
    assert(destination != null), assert(source != null), assert(size > 0);

    Size countBlock = size / sizeof(qword);
    Size countByte = size % sizeof(qword);

    while ((countBlock --) > 0) {
        ((qword *) destination)[countBlock] = ((qword *) source)[countBlock];
    }

    while ((countByte --) > 0) {
        ((Byte *) destination)[countByte] = ((Byte *) source)[countByte];
    }
}
