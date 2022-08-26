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
#include "enhanced/basic/String.h"
#include "enhanced/basic/container/List.h"

#if defined(C_LANGUAGE) || defined(ENHANCED_BASIC_C_MODE)

#else

namespace enhanced::basic {
    class ENHANCED_BASIC_API MutableString : public String {
    public:
        MutableString(NotNull const char* value = "");

        MutableString(NotNull char* value);

        explicit MutableString(Size length);

        MutableString(const MutableString& other);

        ~MutableString() noexcept;

        RetCannotIgnored
        char& at(Size index) const;

        RetCannotIgnored
        char& operator[](Size index) const;

        MutableString& append(const MutableString& string);

        MutableString& replace(char oldChar, char newChar);

        MutableString& replace(const MutableString& oldSubstring, const MutableString& newSubstring);

        MutableString& replace(char oldChar, const MutableString& newSubstring);

        MutableString& replace(const MutableString& oldSubstring, char newChar);

        MutableString& toUppercase();

        MutableString& toLowercase();

        MutableString& operator=(const MutableString& other);

        MutableString& operator+=(const MutableString& string);
    };
}

#endif // defined(C_LANGUAGE) || defined(ENHANCED_BASIC_C_MODE)
