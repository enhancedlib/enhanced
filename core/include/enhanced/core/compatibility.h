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

#ifdef CXX_LANGUAGE

#ifdef CXX_98
#define noexcept throw()
#define constexpr
#define final

#define noexcept_ext(condition)
#define default_cons {}
#define default_dest {}
#else
#define noexcept_ext(condition) noexcept(condition)
#define default_cons = default
#define default_dest = default
#endif

#ifndef CXX_17_OR_MORE
#define NAMESPACE_L1_BEGIN(level1) namespace level1 {
#define NAMESPACE_L1_END }

#define NAMESPACE_L2_BEGIN(level1, level2) namespace level1 { namespace level2 {
#define NAMESPACE_L2_END } }

#define NAMESPACE_L3_BEGIN(level1, level2, level3) namespace level1 { namespace level2 { namespace level3 {
#define NAMESPACE_L3_END } } }

#define NAMESPACE_L4_BEGIN(level1, level2, level3, level4) namespace level1 { namespace level2 { namespace level3 { namespace level4 {
#define NAMESPACE_L4_END } } } }

#define NAMESPACE_L5_BEGIN(level1, level2, level3, level4, level5) namespace level1 { namespace level2 { namespace level3 { namespace level4 { namespace level5 {
#define NAMESPACE_L5_END } } } } }

#else

#define NAMESPACE_L1_BEGIN(level1) namespace level1 {
#define NAMESPACE_L1_END }

#define NAMESPACE_L2_BEGIN(level1, level2) namespace level1::level2 {
#define NAMESPACE_L2_END }

#define NAMESPACE_L3_BEGIN(level1, level2, level3) namespace level1::level2::level3 {
#define NAMESPACE_L3_END }

#define NAMESPACE_L4_BEGIN(level1, level2, level3, level4) namespace level1::level2::level3::level4 {
#define NAMESPACE_L4_END }

#define NAMESPACE_L5_BEGIN(level1, level2, level3, level4, level5) namespace level1::level2::level3::level4::level5 {
#define NAMESPACE_L5_END }

#endif

#ifndef CXX_20_OR_MORE
#define consteval constexpr
#endif

#endif
