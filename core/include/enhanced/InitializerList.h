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

#pragma once

#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>

namespace enhanced {
    template <typename Type>
    class InitializerList {
    private:
        std::initializer_list<Type> initList;

    public:
        inline constexpr InitializerList(std::initializer_list<Type> initList) : initList(initList) {}

        [[RetNotIgnored]]
        inline constexpr const Type* begin() const noexcept {
            return initList.begin();
        }

        [[RetNotIgnored]]
        inline constexpr const Type* end() const noexcept {
            return initList.end();
        }

        [[RetNotIgnored]]
        inline constexpr const Type* toArray() const noexcept {
            return initList.begin();
        }

        [[RetNotIgnored]]
        inline constexpr sizetype getSize() const noexcept {
            return initList.size();
        }

        [[RetNotIgnored]]
        inline constexpr Type& get(sizetype index) const noexcept {
            return toArray()[index];
        }
    };
}

#define E_INIT_LIST_CONSTRUCTOR(NAME, ...) NAME(std::initializer_list<Type> list) __VA_ARGS__ : NAME(enhanced::InitializerList(list)) {}

#ifdef ENHANCED_MACRO_NO_PREFIX_ALIAS
    #define INIT_LIST_CONSTRUCTOR E_INIT_LIST_CONSTRUCTOR
#endif
