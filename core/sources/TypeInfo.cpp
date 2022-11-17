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

#include <enhanced/core/TypeInfo.h>

#include <enhanced/core/defines.h>
#include <enhanced/core/types.h>
#include <enhanced/core/String.h>
#include <enhanced/core/util/traits.h>

using enhanced::core::util::removeConst;

namespace enhanced::core {
    $(NoIgnoreReturn)
    func TypeInfo::getName() const -> String {
        return removeConst(info.name());
    }

    $(NoIgnoreReturn)
    func TypeInfo::hashCode() const -> sizetype {
        return info.hash_code();
    }
}
