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

#ifndef ENHANCED_GENERICS_ALLOCATOR_H
#define ENHANCED_GENERICS_ALLOCATOR_H

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/assert.h"
#include "EnhancedCore/annotations.h"

#include "EnhancedBasic/export.h"

#include "EnhancedBasic/generic/Generic.h"

namespace EnhancedBasic {
    namespace generic {
        class ENHANCED_BASIC_API Allocator0 {
        private:
            Size size = 0;

        protected:
            GenericPointer space = null;

            $RetNotIgnored()
            Size getSize0() const;

            void allocate0(Size newSize, Size sizeOfType);

            void destroy0();

            void resize0(Size resize, Size sizeOfType);
        };

        template <typename Type>
        class Allocator : private Allocator0 {
        public:
        #ifdef CXX_11_OR_MORE
            Allocator() = default;
        #else
            Allocator() {}
        #endif // CXX_11_OR_MORE

            $RetNotIgnored()
            Size getSize() const {
                return Allocator0::getSize0();
            }

            $RetNotIgnored()
            Type &get(Size index) const {
                return reinterpret_cast<Type *>(Allocator0::space)[index];
            }

            void allocate(Size newSize) {
                Allocator0::allocate0(newSize, sizeof(Type));
            }

            void destroy() {
                Allocator0::destroy0();
            }

            $RetReferenced
            template <typename ...Args>
            Type &construct(Size index, Args ...args) {
                return this->get(index) = Type(args...);
            }

            void destruct(Size index) {
                this->get(index).~Type();
            }

            $RetReferenced
            template <typename ...Args>
            Type *constructAll(Args ...args) {
                for (Size index = 0; index < this->getSize(); ++ index) {
                    this->get(index) = Type(args...);
                }
            }

            void destructAll() {
                for (Size index = 0; index < this->getSize(); ++ index) {
                    this->get(index).~Type();
                }
            }

            void resize(Size newSize) {
                Allocator0::resize0(newSize, sizeof(Type));
            }
        };
    } // namespace core
} // namespace EnhancedBasic

#endif // !ENHANCED_GENERICS_ALLOCATOR_H
