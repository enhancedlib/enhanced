/*
 * Copyright (C) 2023 Liu Baihao. All rights reserved.
 *
 * Licensed under the MIT License with "Fairness" Exception.
 *
 * You may not use this file except in compliance with the License.
 *
 * This file is part of The Enhanced Software, and IT ALWAYS
 * PROVIDES "AS IS" WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
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

        [[RetNotIgnored]]
        String getName() const;

        [[RetNotIgnored]]
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
