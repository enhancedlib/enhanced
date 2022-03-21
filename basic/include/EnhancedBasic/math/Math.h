/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 * This software is licensed under Enhanced License.
 *
 * This copyright disclaimer is subject to change without notice.
 *
 * This software is a free software,
 * everyone can change, copy, publication, demonstrate, use, etc.
 *
 * If you change and publication this software,
 * must credit the original software source and author's name,
 * and include this copyright disclaimer and
 * the license of this software in your software.
 *
 * This software and documentation may provide
 * third-party content, product and other information.
 * I am not responsible for any loss or damage caused
 * by your access to or use of third-party content, products, etc.
 */

#ifndef ENHANCED_BASIC_MATH_MATH_H
#define ENHANCED_BASIC_MATH_MATH_H

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"

#include "EnhancedBasic/export.h"

#if defined(C_LANGUAGE) /* C language */ || defined(ENHANCED_BASIC_C_MODE)

EXTERN_C_START

EXTERN_C_END

#else

namespace EnhancedBasic {
    namespace Math {
        class ENHANCED_BASIC_API Math final {
        private:
            Math();

        public:
            static uint8 abs(int8 number);

            static uint16 abs(int16 number);

            static uint32 abs(int32 number);

            static uint64 abs(int64 number);
        };
    } // namespace Math
} // namespace EnhancedBasic


#endif // defined(C_LANGUAGE) || defined(ENHANCED_BASIC_C_MODE)

#endif // !ENHANCED_BASIC_MATH_MATH_H
