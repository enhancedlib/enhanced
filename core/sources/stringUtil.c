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
char* stringNew(const Size length) {
    char* str = (char*) memoryAlloc((length + 1) * sizeof(char));
    if (str == null) {
        return null;
    }
    str[length] = '\0';

    return str;
}

RetRequiresRelease RetNullable MustInspectResult
char* stringCopy(NotNull const char* source) {
    return stringCopyExt(source, stringLength(source));
}

RetRequiresRelease RetNullable MustInspectResult
char* stringCopyExt(NotNull const char* source, Size length) {
    assert(source != null);

    char* copy = stringNew(length);
    if (copy == null) {
        return null;
    }

    memoryCopy(copy, source, length);

    return copy;
}

RetRequiresRelease RetNullable MustInspectResult
char* stringCopyResize(NotNull const char* string, Size oldSize, Size newSize) {
    assert(string != null);

    char* copy = stringNew(newSize);
    if (copy == null) {
        return null;
    }

    memoryCopy(copy, string, (newSize > oldSize) ? oldSize : newSize);

    return copy;
}

RetCannotIgnored
Size stringLength(NotNull const char* string) {
    assert(string != null);

    Size length;
    for (length = 0; string[length] != '\0'; ++length) {}

    return length;
}

RetCannotIgnored
bool stringEqual(const char* string1, const char* string2) {
    Size length;

    if (string1 == string2) {
        return true;
    } else if (string1 == null || string2 == null) {
        return false;
    } else if ((length = stringLength(string1)) == stringLength(string2)) {
        for (Size index = 0; index < length; ++index) {
            if (string1[index] != string2[index]) return false;
        }
        return true;
    }

    return false;
}

RetCannotIgnored
bool stringEqualExt(const char* string1, const Size length1, const char* string2, Size length2) {
    if (string1 == string2) {
        return true;
    } else if (string1 == null || string2 == null) {
        return false;
    } else if (length1 == length2) {
        for (Size index = 0; index < length1; ++index) {
            if (string1[index] != string2[index]) return false;
        }
        return true;
    }

    return false;
}

RetRequiresRelease RetNullable MustInspectResult
wchar* wstringNew(const Size length) {
    wchar* str = (wchar*) memoryAlloc((length + 1) * sizeof(wchar));
    if (str == null) {
        return null;
    }
    str[length] = L'\0';

    return str;
}

RetRequiresRelease RetNullable MustInspectResult
wchar* wstringCopy(NotNull const wchar* source) {
    return wstringCopyExt(source, wstringLength(source));
}

RetRequiresRelease RetNullable MustInspectResult
wchar* wstringCopyExt(NotNull const wchar* source, Size length) {
    assert(source != null);

    wchar* copy = wstringNew(length);
    if (copy == null) {
        return null;
    }

    memoryCopy(copy, source, length);

    return copy;
}

RetRequiresRelease RetNullable MustInspectResult
wchar* wstringCopyResize(NotNull const wchar* wstring, Size oldSize, Size newSize) {
    assert(wstring != null);

    wchar* copy = wstringNew(newSize);
    if (copy == null) {
        return null;
    }

    memoryCopy(copy, wstring, (newSize > oldSize) ? oldSize : newSize);

    return copy;
}

RetCannotIgnored
Size wstringLength(NotNull const wchar* wstring) {
    assert(wstring != null);

    Size length;
    for (length = 0; wstring[length] != L'\0'; ++length) {}

    return length;
}

RetCannotIgnored
bool wstringEqual(const wchar* wstring1, const wchar* wstring2) {
    Size length;

    if (wstring1 == wstring2) {
        return true;
    } else if (wstring1 == null || wstring2 == null) {
        return false;
    } else if ((length = wstringLength(wstring1)) == wstringLength(wstring2)) {
        for (Size index = 0; index < length; ++index) {
            if (wstring1[index] != wstring2[index]) return false;
        }
        return true;
    }

    return false;
}

RetCannotIgnored
bool wstringEqualExt(const wchar* wstring1, Size length1, const wchar* wstring2, Size length2) {
    if (wstring1 == wstring2) {
        return true;
    } else if (wstring1 == null || wstring2 == null) {
        return false;
    } else if (length1 == length2) {
        for (Size index = 0; index < length1; ++index) {
            if (wstring1[index] != wstring2[index]) return false;
        }
        return true;
    }

    return false;
}
