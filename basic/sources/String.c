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

#include "enhanced/basic/String.h"

#include "enhanced/core/defines.h"
#include "enhanced/core/types.h"
#include "enhanced/core/assert.h"
#include "enhanced/core/memory.h"
#include "enhanced/core/string.h"

/*!
 * Get the length of the string.
 *
 * @param self The string.
 * @return
 */
static Size getLength(const String* self);

/*!
 * To concatenate the current string with another string.
 *
 * @param self The string.
 * @param str
 * @return String
 */
static String add(String* self, String str);

String newEmptyString() {
    char* value = (char*) memoryAlloc(sizeof(char));
    *value = '\0';
    return newStringExt(value, 0);
}

String toString(char* const value) {
    return newStringExt(value, stringLength(value));
}

String newString(const Size length) {
    char* value = (char*) memoryAlloc((length + 1) * sizeof(char));
    return newStringExt(value, length);
}

String newStringExt(const char* const value, const Size length) {
    String string = {
        .value = (char*) value,
        .length = length,
        .getLength = getLength,
        .add = add
    };
    return string;
}

Size getLength(const String* self) {
    return self->length;
}

String add(String* self, String str) {
    assert(self != null), assert(str.length > 0);

    Size newLength = self->length + str.length;
    char* newString = (char*) memoryAlloc((newLength + 1) * sizeof(char));
    if (newString == null) {
        return *self;
    }

    for (Size index = 0; index < self->length; ++index) {
        newString[index] = self->value[index];
    }
    for (Size index = self->length; index < newLength; ++index) {
        newString[index] = str.value[index - self->length];
    }

    self->length = newLength;
    self->value = newString;

    return *self;
}
