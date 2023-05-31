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
#include <enhanced/String.h>
#include <enhanced/exceptions/Error.h>

namespace enhanced::exceptions {
    class E_CORE_API AssertionError : public Error {
    public:
        E_DEFINE_EXCEPTION_NAME(enhanced::exceptions::AssertionError)

        explicit AssertionError(const String& message = "") noexcept;

        explicit AssertionError(const String& expression, const String& file, sizetype line) noexcept;

        explicit AssertionError(const String& expression, const String& file, sizetype line, const String& message) noexcept;
    };
}
