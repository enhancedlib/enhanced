/*
 * Copyright (C) 2023 Liu Baihao. All rights reserved.
 *
 * Licensed under the MIT License with the Distribution Exception.
 * You may not use this file except in compliance with the License.
 *
 * THIS FILE IS PART OF THE ENHANCED SOFTWARE, and IT ALWAYS
 * PROVIDES "AS IS" WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
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
    class ENHANCED_CORE_API CharSequence {
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
