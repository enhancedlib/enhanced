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
