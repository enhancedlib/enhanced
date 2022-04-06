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

#ifndef ENHANCED_BASIC_COLLECTION_QUEUE_H
#define ENHANCED_BASIC_COLLECTION_QUEUE_H

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/annotations.h"

#include "EnhancedBasic/collection/Collection.h"

#ifdef CXX_LANGUAGE // C++ language

namespace EnhancedBasic {
    namespace collection {
        template <typename Type>
        struct Queue : public Collection<Type> {
            $RetNotIgnored()
            virtual Type &getFirst() const = 0;

            $RetNotIgnored()
            virtual Type &getLast() const = 0;

            $RetNotIgnored()
            virtual Type &get(Size index) const = 0;

            $RetNotIgnored()
            virtual Type &operator[](Size index) const = 0;

            $RetRequiresRelease()
            virtual Queue<Type> *copy() const = 0;

            virtual void addLast(const Type &element) = 0;

            virtual Type removeFirst() = 0;

            virtual void add(const Type &element) = 0;

            virtual Type remove() = 0;

            virtual void push(const Type &element) = 0;

            virtual Type popup() = 0;
        };
    } // namespace collection
} // namespace EnhancedBasic

#endif // CXX_LANGUAGE

#endif // !ENHANCED_BASIC_COLLECTION_QUEUE_H
