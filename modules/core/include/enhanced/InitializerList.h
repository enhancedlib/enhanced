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

#pragma once

#include <initializer_list> // std::initializer_list

#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>

#define E_INIT_LIST_CONSTRUCTOR(NAME, TYPE) inline NAME(std::initializer_list<TYPE> list) : NAME(enhanced::InitializerList(list)) {}

#ifdef ENHANCED_MACRO_NO_PREFIX_ALIAS
    #define INIT_LIST_CONSTRUCTOR E_INIT_LIST_CONSTRUCTOR
#endif

namespace enhanced {
    template <typename Type>
    class InitializerList {
    private:
        std::initializer_list<Type> initList;

    public:
        inline constexpr InitializerList(std::initializer_list<Type> initList) noexcept : initList(initList) {}

        E_ANNOTATE(RetNotIgnored)
        inline constexpr const Type* begin() const noexcept {
            return initList.begin();
        }

        E_ANNOTATE(RetNotIgnored)
        inline constexpr const Type* end() const noexcept {
            return initList.end();
        }

        E_ANNOTATE(RetNotIgnored)
        inline constexpr const Type* toArray() const noexcept {
            return initList.begin();
        }

        E_ANNOTATE(RetNotIgnored)
        inline constexpr sizetype getSize() const noexcept {
            return initList.size();
        }

        E_ANNOTATE(RetNotIgnored)
        inline constexpr Type& get(sizetype index) const noexcept {
            return toArray()[index];
        }
    };
}
