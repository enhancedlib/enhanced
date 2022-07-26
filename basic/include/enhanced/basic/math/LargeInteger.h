/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 *
 * This software is licensed under Enhanced License.
 * You may not use this file except in compliance with the License.
 * You should see a copy of Enhanced License in this software, if not, visit
 * <https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt>
 *
 * The Software is always provided "AS IS",
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 *
 */

#pragma once

#include "enhanced/core/defines.h"
#include "enhanced/core/types.h"

#include "enhanced/basic/export.h"
#include "enhanced/basic/String.h"

#if defined(C_LANGUAGE) /* C language */ || defined(ENHANCED_BASIC_C_MODE)

EXTERN_C_START

EXTERN_C_END

#else // C++ language

namespace enhanced::basic::math {
    class ENHANCED_BASIC_API LargeInteger {
    private:
        byte* bytes;

        bool isNegative;

        Size size;

        LargeInteger(uint64 number);

    public:
        template <typename NumberType>
        static LargeInteger from(NumberType number);

        LargeInteger(const enhanced::basic::String& number);

        LargeInteger add(LargeInteger number);

        LargeInteger sub(LargeInteger number);

        LargeInteger mul(LargeInteger number);

        LargeInteger div(LargeInteger number);
    };
}

#endif // defined(C_LANGUAGE) || defined(ENHANCED_BASIC_C_MODE)
