/*
 * This file is part of Enhanced Framework.
 *
 * Copyright (C) 2023 Liu Baihao (sharedwonder). All rights reserved.
 *
 * Permission is hereby granted, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software,
 * including without limitation the rights to use, copy, modify, merge,
 * distribute, subject to the following restrictions:
 *
 * 1. The above copyright notice and this permission notice shall be included in
 *    all copies of the Software and modified versions.
 *
 * 2. You may not charge any fees or receive other compensation for the
 *    distribution of the Software.
 *
 * 3. You may not misrepresent the source of the Software, and you may not claim
 *    that you wrote the original version.
 *
 * 4. If you use this Software in your product, you should indicate the it in
 *    the product documentation.
 *
 * Unless you have obtained the written consent of the copyright holders,
 * you may not break these restrictions.
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

#include <typeinfo> // std::type_info, typeid (keyword)

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

        E_ANNOTATE(RetNotIgnored)
        String getName() const;

        E_ANNOTATE(RetNotIgnored)
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
