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
#include <enhanced/util/Traits.h>

#define __E_PROPERTY_GETTER_get(ACCESS_MODIFIER) \
ACCESS_MODIFIER: \
    [[RetNotIgnored]] \
    inline const Self* operator->() const { \
        return &self; \
    } \
    [[RetNotIgnored]] \
    inline const Self& operator*() const { \
        return operator()(); \
    } \
    [[RetNotIgnored]] \
    inline operator const Self&() const { \
        return operator()(); \
    } \
    [[RetNotIgnored]] \
    inline const Self& operator()() const

#define __E_PROPERTY_SETTER_set(ACCESS_MODIFIER) \
ACCESS_MODIFIER: \
    [[ReturnSelf]] \
    inline Self& operator=(const Self& value)

#define __E_PROPERTY_GETTER_getter(ACCESS_MODIFIER) \
    __E_PROPERTY_GETTER_get(ACCESS_MODIFIER) { \
        return self; \
    }

#define __E_PROPERTY_SETTER_setter(ACCESS_MODIFIER) \
    __E_PROPERTY_SETTER_set(ACCESS_MODIFIER) { \
        return self = value; \
    }

#define E_PROPERTIES_CLASS(NAME) using __PROPERTIES_CLASS_SELF = NAME

#define E_PROPERTIES_STRUCT(NAME) \
    private: \
        E_PROPERTIES_CLASS(NAME); \
    public:

#define E_PROPERTY(TYPE, NAME, GETTER, SETTER, ...) \
    struct Property_##NAME final { \
        friend __PROPERTIES_CLASS_SELF; \
    private: \
        using Self = TYPE; \
        Self self; \
        inline Property_##NAME(Self value) : self(enhanced::util::move(value)) {} \
        __E_PROPERTY_GETTER_##GETTER \
        __E_PROPERTY_SETTER_##SETTER \
    public: \
        __VA_ARGS__ \
    } NAME

#ifdef ENHANCED_MACRO_NO_PREFIX_ALIAS
    #define PROPERTIES_CLASS E_PROPERTIES_CLASS
    #define PROPERTIES_STRUCT E_PROPERTIES_STRUCT
    #define PROPERTY E_PROPERTY
#endif
