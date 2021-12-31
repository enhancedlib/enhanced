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

#ifndef ENHANCED_CONTAINER_COLLECTION_MIXED_MIXED0ARRAY0LIST_H
#define ENHANCED_CONTAINER_COLLECTION_MIXED_MIXED0ARRAY0LIST_H

#include "EnhancedCore/defines.h"
#include "EnhancedCore/annotations.h"
#include "EnhancedCore/types.h"

#include "EnhancedContainer/defines.h"

#include "EnhancedContainer/collection/RandomAccess.h"
#include "EnhancedContainer/collection/mixed/MixedList.h"

#ifdef CXX_LANGUAGE // C++ language

namespace EnhancedContainer {
    namespace Collection {
        namespace Mixed {
            /*!
             * This class is the universal implementation class for
             * the template class "MixedArrayList\<Type\>".
             *
             * @note You should not extend this class from another class.
             *       And you should not instantiate this class directly.
             *       The correct approach is to instantiate the
             *       template class "MixedArrayList\<Type\>" (with "Type" as a type).
             *       Because this class has no public methods.
             *
             * <p>The meaning of this class is to separate the actual
             * implementation of the functions in the template class
             * "MixedArrayList\<Type\>" from the definition of
             * the template class "MixedArrayList\<Type\>".</p>
             *
             * <p>Methods in the template class "MixedArrayList\<Type\>" Type "only cast.</p>
             * <p>You'll see similar code in other classes in this module.</p>
             */
            class ENHANCED_CONTAINER_API MixedArrayList0 {
            private:
                struct Node {
                    void *value;

                    bool requiresRelease;
                };

                Size maxCount;

                Node *elements;

                Size length;

            protected:
                struct ElementOperator {
                    void *(*elementNew)(void *&);

                    void (*elementDelete)(void *&);

                    bool (*elementEqual)(void *&, void *&);
                };

                class ENHANCED_CONTAINER_API MixedArrayListIterator0 {
                private:
                    const MixedArrayList0 *mixedArrayList;

                    mutable MixedArrayList0::Node *indexer;

                    mutable bool isFirst;

                    const MixedArrayList0::Node *end;

                protected:
                    explicit MixedArrayListIterator0(const MixedArrayList0 *mixedArrayList);

                    $RetNotIgnored()
                    bool hasNext0() const;

                    void next0() const;

                    $RetNotIgnored()
                    bool each0() const;

                    $RetNotIgnored()
                    void *get0() const;

                    void reset0() const;

                    $RetNotIgnored()
                    Size count0() const;

                public:
                    virtual ~MixedArrayListIterator0() noexcept;
                };

                ElementOperator elementOperator;

                mutable MixedArrayListIterator0 *iterator;

                MixedArrayList0(Size length, ElementOperator elementOperator);

                virtual ~MixedArrayList0() noexcept;

                $RetNotIgnored()
                Size getLength0() const;

                $RetNotIgnored()
                bool isEmpty0() const;

                $RetNotIgnored()
                void *get0(Size index) const;

                $RetNotIgnored()
                bool contain0(const void *element) const;

                void add0(const void *element);

                void addReferenced0(const void *element);

                void remove0();

                void expand0(Size size);

                void shrink0(Size size);
            };

            template <typename Type>
            class MixedArrayList final : public MixedList<Type>, public RandomAccess<Type>, private MixedArrayList0 {
            private:
                class MixedArrayListIterator : public MixedArrayListIterator0, public Iterator<Type> {
                    friend class MixedArrayList<Type>;

                public:
                    inline explicit MixedArrayListIterator(const MixedArrayList<Type> *arrayList) :
                        MixedArrayListIterator0(arrayList) {}

                    $RetNotIgnored()
                    inline bool hasNext() const override {
                        return MixedArrayListIterator0::hasNext0();
                    }

                    inline const Iterator<Type> *next() const override {
                        MixedArrayListIterator0::next0();
                        return this;
                    }

                    $RetNotIgnored()
                    inline bool each() const override {
                        return MixedArrayListIterator0::each0();
                    }

                    $RetNotIgnored()
                    inline Type get() const override {
                        return *reinterpret_cast<Type *>(MixedArrayListIterator0::get0());
                    }

                    inline void reset() const override {
                        MixedArrayListIterator0::reset0();
                    }

                    $RetNotIgnored()
                    inline Size count() const override {
                        return MixedArrayListIterator0::count0();
                    }
                };

                static void *elementNew(void *&element) {
                    return new Type(*reinterpret_cast<Type *>(element));
                }

                static void elementDelete(void *&element) {
                    delete reinterpret_cast<Type *>(element);
                }

                static bool elementEqual(void *&element1, void *&element2) {
                    return *reinterpret_cast<Type *>(element1) == *reinterpret_cast<Type *>(element2);
                }

            public:
                inline explicit MixedArrayList() : MixedArrayList0(
                    UINT8_MAX, {elementNew, elementDelete, elementEqual}
                ) {}

                inline explicit MixedArrayList(Size maxCount) : MixedArrayList0(
                    maxCount, {elementNew, elementDelete, elementEqual}
                ) {}

                inline MixedArrayList(const MixedArrayList<Type> &originalCopy) : MixedArrayList0(originalCopy) {}

                $RetNotIgnored()
                inline Size getLength() const override {
                    return MixedArrayList0::getLength0();
                }

                $RetNotIgnored()
                inline bool isEmpty() const override {
                    return MixedArrayList0::isEmpty0();
                }

                $RetNotIgnored()
                inline Type &get(Size index) const override {
                    return *reinterpret_cast<Type *>(MixedArrayList0::get0(index));
                }

                $RetNotIgnored()
                inline Type &operator[](Size index) const override {
                    return *reinterpret_cast<Type *>(MixedArrayList0::get0(index));
                }

                $RetNotIgnored()
                inline Iterator<Type> *iterator() const override {
                    return static_cast<MixedArrayListIterator *>(
                        MixedArrayList0::iterator = new MixedArrayListIterator(this)
                    );
                }

                $RetNotIgnored()
                inline bool contain(const Type &element) const override {
                    return MixedArrayList0::contain0(&element);
                }

                $RetRequiresRelease()
                inline MixedArrayList<Type> *copy() const override {
                    return new MixedArrayList<Type>(*this);
                }

                inline void add(const Type &element) override {
                    MixedArrayList0::add0(&element);
                }

                inline void addReferenced(const Type &element) override {
                    MixedArrayList0::addReferenced0(&element);
                }

                inline Type remove() override {
                    Type value = this->get(this->getLength() - 1);
                    MixedArrayList0::remove0();
                    return value;
                }
            };
        } // namespace Reference
    } // namespace Collection
} // namespace EnhancedContainer

#endif // CXX_LANGUAGE

#endif // !ENHANCED_CONTAINER_COLLECTION_MIXED_MIXED0ARRAY0LIST_H
