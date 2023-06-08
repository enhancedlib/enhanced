/*
 * This file is part of Enhanced Framework.
 *
 * Copyright (C) 2023 Liu Baihao (sharedwonder). All rights reserved.
 *
 * Permission is hereby granted, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software,
 * including without limitation the rights to use, copy, modify, merge,
 * distribute, subject to the following restrictions:
 *
 * 1. The above copyright notice and this permission notice shall be included in
 *    all copies of the Software and modified versions.
 *
 * 2. You may not charge any fees or receive other compensation for the
 *    distribution of the Software.
 *
 * 3. You may not misrepresent the source of the Software, and you may not claim
 *    that you wrote the original version.
 *
 * 4. If you use this Software in your product, you should indicate the it in
 *    the product documentation.
 *
 * Unless you have obtained the written consent of the copyright holders,
 * you may not break these restrictions.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <enhanced/CharSequence.h>

#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/String.h>
#include <enhanced/util/Traits.h>

using enhanced::util::removePtrConst;

namespace enhanced {
    template <typename CharType>
    requires util::isCharType<CharType>
    CharSequence<CharType>::CharSequence(const CharType* value, sizetype length, bool isOwn) :
        value(removePtrConst(value)), length(length), isOwn(isOwn) {}

    template <typename CharType>
    requires util::isCharType<CharType>
    CharSequence<CharType>::CharSequence(const CharType* value, sizetype length) : value(removePtrConst(value)), length(length) {}

    template <typename CharType>
    requires util::isCharType<CharType>
    CharSequence<CharType>::CharSequence(const CharSequence& other) :
        value(other.isOwn ? TStringUtil<CharType>::copy(other.value) : other.value), length(other.length), isOwn(other.isOwn) {}

    template <typename CharType>
    requires util::isCharType<CharType>
    CharSequence<CharType>::CharSequence(CharSequence&& other) noexcept : value(other.value), length(other.length), isOwn(other.isOwn) {
        other.value = nullptr;
        other.length = E_SIZE_TYPE_MAX;
        other.isOwn = false;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    CharSequence<CharType>::~CharSequence() noexcept {
        if (isOwn) delete[] value;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetNotIgnored)
    bool CharSequence<CharType>::isEmpty() const noexcept {
        return length == 0;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetNotIgnored)
    sizetype CharSequence<CharType>::getLength() const noexcept {
        return length;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetNotIgnored)
    CharType* CharSequence<CharType>::chars() const noexcept {
        return value;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetNotIgnored)
    const byte* CharSequence<CharType>::toBytes() const noexcept {
        return reinterpret_cast<const byte*>(value);
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetNotIgnored)
    const CharType CharSequence<CharType>::at(sizetype index) const noexcept {
        return value[index];
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetNotIgnored)
    const CharType CharSequence<CharType>::operator[](sizetype index) const noexcept {
        return value[index];
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(ReturnSelf)
    CharSequence<CharType>& CharSequence<CharType>::operator=(const CharSequence& other) noexcept {
        if (this == &other) return *this;

        if (isOwn) delete[] value;

        value = other.value;
        length = other.length;
        isOwn = other.isOwn;

        return *this;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(ReturnSelf)
    CharSequence<CharType>& CharSequence<CharType>::operator=(CharSequence&& other) noexcept {
        if (this == &other) return *this;

        if (isOwn) delete[] value;

        value = other.value;
        length = other.length;
        isOwn = other.isOwn;

        other.value = nullptr;
        other.length = E_SIZE_TYPE_MAX;
        other.isOwn = false;

        return *this;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    CharSequence<CharType>::operator CharType*() const noexcept {
        return chars();
    }

    template class CharSequence<char>;
    template class CharSequence<wchar>;
    template class CharSequence<u8char>;
    template class CharSequence<u16char>;
    template class CharSequence<u32char>;
}
