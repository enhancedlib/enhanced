/*
 * This file is part of Enhanced Framework.
 *
 * Copyright (C) 2023 Liu Baihao (sharedwonder). All rights reserved.
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
 *    distribution of the Software, excluding distribution of modified versions
 *    and products using the Software.
 *
 * 5. If you use this Software in your product, you shall indicate it.
 *
 * 6. Neither the name of the author nor the names of its contributors may
 *    be used to endorse or promote products derived from the Software
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

#include <enhanced/Defines.h>
#include <enhanced/CoreApi.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/Traits.h>

namespace enhanced {
    template <typename CharType>
    requires isCharType<CharType>
    class E_API(core) CharSequence {
        E_CLASS(CharSequence)

    E_CLASS_HEADER
        template <typename Type>
        requires isCharType<Type>
        friend class TString;

    E_CLASS_BODY
    protected:
        CharType* value;

        sizetype length;

        bool isOwn = false;

        CharSequence(const CharType* value, sizetype length, bool isOwn);

    public:
        CharSequence(const CharType* value, sizetype length);

        CharSequence(const CharSequence& other);

        CharSequence(CharSequence&& other) noexcept;

        ~CharSequence() noexcept;

        E_RET_NO_DISCARD()
        CharType* chars() const noexcept;

        E_RET_NO_DISCARD()
        sizetype getLength() const noexcept;

        E_RET_NO_DISCARD()
        bool isEmpty() const noexcept;

        E_RET_NO_DISCARD()
        const byte* toBytes() const noexcept;

        E_RET_NO_DISCARD()
        const CharType at(sizetype index) const noexcept;

    #ifdef E_SM_SIZE_TYPE_32BIT
        E_RET_NO_DISCARD()
        const CharType operator[](int index) const noexcept;
    #else
        E_RET_NO_DISCARD()
        const CharType operator[](sizetype index) const noexcept;
    #endif

        E_RETURN_SELF()
        CharSequence& operator=(const CharSequence& other) noexcept;

        E_RETURN_SELF()
        CharSequence& operator=(CharSequence&& other) noexcept;

        operator CharType*() const noexcept;
    };
}
