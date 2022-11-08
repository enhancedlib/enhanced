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

#pragma once

#include <typeinfo>

#include <enhanced/core/defines.h>
#include <enhanced/core/types.h>
#include <enhanced/core/String.h>

#ifdef CXX_LANGUAGE

NAMESPACE_L2_BEGIN(enhanced, core)

class TypeInfo final {
private:
    template <typename Type>
    friend constexpr TypeInfo typeInfoOf();

    const std::type_info& info;

    constexpr TypeInfo(const std::type_info& info) : info(info) {};

public:
#ifdef CXX_11_OR_LATER
    TypeInfo(const TypeInfo& info) = delete;

    TypeInfo& operator=(const TypeInfo& info) = delete;
#endif

    NoIgnoreRet
    String getName() const;

    NoIgnoreRet
    String getRawName() const;

    NoIgnoreRet
    sizetype hashCode() const;
};

template <typename Type>
inline constexpr TypeInfo typeInfoOf() {
    return typeid(Type);
}

NAMESPACE_L2_END

#endif
