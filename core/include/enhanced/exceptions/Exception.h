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

namespace enhanced::exceptions {
    class ENHANCED_CORE_API Exception {
    protected:
        const String message;

        const Exception* cause;

    public:
        $NoIgnoreReturn
        virtual func getName() const -> const String {
            return "enhanced::exceptions::Exception";
        }

        explicit Exception(const String& message = "") noexcept;

        explicit Exception(const Exception* cause) noexcept;

        Exception(const String& message, const Exception* cause) noexcept;

        virtual ~Exception() noexcept;

        $NoIgnoreReturn
        virtual func getTraceback() const noexcept -> String;

        $NoIgnoreReturn
        virtual func getCause() const noexcept -> const Exception*;

        $NoIgnoreReturn
        virtual func getMessage() const noexcept -> const String&;
    };
}

#define DEFINE_EXCEPTION_NAME(name) \
        $NoIgnoreReturn \
        func getName() const -> const String override { \
            return #name; \
        }
