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
#include <enhanced/io/OutputStream.h>

namespace enhanced::io {
    class ENHANCED_CORE_API BufferOutputStream : public OutputStream {
    public:
        void write(byte ch) const override;

        void write(const byte* buffer, sizetype size) const override;
    };
}
