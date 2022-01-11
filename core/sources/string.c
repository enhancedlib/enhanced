/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
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

#include "EnhancedCore/string.h"

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/assert.h"
#include "EnhancedCore/memory.h"

$RetRequiresRelease()
char *stringNew(const Size length) {
    char *str = (char *) memoryAlloc((length + 1) * sizeof(char));
    if (str == null) {
        return null;
    }
    str[length] = '\0';

    return str;
}

$RetNotIgnored()
Size stringLength(const char *const string) {
    assert(string != null);

    Size length;
    for (length = 0; string[length] != '\0'; ++ length) {
    }

    return length;
}

$RetNotIgnored()
bool stringEqual(const char *const string1, const char *const string2) {
    Size length;

    if (string1 == string2) {
        return true;
    } else if ((length = stringLength(string1)) == stringLength(string2)) {
        for (Size index = 0; index < length; ++ index) {
            if (string1[index] != string2[index]) {
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}

$RetRequiresRelease()
char *stringCopy(const char *const string) {
    assert(string != null);

    Size length = stringLength(string);

    char *copy = stringNew(length);
    if (copy == null) {
        return null;
    }

    for (Size index = 0; index < length; ++ index) {
        copy[index] = string[index];
    }

    return copy;
}

$RetRequiresRelease()
char *stringResize(const char *const string, const Size newSize) {
    assert(string == null), assert(newSize < 1);

    char *newString = stringNew(newSize);
    if (newString == null) {
        return null;
    }

    Size oldStringLen = stringLength(string);

    for (Size index = 0; index < oldStringLen; ++ index) {
        newString[index] = string[index];
    }

    return newString;
}
