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

#include <functional>

#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/Traits.h>
#include <enhanced/Functional.h>
#include <enhanced/exceptions/NotImplementedError.h>

namespace enhanced {
    template <typename FunctionType>
    requires isFunction<FunctionType> && (!FunctionParser<FunctionType>::hasVarargs)
    class Function : public Functional {
        E_CLASS(Function)

    E_CLASS_BODY
    public:
        using ReturnType = typename FunctionParser<FunctionType>::ReturnType;
        using NeatFunctionType = typename FunctionParser<FunctionType>::NeatFunctionType;

    private:
        std::function<FunctionType> function;

    public:
        Function() = default;

        Function(std::function<FunctionType> function) : function(function) {}

        template <typename... Args>
        inline ReturnType invoke(Args&&... args) const {
            return function(forward<Args&&>(args)...);
        }

        template <typename... Args>
        inline ReturnType operator()(Args&&... args) const {
            return invoke(forward<Args&&>(args)...);
        }
    };
}
