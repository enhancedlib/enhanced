/*
 * Copyright (C) 2021 Liu Baihao. All rights reserved.
 * This product is licensed under Enhanced License.
 *
 * This copyright disclaimer is subject to change without notice.
 *
 * This software is a free software,
 * everyone can change, copy, publication, demonstrate, use, etc.
 *
 * If you change and publication this software,
 * must credit the original software source and author's name,
 * and include this copyright disclaimer and
 * the license of this software in your software.
 *
 * This software and documentation may provide
 * third-party content, product and other information.
 * I am not responsible for any loss or damage caused
 * by your access to or use of third-party content, products, etc.
 */

#ifndef ENHANCED_CONTAINER_COLLECTION_REFERENCE_REFERENCE0DEQUE_H
#define ENHANCED_CONTAINER_COLLECTION_REFERENCE_REFERENCE0DEQUE_H

#include "EnhancedCore/defines.h"
#include "EnhancedCore/annotations.h"
#include "EnhancedCore/types.h"

#include "EnhancedContainer/collection/Deque.h"
#include "EnhancedContainer/collection/referenced/ReferencedQueue.h"

#ifdef CXX_LANGUAGE // C++ language

namespace EnhancedContainer {
    namespace Collection {
        namespace Referenced {
        /*
         * When you build project with Microsoft Visual C++ compiler,
         * If you don't explicitly explicit extend the "Collection" class, you will see an error in compiling.
         * The compiler thinks the return type of virtual function 'copy' isn't
         * covariant with the return type the super method.
         * So the class must explicitly extend the "Collection" class.
         *
         * But when the class explicitly extend the "Collection" class,
         * The compiler show a warning (C4584), it thinks the class already extend "Collection" class.
         * So I use "#pragma warning(disable: 4584)" to disable the warning.
         */
        #ifdef COMPILER_MSVC
        #pragma warning(push)
        #pragma warning(disable: 4584)
            template <typename Type>
            interface ReferencedDeque : public Collection<Type>, public Queue<Type>,
                                        public Deque<Type>, public ReferencedQueue<Type> {
        #else
            template <typename Type>
            interface ReferencedDeque : public Deque<Type>, public ReferencedQueue<Type> {
        #endif // COMPILER_MSVC
                virtual ReferencedDeque<Type> *copy() const = 0;
            };
        } // namespace Referenced
    } // namespace Collection
} // namespace EnhancedContainer

#endif // CXX_LANGUAGE

#endif // !ENHANCED_CONTAINER_COLLECTION_REFERENCE_REFERENCE0DEQUE_H
