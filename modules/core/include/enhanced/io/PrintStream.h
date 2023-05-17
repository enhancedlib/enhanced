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
#include <enhanced/io/OutputStream.h>
#include <enhanced/io/Display.h>

namespace enhanced::io {
    class ENHANCED_CORE_API PrintStream : public OutputStream {
    public:
        template <typename Type>
        requires isDisplayable<util::RemoveRefAndCv<Type>>
        void print(Type&& value) const {
            display(*this, value);
        }

        template <typename Type>
        requires isDisplayable<util::RemoveRefAndCv<Type>>
        void println(Type&& value) const {
            display(*this, value);
            println();
        }

        void println() const;

        void printf(const String& message, ...) const;

        void close() const override;

        void flush() const override;
    };
}
