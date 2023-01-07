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
#include <enhanced/ExportCore.h>
#include <enhanced/Types.h>
#include <enhanced/Memory.h>
#include <enhanced/Process.h>
#include <enhanced/String.h>
#include <enhanced/MutString.h>

namespace enhanced::exceptions {
    class ENHANCED_CORE_API Exception {
    protected:
        String message;

        const Exception* cause;

    public:
        $NoIgnoreReturn
        virtual const String getName() const {
            return "enhanced::exceptions::Exception";
        }

        explicit Exception(const String& message = "") noexcept;

        explicit Exception(const Exception* cause) noexcept;

        explicit Exception(const String& message, const Exception* cause) noexcept;

        virtual ~Exception() noexcept;

        void printInfo() const;

        $NoIgnoreReturn
        virtual MutString getInfo() const noexcept;

        $NoIgnoreReturn
        virtual const Exception* getCause() const noexcept;

        $NoIgnoreReturn
        virtual const String& getMessage() const noexcept;
    };

    using ExceptionHandler = void (*)();

    ENHANCED_CORE_API void defaultExceptionHandler() noexcept;

    ENHANCED_CORE_API const ExceptionHandler& setupExceptionHandler(const ExceptionHandler& handler) noexcept;

    ENHANCED_CORE_API extern ExceptionHandler exceptionHandler;
}

#define DEFINE_EXCEPTION_NAME(NAME) \
    $NoIgnoreReturn \
    const String getName() const override { \
        return #NAME; \
    }
