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


#ifndef ENHANCED_BASIC_COLLECTION_VECTOR_H
#define ENHANCED_BASIC_COLLECTION_VECTOR_H

#include "EnhancedCore/defines.h"
#include "EnhancedCore/annotations.h"
#include "EnhancedCore/types.h"

#include "EnhancedBasic/defines.h"

#include "EnhancedBasic/collection/List.h"
#include "EnhancedBasic/collection/RandomAccess.h"

#ifdef CXX_LANGUAGE // C++ language

namespace EnhancedBasic {
    namespace Collection {
        /*!
         * This class is the universal implementation class for
         * the template class "Vector".
         * \n
         * Separate the implementation of Vector from the template
         * by type erasure (pseudo-generic). \n
         * \n
         * Methods in the template class "Vector" do only
         * type erasure. \n
         * \n
         * You'll see similar code in other classes in this module.
         *
         * @note You should not extend this class from another class.
         *       And you should not instantiate this class directly.
         *       The correct approach is to instantiate the
         *       template class "Vector" (with "Type" as a type).
         *       Because this class has no public methods.
         */
        class ENHANCED_BASIC_API Vector0 {
        private:
            Size maxCount;

            void *elements;

            Size length;

        protected:
            struct GenericsOperator {
                void *(*genericsArrayNew)(const Size &size);

                void (*genericsArrayDelete)(void *const &elements);

                void (*genericsArrayCopy)(void *const &destination, void *const &source, const Size &size);

                void *(*genericsArrayIndex)(void *const &elements, const Size &index);

                void (*genericsArraySetElement)(void *const &elements, const Size &index, void *const &value);

                bool (*genericsEquals)(void *const &element, void *const &value);
            };

            class ENHANCED_BASIC_API VectorIterator0 {
            private:
                const Vector0 *vector;

                mutable void *indexer;

                mutable bool isFirst;

                const void *end;

            protected:
                explicit VectorIterator0(const Vector0 *vector);

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
                virtual ~VectorIterator0() noexcept;
            };

            GenericsOperator genericsOperator;

            mutable VectorIterator0 *iterator;

            Vector0(Size length, GenericsOperator genericsOperator);

            virtual ~Vector0() noexcept;

            $RetNotIgnored()
            Size getLength0() const;

            $RetNotIgnored()
            bool isEmpty0() const;

            $RetNotIgnored()
            void *get0(Size index) const;

            $RetNotIgnored()
            bool contain0(const void *value) const;

            void add0(const void *element);

            void remove0();

            void expand0(Size size);

            void shrink0(Size size);
        };

        template <typename Type>
        class Vector final : public List<Type>, public RandomAccess<Type>, private Vector0 {
        private:
            class VectorIterator : public Core::Iterator<Type>, private Vector0::VectorIterator0 {
                friend class Vector<Type>;

            public:
                inline explicit VectorIterator(const Vector<Type> *vector) :
                    VectorIterator0(vector) {}

                $RetNotIgnored()
                inline bool hasNext() const override {
                    return VectorIterator0::hasNext0();
                }

                inline const Core::Iterator<Type> *next() const override {
                    VectorIterator0::next0();
                    return this;
                }

                $RetNotIgnored()
                inline bool each() const override {
                    return VectorIterator0::each0();
                }

                $RetNotIgnored()
                inline Type &get() const override {
                    return *reinterpret_cast<Type *>(VectorIterator0::get0());
                }

                inline void reset() const override {
                    VectorIterator0::reset0();
                }

                $RetNotIgnored()
                inline Size count() const override {
                    return VectorIterator0::count0();
                }
            };

            static void *genericsArrayNew(const Size &size) {
                return new Type[size];
            }

            static void genericsArrayDelete(void *const &elements) {
                delete[] static_cast<Type *>(elements);
            }

            static void genericsArrayCopy(void *const &destination, void *const &source, const Size &size) {
                for (Size index = 0; index < size; ++ index) {
                    static_cast<Type *>(destination)[index] = static_cast<Type *>(source)[index];
                }
            }

            static void *genericsArrayIndex(void *const &elements, const Size &index) {
                return static_cast<Type *>(elements) + index;
            }

