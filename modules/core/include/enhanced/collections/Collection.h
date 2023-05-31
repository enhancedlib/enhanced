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
#include <enhanced/Annotations.h>

namespace enhanced::collections {
    template <typename Type>
    struct Collection {
        using Element = Type;

        virtual ~Collection() noexcept = default;

        E_ANNOTATE(RetNotIgnored)
        virtual sizetype getSize() const = 0;

        E_ANNOTATE(RetNotIgnored)
        virtual bool isEmpty() const = 0;

        E_ANNOTATE(RetNotIgnored)
        virtual bool contain(const Type& value) const = 0;

        virtual void clear() = 0;
    };

    E_CORE_API extern sizetype ARRAY_INIT_SIZE; // Default value: 256
}
