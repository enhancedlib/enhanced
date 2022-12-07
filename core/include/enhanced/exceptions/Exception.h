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

    using TerminateHandler = void (*)();

    ENHANCED_CORE_API void defaultTerminateHandler() noexcept;

    ENHANCED_CORE_API const TerminateHandler& setupTerminateHandler(const TerminateHandler& terminateHandler) noexcept;

    ENHANCED_CORE_API extern TerminateHandler terminateHandlerFunc;
}

#define DEFINE_EXCEPTION_NAME(name) \
    $NoIgnoreReturn \
    const String getName() const override { \
        return #name; \
    }
