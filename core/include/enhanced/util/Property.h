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
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/util/Traits.h>

#define propertiesClass(name) using CLASS = name

#define property(type, name, getter, setter, ...) \
    struct Property_##name { \
        friend CLASS; \
    private: \
        using Self = type; \
        Self self; \
        inline Property_##name(Self value) : self(enhanced::util::move(value)) {} \
        __property_getter_##getter \
        __property_setter_##setter \
    public: \
        __VA_ARGS__ \
    } name

#define __property_getter_get(accessModifier) \
accessModifier: \
    $NoIgnoreReturn \
    inline const Self* operator->() const { \
        return &self; \
    } \
    $NoIgnoreReturn \
    inline const Self& operator*() const { \
        return operator()(); \
    } \
    $NoIgnoreReturn \
    inline operator const Self&() const { \
        return operator()(); \
    } \
    $NoIgnoreReturn \
    inline const Self& operator()() const

#define __property_setter_set(accessModifier) \
accessModifier: \
    inline Self& operator=(const Self& value)

#define __property_getter_getter(accessModifier) \
    __property_getter_get(accessModifier) { \
        return self; \
    }

#define __property_setter_setter(accessModifier) \
    __property_setter_set(accessModifier) { \
        return self = value; \
    }
