/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 *
 * Licensed under the Enhanced Software License.
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://sharedwonder.github.io/enhanced/LICENSE.txt
 *
 * UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING,
 * THE SOFTWARE IS ALWAYS PROVIDED "AS IS",
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#include <enhanced/core/stringUtil.h>

#include <enhanced/core/defines.h>
#include <enhanced/core/types.h>
#include <enhanced/core/assert.h>
#include <enhanced/core/memory.h>

RetRequiresRelease RetNullable MustInspectResult
char* stringNew(const sizetype length) {
    char* str = (char*) memoryAlloc((length + 1) * sizeof(char));
    if (str == null) {
        return null;
    }
    str[length] = '\0';

    return str;
}

RetRequiresRelease RetNullable MustInspectResult
char* stringCopy(const char* source) {
    return stringCopyExt(source, stringLength(source));
}

RetRequiresRelease RetNullable MustInspectResult
char* stringCopyExt(const char* source, sizetype length) {
    assert(source != null);

    char* copy = stringNew(length);
    if (copy == null) {
        return null;
    }

    memoryCopy(copy, source, length);

    return copy;
}

RetRequiresRelease RetNullable MustInspectResult
char* stringCopyResize(const char* string, sizetype oldSize, sizetype newSize) {
    assert(string != null);

    char* copy = stringNew(newSize);
    if (copy == null) {
        return null;
    }

    memoryCopy(copy, string, (newSize > oldSize) ? oldSize : newSize);

    return copy;
}

NoIgnoreRet
sizetype stringLength(const char* string) {
    assert(string != null);

    sizetype length;
    for (length = 0; string[length] != '\0'; ++length) {}

    return length;
}

NoIgnoreRet
bool stringEqual(const char* string1, const char* string2) {
    if (string1 == string2) {
        return true;
    } else if (string1 == null || string2 == null) {
        return false;
    } else {
        for (sizetype index = 0;; ++index) {
            if ((string1[index] == '\0') ^ (string2[index] == '\0')) return false;
            if (string1[index] != string2[index]) return false;
        }
    }
}

RetRequiresRelease RetNullable MustInspectResult
wchar* wstringNew(const sizetype length) {
    wchar* str = (wchar*) memoryAlloc((length + 1) * sizeof(wchar));
    if (str == null) {
        return null;
    }
    str[length] = L'\0';

    return str;
}

RetRequiresRelease RetNullable MustInspectResult
wchar* wstringCopy(const wchar* source) {
    return wstringCopyExt(source, wstringLength(source));
}

RetRequiresRelease RetNullable MustInspectResult
wchar* wstringCopyExt(const wchar* source, sizetype length) {
    assert(source != null);

    wchar* copy = wstringNew(length);
    if (copy == null) {
        return null;
    }

    memoryCopy(copy, source, length);

    return copy;
}

RetRequiresRelease RetNullable MustInspectResult
wchar* wstringCopyResize(const wchar* wstring, sizetype oldSize, sizetype newSize) {
    assert(wstring != null);

    wchar* copy = wstringNew(newSize);
    if (copy == null) {
        return null;
    }

    memoryCopy(copy, wstring, (newSize > oldSize) ? oldSize : newSize);

    return copy;
}

NoIgnoreRet
sizetype wstringLength(const wchar* wstring) {
    assert(wstring != null);

    sizetype length;
    for (length = 0; wstring[length] != L'\0'; ++length) {}

    return length;
}

NoIgnoreRet
bool wstringEqual(const wchar* wstring1, const wchar* wstring2) {
    if (wstring1 == wstring2) {
        return true;
    } else if (wstring1 == null || wstring2 == null) {
        return false;
    } else {
        for (sizetype index = 0;; ++index) {
            if ((wstring1[index] == L'\0') ^ (wstring2[index] == L'\0')) return false;
            if (wstring1[index] != wstring2[index]) return false;
        }
    }
}
