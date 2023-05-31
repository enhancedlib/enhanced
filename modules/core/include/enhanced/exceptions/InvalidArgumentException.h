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
#include <enhanced/exceptions/Exception.h>
#include <enhanced/exceptions/RuntimeException.h>

namespace enhanced::exceptions {
    class E_CORE_API InvalidArgumentException : public RuntimeException {
    public:
        E_DEFINE_EXCEPTION_NAME(enhanced::exceptions::InvalidArgumentException)

        explicit InvalidArgumentException(const String& message = "") noexcept;

        explicit InvalidArgumentException(const Exception* cause) noexcept;

        InvalidArgumentException(const String& message, const Exception* cause) noexcept;
    };
}
