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

#define _E_PROPERTY_GETTER_GET(ACCESS_MODIFIER) \
ACCESS_MODIFIER: \
    E_RET_NO_DISCARD() \
    inline const enhanced::RemoveRefAndCv<Type>& operator()() const { \
        return get(); \
    } \
    E_RET_NO_DISCARD() \
    inline const enhanced::RemoveRefAndCv<Type>& get() const

#define _E_PROPERTY_SETTER_SET(ACCESS_MODIFIER) \
ACCESS_MODIFIER: \
    inline void operator()(const enhanced::RemoveRefAndCv<Type>& value) { \
        set(value); \
    } \
    inline void set(const enhanced::RemoveRefAndCv<Type>& value)

#define _E_PROPERTY_GETTER_DEFAULT_GETTER(ACCESS_MODIFIER) \
    _E_PROPERTY_GETTER_GET(ACCESS_MODIFIER) { \
        return field; \
    }

#define _E_PROPERTY_SETTER_DEFAULT_SETTER(ACCESS_MODIFIER) \
    _E_PROPERTY_SETTER_SET(ACCESS_MODIFIER) { \
        field = value; \
    }

#define E_PROPERTY(TYPE, NAME, VALUE, GETTER, SETTER) \
    protected: \
        class EProperty$##NAME { \
            friend E_CLASS_TYPE; \
        public: \
            using Type = TYPE; \
        private: \
            Type field; \
            inline EProperty$##NAME() : field(VALUE) {} \
            _E_PROPERTY_GETTER_##GETTER \
            _E_PROPERTY_SETTER_##SETTER \
        }; \
    public: \
        EProperty$##NAME NAME {}; \
    private:

#define E_PROPERTY_REF(BASE, NAME) \
    class EPropertyRef$##NAME : public EProperty$##NAME { \
        friend E_CLASS_TYPE; \
    public: \
        inline EPropertyRef$##NAME() = delete; \
        template <typename _ = void> \
        E_RET_NO_DISCARD() \
        inline const enhanced::RemoveRefAndCv<Type>& get() const \
        requires enhanced::testValid<decltype(EProperty$##NAME::get())> { \
            return EProperty$##NAME::get(); \
        } \
        template <typename _ = void> \
        inline void set(const enhanced::RemoveRefAndCv<Type>& value) \
        requires enhanced::testValid<decltype(EProperty$##NAME::set(value))> { \
            EProperty$##NAME::set(value); \
        } \
    }; \
    template <typename _ = void> \
    E_RET_NO_DISCARD() \
    inline const typename enhanced::RemoveRefAndCv<EProperty$##NAME::Type>& NAME() const \
    requires enhanced::testValid<decltype(enhanced::forceCast<EPropertyRef$##NAME>(BASE::NAME).get())> { \
        return ((const EPropertyRef$##NAME&) BASE::NAME).get(); \
    } \
    template <typename _ = void> \
    inline void NAME(const enhanced::RemoveRefAndCv<typename EProperty$##NAME::Type>& value) \
    requires enhanced::testValid<decltype(enhanced::forceCast<EPropertyRef$##NAME>(BASE::NAME).set(value))> { \
        ((EPropertyRef$##NAME&) BASE::NAME).set(value); \
    }
