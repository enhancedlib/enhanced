/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 * This software is licensed under Enhanced License.
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


#ifndef ENHANCED_BASIC_COLLECTION_LIST_H
#define ENHANCED_BASIC_COLLECTION_LIST_H

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"

#include "EnhancedBasic/collection/Collection.h"

#ifdef CXX_LANGUAGE // C++ language

namespace EnhancedBasic {
    namespace collection {
        template <typename Type>
        struct List : public Collection<Type> {
            virtual Type &get(Size index) const = 0;

            virtual Type &operator[](Size index) const = 0;

            $RetRequiresRelease()
            virtual List<Type> *copy() const = 0;

            virtual void add(const Type &element) = 0;

            virtual Type remove() = 0;
        };
    } // namespace collection
} // namespace EnhancedBasic

#endif // CXX_LANGUAGE

#endif // !ENHANCED_BASIC_COLLECTION_LIST_H
