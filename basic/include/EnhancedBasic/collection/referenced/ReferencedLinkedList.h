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

#ifndef ENHANCED_BASIC_COLLECTION_REFERENCE_REFERENCE0LINKED0LIST_H
#define ENHANCED_BASIC_COLLECTION_REFERENCE_REFERENCE0LINKED0LIST_H

#include "EnhancedCore/defines.h"
#include "EnhancedCore/annotations.h"
#include "EnhancedCore/types.h"

#include "EnhancedBasic/defines.h"
#include "EnhancedBasic/core/Iterator.h"

#include "EnhancedBasic/collection/referenced/ReferencedList.h"
#include "EnhancedBasic/collection/referenced/ReferencedDeque.h"

#ifdef CXX_LANGUAGE // C++ language

namespace EnhancedBasic {
    namespace Collection {
        namespace Referenced {
            /*!
             * This class is the universal implementation class for
             * the template class "ReferencedLinkedList\<Type\>".
             *
             * @note You should not extend this class from another class.
             *       And you should not instantiate this class directly.
             *       The correct approach is to instantiate the
             *       template class "ReferencedLinkedList\<Type\>" (with "Type" as a type).
             *       Because this class has no public methods.
             *
             * <p>The meaning of this class is to separate the actual
             * implementation of the functions in the template class
             * "ReferencedLinkedList\<Type\>" from the definition of
             * the template class "ReferencedLinkedList\<Type\>".</p>
             *
             * <p>Methods in the template class "ReferencedLinkedList\<Type\>" Type "only cast.</p>
             * <p>You'll see similar code in other classes in this module.</p>
             */
            class ENHANCED_BASIC_API ReferencedLinkedList0 {
            private:
                struct Node {
                    void *value;

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
                    bool (*genericsEquals)(void *const &, void *const &);
                };

                class ENHANCED_BASIC_API ReferencedLinkedListIterator0 {
                private:
                    const ReferencedLinkedList0 *referencedLinkedList;

                    mutable bool isFirst;

                protected:
                    explicit ReferencedLinkedListIterator0(const ReferencedLinkedList0 *referencedLinkedList);

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
                    virtual ~ReferencedLinkedListIterator0() noexcept;
                };

                GenericsOperator genericsOperator;

                mutable ReferencedLinkedListIterator0 *iterator;

                explicit ReferencedLinkedList0(GenericsOperator genericsOperator);

                ReferencedLinkedList0(const ReferencedLinkedList0 &originalCopy);

                virtual ~ReferencedLinkedList0() noexcept;

                $RetNotIgnored()
                Size getLength0() const;

                $RetNotIgnored()
                bool isEmpty0() const;

                $RetNotIgnored()
                bool contain0(const void *value) const;

                $RetNotIgnored()
                void *getLast0() const;

                $RetNotIgnored()
                void *getFirst0() const;

                $RetNotIgnored()
                void *get0(Size index) const;

                void addLast0(const void *element);

                void removeLast0();

