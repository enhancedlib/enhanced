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

namespace enhancedInternal::util {
    template <typename Return, typename... Args>
    class FunctionImpl {
    public:
        using ReturnType = Return;

        inline func invoke(Args... args) -> ReturnType {
            NOT_IMPLEMENTED();
        }

        inline func operator()(Args... args) -> ReturnType {
            return invoke(args...);
        }
    };

    template <typename>
    struct GetFunctionImpl final {};

    template <typename ReturnType, typename... Args>
    struct GetFunctionImpl<ReturnType (Args...)> final {
        using Type = FunctionImpl<ReturnType, Args...>;
    };
}

namespace enhanced::util {
    template <typename FunctionType>
    requires isFunction<FunctionType>
    class Function : public Functional, public enhancedInternal::util::GetFunctionImpl<FunctionType>::Type {
    private:
    	using FunctionImpl = typename enhancedInternal::util::GetFunctionImpl<FunctionType>::Type;

    public:
        Function() = default;

        template <typename Callable>
        Function(Callable callable) {
            NOT_IMPLEMENTED();
        }

        template <typename... Args>
        Function(typename FunctionImpl::ReturnType (*function)(Args...)) {
            NOT_IMPLEMENTED();
        }
    };
}
