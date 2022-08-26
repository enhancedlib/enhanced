/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 *
 * Licensed under the Enhanced License, Version 0.5.4 (the "License").
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt
 *
 * UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING,
 * THE SOFTWARE IS ALWAYS PROVIDED "AS IS",
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#pragma once

#include "enhanced/core/defines.h"
#include "enhanced/core/types.h"
#include "enhanced/core/annotations.h"

#include "enhanced/basic/container/Deque.h"
#include "enhanced/basic/container/mixed/MixedQueue.h"

#ifdef CXX_LANGUAGE

namespace enhanced::basic::container::mixed {
/*
 * When you build project with Microsoft Visual C++ Compiler,
 * If you don't explicitly extend the "Collection" class, you will see an error in compiling.
 * The compiler thinks the return type of virtual function 'copy' isn't
 * covariant with the return type the super method.
 * So the class must explicitly extend the "Collection" class.
 *
 * But when the class explicitly extend the "Collection" class,
 * The compiler show a warning (C4584), it thinks the class already extended "Collection" class.
 * So I use "#pragma warning(disable: 4584)" to disable the warning.
 */
#ifdef COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4584)
    template <typename Type>
    struct MixedDeque : public Collection<Type>, public Queue<Type>,
                        public Deque<Type>, public MixedQueue<Type> {
#else
    template <typename Type>
    struct MixedDeque : public Deque<Type>, public MixedQueue<Type> {
#endif // COMPILER_MSVC
        virtual MixedDeque<Type>* copy() const = 0;

        virtual void addLastReference(const Type& element) = 0;

        virtual void addFirstReference(const Type& element) = 0;

        virtual void addReference(const Type& element) = 0;

        virtual void pushReference(const Type& element) = 0;
    };
}

#endif // CXX_LANGUAGE
