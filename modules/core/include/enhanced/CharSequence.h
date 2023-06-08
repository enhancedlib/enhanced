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

#pragma once

#include <enhanced/Defines.h>
#include <enhanced/ExportCore.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/util/Traits.h>

namespace enhanced {
    template <typename CharType>
    requires util::isCharType<CharType>
    class E_CORE_API CharSequence {
        template <typename Type>
        requires util::isCharType<Type>
        friend class TString;

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

        E_ANNOTATE(RetNotIgnored)
        CharType* chars() const noexcept;

        E_ANNOTATE(RetNotIgnored)
        sizetype getLength() const noexcept;

        E_ANNOTATE(RetNotIgnored)
        bool isEmpty() const noexcept;

        E_ANNOTATE(RetNotIgnored)
        const byte* toBytes() const noexcept;

        E_ANNOTATE(RetNotIgnored)
        const CharType at(sizetype index) const noexcept;

        E_ANNOTATE(RetNotIgnored)
        const CharType operator[](sizetype index) const noexcept;

        E_ANNOTATE(ReturnSelf)
        CharSequence& operator=(const CharSequence& other) noexcept;

        E_ANNOTATE(ReturnSelf)
        CharSequence& operator=(CharSequence&& other) noexcept;

        operator CharType*() const noexcept;
    };
}
