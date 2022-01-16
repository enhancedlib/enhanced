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

#ifndef ENHANCED_CORE_STRING_H
#define ENHANCED_CORE_STRING_H

#include "EnhancedCore/defines.h"
#include "EnhancedCore/export.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/annotations.h"

EXTERN_C_START

/*!
 * Creates a new string.
 *
 * @param length   The count of the new string.
 */
$RetRequiresRelease()
ENHANCED_CORE_API char *stringNew(Size length);

/*!
 * Gets the count of a string.
 *
 * @param string  A string.
 * @return Size   The count of the string.
 */
$RetNotIgnored()
ENHANCED_CORE_API Size stringLength(const char *string);

/*!
 * Verifies two strings are the same.
 *
 * @param string1  A string.
 * @param string2  Another string.
 * @return bool    Whether the string "string1" is equal to the string "string2".
 */
$RetNotIgnored()
ENHANCED_CORE_API bool stringEqual(const char *string1, const char *string2);

/*!
 * Copies a string to a new string of the same count.
 *
 * @param string  A string.
 * @return char*  The new string.
 */
$RetRequiresRelease()
ENHANCED_CORE_API char *stringCopy(const char *string);

/*!
 * Resets the size of a string.
 *
 * @param string   A string.
 * @param newSize  The count of the new string.
 * @return char*   The new string.
 */
$RetRequiresRelease()
ENHANCED_CORE_API char *stringResize(const char *string, Size newSize);

EXTERN_C_END

#endif // !ENHANCED_CORE_STRING_H
