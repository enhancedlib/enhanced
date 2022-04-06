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
 * The authors or copyright holders be not responsible for any loss or damage
 * caused by your access to or use of third-party content, products, etc.
 *
 * For any loss or damage caused by This software,
 * the authors or copyright holders may provide possible solutions,
 * but it does not mean that the authors or copyright holders
 * will definitely solve the problem.
 * In no event shall the author or copyright
 * owner be liable for any claims, damages or other liabilities.
 *
 * You should see the Enhanced License in this software, if not, visit
 * <https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt>
 */

#ifndef ENHANCED_BASIC_COLLECTION_MIXED_MIXED0DEQUE_H
#define ENHANCED_BASIC_COLLECTION_MIXED_MIXED0DEQUE_H

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/annotations.h"

#include "EnhancedBasic/collection/Deque.h"
#include "EnhancedBasic/collection/mixed/MixedQueue.h"

#ifdef CXX_LANGUAGE // C++ language

namespace EnhancedBasic {
    namespace collection {
        namespace mixed {
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
                virtual MixedDeque<Type> *copy() const = 0;

                virtual void addLastReferenced(const Type &element) = 0;

                virtual void addFirstReferenced(const Type &element) = 0;

                virtual void addReferenced(const Type &element) = 0;

                virtual void pushReferenced(const Type &element) = 0;
            };
        } // namespace mixed
    } // namespace collection
} // namespace EnhancedBasic

#endif // CXX_LANGUAGE

#endif // !ENHANCED_BASIC_COLLECTION_MIXED_MIXED0DEQUE_H
