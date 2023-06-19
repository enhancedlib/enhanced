/*
 * This file is part of Enhanced Framework.
 *
 * Copyright (C) 2023 Liu Baihao (sharedwonder). All rights reserved.
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
 *    distribution of the Software, excluding distribution of modified versions
 *    and products using the Software.
 *
 * 5. If you use this Software in your product, you shall indicate it.
 *
 * 6. Neither the name of the author nor the names of its contributors may
 *    be used to endorse or promote products derived from the Software
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

// TODO

#define E_INTERFACE() template <typename E_INTERFACE_IMPL_CLASS>

#define E_INTERFACE_IMPL_CLASS _enhanced_InterfaceImplementationClass

#define E_INTERFACE_METHOD(NAME, RETURN, PARAMETERS, ...) \
    private: \
        inline constexpr void _enhanced_interfaceMethodTest_##NAME PARAMETERS __VA_ARGS__ {}; \
        template <typename... Args> \
        inline constexpr auto NAME(Args&&... args) __VA_ARGS__ \
        noexcept(noexcept(static_cast<__VA_ARGS__ E_INTERFACE_IMPL_CLASS*>(this)->NAME(enhanced::forward<decltype(args)>(args)...))) -> RETURN \
        requires enhanced::testValid<decltype(this->_enhanced_interfaceMethodTest_##NAME(args...))> && enhanced::isSame<RETURN, \
            decltype(static_cast<__VA_ARGS__ E_INTERFACE_IMPL_CLASS*>(this)->NAME(enhanced::forward<decltype(args)>(args)...))> { \
            return static_cast<__VA_ARGS__ E_INTERFACE_IMPL_CLASS*>(this)->NAME(enhanced::forward<decltype(args)>(args)...); \
        } \
    public:

#define E_INTERFACE_METHOD_RET_AUTO(NAME, PARAMETERS, ...) \
    private: \
        inline constexpr void _enhanced_interfaceMethodTest_##NAME PARAMETERS __VA_ARGS__ {}; \
        template <typename... Args> \
        inline constexpr auto NAME(Args&&... args) __VA_ARGS__ \
        noexcept(noexcept(static_cast<__VA_ARGS__ E_INTERFACE_IMPL_CLASS*>(this)->NAME(enhanced::forward<decltype(args)>(args)...))) \
        requires enhanced::testValid<decltype(this->_enhanced_interfaceMethodTest_##NAME(args...))> { \
            return static_cast<__VA_ARGS__ E_INTERFACE_IMPL_CLASS*>(this)->NAME(enhanced::forward<decltype(args)>(args)...); \
        } \
    public: