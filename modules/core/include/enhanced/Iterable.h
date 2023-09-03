/*
 * This file is part of Enhanced Framework.
 *
 * Copyright (C) 2023 sharedwonder (Liu Baihao). All rights reserved.
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
 *    distribution of the Software, except for distributing modified versions and
 *    products that use the Software.
 *
 * 5. If you use this Software in your product, you shall indicate it.
 *
 * 6. Neither the name of the author nor the names of its contributors may
 *    be used to endorse or promote products derived from the Software.
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

#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/Traits.h>
#include <enhanced/TraitInterface.h>
#include <enhanced/Iterator.h>

namespace enhanced {
    E_TRAIT_INTERFACE()
    class Iterable {
        E_CLASS(Iterable)

    E_CLASS_HEADER
        E_TRAIT_INTERFACE_METHOD_RET_ANY(iterator, (), const)

    E_CLASS_BODY
        E_RET_NO_DISCARD()
        inline constexpr auto begin() const noexcept {
            auto it = ForEachIterator<ForwardIterator<decltype(iterator())>>(ForwardIterator<decltype(iterator())>(iterator()));
            it.step();
            return it;
        }

        E_RET_NO_DISCARD()
        inline constexpr byte end() const noexcept {
            return 0;
        }
    };

    template <typename Type>
    class ReversedForEach {
        E_CLASS(ReversedForEach)

    E_CLASS_HEADER
        static_assert(isBaseOf<Iterable<Type>, Type>);
        static_assert(testValid<decltype(declvalue<const Type&>().reverseIterator())>);

    E_CLASS_BODY
    private:
        const Type& iterable;

    public:
        ReversedForEach(const Type& iterable) noexcept : iterable(iterable) {}

        E_RET_NO_DISCARD()
        inline constexpr auto begin() const noexcept {
            auto it = ForEachIterator<decltype(iterable.reverseIterator())>(iterable.reverseIterator());
            it.step();
            return it;
        }

        E_RET_NO_DISCARD()
        inline constexpr byte end() const noexcept {
            return 0;
        }
    };
}
