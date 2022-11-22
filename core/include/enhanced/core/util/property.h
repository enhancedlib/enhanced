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

#include <enhanced/core/defines.h>
#include <enhanced/core/types.h>
#include <enhanced/core/annotations.h>
#include <enhanced/core/util/traits.h>

#define Property(type, name, value, getter, setter, ...) \
    struct { \
    private: \
        using Self = type; \
        Self self = value; \
        __PROPERTY_GETTER_##getter \
        __PROPERTY_SETTER_##setter \
    public: \
        __VA_ARGS__ \
    } name

#define PropertyFieldClass(clazz) using CLASS = clazz

#define PropertyField(type, name, getter, setter, ...) \
    struct PropertyField_##name { \
        friend CLASS; \
    private: \
        using Self = type; \
        Self self; \
        inline PropertyField_##name(Self&& value) : self(value) {} \
        __PROPERTY_GETTER_##getter \
        __PROPERTY_SETTER_##setter \
    public: \
        __VA_ARGS__ \
    } name

#define __PROPERTY_GETTER_get(accessModifier) \
accessModifier: \
    $(NoIgnoreReturn) \
    inline func operator->() const -> const Self* { \
        return &self; \
    } \
    $(NoIgnoreReturn) \
    inline operator const Self&() const { \
        return operator()(); \
    } \
    $(NoIgnoreReturn) \
    inline func operator()() const -> const Self&

#define __PROPERTY_SETTER_set(accessModifier) \
accessModifier: \
    inline func operator=(const Self& value) -> Self&

#define __PROPERTY_GETTER_getdef(accessModifier) \
    __PROPERTY_GETTER_get(accessModifier) { \
        return self; \
    }

#define __PROPERTY_SETTER_setdef(accessModifier) \
    __PROPERTY_SETTER_set(accessModifier) { \
        return self = value; \
    }
