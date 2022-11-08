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

#ifdef CXX_LANGUAGE

NAMESPACE_L2_BEGIN(enhanced, core)

template <typename CharType>
class ENHANCED_CORE_API CharSequence {
protected:
    CharType* value;

    sizetype length;

public:
    CharSequence(CharType* value, sizetype length);

    CharSequence(const CharSequence& other) noexcept;

    CharSequence(CharSequence&& other) noexcept;

    virtual ~CharSequence() noexcept;

    NoIgnoreRet
    sizetype getLength() const noexcept;

    NoIgnoreRet
    bool isEmpty() const noexcept;

    NoIgnoreRet
    CharType* getChars() const noexcept;

    NoIgnoreRet
    const CharType at(sizetype index) const noexcept;

    NoIgnoreRet
    const CharType operator[](sizetype index) const noexcept;

    CharSequence& operator=(const CharSequence& other) noexcept;

    CharSequence& operator=(CharSequence&& other) noexcept;

    NoIgnoreRet
    operator CharType*() const noexcept;
};

NAMESPACE_L2_END

#endif
