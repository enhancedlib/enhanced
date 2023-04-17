/*
 * Copyright (C) 2023 Liu Baihao. All rights reserved.
 *
 * Licensed under the MIT License with "Fairness" Exception.
 *
 * You may not use this file except in compliance with the License.
 *
 * This file is part of The Enhanced Software, and IT ALWAYS
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
    class ENHANCED_CORE_API MemoryAllocationError : public Error {
    public:
        E_DEFINE_EXCEPTION_NAME(enhanced::exceptions::MemoryAllocationError)

        explicit MemoryAllocationError(const String& message = "") noexcept;
    };
}
