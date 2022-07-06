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

#include "Enhanced/core/string.h"

#include "Enhanced/core/defines.h"
#include "Enhanced/core/types.h"
#include "Enhanced/core/assert.h"
#include "Enhanced/core/memory.h"

RetRequiresRelease()
char* stringNew(const Size length) {
    char* str = (char*) memoryAlloc((length + 1) * sizeof(char));
    if (str == null) {
        return null;
    }
    str[length] = '\0';

    return str;
}

RetNotIgnored()
Size stringLength(const char* const string) {
    assert(string != null);

    Size length;
    for (length = 0; string[length] != '\0'; ++ length) {
    }

    return length;
}

RetNotIgnored()
bool stringEqual(const char* const string1, const char* const string2) {
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

RetRequiresRelease()
char* stringCopy(const char* const string) {
    assert(string != null);

    Size length = stringLength(string);

    char* copy = stringNew(length);
    if (copy == null) {
        return null;
    }

    memoryCopy(copy, string, length);

    for (Size index = 0; index < length; ++ index) {
        copy[index] = string[index];
    }

    return copy;
}

RetRequiresRelease()
char* stringResize(const char* const string, const Size newSize) {
    assert(string != null), assert(newSize > 1);

    char* newString = stringNew(newSize);
    if (newString == null) {
        return null;
    }

    Size oldStringLen = stringLength(string);

    for (Size index = 0; index < oldStringLen; ++ index) {
        newString[index] = string[index];
    }

    return newString;
}
