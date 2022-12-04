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
#include <enhanced/Annotations.h>

namespace enhanced::collections {
    template <typename Type>
    struct Collection {
        virtual ~Collection() noexcept = default;

        $NoIgnoreReturn
        virtual sizetype getSize() const = 0;

        $NoIgnoreReturn
        virtual bool isEmpty() const = 0;

        $NoIgnoreReturn
        virtual bool contain(const Type& value) const = 0;

        virtual void clear() = 0;
    };

    ENHANCED_CORE_API extern sizetype ARRAY_INIT_SIZE; // Default value: 256
}
