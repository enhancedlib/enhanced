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
    protected:
        TString(CharType* value, sizetype length) noexcept;

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
        static func calcLength(const CharType* string) -> sizetype;

        $(NoIgnoreReturn)
        static func isEqual(const CharType* string1, const CharType* string2) noexcept -> bool;

        static func from(const CharType* value) -> TString;

        template <sizetype count>
        static inline func join(TString strings[count]) -> TMutString<CharType> {
            return join(count, strings);
        }

        static func join(InitializerList<TString> list) -> TMutString<CharType>;

        static func join(const TString* strings, sizetype count) -> TMutString<CharType>;

        TString() noexcept;

        template <sizetype size>
        inline TString(const CharType(&value)[size]) noexcept : TString((CharType*) value, size) {}

        TString(const CharType* value);

        TString(CharType* value);

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
        func operator==(const CharType* string) const noexcept -> bool;

        $(NoIgnoreReturn)
        func operator+(const TString& string) const -> TMutString<CharType>;;

        func operator=(const TString& other) noexcept -> TString&;

        func operator=(TString&& other) noexcept -> TString&;
    };

    using String = TString<char>;
    using WideString = TString<wchar>;
    #ifdef CXX_U8CHAR_SUPPORTED
    using U8String = TString<u8char>;
    #endif
    using U16String = TString<u16char>;
    using U32String = TString<u32char>;
}

#ifdef CXX_U8CHAR_SUPPORTED
#define TSTRING(type, string) enhanced::core::util::traits::templateSwitch<const type(&)[sizeof(string) / sizeof(char)]> \
    (string, WIDE_TEXT(string), U8_TEXT(string), U16_TEXT(string), U32_TEXT(string))
#else
#define TSTRING(type, string) enhanced::core::util::traits::templateSwitch<type><const type(&)[sizeof(string) / sizeof(char)]> \
    (string, WIDE_TEXT(string), U16_TEXT(string), U32_TEXT(string))
#endif
