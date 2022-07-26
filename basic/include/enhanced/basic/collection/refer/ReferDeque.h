/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 *
 * This software is licensed under Enhanced License.
 * You may not use this file except in compliance with the License.
 * You should see a copy of Enhanced License in this software, if not, visit
 * <https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt>
 *
 * The Software is always provided "AS IS",
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#pragma once

#include "enhanced/core/defines.h"
#include "enhanced/core/types.h"
#include "enhanced/core/annotations.h"

#include "enhanced/basic/collection/Deque.h"
#include "ReferQueue.h"

#ifdef CXX_LANGUAGE // C++ language

namespace enhanced::basic::collection::refer {
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
    struct ReferDeque : public Collection<Type>, public Queue<Type>, public Deque<Type>, public ReferQueue<Type> {
#else
    template <typename Type>
    struct ReferDeque : public Deque<Type>, public ReferQueue<Type> {
#endif // COMPILER_MSVC
        RetCannotIgnored()
            virtual Size getLength() const = 0;

        RetCannotIgnored()
            virtual bool isEmpty() const = 0;

        virtual Type& getFirst() const = 0;

        virtual Type& getLast() const = 0;

        virtual Type& get(Size index) const = 0;

        virtual Type& operator[](Size index) const = 0;

        virtual bool contain(const Type& value) const = 0;

        RetCannotIgnored()
            typename Iterable<Type>::ForeachIterator begin() const override {
            return Deque<Type>::begin();
        }

        RetCannotIgnored()
            void* end() const override {
            return Deque<Type>::end();
        }

        virtual Iterator<Type>* iterator() const = 0;

        RetRequiresRelease()
            virtual ReferDeque<Type>* copy() const = 0;

        virtual void addLast(const Type& element) = 0;

        virtual Type removeLast() = 0;

        virtual void addFirst(const Type& element) = 0;

        virtual Type removeFirst() = 0;

        virtual void add(const Type& element) = 0;

        virtual Type remove() = 0;

        virtual void push(const Type& element) = 0;

        virtual Type popup() = 0;
    };
}

#endif // CXX_LANGUAGE
