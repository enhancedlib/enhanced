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

#ifndef ENHANCED_BASIC_COLLECTION_MIXED_MIXED0LINKED0LIST_H
#define ENHANCED_BASIC_COLLECTION_MIXED_MIXED0LINKED0LIST_H

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/annotations.h"

#include "EnhancedBasic/export.h"
#include "EnhancedBasic/core/Iterator.h"

#include "EnhancedBasic/collection/mixed/MixedList.h"
#include "EnhancedBasic/collection/mixed/MixedDeque.h"

#ifdef CXX_LANGUAGE // C++ language

namespace EnhancedBasic {
    namespace collection {
        namespace mixed {
            class ENHANCED_BASIC_API MixedLinkedList0 {
            private:
                struct Node {
                    void *value;

                    bool requiresRelease;

                    Node *next;

                    Node *back;
                };

                Node *first;

                Node *last;

                mutable Node *indexer;

                Size length;

                static Node *&nextNode(Node *&node);

                static Node *&backNode(Node *&node);

            protected:
                struct GenericsOperator {
                    void *(*allocate)(void *const &);

                    void (*destroy)(void *const &);

                    bool (*equals)(void *const &, void *const &);
                };

                class ENHANCED_BASIC_API MixedLinkedListIterator0 {
                    friend class MixedLinkedList0;

                private:
                    const MixedLinkedList0 *mixedLinkedList;

                    mutable bool isFirst;

                protected:
                    explicit MixedLinkedListIterator0(const MixedLinkedList0 *mixedLinkedList);

                    virtual ~MixedLinkedListIterator0() noexcept;

                    $RetNotIgnored()
                    bool hasNext0() const;

                    void next0() const;

                    $RetNotIgnored()
                    bool each0() const;

                    $RetNotIgnored()
                    void *get0() const;

                    void reset0() const;

                    Size count0() const;
                };

                GenericsOperator genericsOperator;

                mutable MixedLinkedListIterator0 *iterator;

                explicit MixedLinkedList0(GenericsOperator genericsOperator);

                virtual ~MixedLinkedList0() noexcept;

                MixedLinkedList0(const MixedLinkedList0 &copy);

                Size getLength0() const;

                $RetNotIgnored()
                bool isEmpty0() const;

                $RetNotIgnored()
                bool contain0(const void *value) const;

                void *getLast0() const;

                void *getFirst0() const;

                void *get0(Size index) const;

                void addLast0(const void *element);

                void addLastReferenced0(const void *element);

                void removeLast0();

                void addFirst0(const void *element);

                void addFirstReferenced0(const void *element);

                void removeFirst0();
            };

