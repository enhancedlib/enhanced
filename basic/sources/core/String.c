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

#include "EnhancedBasic/core/String.h"

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/memory.h"
#include "EnhancedCore/string.h"

/*!
 * This function is internal to this file and should not be called from outside.
 *
 * Creates data of type String.
 *
 * @param value
 * @param length
 * @return
 */
static String newString0(char *value, Size length);

/*!
 * This function is internal to this file and should not be called from outside.
 *
 * Creates a pointer of type String.
 *
 * @param value
 * @param length
 * @return
 */
static String *newStringPointer0(char *value, Size length);

/*!
 * To concatenate the current string with another string.
 *
 * @param self
 * @param str
 * @return String
 */
static String add(String *self, String str);

String newEmptyString() {
    char *value = (char *) memoryAlloc(sizeof(char));
    *value = '\0';
    return newString0(value, 0);
}

String *newEmptyStringPointer() {
    char *value = (char *) memoryAlloc(sizeof(char));
    if (value == null) {
        return null;
    }
    *value = '\0';
    return newStringPointer0(value, 0);
}

String toString(char *value) {
    return newString0(value, stringLength(value));
}

String *toStringPointer(char *value) {
    if (value == null) {
        return null;
    }
    return newStringPointer0(value, stringLength(value));
}

String newString(Size length) {
    char *str = (char *) memoryAlloc((length + 1) * sizeof(char));

    return newString0(str, length);
}

String *newStringPointer(Size length) {
    if (length < 1) {
        return null;
    }
    return newStringPointer0((char *) memoryAlloc((length + 1) * sizeof(char)), length);
}

static String add(String *self, String str) {
    if (self == null || str.length < 1) {
        return str;
    }

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

static String newString0(char *value, Size length) {
    String self;

    self.value = value;
    self.length = length;
    self.add = add;

    return self;
}

static String *newStringPointer0(char *value, Size length) {
    String *self = (String *) memoryAlloc(sizeof(String));
    if (self == null) {
        return null;
    }

    self->value = value;
    self->length = length;
    self->add = add;

    return self;
}
