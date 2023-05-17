/*
 * Copyright (C) 2023 Liu Baihao. All rights reserved.
 *
 * Licensed under the MIT License with the Distribution Exception.
 * You may not use this file except in compliance with the License.
 *
 * THIS FILE IS PART OF THE ENHANCED SOFTWARE, and IT ALWAYS
 * PROVIDES "AS IS" WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#include <enhanced/TypeInfo.h>

#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/String.h>
#include <enhanced/util/Traits.h>

using enhanced::util::removeConst;

namespace enhanced {
    E_ANNOTATE(RetNotIgnored)
    String TypeInfo::getName() const {
        return removeConst(info.name());
    }

    E_ANNOTATE(RetNotIgnored)
    sizetype TypeInfo::hashCode() const {
        return info.hash_code();
    }
}
