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

namespace enhanced::exceptions {
    class ENHANCED_CORE_API RuntimeException : public Exception {
    public:
        E_DEFINE_EXCEPTION_NAME(enhanced::exceptions::RuntimeException)

        explicit RuntimeException(const String& message = "") noexcept;

        explicit RuntimeException(const Exception* cause) noexcept;

        RuntimeException(const String& message, const Exception* cause) noexcept;
    };
}
