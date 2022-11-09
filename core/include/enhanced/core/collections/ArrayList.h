/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 *
 * Licensed under the Enhanced Software License.
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://sharedwonder.github.io/enhanced/LICENSE.txt
 *
 * UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING,
 * THE SOFTWARE IS ALWAYS PROVIDED "AS IS",
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#pragma once

#include <enhanced/core/defines.h>
#include <enhanced/core/export.h>
#include <enhanced/core/types.h>
#include <enhanced/core/annotations.h>
#include <enhanced/core/Iterable.h>
#include <enhanced/core/Iterator.h>
#include <enhanced/core/generic.h>
#include <enhanced/core/collections/List.h>
#include <enhanced/core/collections/RandomAccess.h>

#ifdef CXX_LANGUAGE

NAMESPACE_L3_BEGIN(enhanced_internal, core, collections)

class ENHANCED_CORE_API ArrayListImpl {
private:
    void** elements;

    sizetype size;

    sizetype capacity;

protected:
    struct GenericOperator {
        void* (*allocate)(Generic&);

        void (*destroy)(void*);

        bool (*equals)(Generic&, Generic&);
    };

    class ENHANCED_CORE_API ArrayListIteratorImpl {
        friend class ArrayListImpl;

    private:
        const ArrayListImpl* arrayList;

        mutable void** indexer;

    protected:
        explicit ArrayListIteratorImpl(const ArrayListImpl* arrayList);

        virtual ~ArrayListIteratorImpl() noexcept;

        NoIgnoreRet
        bool hasNext0() const;

        void next0() const;

        NoIgnoreRet
        Generic& get0() const;

        void reset0() const;

        NoIgnoreRet
        sizetype count0() const;
    };

    GenericOperator genericOperator;

    ArrayListImpl(sizetype capacity, GenericOperator genericOperator);

    ArrayListImpl(const ArrayListImpl& other);

    virtual ~ArrayListImpl() noexcept;

    NoIgnoreRet
    sizetype getSize0() const;

    NoIgnoreRet
    bool isEmpty0() const;

    NoIgnoreRet
    Generic& get0(sizetype index) const;

    NoIgnoreRet
    bool contain0(Generic& value) const;

    void add0(Generic& element);

    void remove0();

    void expand0(sizetype size);

    void shrink0(sizetype size);
};

NAMESPACE_L3_END

NAMESPACE_L3_BEGIN(enhanced, core, collections)

template <typename Type>
class ENHANCED_CORE_API ArrayList final : public List<Type>, public RandomAccess, private enhanced_internal::core::collections::ArrayListImpl {
private:
    using ArrayListImpl = enhanced_internal::core::collections::ArrayListImpl;

    class ENHANCED_CORE_API ArrayListIterator : public Iterator<Type>, private ArrayListImpl::ArrayListIteratorImpl {
        friend class ArrayList<Type>;

    public:
        inline explicit ArrayListIterator(const ArrayList<Type>* arrayList) : ArrayListIteratorImpl(arrayList) {}

        NoIgnoreRet
        inline bool hasNext() const override {
            return hasNext0();
        }

        inline const Iterator<Type>* next() const override {
            next0();
            return this;
        }

        NoIgnoreRet
        inline Type& get() const override {
            return (Type&) get0();
        }

        inline void reset() const override {
            reset0();
        }

        NoIgnoreRet
        inline sizetype count() const override {
            return count0();
        }
    };

    RetRequiresRelease
    static void* allocate(Generic& element) {
        return new Type((Type&) element);
    }

    static void destroy(void* element) {
        delete (Type*) element;
    }

    NoIgnoreRet
    static bool equals(Generic& element, Generic& value) {
        return ((Type&) element) == ((Type&) value);
    }

    ArrayListIterator iter = ArrayListIterator(this);

public:
    inline ArrayList() : ArrayListImpl(ARRAY_INIT_SIZE, {allocate, destroy, equals}) {}

    inline explicit ArrayList(sizetype capacity) : ArrayListImpl(capacity, {allocate, destroy, equals}) {}

    inline ArrayList(const ArrayList<Type>& other) : ArrayListImpl(other) {}

    NoIgnoreRet
    inline sizetype getSize() const override {
        return getSize0();
    }

    NoIgnoreRet
    inline bool isEmpty() const override {
        return isEmpty0();
    }

    NoIgnoreRet
    inline bool contain(const Type& value) const override {
        return contain0((Generic&) value);
    }

    RetRequiresRelease
    inline ArrayList<Type>* copy() const override {
        return new ArrayList<Type>(*this);
    }

    NoIgnoreRet
    inline const Iterator<Type>& iterator() const override {
        iter.reset();
        return iter;
    }

    NoIgnoreRet
    inline Type& get(sizetype index) const override {
        return (Type&) get0(index);
    }

    NoIgnoreRet
    inline Type& operator[](sizetype index) const override {
        return (Type&) get0(index);
    }

    inline void add(const Type& element) override {
        add0((Generic&) element);
    }

    inline Type remove() override {
        Type value = get(getSize() - 1);
        remove0();
        return value;
    }

    inline void expand(sizetype size) {
        expand0(size);
    }

    inline void shrink(sizetype size) {
        shrink0(size);
    }
};

NAMESPACE_L3_END

#endif
