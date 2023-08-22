/*
 * This file is part of Enhanced Framework.
 *
 * Copyright (C) 2023 sharedwonder (Liu Baihao). All rights reserved.
 *
 * Permission is hereby granted, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software,
 * including without limitation the rights to use, copy, modify, merge,
 * distribute. Unless you have obtained permission from the copyright holders,
 * subject to the following restrictions:
 *
 * 1. The above copyright notice and this permission notice shall be included in
 *    all copies of the Software and modified versions.
 *
 * 2. You may not misrepresent the source of the Software, and you may not claim
 *    that you wrote the original version.
 *
 * 3. You may not misrepresent the modified version as the original version.
 *
 * 4. You may not charge any fees or receive other compensation for the
 *    distribution of the Software, except for distributing modified versions and
 *    products that use the Software.
 *
 * 5. If you use this Software in your product, you shall indicate it.
 *
 * 6. Neither the name of the author nor the names of its contributors may
 *    be used to endorse or promote products derived from the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#include "enhanced/Array.h"
#include <enhanced/Defines.h>
#include <enhanced/CoreAPI.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/Traits.h>
#include <enhanced/Character.h>
#include <enhanced/CharSequence.h>
#include <enhanced/InitializerList.h>
#include <enhanced/collections/ArrayList.h>

#define E_SWITCH_STR(TYPE, STRING) enhanced::select<const TYPE(&)[sizeof(STRING) / sizeof(char)]>(STRING, L##STRING, u8##STRING, u##STRING, U##STRING)

namespace enhanced {
    template <typename CharType>
    requires isCharType<CharType>
    class E_API(core) TString : public CharSequence<CharType> {
        E_CLASS(TString)

    E_CLASS_BODY
    public:
        E_RET_NO_DISCARD()
        static TString<CharType> from(bool value);

        E_RET_NO_DISCARD()
        static TString from(CharType value);

        template <typename IntTypeNs>
        requires isIntegralTypeNs<IntTypeNs>
        E_RET_NO_DISCARD()
        static inline TString from(IntTypeNs value) {
            return from(value, value < 0);
        }

        E_RET_NO_DISCARD()
        static inline TString<CharType> from(const CharType* value) {
            return TString(static_cast<const CharType*&>(value));
        }

        E_RET_NO_DISCARD()
        static TString<CharType> allocate(const CharType* value);

        template <sizetype size>
        E_RET_NO_DISCARD()
        static inline TString allocate(const wrap<CharType[size]>& value) {
            return allocate(value, size);
        }

        E_RET_NO_DISCARD()
        static TString<CharType> allocate(const CharType* value, sizetype length);

        TString() noexcept;

        template <sizetype size>
        inline TString(const wrap<CharType[size]>& value) noexcept : TString((CharType*) value, size - 1) {}

        TString(CharType*& value) noexcept;

        TString(const CharType*& value) noexcept;

        TString(CharType* const& value) noexcept;

        TString(Array<TString> strings);

        E_INIT_LIST_CONSTRUCTOR(TString, TString)
        TString(InitializerList<TString> list);

        TString(const CharType* value, sizetype length) noexcept;

        explicit TString(sizetype length);

    protected:
        TString(const CharType* value, sizetype length, bool ownStorage) noexcept;

    public:
        TString(const TString& other);

        TString(TString&& other) noexcept;

        E_RET_NO_DISCARD()
        sizetype indexOf(CharType ch) const noexcept;

        E_RET_NO_DISCARD()
        sizetype indexOf(CharType ch, sizetype getN) const noexcept;

        E_RET_NO_DISCARD()
        sizetype indexOf(const TString& string) const noexcept;

        E_RET_NO_DISCARD()
        sizetype indexOf(const TString& string, sizetype getN) const noexcept;

        E_RET_NO_DISCARD()
        sizetype indexOfLast(const TString& string) const noexcept;

        E_RET_NO_DISCARD()
        sizetype indexOfLast(const TString& string, sizetype getN) const noexcept;

        E_RET_NO_DISCARD()
        sizetype indexOfLast(CharType ch) const noexcept;

        E_RET_NO_DISCARD()
        sizetype indexOfLast(CharType ch, sizetype getN) const noexcept;

        E_RET_NEED_RELEASE()
        collections::ArrayList<sizetype> indexOfAll(CharType ch) const noexcept;

        E_RET_NEED_RELEASE()
        collections::ArrayList<sizetype> indexOfAll(const TString& string) const noexcept;

        E_RET_NO_DISCARD()
        bool isOwnStorage() const noexcept;

        E_RET_NO_DISCARD()
        TString replace(sizetype start, sizetype end, CharType newChar) const;

        E_RET_NO_DISCARD()
        TString replace(sizetype start, sizetype end, const TString& newSubstring) const;

        E_RET_NO_DISCARD()
        TString replace(CharType oldChar, CharType newChar) const;

        E_RET_NO_DISCARD()
        TString replace(const TString& oldSubstring, const TString& newSubstring) const;

        E_RET_NO_DISCARD()
        TString replace(CharType oldChar, const TString& newSubstring) const;

        E_RET_NO_DISCARD()
        TString replace(const TString& oldSubstring, CharType newChar) const;

        E_RET_NO_DISCARD()
        TString replaceAll(CharType oldChar, CharType newChar) const;

        E_RET_NO_DISCARD()
        TString replaceAll(const TString& oldSubstring, const TString& newSubstring) const;

        E_RET_NO_DISCARD()
        TString replaceAll(CharType oldChar, const TString& newSubstring) const;

        E_RET_NO_DISCARD()
        TString replaceAll(const TString& oldSubstring, CharType newChar) const;

        E_RET_NO_DISCARD()
        TString uppercase() const;

        E_RET_NO_DISCARD()
        TString lowercase() const;

        E_RETURN_SELF()
        TString& toOwnStorage();

        E_RETURN_SELF()
        TString& set(sizetype index, CharType ch);

        E_RETURN_SELF()
        TString& append(CharType ch);

        E_RETURN_SELF()
        TString& append(const TString<CharType>& string);

        E_RETURN_SELF()
        TString& insertFirst(CharType ch);

        E_RETURN_SELF()
        TString& insertFirst(const TString<CharType>& string);

        E_RETURN_SELF()
        TString& replaceTo(sizetype start, sizetype end, CharType newChar);

        E_RETURN_SELF()
        TString& replaceTo(sizetype start, sizetype end, const TString<CharType>& newSubstring);

        E_RETURN_SELF()
        TString& replaceTo(CharType oldChar, CharType newChar);

        E_RETURN_SELF()
        TString& replaceTo(const TString<CharType>& oldSubstring, const TString<CharType>& newSubstring);

        E_RETURN_SELF()
        TString& replaceTo(CharType oldChar, const TString<CharType>& newSubstring);

        E_RETURN_SELF()
        TString& replaceTo(const TString<CharType>& oldSubstring, CharType newChar);

        E_RETURN_SELF()
        TString& replaceAllTo(CharType oldChar, CharType newChar);

        E_RETURN_SELF()
        TString& replaceAllTo(const TString<CharType>& oldSubstring, const TString<CharType>& newSubstring);

        E_RETURN_SELF()
        TString& replaceAllTo(CharType oldChar, const TString<CharType>& newSubstring);

        E_RETURN_SELF()
        TString& replaceAllTo(const TString<CharType>& oldSubstring, CharType newChar);

        E_RETURN_SELF()
        TString& fill(CharType ch) noexcept;

        E_RETURN_SELF()
        TString& uppercaseTo();

        E_RETURN_SELF()
        TString& lowercaseTo();

        E_RET_NO_DISCARD()
        bool operator==(const TString& string) const noexcept;

        E_RET_NO_DISCARD()
        inline bool operator==(const CharType* string) const noexcept {
            return operator==(TString::from(string));
        }

        template <sizetype size>
        E_RET_NO_DISCARD()
        inline bool operator==(const CharType (&string)[size]) const noexcept {
            return operator==(TString(string));
        }

        E_RET_NO_DISCARD()
        TString operator+(const TString& string) const;

        E_RET_NO_DISCARD()
        TString operator+(CharType ch) const;

        E_RETURN_SELF()
        TString& operator=(const TString& other) noexcept;

        E_RETURN_SELF()
        TString& operator=(TString&& other) noexcept;

        E_RETURN_SELF()
        TString& operator+=(const TString<CharType>& string);

        E_RETURN_SELF()
        TString& operator+=(CharType ch);

    protected:
        E_RET_NO_DISCARD()
        static TString from(qword value, bool isNegative);
    };

    template <typename CharType>
    requires isCharType<CharType>
    class E_API(core) TStringUtil {
        E_CLASS(TStringUtil)

    E_CLASS_BODY
        E_RET_NEED_RELEASE()
        static CharType* make(sizetype length);

        E_RET_NEED_RELEASE()
        static CharType* copy(const CharType* source);

        template <sizetype size>
        E_RET_NEED_RELEASE()
        static inline CharType* copy(const wrap<CharType[size]>& source) {
            return copy(source, size);
        }

        E_RET_NEED_RELEASE()
        static CharType* copy(const CharType* source, sizetype length);

        E_RET_NEED_RELEASE()
        static CharType* copy(sizetype newLength, const CharType* source, sizetype oldLength);

        template <sizetype size>
        E_RET_NEED_RELEASE()
        static inline CharType* copy(sizetype newLength, const wrap<CharType[size]>& source) {
            return copy(newLength, source, size);
        }

        E_RET_NO_DISCARD()
        static sizetype calcLength(const CharType* string) noexcept;

        E_RET_NO_DISCARD()
        static bool isEqual(const CharType* string1, const CharType* string2) noexcept;

        E_RET_NO_DISCARD()
        static bool isEqual(const CharType* string1, sizetype length1, const CharType* string2) noexcept;

        E_RET_NO_DISCARD()
        static bool isEqual(const CharType* string1, const CharType* string2, sizetype length2) noexcept;

        E_RET_NO_DISCARD()
        static bool isEqual(const CharType* string1, sizetype length1, const CharType* string2, sizetype length2) noexcept;

        template <sizetype size2>
        E_RET_NO_DISCARD()
        static inline bool isEqual(const CharType* string1, sizetype length1, const wrap<CharType[size2]>& string2) noexcept {
            return isEqual(string1, length1, string2, size2);
        }

        template <sizetype size1>
        E_RET_NO_DISCARD()
        static inline bool isEqual(const wrap<CharType[size1]>& string1, const CharType* string2, sizetype length2) noexcept {
            return isEqual(string1, size1, string2, length2);
        }

        template <sizetype size1, sizetype size2>
        E_RET_NO_DISCARD()
        static constexpr bool isEqual(const wrap<CharType[size1]>& string1, const wrap<CharType[size2]>& string2) noexcept {
            if (size1 != size2) return false;

            for (sizetype index = 0; index < size1; ++index) {
                if (string1[index] != string2[index]) return false;
            }

            return true;
        }

        TStringUtil() = delete;

        ~TStringUtil() = delete;
    };

    using String = TString<char>;
#ifdef E_WCHAR_IS_BUILTIN_TYPE
    using WideString = TString<wchar>;
#endif
    using U8String = TString<u8char>;
    using U16String = TString<u16char>;
    using U32String = TString<u32char>;

    using StringUtil = TStringUtil<char>;
#ifdef E_WCHAR_IS_BUILTIN_TYPE
    using WideStringUtil = TStringUtil<wchar>;
#endif
    using U8StringUtil = TStringUtil<u8char>;
    using U16StringUtil = TStringUtil<u16char>;
    using U32StringUtil = TStringUtil<u32char>;

    inline namespace literals {
        inline String operator""_e(const char* string, sizetype size) {
            return {string, size};
        }

    #ifdef E_WCHAR_IS_BUILTIN_TYPE
        inline WideString operator""_e(const wchar* string, sizetype size) {
            return {string, size};
        }
    #endif

        inline U8String operator""_e(const u8char* string, sizetype size) {
            return {string, size};
        }

        inline U16String operator""_e(const u16char* string, sizetype size) {
            return {string, size};
        }

        inline U32String operator""_e(const u32char* string, sizetype size) {
            return {string, size};
        }

        inline String operator""_ea(const char* string, sizetype size) {
            return String::allocate(string, size);
        }

    #ifdef E_WCHAR_IS_BUILTIN_TYPE
        inline WideString operator""_ea(const wchar* string, sizetype size) {
            return WideString::allocate(string, size);
        }
    #endif

        inline U8String operator""_ea(const u8char* string, sizetype size) {
            return U8String::allocate(string, size);
        }

        inline U16String operator""_ea(const u16char* string, sizetype size) {
            return U16String::allocate(string, size);
        }

        inline U32String operator""_ea(const u32char* string, sizetype size) {
            return U32String::allocate(string, size);
        }
    }
}
