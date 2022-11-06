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

#include <enhanced/core/stringUtil.h>

#include <enhanced/core/defines.h>
#include <enhanced/core/types.h>
#include <enhanced/core/assert.h>
#include <enhanced/core/memory.h>

namespace enhanced::core {
    template <typename CharType>
    RetRequiresRelease
    CharType* tstringNew(const Size length) {
        auto str = new CharType[length + 1];
        str[length] = 0;
        return str;
    }

    template <typename CharType>
    RetRequiresRelease
    CharType* tstringCopy(NotNull const CharType* source) {
        return tstringCopyExt(source, tstringLength(source));
    }

    template <typename CharType>
    RetRequiresRelease
    CharType* tstringCopyExt(NotNull const CharType* source, const Size length) {
        assert(source != null);

        auto copy = tstringNew<CharType>(length);
        memoryCopy(copy, source, length);

        return copy;
    }

    template <typename CharType>
    RetRequiresRelease
    CharType* tstringCopyResize(NotNull const CharType* source, Size oldSize, Size newSize) {
        assert(source != null);

        auto copy = tstringNew<CharType>(newSize);
        memoryCopy(copy, source, (newSize > oldSize) ? oldSize : newSize);

        return copy;
    }

    template <typename CharType>
    Size tstringLength(NotNull const CharType* string) noexcept {
        assert(string != null);

        Size length;
        for (length = 0; string[length] != 0; ++length) {}

        return length;
    }

    template <typename CharType>
    RetCannotIgnored
    bool tstringEqual(const CharType* string1, const CharType* string2) noexcept {
        Size length;

        if (string1 == string2) {
            return true;
        } else if (string1 == null || string2 == null) {
            return false;
        } else if ((length = tstringLength(string1)) == tstringLength(string2)) {
            for (Size index = 0; index < length; ++index) {
                if (string1[index] != string2[index]) return false;
            }
            return true;
        }

        return false;
    }

    template <typename CharType>
    RetCannotIgnored
    bool tstringEqualExt(const CharType* string1, const Size length1, const CharType* string2, Size length2) noexcept {
        if (string1 == string2) {
            return true;
        } else if (string1 == null || string2 == null) {
            return false;
        } else if (length1 == length2) {
            for (Size index = 0; index < length1; ++index) {
                if (string1[index] != string2[index]) return false;
            }
            return true;
        }

        return false;
    }

    template char* tstringNew(Size length);
    template wchar* tstringNew(Size length);
    template char* tstringCopy(NotNull const char* source);
    template wchar* tstringCopy(NotNull const wchar* source);
    template char* tstringCopyExt(NotNull const char* source, Size length);
    template wchar* tstringCopyExt(NotNull const wchar* source, Size length);
    template char* tstringCopyResize(NotNull const char* source, Size oldSize, Size newSize);
    template wchar* tstringCopyResize(NotNull const wchar* source, Size oldSize, Size newSize);
    template Size tstringLength(NotNull const char* string) noexcept;
    template Size tstringLength(NotNull const wchar* string) noexcept;
    template bool tstringEqual(const char* string1, const char* string2) noexcept;
    template bool tstringEqual(const wchar* string1, const wchar* string2) noexcept;
    template bool tstringEqualExt(const char* string1, Size length1, const char* string2, Size length2) noexcept;
    template bool tstringEqualExt(const wchar* string1, Size length1, const wchar* string2, Size length2) noexcept;
}
