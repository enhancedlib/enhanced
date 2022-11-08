/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 *
 * Licensed under the Enhanced Software License, latest version.
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

#include <enhanced/core/TypeInfo.h>

#include <enhanced/core/defines.h>
#include <enhanced/core/types.h>
#include <enhanced/core/String.h>

using enhanced::core::TypeInfo;
using enhanced::core::String;

NoIgnoreRet
String TypeInfo::getName() const {
    return info.name();
}

NoIgnoreRet
String TypeInfo::getRawName() const {
    return info.raw_name();
}

NoIgnoreRet
sizetype TypeInfo::hashCode() const {
    return info.hash_code();
}
