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

#pragma once

#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/String.h>

namespace enhanced {
    class TypeInfo final {
    private:
        template <typename>
        friend constexpr TypeInfo typeInfoOf();

        template <typename Type>
        friend constexpr TypeInfo typeInfoOf(Type&& value);

        const std::type_info& info;

        constexpr TypeInfo(const std::type_info& info) : info(info) {}

    public:
        TypeInfo(const TypeInfo& info) = delete;

        TypeInfo& operator=(const TypeInfo& info) = delete;

        $NoIgnoreReturn
        String getName() const;

        $NoIgnoreReturn
        sizetype hashCode() const;
    };

    template <typename Type>
    inline constexpr TypeInfo typeInfoOf() {
        return typeid(Type);
    }

    template <typename Type>
    inline constexpr TypeInfo typeInfoOf(Type&& value) {
        return typeid(value);
    }
}
