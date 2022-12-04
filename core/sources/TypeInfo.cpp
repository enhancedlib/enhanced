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

#include <enhanced/TypeInfo.h>

#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/String.h>
#include <enhanced/util/Traits.h>

using enhanced::util::removeConst;

namespace enhanced {
    $NoIgnoreReturn
    String TypeInfo::getName() const {
        return removeConst(info.name());
    }

    $NoIgnoreReturn
    sizetype TypeInfo::hashCode() const {
        return info.hash_code();
    }
}
