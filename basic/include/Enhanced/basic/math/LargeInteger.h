/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 * This software is licensed under Enhanced License.
 *
 * This copyright notice is subject to change without notice.
 *
 * This software is a free software, everyone can change,
 * copy, publication, demonstrate, use, etc.
 *
 * This software and documentation may provide
 * third-party content, product and other information.
 * The Licensor is not responsible for any loss or damage
 * caused by your access to or use of third-party content, products, etc.
 *
 * For any loss or damage caused by this software,
 * the licensor may provide possible solutions,
 * but it does not mean that the licensor will definitely solve the problem.
 * In no event shall the licensor be liable for any claims,
 * damages or other liabilities.
 *
 * You should see a copy of Enhanced License in this software, if not, visit
 * <https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt>
 */

#pragma once

#include "Enhanced/core/defines.h"
#include "Enhanced/core/types.h"

#include "Enhanced/basic/export.h"
#include "Enhanced/basic/core/String.h"

#if defined(C_LANGUAGE) /* C language */ || defined(ENHANCED_BASIC_C_MODE)

EXTERN_C_START

EXTERN_C_END

#else // C++ language

namespace Enhanced::basic::math {
    class ENHANCED_BASIC_API LargeInteger {
    private:
        Byte* bytes;

        bool isNegative;

        Size size;

        LargeInteger(uint64 number);

    public:
        template <typename NumberType>
        static LargeInteger from(NumberType number);

        LargeInteger(const Enhanced::basic::core::String& number);

        LargeInteger add(LargeInteger number);

        LargeInteger sub(LargeInteger number);

        LargeInteger mul(LargeInteger number);

        LargeInteger div(LargeInteger number);
    };
}

#endif // defined(C_LANGUAGE) || defined(ENHANCED_BASIC_C_MODE)
