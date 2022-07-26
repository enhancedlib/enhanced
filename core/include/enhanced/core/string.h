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
 */

#pragma once

#include "defines.h"
#include "export.h"
#include "types.h"
#include "annotations.h"

/*!
 * Creates a new string.
 *
 * @param length   The count of the new string.
 */
RetRequiresRelease()
ENHANCED_CORE_API char* stringNew(Size length);

/*!
 * Gets the count of a string.
 *
 * @param string  A string.
 * @return Size   The count of the string.
 */
EXTERN_C
RetCannotIgnored()
ENHANCED_CORE_API Size stringLength(const char* string);

/*!
 * Verifies two strings are the same.
 *
 * @param string1  A string.
 * @param string2  Another string.
 * @return bool    Whether the string "string1" is equal to the string "string2".
 */
EXTERN_C
RetCannotIgnored()
ENHANCED_CORE_API bool stringEqual(const char* string1, const char* string2);

/*!
 * Copies a string to a new string of the same count.
 *
 * @param string  A string.
 * @return char*  The new string.
 */
RetRequiresRelease()
ENHANCED_CORE_API char* stringCopy(const char* string);

/*!
 * Resets the size of a string.
 *
 * @param string   A string.
 * @param newSize  The count of the new string.
 * @return char*   The new string.
 */
RetRequiresRelease()
ENHANCED_CORE_API char* stringResize(const char* string, Size newSize);
