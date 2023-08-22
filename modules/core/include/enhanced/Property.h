/*
 * This file is part of Enhanced Framework.
 *
 * Copyright (C) 2023 sharedwonder (Liu Baihao). All rights reserved.
 *
 * Permission is hereby granted, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software,
 * including without limitation the rights to use, copy, modify, merge,
 * distribute. Unless you have obtained permission from the copyright holders,
 * subject to the following restrictions:
 *
 * 1. The above copyright notice and this permission notice shall be included in
 *    all copies of the Software and modified versions.
 *
 * 2. You may not misrepresent the source of the Software, and you may not claim
 *    that you wrote the original version.
 *
 * 3. You may not misrepresent the modified version as the original version.
 *
 * 4. You may not charge any fees or receive other compensation for the
 *    distribution of the Software, except for distributing modified versions and
 *    products that use the Software.
 *
 * 5. If you use this Software in your product, you shall indicate it.
 *
 * 6. Neither the name of the author nor the names of its contributors may
 *    be used to endorse or promote products derived from the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/Traits.h>

#define _E_PROPERTY_GETTER_get(ACCESS_MODIFIER) \
ACCESS_MODIFIER: \
    E_RET_NO_DISCARD() \
    inline const Type& operator()() const

#define _E_PROPERTY_SETTER_set(ACCESS_MODIFIER) \
ACCESS_MODIFIER: \
    E_RETURN_SELF() \
    inline Type& operator()(const Type& value) { \
        return operator=(value); \
    } \
    inline Type& operator=(const Type& value)

#define _E_PROPERTY_GETTER_getter(ACCESS_MODIFIER) \
    _E_PROPERTY_GETTER_get(ACCESS_MODIFIER) { \
        return property; \
    }

#define _E_PROPERTY_SETTER_setter(ACCESS_MODIFIER) \
    _E_PROPERTY_SETTER_set(ACCESS_MODIFIER) { \
        return property = value; \
    }

#define E_PROPERTY(TYPE, NAME, GETTER, SETTER, ...) \
    protected: \
        class _enhanced_Property_##NAME { \
            friend _enhanced_Class; \
        public: \
            using Type = TYPE; \
        private: \
            Type property; \
            inline _enhanced_Property_##NAME() : property() {} \
            inline _enhanced_Property_##NAME(const Type& value) : property(enhanced::move(value)) {} \
            _E_PROPERTY_GETTER_##GETTER \
            _E_PROPERTY_SETTER_##SETTER \
        }; \
    public: \
        _enhanced_Property_##NAME NAME {__VA_ARGS__}; \
    private:

#define E_PROPERTY_REF(BASE, NAME) \
    class _enhanced_PropertyRef_##NAME : public _enhanced_Property_##NAME { \
        friend _enhanced_Class; \
    private: \
        template <typename Property = _enhanced_Property_##NAME> \
        E_RET_NO_DISCARD() \
        inline const Type& get() const \
        requires enhanced::testValid<decltype(Property::operator()())> { \
            return Property::operator()(); \
        } \
        template <typename Property = _enhanced_Property_##NAME> \
        inline Type& set(const Type& value) \
        requires enhanced::testValid<decltype(Property::operator=(value))> { \
            return Property::operator=(value); \
        } \
    public: \
        inline _enhanced_PropertyRef_##NAME() = delete; \
    }; \
    template <typename Property = _enhanced_Property_##NAME, typename Ref = _enhanced_PropertyRef_##NAME> \
    E_RET_NO_DISCARD() \
    inline const typename Property::Type& NAME() const \
    requires enhanced::testValid<decltype(enhanced::forceCast<Ref>(BASE::NAME).get())> { \
        return ((const _enhanced_PropertyRef_##NAME&) BASE::NAME).get(); \
    } \
    template <typename Property = _enhanced_Property_##NAME> \
    inline typename Property::Type& NAME(const typename Property::Type& value) \
    requires enhanced::testValid<decltype(enhanced::forceCast<_enhanced_PropertyRef_##NAME>(BASE::NAME).set(value))> { \
        return ((_enhanced_PropertyRef_##NAME&) BASE::NAME).set(value); \
    }