        /*
         * When you build project with Microsoft Visual C++ compiler,
         * If you don't explicitly extend the "Collection" class, you will see an error in compiling.
         * The compiler thinks the return type of virtual function 'copy' isn't
         * covariant with the return type the super method.
         * So the class must explicitly extend the "Collection" class.
         *
         * But when the class explicitly extend the "Collection" class,
         * The compiler show a warning (C4584), it thinks the class already extended "Collection" class.
         * So I use "#pragma warning(disable: 4584)" to disable the warning.
         */
        #ifdef COMPILER_MSVC
        #pragma warning(push)
        #pragma warning(disable: 4584)
            template <typename Type>
            class MixedLinkedList final : public Collection<Type>, public MixedDeque<Type>,
                                          public MixedList<Type>, public MixedLinkedList0 {
        #pragma warning(pop)
        #else // Non Microsoft Visual C++ compiler
            template <typename Type>
            class MixedLinkedList final : public MixedList<Type>, public MixedDeque<Type>, private MixedLinkedList0 {
        #endif // COMPILER_MSVC
            private:
                class MixedLinkedListIterator : public core::Iterator<Type>, private MixedLinkedListIterator0 {
                    friend class MixedLinkedList<Type>;

                public:
                    explicit inline MixedLinkedListIterator(const MixedLinkedList<Type> *mixedLinkedList) :
                        MixedLinkedListIterator0(mixedLinkedList) {}

                    inline bool hasNext() const override {
                        return MixedLinkedListIterator0::hasNext0();
                    }

                    inline const core::Iterator<Type> *next() const override {
                        MixedLinkedListIterator0::next0();
                        return this;
                    }

                    inline bool each() const override {
                        return MixedLinkedListIterator0::each0();
                    }

                    inline Type &get() const override {
                        return *reinterpret_cast<Type *>(MixedLinkedListIterator0::get0());
                    }

                    inline void reset() const override {
                        MixedLinkedListIterator0::reset0();
                    }

                    inline Size count() const override {
                        return MixedLinkedListIterator0::count0();
                    }
                };

                static void *allocate(void *const &element) {
                    return reinterpret_cast<void *>(new Type(*reinterpret_cast<Type *>(element)));
                }

                static void destroy(void *const &element) {
                    delete reinterpret_cast<Type *>(element);
                }

                static bool equals(void *const &element, void *const &value) {
                    return *reinterpret_cast<Type *>(element) == *reinterpret_cast<Type *>(value);
                }

            public:
                inline MixedLinkedList() : MixedLinkedList0({allocate, destroy, equals}) {}

                inline MixedLinkedList(const MixedLinkedList<Type> &copy) :
                    MixedLinkedList0(copy) {}

                inline Size getLength() const override {
                    return MixedLinkedList0::getLength0();
                }

                inline bool isEmpty() const override {
                    return MixedLinkedList0::isEmpty0();
                }

                $RetNotIgnored()
                inline bool contain(const Type &value) const override {
                    return MixedLinkedList0::contain0(&value);
                }

                $RetRequiresRelease()
                inline MixedLinkedList<Type> *copy() const override {
                    return new MixedLinkedList<Type>(*this);
                }

                inline Type &getLast() const override {
                    return *reinterpret_cast<Type *>(MixedLinkedList0::getLast0());
                }

                inline Type &getFirst() const override {
                    return *reinterpret_cast<Type *>(MixedLinkedList0::getFirst0());
                }

                $RetNotIgnored()
                inline Type &get(Size index) const override {
                    return *reinterpret_cast<Type *>(MixedLinkedList0::get0(index));
                }

                $RetNotIgnored()
                inline Type &operator[](Size index) const override {
                    return *reinterpret_cast<Type *>(MixedLinkedList0::get0(index));
                }

                inline core::Iterator<Type> *iterator() const override {
                    if (MixedLinkedList0::iterator == null) {
                        MixedLinkedList0::iterator = new MixedLinkedListIterator(this);
                    } else {
                        static_cast<MixedLinkedListIterator *>(MixedLinkedList0::iterator)->reset();
                    }
                    return static_cast<MixedLinkedListIterator *>(MixedLinkedList0::iterator);
                }

                $RetNotIgnored()
                inline typename core::Iterable<Type>::ForeachIterator begin() const override {
                    return MixedList<Type>::begin();
                }

                $RetNotIgnored()
                inline constexpr InvalidType end() const override {
                    return MixedList<Type>::end();
                }

                inline void addLast(const Type &element) override {
                    MixedLinkedList0::addLast0(&element);
                }

                inline void addLastReferenced(const Type &element) override {
                    MixedLinkedList0::addLastReferenced0(&element);
                }

                inline Type removeLast() override {
                    Type value = this->getLast();
                    MixedLinkedList0::removeFirst0();
                    return value;
                }

                inline void addFirst(const Type &element) override {
                    MixedLinkedList0::addFirst0(&element);
                }

                inline void addFirstReferenced(const Type &element) override {
                    MixedLinkedList0::addFirstReferenced0(&element);
                }

                inline Type removeFirst() override {
                    Type value = this->getFirst();
                    MixedLinkedList0::removeFirst0();
                    return value;
                }

                inline void add(const Type &element) override {
                    this->addLast(element);
                }

                inline void addReferenced(const Type &element) override {
                    this->addLastReferenced(element);
                }

                inline Type remove() override {
                    return this->removeLast();
                }

                inline void push(const Type &element) override {
                    this->addFirst(element);
                }

                inline void pushReferenced(const Type &element) override {
                    this->addFirstReferenced(element);
                }

                inline Type popup() override {
                    return this->removeFirst();
                }
            };
        } // namespace mixed
    } // namespace collection
} // namespace EnhancedBasic

#endif // CXX_LANGUAGE

#endif // !ENHANCED_BASIC_COLLECTION_MIXED_MIXED0LINKED0LIST_H
