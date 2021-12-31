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

#ifndef ENHANCED_CONTAINER_COLLECTION_MIXED_MIXED0LINKED0LIST_H
#define ENHANCED_CONTAINER_COLLECTION_MIXED_MIXED0LINKED0LIST_H

#include "EnhancedCore/defines.h"
#include "EnhancedCore/annotations.h"
#include "EnhancedCore/types.h"

#include "EnhancedContainer/defines.h"
#include "EnhancedContainer/Iterator.h"

#include "EnhancedContainer/collection/mixed/MixedList.h"
#include "EnhancedContainer/collection/mixed/MixedDeque.h"

#ifdef CXX_LANGUAGE // C++ language

namespace EnhancedContainer {
    namespace Collection {
        namespace Mixed {
            /*!
             * This class is the universal implementation class for
             * the template class "MixedLinkedList\<Type\>".
             *
             * @note You should not extend this class from another class.
             *       And you should not instantiate this class directly.
             *       The correct approach is to instantiate the
             *       template class "MixedLinkedList\<Type\>" (with "Type" as a type).
             *       Because this class has no public methods.
             *       And its methods have no type checking
             *       (they use "void *" as the generic type).
             *
             * <p>The meaning of this class is to separate the actual
             * implementation of the functions in the template class
             * "MixedLinkedList\<Type\>" from the definition of
             * the template class "MixedLinkedList\<Type\>".</p>
             *
             * <p>Methods in the template class "MixedLinkedList\<Type\>" Type "only cast.</p>
             * <p>You'll see similar code in other classes in this module.</p>
             */
            class ENHANCED_CONTAINER_API MixedLinkedList0 {
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
                struct ElementOperator {
                    void *(*elementNew)(void *&);

                    void (*elementDelete)(void *);

                    bool (*elementEqual)(void *&, void *&);
                };

                class ENHANCED_CONTAINER_API MixedLinkedListIterator0 {
                private:
                    const MixedLinkedList0 *mixedLinkedList;

                    mutable bool isFirst;

                protected:
                    explicit MixedLinkedListIterator0(const MixedLinkedList0 *mixedLinkedList);

                    $RetNotIgnored()
                    bool hasNext0() const;

                    void next0() const;

                    $RetNotIgnored()
                    bool each0() const;

                    $RetNotIgnored()
                    void *get0() const;

                    void reset0() const;

                    Size count0() const;

                public:
                    virtual ~MixedLinkedListIterator0() noexcept;
                };

                ElementOperator elementOperator;

                mutable MixedLinkedListIterator0 *iterator;

                explicit MixedLinkedList0(ElementOperator elementOperator);

                virtual ~MixedLinkedList0() noexcept;

                MixedLinkedList0(const MixedLinkedList0 &originalCopy);

                Size getLength0() const;

                $RetNotIgnored()
                bool isEmpty0() const;

                $RetNotIgnored()
                bool contain0(const void *element) const;

                void *&getLast0() const;

                void *&getFirst0() const;

                void *&get0(Size index) const;

                void addLast0(const void *element);

                void addLastReferenced0(const void *element);

                void removeLast0();

                void addFirst0(const void *element);

                void addFirstReferenced0(const void *element);

                void removeFirst0();
            };

        /*
         * When you build project with Microsoft Visual C++ compiler,
         * If you don't explicitly explicit extend the "Collection" class, you will see an error in compiling.
         * The compiler thinks the return type of virtual function 'copy' isn't
         * covariant with the return type the super method.
         * So the class must explicitly extend the "Collection" class.
         *
         * But when the class explicitly extend the "Collection" class,
         * The compiler show a warning (C4584), it thinks the class already extend "Collection" class.
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
                class MixedLinkedListIterator : public Iterator<Type>, private MixedLinkedListIterator0 {
                    friend class MixedLinkedList<Type>;

                public:
                    inline explicit MixedLinkedListIterator(const MixedLinkedList<Type> *mixedLinkedList) :
                        MixedLinkedListIterator0(mixedLinkedList) {}

                    inline bool hasNext() const override {
                        return MixedLinkedListIterator0::hasNext0();
                    }

                    inline const Iterator<Type> *next() const override {
                        MixedLinkedListIterator0::next0();
                        return this;
                    }

                    inline bool each() const override {
                        return MixedLinkedListIterator0::each0();
                    }

                    inline Type get() const override {
                        return *reinterpret_cast<Type *>(MixedLinkedListIterator0::get0());
                    }

                    inline void reset() const override {
                        MixedLinkedListIterator0::reset0();
                    }

                    inline Size count() const override {
                        return MixedLinkedListIterator0::count0();
                    }
                };

                static void *elementNew(void *&element) {
                    return reinterpret_cast<void *>(new Type(*reinterpret_cast<Type *>(element)));
                }

                static void elementDelete(void *element) {
                    delete reinterpret_cast<Type *>(element);
                }

                static bool elementEqual(void *&element1, void *&element2) {
                    return *reinterpret_cast<Type *>(element1) == *reinterpret_cast<Type *>(element2);
                }

            public:
                inline MixedLinkedList() : MixedLinkedList0({elementNew, elementDelete, elementEqual}) {}

                inline MixedLinkedList(const MixedLinkedList<Type> &originalCopy) :
                    MixedLinkedList0(originalCopy) {}

                inline Size getLength() const override {
                    return MixedLinkedList0::getLength0();
                }

                inline bool isEmpty() const override {
                    return MixedLinkedList0::isEmpty0();
                }

                $RetNotIgnored()
                inline bool contain(const Type &element) const override {
                    return MixedLinkedList0::contain0(&element);
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

                inline Iterator<Type> *iterator() const override {
                    return static_cast<MixedLinkedListIterator *>(
                        MixedLinkedList0::iterator = new MixedLinkedListIterator(this)
                    );
                }

                $RetNotIgnored()
                inline typename Iterable<Type>::ForeachIterator begin() const override {
                    return MixedList<Type>::begin();
                }

                $RetNotIgnored()
                inline void *end() const override {
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
        } // namespace Mixed
    } // namespace Collection
} // namespace EnhancedContainer

#endif // CXX_LANGUAGE

#endif // !ENHANCED_CONTAINER_COLLECTION_MIXED_MIXED0LINKED0LIST_H
