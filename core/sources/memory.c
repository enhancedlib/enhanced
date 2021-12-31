/*
 * Copyright (C) 2021 Liu Baihao.
 * This product is licensed under Enhanced License.
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
    if (size < 1) {
        return null;
    }
    return malloc(size);
}

void memoryFree(void *const ptr) {
    if (ptr != null) {
        free(ptr);
    }
}

void memorySet(void *const ptr, const Byte byte, const Size size) {
    assert(ptr != null), assert(size > 0);

    for (Size index = 0; index < size; ++ index) {
        ((Byte *) ptr)[index] = byte;
    }
}

void memoryCopy(void *const target, void *const source, const Size size) {
    assert(target != null), assert(source != null), assert(size > 0);

    for (Size index = 0; index < size; ++ index) {
        ((Byte *) target)[index] = ((Byte *) source)[index];
    }
}
