/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 *
 * Licensed under the Enhanced Software License.
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://sharedwonder.github.io/enhanced/LICENSE.txt
 *
 * UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING,
 * THE SOFTWARE IS ALWAYS PROVIDED "AS IS",
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#include <enhanced/core/String.h>

#include <enhanced/core/defines.h>
#include <enhanced/core/types.h>
#include <enhanced/core/annotations.h>
#include <enhanced/core/memory.h>
#include <enhanced/core/stringUtil.h>
#include <enhanced/core/CharSequence.h>
#include <enhanced/core/MutableString.h>
#include <enhanced/core/collections/List.h>
#include <enhanced/core/collections/ArrayList.h>

using enhanced::core::BasicString;
using enhanced::core::MutableBasicString;
using enhanced::core::collections::List;
using enhanced::core::collections::ArrayList;

template <typename CharType>
BasicString<CharType>::BasicString(NotNull CharType* value, Size length) noexcept : CharSequence<CharType>(value, length)  {}

template <typename CharType>
BasicString<CharType>::BasicString(NotNull const CharType* value) noexcept : BasicString(const_cast<CharType*>(value)) {}

template <typename CharType>
BasicString<CharType>::BasicString(NotNull CharType* value) noexcept : CharSequence<CharType>(value, tstringLength(value)) {}

template <typename CharType>
BasicString<CharType>::BasicString(const BasicString& other) noexcept = default;

template <typename CharType>
BasicString<CharType>::BasicString(BasicString&& other) noexcept = default;

template <typename CharType>
RetCannotIgnored
Size BasicString<CharType>::indexOf(const CharType ch) const noexcept {
    for (Size index = 0; index < this->length; ++index) {
        if (this->value[index] == ch) {
            return index;
        }
    }

    return SIZE_MAX;
}

template <typename CharType>
RetCannotIgnored
Size BasicString<CharType>::indexOf(const BasicString& string) const noexcept {
    Size substringIndex = 0;

    for (Size index = 0; index < this->length; ++index) {
        if (this->value[index] == string[substringIndex]) {
            ++substringIndex;
        } else {
            substringIndex = 0;
        }

        if (substringIndex == string.length) {
            return index - string.length + 1;
        }
    }

    return SIZE_MAX;
}

template <typename CharType>
RetCannotIgnored
Size BasicString<CharType>::indexOf(const CharType ch, const Size getN) const noexcept {
    Size indexN = 0;

    for (Size index = 0; index < this->length; ++index) {
        if (this->value[index] == ch) {
            if (getN == indexN) {
                return index;
            } else {
                ++indexN;
            }
        }
    }

    return SIZE_MAX;
}

template <typename CharType>
RetCannotIgnored
Size BasicString<CharType>::indexOf(const BasicString& string, const Size getN) const noexcept {
    Size indexN = 0;
    Size substringIndex = 0;

    for (Size index = 0; index < this->length; ++index) {
        if (this->value[index] == string[substringIndex]) {
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

    return SIZE_MAX;
}

template <typename CharType>
RetCannotIgnored
Size BasicString<CharType>::lastIndexOf(const CharType ch) const noexcept {
    for (Size index = this->length - 1;; --index) {
        if (this->value[index] == ch) {
            return index;
        }

        if (index == 0) {
            break;
        }
    }

    return SIZE_MAX;
}

template <typename CharType>
RetCannotIgnored
Size BasicString<CharType>::lastIndexOf(const BasicString& string) const noexcept {
    Size substringIndex = string.length - 1;

    for (Size index = this->length - 1;; --index) {
        if (this->value[index] == string[substringIndex]) {
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

    return SIZE_MAX;
}

template <typename CharType>
RetCannotIgnored
Size BasicString<CharType>::lastIndexOf(const CharType ch, const Size getN) const noexcept {
    Size indexN = 0;

    for (Size index = this->length - 1;; --index) {
        if (this->value[index] == ch) {
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

    return SIZE_MAX;
}

template <typename CharType>
RetCannotIgnored
Size BasicString<CharType>::lastIndexOf(const BasicString& string, const Size getN) const noexcept {
    Size indexN = 0;
    Size substringIndex = string.length - 1;

    for (Size index = this->length - 1;; --index) {
        if (this->value[index] == string[substringIndex]) {
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

    return SIZE_MAX;
}

template <typename CharType>
RetRequiresRelease
ArrayList<Size> BasicString<CharType>::indexOfAll(const CharType ch) const noexcept {
    ArrayList<Size> allIndexes;

    for (Size index = 0; index < this->length; ++index) {
        if (this->value[index] == ch) {
            allIndexes.add(index);
        }
    }

    return allIndexes;
}

template <typename CharType>
RetRequiresRelease
ArrayList<Size> BasicString<CharType>::indexOfAll(const BasicString& string) const noexcept {
    ArrayList<Size> allIndexes;
    Size substringIndex = 0;

    for (Size index = 0; index < this->length; ++index) {
        if (this->value[index] == string[substringIndex]) {
            ++substringIndex;
        } else {
            substringIndex = 0;
        }

        if (substringIndex == string.length) {
            allIndexes.add(index - string.length + 1);
        }
    }

    return allIndexes;
}

template <typename CharType>
RetCannotIgnored
MutableBasicString<CharType> BasicString<CharType>::replace(CharType oldChar, CharType newChar) const {
    return MutableBasicString<CharType>(this->value).replaceTo(oldChar, newChar);
}

template <typename CharType>
RetCannotIgnored
MutableBasicString<CharType> BasicString<CharType>::replace(const BasicString& oldSubstring, const BasicString& newSubstring) const {
    return MutableBasicString<CharType>(this->value).replaceTo(oldSubstring, newSubstring);
}

template <typename CharType>
RetCannotIgnored
MutableBasicString<CharType> BasicString<CharType>::replace(CharType oldChar, const BasicString& newSubstring) const {
    return MutableBasicString<CharType>(this->value).replaceTo(oldChar, newSubstring);
}

template <typename CharType>
RetCannotIgnored
MutableBasicString<CharType> BasicString<CharType>::replace(const BasicString& oldSubstring, CharType newChar) const {
    return MutableBasicString<CharType>(this->value).replaceTo(oldSubstring, newChar);
}

template <typename CharType>
MutableBasicString<CharType> BasicString<CharType>::uppercase() const {
    return MutableBasicString<CharType>(this->value).toUppercase();
}

template <typename CharType>
MutableBasicString<CharType> BasicString<CharType>::lowercase() const {
    return MutableBasicString<CharType>(this->value).toLowercase();
}

template <typename CharType>
bool BasicString<CharType>::operator==(const BasicString& string) const noexcept {
    return tstringEqual(this->value, string.value);
}

template <typename CharType>
RetCannotIgnored
MutableBasicString<CharType> BasicString<CharType>::operator+(const BasicString& string) const {
    Size newLength = this->length + string.length;
    MutableBasicString<CharType> newString(newLength);

    memoryCopy(newString.value, this->value, newLength);
    memoryCopy(newString.value + this->length, string.value, newLength);

    return newString;
}

template <typename CharType>
BasicString<CharType>& BasicString<CharType>::operator=(const BasicString& other) noexcept = default;

template <typename CharType>
BasicString<CharType>& BasicString<CharType>::operator=(BasicString&& other) noexcept = default;

template class enhanced::core::BasicString<char>;
template class enhanced::core::BasicString<wchar>;
