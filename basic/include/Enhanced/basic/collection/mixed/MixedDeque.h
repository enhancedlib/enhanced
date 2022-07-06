/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 * This software is licensed under Enhanced License.
 *
 * This copyright notice is subject to change without notice.
 *
 * This software is a free software, everyone can change,
 * copy, publication, demonstrate, use, etc.
 *
 * This software and documentation may provide
 * third-party content, product and other information.
 * The Licensor is not responsible for any loss or damage
 * caused by your access to or use of third-party content, products, etc.
 *
 * For any loss or damage caused by this software,
 * the licensor may provide possible solutions,
 * but it does not mean that the licensor will definitely solve the problem.
 * In no event shall the licensor be liable for any claims,
 * damages or other liabilities.
 *
 * You should see a copy of Enhanced License in this software, if not, visit
 * <https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt>
 */

#pragma once

#include "Enhanced/core/defines.h"
#include "Enhanced/core/types.h"
#include "Enhanced/core/annotations.h"

#include "Enhanced/basic/collection/Deque.h"
#include "MixedQueue.h"

#ifdef CXX_LANGUAGE // C++ language

namespace Enhanced::basic::collection::mixed {
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
