/*
 * Copyright (C) 2021 Liu Baihao. All rights reserved.
 * This product is licensed under Enhanced License.
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

#ifndef ENHANCED_CORE_ASSERT_H
#define ENHANCED_CORE_ASSERT_H

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"

ENHANCED_CORE_API void assertFailed(const char *message, const char *file, unsigned int line);

#ifdef assert
#undef assert
#endif // assert

#define dynamic_assert(exception) \
    ((exception) || (assertFailed(#exception, __FILE__, __LINE__), 0))

#ifdef DEBUG
#define assert(exception) dynamic_assert(exception)
#else
#define assert(exception) (void) 0
#endif // DEBUG

#endif // !ENHANCED_CORE_ASSERT_H
