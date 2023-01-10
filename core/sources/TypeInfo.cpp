/*
 * Copyright (C) 2023 Liu Baihao. All rights reserved.
 *
 * Licensed under the Enhanced Software License.
 *
 * This file is part of the Enhanced Software, and IT ALWAYS
 * PROVIDES "AS IS" WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 *
 * You may not use this file except in compliance with the License.
 * You should obtain a copy of the License in the distribution,
 * if not, see <https://sharedwonder.github.io/enhanced/LICENSE.txt>
 */

#include <enhanced/TypeInfo.h>

#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/String.h>
#include <enhanced/util/Traits.h>

using enhanced::util::removeConst;

namespace enhanced {
    [[RetNotIgnored]]
    String TypeInfo::getName() const {
        return removeConst(info.name());
    }

    [[RetNotIgnored]]
    sizetype TypeInfo::hashCode() const {
        return info.hash_code();
    }
}
