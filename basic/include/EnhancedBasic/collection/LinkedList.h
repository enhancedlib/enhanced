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

#ifndef ENHANCED_BASIC_COLLECTION_LINKED0LIST_H
#define ENHANCED_BASIC_COLLECTION_LINKED0LIST_H

#include "EnhancedCore/defines.h"
#include "EnhancedCore/annotations.h"
#include "EnhancedCore/types.h"

#include "EnhancedBasic/defines.h"
#include "EnhancedBasic/core/Iterator.h"

#include "EnhancedBasic/collection/List.h"
#include "EnhancedBasic/collection/Deque.h"

#ifdef CXX_LANGUAGE // C++ language

namespace EnhancedBasic {
    namespace Collection {
        /*!
         * This class is the universal implementation class for
         * the template class "LinkedList\<Type\>".
         *
         * @note You should not extend this class from another class.
         *       And you should not instantiate this class directly.
         *       The correct approach is to instantiate the
         *       template class "LinkedList\<Type\>" (with "Type" as a type).
         *       Because this class has no public methods.
         *
         * <p>The meaning of this class is to separate the actual
         * implementation of the functions in the template class
         * "LinkedList\<Type\>" from the definition of
         * the template class "LinkedList\<Type\>".</p>
         *
         * <p>Methods in the template class "LinkedList\<Type\>" Type "only cast.</p>
         * <p>You'll see similar code in other classes in this module.</p>
         */
        class ENHANCED_BASIC_API LinkedList0 {
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
                void *(*genericsNew)(void *const &);

                void (*genericsDelete)(void *const &);

                bool (*genericsEquals)(void *const &, void *const &);
            };

            class ENHANCED_BASIC_API LinkedListIterator0 {
            private:
                const LinkedList0 *linkedList;

                mutable bool isFirst;

            protected:
                explicit LinkedListIterator0(const LinkedList0 *linkedList);

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
                virtual ~LinkedListIterator0() noexcept;
            };

            GenericsOperator genericsOperator;

            mutable LinkedListIterator0 *iterator;

            explicit LinkedList0(GenericsOperator genericsOperator);

            LinkedList0(const LinkedList0 &originalCopy);

            virtual ~LinkedList0() noexcept;

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
        class LinkedList final : public Collection<Type>, public List<Type>, public Deque<Type>, public LinkedList0 {
    #pragma warning(pop)
    #else // Non Microsoft Visual C++ compiler
        template <typename Type>
        class LinkedList : public List<Type>, public Deque<Type>, private LinkedList0 {
    #endif // COMPILER_MSVC
        private:
            class LinkedListIterator : public Core::Iterator<Type>, private LinkedListIterator0 {
                friend class LinkedList<Type>;

            public:
                inline explicit LinkedListIterator(const LinkedList<Type> *linkedList) :
                    LinkedListIterator0(linkedList) {}

                $RetNotIgnored()
                inline bool hasNext() const override {
                    return LinkedListIterator0::hasNext0();
                }

                inline const Core::Iterator<Type> *next() const override {
                    LinkedListIterator0::next0();
                    return this;
                }

                $RetNotIgnored()
                inline bool each() const override {
                    return LinkedListIterator0::each0();
                }

                $RetNotIgnored()
                inline Type &get() const override {
                    return *reinterpret_cast<Type *>(LinkedListIterator0::get0());
                }

                inline void reset() const override {
                    LinkedListIterator0::reset0();
                }

                $RetNotIgnored()
                inline Size count() const override {
                    return LinkedListIterator0::count0();
                }
            };

            static void *genericsNew(void *const &element) {
                return reinterpret_cast<void *>(new Type(*reinterpret_cast<Type *>(element)));
            }

            static void genericsDelete(void *const &element) {
                delete reinterpret_cast<Type *>(element);
            }

            static bool genericsEquals(void *const &element, void *const &value) {
                return *reinterpret_cast<Type *>(element) == *reinterpret_cast<Type *>(value);
            }

        public:
            inline explicit LinkedList() : LinkedList0({genericsNew, genericsDelete, genericsEquals}) {}

            inline LinkedList(const LinkedList<Type> &originalCopy) : LinkedList0(originalCopy) {}

            $RetNotIgnored()
            inline Size getLength() const override {
                return LinkedList0::getLength0();
            }

            $RetNotIgnored()
            inline bool isEmpty() const override {
                return LinkedList0::isEmpty0();
            }

            $RetNotIgnored()
            inline bool contain(const Type &value) const override {
                return LinkedList0::contain0(&value);
            }

            $RetRequiresRelease()
            inline LinkedList<Type> *copy() const override {
                return new LinkedList<Type>(*this);
            }

            $RetNotIgnored()
            inline Type &getLast() const override {
                return *reinterpret_cast<Type *>(LinkedList0::getLast0());
            }

            $RetNotIgnored()
            inline Type &getFirst() const override {
                return *reinterpret_cast<Type *>(LinkedList0::getFirst0());
            }

            $RetNotIgnored()
            inline Type &get(Size index) const override {
                return *reinterpret_cast<Type *>(LinkedList0::get0(index));
            }

            $RetNotIgnored()
            inline Type &operator[](Size index) const override {
                return *reinterpret_cast<Type *>(LinkedList0::get0(index));
            }

            $RetNotIgnored()
            inline Core::Iterator<Type> *iterator() const override {
                if (LinkedList0::iterator == null) {
                    LinkedList0::iterator = new LinkedListIterator(this);
                } else {
                    static_cast<LinkedListIterator *>(LinkedList0::iterator)->reset();
                }
                return static_cast<LinkedListIterator *>(LinkedList0::iterator);
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
                LinkedList0::addLast0(&element);
            }

            inline Type removeLast() override {
                Type value = this->getLast();
                LinkedList0::removeFirst0();
                return value;
            }

            inline void addFirst(const Type &element) override {
                LinkedList0::addFirst0(&element);
            }

            inline Type removeFirst() override {
                Type value = this->getFirst();
                LinkedList0::removeFirst0();
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
    } // namespace Collection
} // namespace EnhancedBasic

#endif // CXX_LANGUAGE

#endif // !ENHANCED_BASIC_COLLECTION_LINKED0LIST_H
