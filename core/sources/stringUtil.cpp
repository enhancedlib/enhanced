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
#include <enhanced/core/annotations.h>
#include <enhanced/core/types.h>
#include <enhanced/core/memory.h>
#include <enhanced/core/exception/NullPointerException.h>

using enhanced::core::exception::NullPointerException;

namespace enhanced::core {
    template <typename CharType>
    RetRequiresRelease
    CharType* tstringNew(sizetype length) {
        auto str = new CharType[length + 1];
        str[length] = 0;
        return str;
    }

    template <typename CharType>
    RetRequiresRelease
    CharType* tstringCopy(const CharType* source) {
        return tstringCopyExt(source, tstringLength(source));
    }

    template <typename CharType>
    RetRequiresRelease
    CharType* tstringCopyExt(const CharType* source, sizetype length) {
        if (source == null) throw NullPointerException("The given argument 'source' is null");

        auto copy = tstringNew<CharType>(length);
        memoryCopy(copy, source, length);

        return copy;
    }

    template <typename CharType>
    RetRequiresRelease
    CharType* tstringCopyResize(const CharType* source, sizetype oldSize, sizetype newSize) {
        if (source == null) throw NullPointerException("The given argument 'source' is null");

        auto copy = tstringNew<CharType>(newSize);
        memoryCopy(copy, source, (newSize > oldSize) ? oldSize : newSize);

        return copy;
    }

    template <typename CharType>
    sizetype tstringLength(const CharType* string) {
        if (string == null) throw NullPointerException("The given argument 'string' is null");

        sizetype length;
        for (length = 0; string[length] != 0; ++length) {}

        return length;
    }

    template <typename CharType>
    NoIgnoreRet
    bool tstringEqual(const CharType* string1, const CharType* string2) noexcept {
        if (string1 == string2) {
            return true;
        } else if (string1 == null || string2 == null) {
            return false;
        } else {
            for (sizetype index = 0;; ++index) {
                if ((string1[index] == 0) ^ (string2[index] == 0)) return false;
                if (string1[index] != string2[index]) return false;
            }
        }
    }

    template char* tstringNew(sizetype length);
    template wchar* tstringNew(sizetype length);
    template u8char* tstringNew(sizetype length);
    template u16char* tstringNew(sizetype length);
    template u32char* tstringNew(sizetype length);

    template char* tstringCopy(const char* source);
    template wchar* tstringCopy(const wchar* source);
    template u8char* tstringCopy(const u8char* source);
    template u16char* tstringCopy(const u16char* source);
    template u32char* tstringCopy(const u32char* source);

    template char* tstringCopyExt(const char* source, sizetype length);
    template wchar* tstringCopyExt(const wchar* source, sizetype length);
    template u8char* tstringCopyExt(const u8char* source, sizetype length);
    template u16char* tstringCopyExt(const u16char* source, sizetype length);
    template u32char* tstringCopyExt(const u32char* source, sizetype length);

    template char* tstringCopyResize(const char* source, sizetype oldSize, sizetype newSize);
    template wchar* tstringCopyResize(const wchar* source, sizetype oldSize, sizetype newSize);
    template u8char* tstringCopyResize(const u8char* source, sizetype oldSize, sizetype newSize);
    template u16char* tstringCopyResize(const u16char* source, sizetype oldSize, sizetype newSize);
    template u32char* tstringCopyResize(const u32char* source, sizetype oldSize, sizetype newSize);

    template sizetype tstringLength(const char* string);
    template sizetype tstringLength(const wchar* string);
    template sizetype tstringLength(const u8char* string);
    template sizetype tstringLength(const u16char* string);
    template sizetype tstringLength(const u32char* string);

    template bool tstringEqual(const char* string1, const char* string2) noexcept;
    template bool tstringEqual(const wchar* string1, const wchar* string2) noexcept;
    template bool tstringEqual(const u8char* string1, const u8char* string2) noexcept;
    template bool tstringEqual(const u16char* string1, const u16char* string2) noexcept;
    template bool tstringEqual(const u32char* string1, const u32char* string2) noexcept;
}
