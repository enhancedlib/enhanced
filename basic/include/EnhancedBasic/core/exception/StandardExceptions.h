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

#ifndef ENHANCED_BASIC_CORE_EXCEPTION_STANDARD_EXCEPTIONS_H
#define ENHANCED_BASIC_CORE_EXCEPTION_STANDARD_EXCEPTIONS_H

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"

#if defined(C_LANGUAGE) /* C language */ || defined(ENHANCED_BASIC_C_MODE)

typedef enum StandardExceptions {
    Exception
} StandardExceptions;

#endif defined(C_LANGUAGE) || defined(ENHANCED_BASIC_C_MODE)

#endif // !ENHANCED_BASIC_CORE_EXCEPTION_STANDARD_EXCEPTIONS_H
