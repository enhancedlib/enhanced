 /*
 * Copyright (C) 2023 Liu Baihao. All rights reserved.
 *
 * Licensed under the MIT License with the Distribution Exception.
 * You may not use this file except in compliance with the License.
 *
 * THIS FILE IS PART OF THE ENHANCED SOFTWARE, and IT ALWAYS
 * PROVIDES "AS IS" WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#pragma once

#include <enhanced/Defines.h>
#include <enhanced/ExportCore.h>
#include <enhanced/Types.h>
#include <enhanced/Memory.h>
#include <enhanced/Process.h>
#include <enhanced/String.h>

#define E_DEFINE_EXCEPTION_NAME(NAME) \
    E_ANNOTATE(RetNotIgnored) \
    const String getName() const override { \
        return #NAME; \
    }

#ifdef E_SM_MACRO_NO_PREFIX_ALIAS
    #define DEFINE_EXCEPTION_NAME E_DEFINE_EXCEPTION_NAME
#endif

namespace enhanced::exceptions {
    class E_CORE_API Exception {
    protected:
        String message;

        const Exception* cause;

    public:
        E_ANNOTATE(RetNotIgnored)
        virtual const String getName() const {
            return "enhanced::exceptions::Exception";
        }

        explicit Exception(const String& message = "") noexcept;

        explicit Exception(const Exception* cause) noexcept;

        explicit Exception(const String& message, const Exception* cause) noexcept;

        virtual ~Exception() noexcept;

        void printInfo() const;

        E_ANNOTATE(RetNotIgnored)
        virtual String getInfo() const noexcept;

        E_ANNOTATE(RetNotIgnored)
        virtual const Exception* getCause() const noexcept;

        E_ANNOTATE(RetNotIgnored)
        virtual const String& getMessage() const noexcept;
    };

    using ExceptionHandler = void (*)();

    E_CORE_API void defaultExceptionHandler() noexcept;

    E_CORE_API const ExceptionHandler& setupExceptionHandler(const ExceptionHandler& handler) noexcept;

    E_CORE_API extern ExceptionHandler exceptionHandler;
}