                void addFirst0(const void *element);

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
            class ReferencedLinkedList final : public Collection<Type>, public ReferencedList<Type>,
                                               public ReferencedDeque<Type>, public ReferencedLinkedList0 {
        #pragma warning(pop)
        #else // Non Microsoft Visual C++ compiler
            template <typename Type>
            class ReferencedLinkedList final : public ReferencedList<Type>, public ReferencedDeque<Type>,
                                               private ReferencedLinkedList0 {
        #endif // COMPILER_MSVC
            private:
                class ReferencedLinkedListIterator : public Core::Iterator<Type>, private ReferencedLinkedListIterator0 {
                    friend class ReferencedLinkedList<Type>;

                public:
                    inline explicit
                    ReferencedLinkedListIterator(const ReferencedLinkedList<Type> *referenceLinkedList) :
                        ReferencedLinkedListIterator0(referenceLinkedList) {}

                    inline bool hasNext() const override {
                        return ReferencedLinkedListIterator0::hasNext0();
                    }

                    inline const Core::Iterator<Type> *next() const override {
                        ReferencedLinkedListIterator0::next0();
                        return this;
                    }

                    inline bool each() const override {
                        return ReferencedLinkedListIterator0::each0();
                    }

                    inline Type &get() const override {
                        return *reinterpret_cast<Type *>(ReferencedLinkedListIterator0::get0());
                    }

                    inline void reset() const override {
                        ReferencedLinkedListIterator0::reset0();
                    }

                    inline Size count() const override {
                        return ReferencedLinkedListIterator0::count0();
                    }
                };

                static bool genericsEquals(void *const &element, void *const &value) {
                    return *reinterpret_cast<Type *>(element) == *reinterpret_cast<Type *>(value);
                }

            public:
                inline ReferencedLinkedList() : ReferencedLinkedList0({genericsEquals}) {}

                ReferencedLinkedList(const ReferencedLinkedList<Type> &originalCopy) :
                    ReferencedLinkedList0(originalCopy) {}

                $RetNotIgnored()
                inline Size getLength() const override {
                    return ReferencedLinkedList0::getLength0();
                }

                $RetNotIgnored()
                inline bool isEmpty() const override {
                    return ReferencedLinkedList0::isEmpty0();
                }

                $RetNotIgnored()
                inline bool contain(const Type &value) const override {
                    return ReferencedLinkedList0::contain0(&value);
                }

                $RetRequiresRelease()
                inline ReferencedLinkedList<Type> *copy() const override {
                    return new ReferencedLinkedList<Type>(*this);
                }

                $RetNotIgnored()
                inline Type &getLast() const override {
                    return *reinterpret_cast<Type *>(ReferencedLinkedList0::getLast0());
                }

                $RetNotIgnored()
                inline Type &getFirst() const override {
                    return *reinterpret_cast<Type *>(ReferencedLinkedList0::getFirst0());
                }

                $RetNotIgnored()
                inline Type &get(Size index) const override {
                    return *reinterpret_cast<Type *>(ReferencedLinkedList0::get0(index));
                }

                $RetNotIgnored()
                inline Type &operator[](Size index) const override {
                    return *reinterpret_cast<Type *>(ReferencedLinkedList0::get0(index));
                }

                $RetNotIgnored()
                inline Core::Iterator<Type> *iterator() const override {
                    if (ReferencedLinkedList0::iterator == null) {
                        ReferencedLinkedList0::iterator = new ReferencedLinkedListIterator(this);
                    } else {
                        static_cast<ReferencedLinkedListIterator *>(ReferencedLinkedList0::iterator)->reset();
                    }
                    return static_cast<ReferencedLinkedListIterator *>(ReferencedLinkedList0::iterator);
                }

                $RetNotIgnored()
                inline typename Core::Iterable<Type>::ForeachIterator begin() const override {
                    return List<Type>::begin();
                }

                $RetNotIgnored()
                inline void *end() const override {
                    return List<Type>::end();
                }

                inline void addLast(const Type &element) override {
                    ReferencedLinkedList0::addLast0(&element);
                }

                inline Type removeLast() override {
                    Type value = this->getLast();
                    ReferencedLinkedList0::removeFirst0();
                    return value;
                }

                inline void addFirst(const Type &element) override {
                    ReferencedLinkedList0::addFirst0(&element);
                }

                inline Type removeFirst() override {
                    Type value = this->getFirst();
                    ReferencedLinkedList0::removeFirst0();
                    return value;
                }

                inline void add(const Type &element) override {
                    this->addLast(element);
                }

                inline Type remove() override {
                    return this->removeLast();
                }

                inline void push(const Type &element) override {
                    this->addFirst(element);
                }

                inline Type popup() override {
                    return this->removeFirst();
                }
            };
        } // namespace Referenced
    } // namespace Collection
} // namespace EnhancedBasic

#endif // CXX_LANGUAGE

#endif // !ENHANCED_BASIC_COLLECTION_REFERENCE_REFERENCE0LINKED0LIST_H
