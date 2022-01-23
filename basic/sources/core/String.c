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

#include "EnhancedBasic/core/String.h"

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/assert.h"
#include "EnhancedCore/memory.h"
#include "EnhancedCore/string.h"

using(EnhancedBasic$core$String);

/*!
 * Get the length of the string.
 *
 * @param self The string.
 * @return
 */
static Size getLength(const String *self);

/*!
 * To concatenate the current string with another string.
 *
 * @param self The string.
 * @param str
 * @return String
 */
static String add(String *self, String str);

String newEmptyString() {
    char *value = (char *) memoryAlloc(sizeof(char));
    *value = '\0';
    return newStringExt(value, 0);
}

String toString(char *const value) {
    return newStringExt(value, stringLength(value));
}

String newString(const Size length) {
    char *value = (char *) memoryAlloc((length + 1) * sizeof(char));
    return newStringExt(value, length);
}

String newStringExt(const char *const value, const Size length) {
    String string = {(char *) value, length, getLength, add};
    return string;
}

Size getLength(const String *self) {
    return self->length;
}

String add(String *self, String str) {
    assert(self != null), assert(str.length > 0);

    Size new_length = self->length + str.length;
    char *new_str = (char *) memoryAlloc((new_length + 1) * sizeof(char));
    if (new_str == null) {
        return *self;
    }

    for (Size index = 0; index < self->length; ++ index) {
        new_str[index] = self->value[index];
    }
    for (Size index = self->length; index < new_length; ++ index) {
        new_str[index] = str.value[index - self->length];
    }

    self->length = new_length;
    self->value = new_str;

    return *self;
}
