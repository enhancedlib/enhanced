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

#include <enhanced/CharSequence.h>

#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/Traits.h>
#include <enhanced/String.h>

using enhanced::removePtrConst;

namespace enhanced {
    template <typename CharType>
    requires isCharType<CharType>
    CharSequence<CharType>::CharSequence(const CharType* value, sizetype length, bool ownStorage) :
        value(removePtrConst(value)), length(length), ownStorage(ownStorage) {}

    template <typename CharType>
    requires isCharType<CharType>
    CharSequence<CharType>::CharSequence(const CharType* value, sizetype length) : value(removePtrConst(value)), length(length) {}

    template <typename CharType>
    requires isCharType<CharType>
    CharSequence<CharType>::CharSequence(const CharSequence& other) :
        value(other.ownStorage ? TStringUtil<CharType>::copy(other.value) : other.value), length(other.length), ownStorage(other.ownStorage) {}

    template <typename CharType>
    requires isCharType<CharType>
    CharSequence<CharType>::CharSequence(CharSequence&& other) noexcept : value(other.value), length(other.length), ownStorage(other.ownStorage) {
        other.value = nullptr;
        other.length = E_SIZE_TYPE_MAX;
        other.ownStorage = false;
    }

    template <typename CharType>
    requires isCharType<CharType>
    CharSequence<CharType>::~CharSequence() noexcept {
        if (ownStorage) delete[] value;
    }

    template <typename CharType>
    requires isCharType<CharType>
    E_RET_NO_DISCARD()
    bool CharSequence<CharType>::isEmpty() const noexcept {
        return length == 0;
    }

    template <typename CharType>
    requires isCharType<CharType>
    E_RET_NO_DISCARD()
    sizetype CharSequence<CharType>::getLength() const noexcept {
        return length;
    }

    template <typename CharType>
    requires isCharType<CharType>
    E_RET_NO_DISCARD()
    CharType* CharSequence<CharType>::chars() const noexcept {
        return value;
    }

    template <typename CharType>
    requires isCharType<CharType>
    E_RET_NO_DISCARD()
    const byte* CharSequence<CharType>::toBytes() const noexcept {
        return reinterpret_cast<const byte*>(value);
    }

    template <typename CharType>
    requires isCharType<CharType>
    E_RET_NO_DISCARD()
    const CharType CharSequence<CharType>::at(sizetype index) const noexcept {
        return value[index];
    }

    template <typename CharType>
    requires isCharType<CharType>
    E_RET_NO_DISCARD()
    const CharType CharSequence<CharType>::operator[]
#ifdef E_SIZE_TYPE_32BIT
    (int index)
#else
    (sizetype index)
#endif
    const noexcept {
        return value[index];
    }

    template <typename CharType>
    requires isCharType<CharType>
    E_RETURN_SELF()
    CharSequence<CharType>& CharSequence<CharType>::operator=(const CharSequence& other) noexcept {
        if (this == &other) return *this;

        if (ownStorage) delete[] value;

        value = other.value;
        length = other.length;
        ownStorage = other.ownStorage;

        return *this;
    }

    template <typename CharType>
    requires isCharType<CharType>
    E_RETURN_SELF()
    CharSequence<CharType>& CharSequence<CharType>::operator=(CharSequence&& other) noexcept {
        if (this == &other) return *this;

        if (ownStorage) delete[] value;

        value = other.value;
        length = other.length;
        ownStorage = other.ownStorage;

        other.value = nullptr;
        other.length = E_SIZE_TYPE_MAX;
        other.ownStorage = false;

        return *this;
    }

    template <typename CharType>
    requires isCharType<CharType>
    CharSequence<CharType>::operator CharType*() const noexcept {
        return chars();
    }

    template class CharSequence<char>;
    template class CharSequence<wchar>;
    template class CharSequence<u8char>;
    template class CharSequence<u16char>;
    template class CharSequence<u32char>;
}
