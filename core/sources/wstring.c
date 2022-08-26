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

#include "enhanced/core/wstring.h"

#include "enhanced/core/defines.h"
#include "enhanced/core/types.h"
#include "enhanced/core/assert.h"
#include "enhanced/core/memory.h"

RetRequiresRelease
wchar* wstringNew(const Size length) {
    wchar* str = (wchar*) memoryAlloc((length + 1) * sizeof(wchar));
    if (str == null) {
        return null;
    }
    str[length] = L'\0';

    return str;
}

RetCannotIgnored
Size wstringLength(const wchar* const wstring) {
    assert(wstring != null);

    Size length;
    for (length = 0; wstring[length] != L'\0'; ++length) {}

    return length;
}

RetCannotIgnored
bool wstringEqual(const wchar* const wstring1, const wchar* const wstring2) {
    Size length;

    if (wstring1 == wstring2) {
        return true;
    } else if ((length = wstringLength(wstring1)) == wstringLength(wstring2)) {
        for (Size index = 0; index < length; ++index) {
            if (wstring1[index] != wstring2[index]) {
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}

RetRequiresRelease
wchar* wstringCopy(const wchar* const wstring) {
    assert(wstring != null);

    Size length = wstringLength(wstring);
    wchar* copy = wstringNew(length);
    if (copy == null) {
        return null;
    }

    memoryCopy(copy, wstring, length + 1);

    return copy;
}

RetRequiresRelease
wchar* wstringResize(const wchar* const wstring, const Size newSize) {
    assert(wstring != null), assert(newSize > 1);

    Size length = wstringLength(wstring);
    wchar* copy = wstringNew(newSize);
    if (copy == null) {
        return null;
    }

    memoryCopy(copy, wstring, length + 1);

    return copy;
}
