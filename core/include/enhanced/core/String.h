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

#pragma once

#include <enhanced/core/defines.h>
#include <enhanced/core/export.h>
#include <enhanced/core/types.h>
#include <enhanced/core/annotations.h>
#include <enhanced/core/CharSequence.h>
#include <enhanced/core/InitializerList.h>
#include <enhanced/core/util/traits.h>
#include <enhanced/core/collections/ArrayList.h>

namespace enhanced::core {
    template <typename CharType>
    class TMutString;

    template <typename CharType>
    class ENHANCED_CORE_API TString : public CharSequence<CharType> {
    public:
        $(RetRequiresRelease)
        static func make(sizetype length) -> CharType*;

        $(RetRequiresRelease)
        static func copy(const CharType* source) -> CharType*;

        $(RetRequiresRelease)
        static func copy(const CharType* source, sizetype length) -> CharType*;

        $(RetRequiresRelease)
        static func copy(const CharType* source, sizetype oldLength, sizetype newLength) -> CharType*;

        $(NoIgnoreReturn)
        static func calcLength(const CharType* string) noexcept -> sizetype;

        $(NoIgnoreReturn)
        static func isEqual(const CharType* string1, const CharType* string2) noexcept -> bool;

        $(NoIgnoreReturn)
        static func isEqual(const CharType* string1, const CharType* string2, sizetype length1, sizetype length2) noexcept -> bool;

        template <sizetype count>
        static inline func join(TString strings[count]) -> TMutString<CharType> {
            return join(count, strings);
        }

        static func join(InitializerList<TString> list) -> TMutString<CharType>;

        static func join(const TString* strings, sizetype count) -> TMutString<CharType>;

        TString() noexcept;

        TString(const CharType* value, sizetype length) noexcept;

        template <sizetype size>
        inline TString(const CharType (&value)[size]) noexcept : TString((CharType*) value, size - 1) {}

        TString(const CharType*& value);

        TString(CharType*& value);

        TString(CharType* const& value);

        TString(const TString& other) noexcept;

        TString(TString&& other) noexcept;

        $(NoIgnoreReturn)
        func indexOf(CharType ch) const noexcept -> sizetype;

        $(NoIgnoreReturn)
        func indexOf(CharType ch, sizetype getN) const noexcept -> sizetype;

        $(NoIgnoreReturn)
        func indexOf(const TString& string) const noexcept -> sizetype;

        $(NoIgnoreReturn)
        func indexOf(const TString& string, sizetype getN) const noexcept -> sizetype;

        $(NoIgnoreReturn)
        func indexOfLast(const TString& string) const noexcept -> sizetype;

        $(NoIgnoreReturn)
        func indexOfLast(const TString& string, sizetype getN) const noexcept -> sizetype;

        $(NoIgnoreReturn)
        func indexOfLast(CharType ch) const noexcept -> sizetype;

        $(NoIgnoreReturn)
        func indexOfLast(CharType ch, sizetype getN) const noexcept -> sizetype;

        $(RetRequiresRelease)
        func indexOfAll(CharType ch) const noexcept -> collections::ArrayList<sizetype>;

        $(RetRequiresRelease)
        func indexOfAll(const TString& string) const noexcept -> collections::ArrayList<sizetype>;

        $(NoIgnoreReturn)
        func replace(sizetype start, sizetype end, CharType newChar) const -> TMutString<CharType>;

        $(NoIgnoreReturn)
        func replace(sizetype start, sizetype end, const TString& newSubstring) const -> TMutString<CharType>;

        $(NoIgnoreReturn)
        func replace(CharType oldChar, CharType newChar) const -> TMutString<CharType>;

        $(NoIgnoreReturn)
        func replace(const TString& oldSubstring, const TString& newSubstring) const -> TMutString<CharType>;

        $(NoIgnoreReturn)
        func replace(CharType oldChar, const TString& newSubstring) const -> TMutString<CharType>;

        $(NoIgnoreReturn)
        func replace(const TString& oldSubstring, CharType newChar) const -> TMutString<CharType>;

        $(NoIgnoreReturn)
        func replaceAll(CharType oldChar, CharType newChar) const -> TMutString<CharType>;;

        $(NoIgnoreReturn)
        func replaceAll(const TString& oldSubstring, const TString& newSubstring) const -> TMutString<CharType>;;

        $(NoIgnoreReturn)
        func replaceAll(CharType oldChar, const TString& newSubstring) const -> TMutString<CharType>;;

        $(NoIgnoreReturn)
        func replaceAll(const TString& oldSubstring, CharType newChar) const -> TMutString<CharType>;;

        $(NoIgnoreReturn)
        func uppercase() const -> TMutString<CharType>;;

        $(NoIgnoreReturn)
        func lowercase() const -> TMutString<CharType>;;

        $(NoIgnoreReturn)
        func operator==(const TString& string) const noexcept -> bool;

        $(NoIgnoreReturn)
        func operator+(const TString& string) const -> TMutString<CharType>;

        func operator=(const TString& other) noexcept -> TString&;

        func operator=(TString&& other) noexcept -> TString&;
    };

    using String = TString<char>;
    #ifdef WCHAR_IS_BUILTIN_TYPE
    using WideString = TString<wchar>;
    #endif
    using U8String = TString<u8char>;
    using U16String = TString<u16char>;
    using U32String = TString<u32char>;

    inline namespace literals {
        inline func operator""_s(const char* string, sizetype size) -> String {
            return {string, size};
        }

    #ifdef WCHAR_IS_BUILTIN_TYPE
        inline func operator""_s(const wchar* string, sizetype size) -> WideString {
            return {string, size};
        }
    #endif

        inline func operator""_s(const u8char* string, sizetype size) -> U8String {
            return {string, size};
        }

        inline func operator""_s(const u16char* string, sizetype size) -> U16String {
            return {string, size};
        }

        inline func operator""_s(const u32char* string, sizetype size) -> U32String {
            return {string, size};
        }
    }
}

#define TSTRING(type, string) enhanced::core::util::switchType<const type(&)[sizeof(string) / sizeof(char)]> \
    (string, WIDE_TEXT(string), U8_TEXT(string), U16_TEXT(string), U32_TEXT(string))

#define STR(quote) quote##_s
