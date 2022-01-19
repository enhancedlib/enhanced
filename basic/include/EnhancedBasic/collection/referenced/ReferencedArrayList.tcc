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

#ifndef ENHANCED_BASIC_COLLECTION_REFERENCED_REFERENCED0ARRAY0LIST_TCC
#define ENHANCED_BASIC_COLLECTION_REFERENCED_REFERENCED0ARRAY0LIST_TCC

#include "EnhancedBasic/collection/referenced/ReferencedArrayList.h"

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/annotations.h"

#include "EnhancedBasic/core/Iterable.h"
#include "EnhancedBasic/core/Iterator.h"

#include "EnhancedBasic/generic/Generic.h"

#ifdef CXX_LANGUAGE // C++ language

namespace EnhancedBasic {
    namespace collection {
        namespace referenced {
            template <typename Type>
            ReferencedArrayList<Type>::ReferencedArrayListIterator::ReferencedArrayListIterator(
                const ReferencedArrayList<Type> *referencedArrayList) :
                ReferencedArrayListIterator0(referencedArrayList) {}

            template <typename Type>
            $RetNotIgnored()
            bool ReferencedArrayList<Type>::ReferencedArrayListIterator::hasNext() const {
                return ReferencedArrayListIterator0::hasNext0();
            }

            template <typename Type>
            const core::Iterator<Type> *ReferencedArrayList<Type>::ReferencedArrayListIterator::next() const {
                ReferencedArrayListIterator0::next0();
                return this;
            }

            template <typename Type>
            $RetNotIgnored()
            bool ReferencedArrayList<Type>::ReferencedArrayListIterator::each() const {
                return ReferencedArrayListIterator0::each0();
            }

            template <typename Type>
            $RetNotIgnored()
            Type &ReferencedArrayList<Type>::ReferencedArrayListIterator::get() const {
                return (Type &) ReferencedArrayListIterator0::get0();
            }

            template <typename Type>
            void ReferencedArrayList<Type>::ReferencedArrayListIterator::reset() const {
                ReferencedArrayListIterator0::reset0();
            }

            template <typename Type>
            $RetNotIgnored()
            Size ReferencedArrayList<Type>::ReferencedArrayListIterator::count() const {
                return ReferencedArrayListIterator0::count0();
            }

            template <typename Type>
            $RetNotIgnored()
            bool ReferencedArrayList<Type>::equals(GenericReference element, GenericReference value) {
                return ((Type &) element) == ((Type &) (value));
            }

            template <typename Type>
            ReferencedArrayList<Type>::ReferencedArrayList() : ReferencedArrayList0(UINT8_MAX, {equals}) {}

            template <typename Type>
            ReferencedArrayList<Type>::ReferencedArrayList(Size maxCount) : ReferencedArrayList0(maxCount, {equals}) {}

            template <typename Type>
            ReferencedArrayList<Type>::ReferencedArrayList(const ReferencedArrayList<Type> &other) :
                ReferencedArrayList0(other) {}

            template <typename Type>
            $RetNotIgnored()
            Size ReferencedArrayList<Type>::getLength() const {
                return ReferencedArrayList0::getLength0();
            }

            template <typename Type>
            $RetNotIgnored()
            bool ReferencedArrayList<Type>::isEmpty() const {
                return ReferencedArrayList0::isEmpty0();
            }

            template <typename Type>
            $RetNotIgnored()
            Type &ReferencedArrayList<Type>::get(Size index) const {
                return (Type &) ReferencedArrayList0::get0(index);
            }

            template <typename Type>
            $RetNotIgnored()
            Type &ReferencedArrayList<Type>::operator[](Size index) const {
                return reinterpret_cast<Type &>(ReferencedArrayList0::get0(index));
            }

            template <typename Type>
            core::Iterator <Type> *ReferencedArrayList<Type>::iterator() const {
                return core::Iterable<Type>::
                    template getIterator<ReferencedArrayListIterator>(ReferencedArrayList0::iterator, this);
            }

            template <typename Type>
            $RetNotIgnored()
            bool ReferencedArrayList<Type>::contain(const Type &value) const {
                return ReferencedArrayList0::contain0((GenericReference) value);
            }

            template <typename Type>
            $RetRequiresRelease()
            ReferencedArrayList <Type> *ReferencedArrayList<Type>::copy() const {
                return new ReferencedArrayList<Type>(*this);
            }

            template <typename Type>
            void ReferencedArrayList<Type>::add(const Type &element) {
                ReferencedArrayList0::add0((GenericReference) element);
            }

            template <typename Type>
            Type ReferencedArrayList<Type>::remove() {
                Type value = this->get(this->getLength() - 1);
                ReferencedArrayList0::remove0();
                return value;
            }
        } // namespace referenced
    } // namespace collection
} // namespace EnhancedBasic

#endif // CXX_LANGUAGE

#endif // !ENHANCED_BASIC_COLLECTION_REFERENCED_REFERENCED0ARRAY0LIST_TCC
