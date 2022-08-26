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
#include "enhanced/basic/CharSequence.h"
#include "enhanced/basic/container/List.h"

#if defined(C_LANGUAGE) || defined(ENHANCED_BASIC_C_MODE)

EXTERN_C_START

typedef struct String {
    /*!
     * This variable is used to hold the original string.
     */
    char* value;

    /*!
     * This variable is used to record the count of a string.
     */
    Size length;

    Size (*getLength)(const struct String* self);

    /*!
     * To concatenate the current string with another string.
     *
     * @param self
     * @param str
     * @return String
     */
    struct String (*const add)(struct String* self, struct String str);
} String;

ENHANCED_BASIC_API String newEmptyString();

ENHANCED_BASIC_API String toString(char* value);

ENHANCED_BASIC_API String newString(Size length);

ENHANCED_BASIC_API String newStringExt(const char* value, Size length);

EXTERN_C_END

#else

namespace enhanced::basic {
    class MutableString;

    class ENHANCED_BASIC_API String : public CharSequence<char> {
    protected:
        String(NotNull char* value, Size length);

    public:
        String(NotNull const char* value = "");

        String(NotNull char* value);

        String(const String& other);

        RetCannotIgnored
        Size indexOf(char ch) const;

        RetCannotIgnored
        Size indexOf(char ch, Size getN) const;

        RetCannotIgnored
        Size indexOf(const String& string) const;

        RetCannotIgnored
        Size indexOf(const String& string, Size getN) const;

        RetCannotIgnored
        Size lastIndexOf(const String& string) const;

        RetCannotIgnored
        Size lastIndexOf(const String& string, Size getN) const;

        RetCannotIgnored
        Size lastIndexOf(char ch) const;

        RetCannotIgnored
        Size lastIndexOf(char ch, Size getN) const;

        RetRequiresRelease
        container::List<Size>* indexOfAll(char ch) const;

        RetRequiresRelease
        container::List<Size>* indexOfAll(const String& string) const;

        RetCannotIgnored
        MutableString uppercase();

        RetCannotIgnored
        MutableString lowercase();

        RetCannotIgnored

        RetCannotIgnored
        bool operator==(const String& string) const;

        RetCannotIgnored
        MutableString operator+(const String& string) const;
    };
}

#endif // defined(C_LANGUAGE) || defined(ENHANCED_BASIC_C_MODE)
