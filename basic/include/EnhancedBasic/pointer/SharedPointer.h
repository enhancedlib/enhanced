/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
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

#ifndef ENHANCED_BASIC_POINTER_SHARED0POINTER_H
#define ENHANCED_BASIC_POINTER_SHARED0POINTER_H

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/memory.h"

#ifdef CXX_LANGUAGE // C++ language

namespace EnhancedBasic {
    namespace Pointer {
        template <typename Type>
        class SharedPointer final {
        private:
            Type *ptr;

            Size *referenceCount;

        public:
            SharedPointer(Type *ptr = null) : ptr(ptr), referenceCount(new Size(1)) {}

            SharedPointer(const SharedPointer<Type> &originalCopy) :
                ptr(originalCopy.ptr), referenceCount(originalCopy.referenceCount) {}

            ~SharedPointer() noexcept {
                this->release();
            }

            void release() noexcept {
                if ((-- (*this->referenceCount)) == 0) {
                    if (this->ptr != null) {
                        delete[] this->ptr;
                        this->ptr = null;
                    }
                    delete this->referenceCount;
                }
            }

            Type operator*() const noexcept {
                return *this->ptr;
            }

            Type **operator&() const noexcept {
                return &this->ptr;
            }

            Type &operator[](Size index) const noexcept {
                return this->ptr[index];
            }

            Type *operator->() const noexcept {
                return this->ptr;
            }

            SharedPointer<Type> &operator=(const SharedPointer<Type> &self) noexcept {
                this->release();
                this->ptr = self.ptr;
                this->referenceCount = self.referenceCount;
                ++ (*this->referenceCount);

                return *this;
            }

            SharedPointer<Type> operator+(Size offset) const noexcept {
                return this->ptr + offset;
            }

            SharedPointer<Type> operator+=(Size offset) noexcept {
                SharedPointer<Type> copy = *this;
                copy.ptr += offset;
                return copy;
            }

            SharedPointer<Type> operator++() noexcept {
                SharedPointer<Type> copy = *this;
                ++ copy.ptr;
                return copy;
            }

            SharedPointer<Type> operator-(Size offset) const noexcept {
                return this->ptr - offset;
            }

            SharedPointer<Type> operator-=(Size offset) noexcept {
                SharedPointer<Type> copy = *this;
                copy.ptr -= offset;
                return copy;
            }

            SharedPointer<Type> operator--() noexcept {
                SharedPointer<Type> copy = *this;
                -- copy.ptr;
                return copy;
            }

            operator Type *() const noexcept {
                return this->ptr;
            }
        };
    } // namespace Pointer
} // namespace EnhancedBasic

#endif // CXX_LANGUAGE

#endif // !ENHANCED_BASIC_POINTER_SHARED0POINTER_H
