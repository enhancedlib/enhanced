/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 *
 * Licensed under the Enhanced License, Version 0.5.4 (the "License").
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt
 *
 * UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING,
 * THE SOFTWARE IS ALWAYS PROVIDED "AS IS",
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#pragma once

#include "enhanced/core/defines.h"
#include "enhanced/core/types.h"
#include "enhanced/core/annotations.h"

#include "enhanced/basic/export.h"

#if defined(C_LANGUAGE) || defined(ENHANCED_BASIC_C_MODE)

#else

namespace enhanced::basic {
    template <typename CharType>
    class ENHANCED_BASIC_API CharSequence {
    protected:
        CharType* value;

        Size length;

    public:
        CharSequence(NotNull CharType* value, Size length);

        CharSequence(const CharSequence& other) noexcept;

        ~CharSequence();

        RetCannotIgnored
        Size getLength() const;

        RetCannotIgnored
        bool isEmpty() const;

        RetCannotIgnored
        CharType* getChars() const;

        RetCannotIgnored
        const CharType at(Size index) const;

        RetCannotIgnored
        const CharType operator[](Size index) const;

        RetCannotIgnored
        operator CharType*() const;
    };
}

#endif // defined(C_LANGUAGE) || defined(ENHANCED_BASIC_C_MODE)
