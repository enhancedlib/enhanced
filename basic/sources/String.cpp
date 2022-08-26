/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 *
 * Licensed under the Enhanced License, Version 0.5.4 (the "License").
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt
 *
 * UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING,
 * THE SOFTWARE IS ALWAYS PROVIDED "AS IS",
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#include "enhanced/basic/String.h"

#include "enhanced/core/defines.h"
#include "enhanced/core/types.h"
#include "enhanced/core/annotations.h"
#include "enhanced/core/memory.h"
#include "enhanced/core/string.h"

#include "enhanced/basic/MutableString.h"
#include "enhanced/basic/container/List.h"
#include "enhanced/basic/container/ArrayList.h"

using enhanced::basic::String;
using enhanced::basic::CharSequence;
using enhanced::basic::MutableString;
using enhanced::basic::container::List;
using enhanced::basic::container::ArrayList;

String::String(NotNull char* value, Size length) : CharSequence<char>(value, length) {}

String::String(NotNull const char* const value) : String(const_cast<char*>(value)) {}

String::String(NotNull char* const value) : CharSequence<char>(value, stringLength(value)) {}

String::String(const String& other) : CharSequence<char>(other, other.length) {}

RetCannotIgnored
Size String::indexOf(const char ch) const {
    for (Size index = 0; index < length; ++index) {
        if (value[index] == ch) {
            return index;
        }
    }

    return -1;
}

RetCannotIgnored
Size String::indexOf(const String& string) const {
    Size substringIndex = 0;

    for (Size index = 0; index < length; ++index) {
        if (value[index] == string[substringIndex]) {
            ++substringIndex;
        } else {
            substringIndex = 0;
        }

        if (substringIndex == string.length) {
            return index - string.length + 1;
        }
    }

    return -1;
}

RetCannotIgnored
Size String::indexOf(const char ch, const Size getN) const {
    Size indexN = 0;

    for (Size index = 0; index < length; ++index) {
        if (value[index] == ch) {
            if (getN == indexN) {
                return index;
            } else {
                ++indexN;
            }
        }
    }

    return -1;
}

RetCannotIgnored
Size String::indexOf(const String& string, const Size getN) const {
    Size indexN = 0;
    Size substringIndex = 0;

    for (Size index = 0; index < length; ++index) {
        if (value[index] == string[substringIndex]) {
            ++substringIndex;
        } else {
            substringIndex = 0;
        }

        if (substringIndex == string.length) {
            if (getN == indexN) {
                return index - string.length + 1;
            } else {
                ++indexN;
            }
        }
    }

    return -1;
}

RetCannotIgnored
Size String::lastIndexOf(const char ch) const {
    for (Size index = length - 1;; --index) {
        if (value[index] == ch) {
            return index;
        }

        if (index == 0) {
            break;
        }
    }

    return -1;
}

RetCannotIgnored
Size String::lastIndexOf(const String& string) const {
    Size substringIndex = string.length - 1;

    for (Size index = length - 1;; --index) {
        if (value[index] == string[substringIndex]) {
            --substringIndex;
        } else {
            substringIndex = string.length - 1;
        }

        if (substringIndex == string.length) {
            return index;
        }

        if (index == 0) {
            break;
        }
    }

    return -1;
}

RetCannotIgnored
Size String::lastIndexOf(const char ch, const Size getN) const {
    Size indexN = 0;

    for (Size index = length - 1;; --index) {
        if (value[index] == ch) {
            if (getN == indexN) {
                return index;
            } else {
                ++indexN;
            }
        }

        if (index == 0) {
            break;
        }
    }

    return -1;
}

RetCannotIgnored
Size String::lastIndexOf(const String& string, const Size getN) const {
    Size indexN = 0;
    Size substringIndex = string.length - 1;

    for (Size index = length - 1;; --index) {
        if (value[index] == string[substringIndex]) {
            --substringIndex;
        } else {
            substringIndex = string.length - 1;
        }

        if (substringIndex == string.length) {
            if (getN == indexN) {
                return index;
            } else {
                ++indexN;
            }
        }

        if (index == 0) {
            break;
        }
    }

    return -1;
}

RetRequiresRelease
List<Size>* String::indexOfAll(const char ch) const {
    List<Size>* allIndexes = new ArrayList<Size>();

    for (Size index = 0; index < length; ++index) {
        if (value[index] == ch) {
            allIndexes->add(index);
        }
    }

    return allIndexes;
}

RetRequiresRelease
List<Size>* String::indexOfAll(const String& string) const {
    List<Size>* allIndexes = new ArrayList<Size>();
    Size substringIndex = 0;

    for (Size index = 0; index < length; ++index) {
        if (value[index] == string[substringIndex]) {
            ++substringIndex;
        } else {
            substringIndex = 0;
        }

        if (substringIndex == string.length) {
            allIndexes->add(index - string.length + 1);
        }
    }

    return allIndexes;
}

MutableString String::uppercase() {
    return MutableString(value).toUppercase();
}

MutableString String::lowercase() {
    return MutableString(value).toLowercase();
}

bool String::operator==(const String& string) const {
    return stringEqual(value, string.value);
}

RetCannotIgnored
MutableString String::operator+(const String& string) const {
    Size newLength = length + string.length;
    MutableString newString(newLength);

    memoryCopy(newString.value, value, newLength);
    memoryCopy(newString.value + length, string.value, newLength);

    return newString;
}
