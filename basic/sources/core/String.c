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

#include "Enhanced/basic/core/String.h"

#include "Enhanced/core/defines.h"
#include "Enhanced/core/types.h"
#include "Enhanced/core/assert.h"
#include "Enhanced/core/memory.h"
#include "Enhanced/core/string.h"

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

    for (Size index = 0; index < self->length; ++ index) {
        newString[index] = self->value[index];
    }
    for (Size index = self->length; index < newLength; ++ index) {
        newString[index] = str.value[index - self->length];
    }

    self->length = newLength;
    self->value = newString;

    return *self;
}
