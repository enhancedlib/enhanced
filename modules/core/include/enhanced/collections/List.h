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
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/collections/Queue.h>

namespace enhanced::collections {
    template <typename Type>
    struct List : Queue<Type> {
        virtual void addFirst(const Type& element) = 0;

        virtual void addFirst(Type&& element) = 0;

        virtual Type removeLast() = 0;

        virtual bool removeLastIf() = 0;
    };
}