            static void genericsArraySetElement(void *const &elements, const Size &index, void *const &value) {
                static_cast<Type *>(elements)[index] = *static_cast<Type *>(value);
            }

            static bool genericsEquals(void *const &element, void *const &value) {
                return *reinterpret_cast<Type *>(element) == *reinterpret_cast<Type *>(value);
            }

        public:
            inline explicit Vector() : Vector0(UINT8_MAX, {
                genericsArrayNew, genericsArrayDelete, genericsArrayCopy,
                genericsArrayIndex, genericsArraySetElement, genericsEquals
            }) {}

            inline explicit Vector(Size maxCount) : Vector0(maxCount, {
                genericsArrayNew, genericsArrayDelete, genericsArrayCopy,
                genericsArrayIndex, genericsArraySetElement, genericsEquals
            }) {}

            inline Vector(const Vector<Type> &originalCopy) : Vector0(originalCopy) {}

            inline Vector(void *(*genericsArrayNew)(const Size &size),
                          bool (*genericsEquals)(void *const &element, void *const &value) = Vector::genericsEquals) :
                Vector0(UINT8_MAX, {
                    genericsArrayNew, genericsArrayDelete, genericsArrayCopy,
                    genericsArrayIndex, genericsArraySetElement, genericsEquals
                }) {}

            inline Vector(Size maxCount, void *(*genericsArrayNew)(const Size &size),
                          bool (*genericsEquals)(void *const &element, void *const &value) = Vector::genericsEquals) :
                Vector0(maxCount, {
                    genericsArrayNew, genericsArrayDelete, genericsArrayCopy,
                    genericsArrayIndex, genericsArraySetElement, genericsEquals
                }) {}

            inline Vector(bool (*genericsEquals)(void *const &element, void *const &value)) :
                Vector0(UINT8_MAX, {
                    genericsArrayNew, genericsArrayDelete, genericsArrayCopy,
                    genericsArrayIndex, genericsArraySetElement, genericsEquals
                }) {}

            inline Vector(Size maxCount, bool (*genericsEquals)(void *const &element, void *const &value)) :
                Vector0(maxCount, {
                    genericsArrayNew, genericsArrayDelete, genericsArrayCopy,
                    genericsArrayIndex, genericsArraySetElement, genericsEquals
                }) {}

            $RetNotIgnored()
            inline Size getLength() const override {
                return Vector0::getLength0();
            }

            $RetNotIgnored()
            inline bool isEmpty() const override {
                return Vector0::isEmpty0();
            }

            $RetNotIgnored()
            inline Type &get(Size index) const override {
                return *reinterpret_cast<Type *>(Vector0::get0(index));
            }

            $RetNotIgnored()
            inline Type &operator[](Size index) const override {
                return *reinterpret_cast<Type *>(Vector0::get0(index));
            }

            $RetNotIgnored()
            inline Core::Iterator<Type> *iterator() const override {
                if (Vector0::iterator == null) {
                    Vector0::iterator = new VectorIterator(this);
                } else {
                    static_cast<VectorIterator *>(Vector0::iterator)->reset();
                }
                return static_cast<VectorIterator *>(Vector0::iterator);
            }

            $RetNotIgnored()
            inline bool contain(const Type &value) const override {
                return Vector0::contain0(&value);
            }

            $RetRequiresRelease()
            inline Vector<Type> *copy() const override {
                return new Vector<Type>(*this);
            }

            inline void add(const Type &element) override {
                Vector0::add0(&element);
            }

            inline Type remove() override {
                Type value = this->get(this->getLength() - 1);
                Vector0::remove0();
                return value;
            }
        };
    } // namespace Collection
} // namespace EnhancedBasic

#define VECTOR_GENERICS_ALLOCATOR(type, args) \
    [](const Size &size) { \
        type *array = static_cast<type *>(operator new(size * sizeof(type))); /* NOLINT(bugprone-macro-parentheses) */ \
        for (Size index = 0; index < size; ++ index) { \
            array[index] = type args; \
        } \
        return (void *) array; \
    }

#endif // CXX_LANGUAGE

#endif // !ENHANCED_BASIC_COLLECTION_VECTOR_H
