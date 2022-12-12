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
#include <enhanced/util/Traits.h>
#include <enhanced/util/Functional.h>
#include <enhanced/exceptions/NotImplementedError.h>

namespace enhanced::util {
    template <typename FunctionType>
    requires isFunction<FunctionType>
    class Function : public Functional {
    public:
        using ReturnType = typename FunctionParser<FunctionType>::ReturnType;
        using NeatFunctionType = typename FunctionParser<FunctionType>::NeatFunctionType;

        Function() = default;

        template <typename Callable>
        Function(Callable callable) {
            NOT_IMPLEMENTED();
        }

        Function(FunctionType *function) {
            NOT_IMPLEMENTED();
        }

        template <typename... Args>
        requires isSame<NeatFunctionType, ReturnType (Args...)>
        inline ReturnType invoke(Args... args) const {
            NOT_IMPLEMENTED();
        }

        template <typename... Args>
        requires isSame<NeatFunctionType, ReturnType (Args...)>
        inline ReturnType operator()(Args... args) const {
            return invoke(args...);
        }
    };
}
