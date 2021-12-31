/*
 * Copyright (C) 2021 Liu Baihao.
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


#ifndef ENHANCED_CONTAINER_COLLECTION_ARRAY0LIST_H
#define ENHANCED_CONTAINER_COLLECTION_ARRAY0LIST_H

#include "EnhancedCore/defines.h"
#include "EnhancedCore/annotations.h"
#include "EnhancedCore/types.h"

#include "EnhancedContainer/defines.h"

#include "EnhancedContainer/collection/List.h"
#include "EnhancedContainer/collection/RandomAccess.h"

#ifdef CXX_LANGUAGE // C++ language

namespace EnhancedContainer {
    namespace Collection {
        /*!
         * This class is the universal implementation class for
         * the template class "ArrayList\<Type\>".
         *
         * @note You should not extend this class from another class.
         *       And you should not instantiate this class directly.
         *       The correct approach is to instantiate the
         *       template class "ArrayList\<Type\>" (with "Type" as a type).
         *       Because this class has no public methods.
         *
         * <p>The meaning of this class is to separate the actual
         * implementation of the functions in the template class
         * "ArrayList\<Type\>" from the definition of
         * the template class "ArrayList\<Type\>".</p>
         *
         * <p>Methods in the template class "ArrayList\<Type\>" Type "only cast.</p>
         * <p>You'll see similar code in other classes in this module.</p>
         */
        class ENHANCED_CONTAINER_API ArrayList0 {
        private:
            Size maxCount;

            void **elements;

            Size length;

        protected:
            struct ElementOperator {
                void *(*elementNew)(void *&);

                void (*elementDelete)(void *&);

                bool (*elementEqual)(void *&, void *&);
            };

            class ENHANCED_CONTAINER_API ArrayListIterator0 {
            private:
                const ArrayList0 *arrayList;

                mutable void **indexer;

                mutable bool isFirst;

                const void **end;

            protected:
                explicit ArrayListIterator0(const ArrayList0 *arrayList);

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
                virtual ~ArrayListIterator0() noexcept;
            };

            ElementOperator elementOperator;

            mutable ArrayListIterator0 *iterator;

            ArrayList0(Size length, ElementOperator elementOperator);

            virtual ~ArrayList0() noexcept;

            $RetNotIgnored()
            Size getLength0() const;

            $RetNotIgnored()
            bool isEmpty0() const;

            $RetNotIgnored()
            void *&get0(Size index) const;

            $RetNotIgnored()
            bool contain0(const void *element) const;

            void add0(const void *element);

            void remove0();

            void expand0(Size size);

            void shrink0(Size size);
        };

        template <typename Type>
        class ArrayList final : public List<Type>, public RandomAccess<Type>, private ArrayList0 {
        private:
            class ArrayListIterator : public Iterator<Type>, private ArrayList0::ArrayListIterator0 {
                friend class ArrayList<Type>;

            public:
                inline explicit ArrayListIterator(const ArrayList<Type> *arrayList) :
                    ArrayListIterator0(arrayList) {}

                $RetNotIgnored()
                inline bool hasNext() const override {
                    return ArrayListIterator0::hasNext0();
                }

                inline const Iterator<Type> *next() const override {
                    ArrayListIterator0::next0();
                    return this;
                }

                $RetNotIgnored()
                inline bool each() const override {
                    return ArrayListIterator0::each0();
                }

                $RetNotIgnored()
                inline Type get() const override {
                    return *reinterpret_cast<Type *>(ArrayListIterator0::get0());
                }

                inline void reset() const override {
                    ArrayListIterator0::reset0();
                }

                $RetNotIgnored()
                inline Size count() const override {
                    return ArrayListIterator0::count0();
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
            inline explicit ArrayList() : ArrayList0(UINT8_MAX, {elementNew, elementDelete, elementEqual}) {}

            inline explicit ArrayList(Size maxCount) : ArrayList0(maxCount,{elementNew, elementDelete, elementEqual}) {}

            inline ArrayList(const ArrayList<Type> &originalCopy) : ArrayList0(originalCopy) {}

            $RetNotIgnored()
            inline Size getLength() const override {
                return ArrayList0::getLength0();
            }

            $RetNotIgnored()
            inline bool isEmpty() const override {
                return ArrayList0::isEmpty0();
            }

            $RetNotIgnored()
            inline Type &get(Size index) const override {
                return *reinterpret_cast<Type *>(ArrayList0::get0(index));
            }

            $RetNotIgnored()
            inline Type &operator[](Size index) const override {
                return *reinterpret_cast<Type *>(ArrayList0::get0(index));
            }

            $RetNotIgnored()
            inline Iterator<Type> *iterator() const override {
                return static_cast<ArrayListIterator *>(ArrayList0::iterator = new ArrayListIterator(this));
            }

            $RetNotIgnored()
            inline bool contain(const Type &element) const override {
                return ArrayList0::contain0(&element);
            }

            $RetRequiresRelease()
            inline ArrayList<Type> *copy() const override {
                return new ArrayList<Type>(*this);
            }

            inline void add(const Type &element) override {
                ArrayList0::add0(&element);
            }

            inline Type remove() override {
                Type value = this->get(this->getLength() - 1);
                ArrayList0::remove0();
                return value;
            }
        };
    } // namespace Collection
} // namespace EnhancedContainer

#endif // CXX_LANGUAGE

#endif // !ENHANCED_CONTAINER_COLLECTION_ARRAY0LIST_H
