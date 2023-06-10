/*
 * This file is part of Enhanced Framework.
 *
 * Copyright (C) 2023 Liu Baihao (sharedwonder). All rights reserved.
 *
 * Permission is hereby granted, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software,
 * including without limitation the rights to use, copy, modify, merge,
 * distribute. Unless you have obtained permission from the copyright holders,
 * subject to the following restrictions:
 *
 * 1. The above copyright notice and this permission notice shall be included in
 *    all copies of the Software and modified versions.
 *
 * 2. You may not misrepresent the source of the Software, and you may not claim
 *    that you wrote the original version.
 *
 * 3. You may not misrepresent the modified version as the original version.
 *
 * 4. You may not charge any fees or receive other compensation for the
 *    distribution of the Software, excluding distribution of modified versions
 *    and products using the Software.
 *
 * 5. If you use this Software in your product, you shall indicate it.
 *
 * 6. Neither the name of the author nor the names of its contributors may
 *    be used to endorse or promote products derived from the Software
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#include <initializer_list> // std::initializer_list

#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>

#define E_INIT_LIST_CONSTRUCTOR(NAME, TYPE) inline NAME(std::initializer_list<TYPE> list) : NAME(enhanced::InitializerList(list)) {}

#ifdef E_SM_MACRO_NO_PREFIX_ALIAS
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
