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

#ifndef ENHANCED_BASIC_CORE_ITERABLE_H
#define ENHANCED_BASIC_CORE_ITERABLE_H

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/annotations.h"

#include "EnhancedBasic/core/Iterator.h"

#ifdef CXX_LANGUAGE // C++ language

namespace EnhancedBasic {
    namespace core {
        template <typename Type>
        struct Iterable {
        protected:
            class ForeachIterator final {
            private:
                core::Iterator<Type> *iterator;

            public:
                ForeachIterator(core::Iterator<Type> *iterator);

                bool operator!=($Unused UnusedType unused);

                const core::Iterator<Type> *operator++();

                Type &operator*();
            };

            template <typename IteratorType, typename SuperType, typename Subclass>
            inline IteratorType *getIterator(SuperType *&iterator, const Subclass *self) const;

        public:
            $RetNotIgnored()
            virtual inline Iterable<Type>::ForeachIterator begin() const;

            $RetNotIgnored()
            virtual inline UnusedType end() const;

            virtual core::Iterator<Type> *iterator() const = 0;
        };
    } // namespace core
} // namespace EnhancedBasic

#include "EnhancedBasic/core/Iterable.hpp"

#endif // CXX_LANGUAGE

#endif // !ENHANCED_BASIC_CORE_ITERABLE_H
