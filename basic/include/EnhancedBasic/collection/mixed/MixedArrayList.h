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

#ifndef ENHANCED_BASIC_COLLECTION_MIXED_MIXED0ARRAY0LIST_H
#define ENHANCED_BASIC_COLLECTION_MIXED_MIXED0ARRAY0LIST_H

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/annotations.h"

#include "EnhancedBasic/export.h"

#include "EnhancedBasic/collection/RandomAccess.h"
#include "EnhancedBasic/collection/mixed/MixedList.h"

#ifdef CXX_LANGUAGE // C++ language

namespace EnhancedBasic {
    namespace collection {
        namespace mixed {
            class ENHANCED_BASIC_API MixedArrayList0 {
            private:
                struct Node {
                    void *value;

                    bool requiresRelease;
                };

                Size maxCount;

                Node *elements;

                Size length;

            protected:
                struct GenericsOperator {
                    void *(*allocate)(void *const &);

                    void (*destroy)(void *const &);

                    bool (*equals)(void *const &, void *const &);
                };

                class ENHANCED_BASIC_API MixedArrayListIterator0 {
                    friend class MixedArrayList0;

                private:
                    const MixedArrayList0 *mixedArrayList;

                    mutable MixedArrayList0::Node *indexer;

                    mutable bool isFirst;

                    const MixedArrayList0::Node *end;

                protected:
                    explicit MixedArrayListIterator0(const MixedArrayList0 *mixedArrayList);

                    virtual ~MixedArrayListIterator0() noexcept;

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
                };

                GenericsOperator genericsOperator;

                mutable MixedArrayListIterator0 *iterator;

                MixedArrayList0(Size length, GenericsOperator genericsOperator);

                virtual ~MixedArrayList0() noexcept;

                $RetNotIgnored()
                Size getLength0() const;

                $RetNotIgnored()
                bool isEmpty0() const;

                $RetNotIgnored()
                void *get0(Size index) const;

                $RetNotIgnored()
                bool contain0(const void *value) const;

                void add0(const void *element);

                void addReferenced0(const void *element);

                void remove0();

                void expand0(Size size);

                void shrink0(Size size);
            };

            template <typename Type>
            class MixedArrayList final : public MixedList<Type>, public RandomAccess<Type>, private MixedArrayList0 {
            private:
                class MixedArrayListIterator : public MixedArrayListIterator0, public core::Iterator<Type> {
                    friend class MixedArrayList<Type>;

                public:
                    explicit inline MixedArrayListIterator(const MixedArrayList<Type> *arrayList) :
                        MixedArrayListIterator0(arrayList) {}

                    $RetNotIgnored()
                    inline bool hasNext() const override {
                        return MixedArrayListIterator0::hasNext0();
                    }

                    inline const core::Iterator<Type> *next() const override {
                        MixedArrayListIterator0::next0();
                        return this;
                    }

                    $RetNotIgnored()
                    inline bool each() const override {
                        return MixedArrayListIterator0::each0();
                    }

                    $RetNotIgnored()
                    inline Type &get() const override {
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

                static void *allocate(void *const &element) {
                    return new Type(*reinterpret_cast<Type *>(element));
                }

                static void destroy(void *const &element) {
                    delete reinterpret_cast<Type *>(element);
                }

                static bool equals(void *const &element, void *const &value) {
                    return *reinterpret_cast<Type *>(element) == *reinterpret_cast<Type *>(value);
                }

            public:
                explicit inline MixedArrayList() : MixedArrayList0(
                    UINT8_MAX, {allocate, destroy, equals}
                ) {}

                explicit inline MixedArrayList(Size maxCount) : MixedArrayList0(
                    maxCount, {allocate, destroy, equals}
                ) {}

                inline MixedArrayList(const MixedArrayList<Type> &copy) : MixedArrayList0(copy) {}

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
                inline core::Iterator<Type> *iterator() const override {
                    if (MixedArrayList0::iterator == null) {
                        MixedArrayList0::iterator = new MixedArrayListIterator(this);
                    } else {
                        static_cast<MixedArrayListIterator *>(MixedArrayList0::iterator)->reset();
                    }
                    return static_cast<MixedArrayListIterator *>(MixedArrayList0::iterator);
                }

                $RetNotIgnored()
                inline bool contain(const Type &value) const override {
                    return MixedArrayList0::contain0(&value);
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
    } // namespace collection
} // namespace EnhancedBasic

#endif // CXX_LANGUAGE

#endif // !ENHANCED_BASIC_COLLECTION_MIXED_MIXED0ARRAY0LIST_H
