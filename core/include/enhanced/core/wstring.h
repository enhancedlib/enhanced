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

#include "defines.h"
#include "export.h"
#include "types.h"
#include "annotations.h"

/*!
 * Creates a new wide string.
 *
 * @param length  The count of the new wide string.
 */
RetRequiresRelease
ENHANCED_CORE_API wchar* wstringNew(Size length);

/*!
 * Gets the count of a wide string.
 *
 * @param wstring  A wide string.
 * @return Size    The count of the wide string.
 */
EXTERN_C
RetCannotIgnored
ENHANCED_CORE_API Size wstringLength(const wchar* wstring);

/*!
 * Verifies two wide strings are the same.
 *
 * @param wstring1   A wide string.
 * @param wstring2   Another wide string.
 * @return bool      Whether the wide string "wstring1" is equal to the wide string "wstring2".
 */
EXTERN_C
RetCannotIgnored
ENHANCED_CORE_API bool wstringEqual(const wchar* wstring1, const wchar* wstring2);

/*!
 * Copies a wide string to a new wide string of the same count.
 *
 * @param wstring  A wide string.
 * @return char*   The new wide string.
 */
RetRequiresRelease
ENHANCED_CORE_API wchar* wstringCopy(const wchar* string);

/*!
 * Resets the size of a wide string.
 *
 * @param wstring   A wide string.
 * @param newSize   The count of the new wide string.
 * @return char*    The new wide string.
 */
RetRequiresRelease
ENHANCED_CORE_API wchar* wstringResize(const wchar* wstring, Size newSize);
