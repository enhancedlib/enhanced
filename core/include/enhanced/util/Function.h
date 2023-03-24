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
#include <enhanced/util/Traits.h>
#include <enhanced/util/Functional.h>
// #include <enhanced/exceptions/NotImplementedError.h>

namespace enhanced::util {
    template <typename FunctionType>
    requires isFunction<FunctionType> && (!FunctionParser<FunctionType>::hasVarargs)
    class Function : public Functional {
    private:
        std::function<FunctionType> function;

    public:
        using ReturnType = typename FunctionParser<FunctionType>::ReturnType;
        using NeatFunctionType = typename FunctionParser<FunctionType>::NeatFunctionType;

        Function() = default;

        Function(std::function<FunctionType> function) : function(function) {}

        // template <typename Callable>
        // Function(Callable callable) {
        //     E_NOT_IMPLEMENTED();
        // }

        // Function(FunctionType *function) {
        //     E_NOT_IMPLEMENTED();
        // }

        template <typename... Args>
        requires isSame<NeatFunctionType, ReturnType (Args...)>
        inline ReturnType invoke(Args... args) const {
            // E_NOT_IMPLEMENTED();
            return function(args...);
        }

        template <typename... Args>
        requires isSame<NeatFunctionType, ReturnType (Args...)>
        inline ReturnType operator()(Args... args) const {
            return invoke(args...);
        }
    };
}
