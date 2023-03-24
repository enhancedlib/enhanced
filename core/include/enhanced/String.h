/*
 * Copyright (C) 2023 Liu Baihao. All rights reserved.
 *
 * Licensed under the Enhanced Software License.
 *
 * This file is part of the Enhanced Software, and IT ALWAYS
 * PROVIDES "AS IS" WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 *
 * You may not use this file except in compliance with the License.
 * You should obtain a copy of the License in the distribution,
 * if not, see <https://sharedwonder.github.io/enhanced/LICENSE.txt>
 */

#pragma once

#include <enhanced/Defines.h>
#include <enhanced/ExportCore.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/Character.h>
#include <enhanced/CharSequence.h>
#include <enhanced/InitializerList.h>
#include <enhanced/util/Traits.h>
#include <enhanced/collections/ArrayList.h>

#define E_SWITCH_STR(TYPE, STRING) enhanced::util::switchType<const TYPE(&)[sizeof(STRING) / sizeof(char)]> \
    (STRING, L##STRING, u8##STRING, u##STRING, U##STRING)

#ifdef ENHANCED_MACRO_NO_PREFIX_ALIAS
    #define SWITCH_STR E_SWITCH_STR
#endif

namespace enhanced {
    template <typename CharType>
    requires util::isCharType<CharType>
    class ENHANCED_CORE_API TMutString;

    template <typename CharType>
    requires util::isCharType<CharType>
    class ENHANCED_CORE_API TString : public CharSequence<CharType> {
    protected:
        TString(const CharType* value, sizetype length, bool isMutable) noexcept;

        [[RetNotIgnored]]
        static TMutString<CharType> from(qword value, bool isNegative);

    public:
        [[RetNotIgnored]]
        static TString<CharType> from(bool value);

        [[RetNotIgnored]]
        static TMutString<CharType> from(CharType value);

        template <typename IntTypeNs>
        requires util::isIntegralTypeNs<IntTypeNs>
        [[RetNotIgnored]]
        static inline TMutString<CharType> from(IntTypeNs value) {
            return from(value, value < 0);
        }

        template <typename... Args>
        requires (util::typeVecCount<Args...> >= 2)
        [[RetNotIgnored]]
        static inline TMutString<CharType> join(Args&&... values) {
            return join({values...});
        }

        template <sizetype count>
        [[RetNotIgnored]]
        static inline TMutString<CharType> join(TString (&strings)[count]) {
            return join(strings, count);
        }

        [[RetNotIgnored]]
        static TMutString<CharType> join(InitializerList<TString> list);

        [[RetNotIgnored]]
        static TMutString<CharType> join(const TString* strings, sizetype count);

        TString() noexcept;

        TString(const CharType* value, sizetype length) noexcept;

        template <sizetype size>
        inline TString(const CharType (&value)[size]) noexcept : TString((CharType*) value, size - 1) {}

        TString(const CharType*& value);

        TString(CharType*& value);

        TString(CharType* const& value);

        TString(const TString& other);

        TString(TString&& other) noexcept;

        [[RetNotIgnored]]
        sizetype indexOf(CharType ch) const noexcept;

        [[RetNotIgnored]]
        sizetype indexOf(CharType ch, sizetype getN) const noexcept;

        [[RetNotIgnored]]
        sizetype indexOf(const TString& string) const noexcept;

        [[RetNotIgnored]]
        sizetype indexOf(const TString& string, sizetype getN) const noexcept;

        [[RetNotIgnored]]
        sizetype indexOfLast(const TString& string) const noexcept;

        [[RetNotIgnored]]
        sizetype indexOfLast(const TString& string, sizetype getN) const noexcept;

        [[RetNotIgnored]]
        sizetype indexOfLast(CharType ch) const noexcept;

        [[RetNotIgnored]]
        sizetype indexOfLast(CharType ch, sizetype getN) const noexcept;

        [[RetRequiresRelease]]
        collections::ArrayList<sizetype> indexOfAll(CharType ch) const noexcept;

        [[RetRequiresRelease]]
        collections::ArrayList<sizetype> indexOfAll(const TString& string) const noexcept;

        [[RetNotIgnored]]
        TMutString<CharType> toMutable() const;

        [[RetNotIgnored]]
        TMutString<CharType> replace(sizetype start, sizetype end, CharType newChar) const;

        [[RetNotIgnored]]
        TMutString<CharType> replace(sizetype start, sizetype end, const TString& newSubstring) const;

        [[RetNotIgnored]]
        TMutString<CharType> replace(CharType oldChar, CharType newChar) const;

        [[RetNotIgnored]]
        TMutString<CharType> replace(const TString& oldSubstring, const TString& newSubstring) const;

        [[RetNotIgnored]]
        TMutString<CharType> replace(CharType oldChar, const TString& newSubstring) const;

        [[RetNotIgnored]]
        TMutString<CharType> replace(const TString& oldSubstring, CharType newChar) const;

        [[RetNotIgnored]]
        TMutString<CharType> replaceAll(CharType oldChar, CharType newChar) const;

        [[RetNotIgnored]]
        TMutString<CharType> replaceAll(const TString& oldSubstring, const TString& newSubstring) const;

        [[RetNotIgnored]]
        TMutString<CharType> replaceAll(CharType oldChar, const TString& newSubstring) const;

        [[RetNotIgnored]]
        TMutString<CharType> replaceAll(const TString& oldSubstring, CharType newChar) const;

        [[RetNotIgnored]]
        TMutString<CharType> uppercase() const;

        [[RetNotIgnored]]
        TMutString<CharType> lowercase() const;

        [[RetNotIgnored]]
        bool operator==(const TString& string) const noexcept;

        [[RetNotIgnored]]
        bool operator!=(const TString& string) const noexcept;

        [[RetNotIgnored]]
        TMutString<CharType> operator+(const TString& string) const;

        [[RetNotIgnored]]
        TMutString<CharType> operator+(CharType ch) const;

        [[ReturnSelf]]
        TString& operator=(const TString& other) noexcept;

        [[ReturnSelf]]
        TString& operator=(TString&& other) noexcept;
    };

    template <typename CharType>
    requires util::isCharType<CharType>
    struct TStringUtil {
        TStringUtil() = delete;

        ~TStringUtil() = delete;

        [[RetRequiresRelease]]
        static CharType* make(sizetype length);

        [[RetRequiresRelease]]
        static CharType* copy(const CharType* source);

        [[RetRequiresRelease]]
        static CharType* copy(const CharType* source, sizetype length);

        [[RetRequiresRelease]]
        static CharType* copy(const CharType* source, sizetype oldLength, sizetype newLength);

        [[RetNotIgnored]]
        static sizetype calcLength(const CharType* string) noexcept;

        [[RetNotIgnored]]
        static bool isEqual(const CharType* string1, const CharType* string2) noexcept;

        [[RetNotIgnored]]
        static bool isEqual(const CharType* string1, const CharType* string2, sizetype length1, sizetype length2) noexcept;

        template <sizetype size1, sizetype size2>
        [[RetNotIgnored]]
        static constexpr bool isEqual(const CharType (&string1)[size1], const CharType (&string2)[size2]) noexcept {
            if (size1 != size2) return false;

            for (sizetype index = 0;; ++index) {
                if ((string1[index] == E_SWITCH_CHAR(CharType, '\0')) ^ (string2[index] == E_SWITCH_CHAR(CharType, '\0'))) {
                    return false;
                }

                if (string1[index] != string2[index]) return false;
            }
        }
    };

    using String = TString<char>;
#ifdef WCHAR_IS_BUILTIN_TYPE
    using WideString = TString<wchar>;
#endif
    using U8String = TString<u8char>;
    using U16String = TString<u16char>;
    using U32String = TString<u32char>;

    using StringUtil = TStringUtil<char>;
#ifdef WCHAR_IS_BUILTIN_TYPE
    using WideStringUtil = TStringUtil<wchar>;
#endif
    using U8StringUtil = TStringUtil<u8char>;
    using U16StringUtil = TStringUtil<u16char>;
    using U32StringUtil = TStringUtil<u32char>;

    inline namespace literals {
        inline String operator""_ES(const char* string, sizetype size) {
            return {string, size};
        }

    #ifdef WCHAR_IS_BUILTIN_TYPE
        inline WideString operator""_ES(const wchar* string, sizetype size) {
            return {string, size};
        }
    #endif

        inline U8String operator""_ES(const u8char* string, sizetype size) {
            return {string, size};
        }

        inline U16String operator""_ES(const u16char* string, sizetype size) {
            return {string, size};
        }

        inline U32String operator""_ES(const u32char* string, sizetype size) {
            return {string, size};
        }
    }
}
