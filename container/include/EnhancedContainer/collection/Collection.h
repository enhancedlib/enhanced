/*
 * Copyright (C) 2021 Liu Baihao.
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

#ifndef ENHANCED_CONTAINER_COLLECTION_COLLECTION_H
#define ENHANCED_CONTAINER_COLLECTION_COLLECTION_H

#include "EnhancedCore/annotations.h"
#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"

#include "EnhancedContainer/Iterable.h"

#ifdef CXX_LANGUAGE // C++ language

namespace EnhancedContainer {
    namespace Collection {
        template <typename Type>
        interface Collection : public Iterable<Type> {
        #ifdef CXX_11_OR_MORE

            virtual ~Collection() noexcept = default;

        #else // below C++11

            virtual ~Collection() {}

        #endif // CXX_11_OR_MORE

            $RetNotIgnored()
            virtual Size getLength() const = 0;

            $RetNotIgnored()
            virtual bool isEmpty() const = 0;

            $RetNotIgnored()
            virtual bool contain(const Type &element) const = 0;

            $RetRequiresRelease()
            virtual Collection<Type> *copy() const = 0;
        };
    } // namespace Collection
} // namespace EnhancedContainer

#endif // CXX_LANGUAGE

#endif // !ENHANCED_CONTAINER_COLLECTION_COLLECTION_H
