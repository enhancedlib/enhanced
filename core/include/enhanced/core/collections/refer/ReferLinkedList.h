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
#include <enhanced/core/annotations.h>
#include <enhanced/core/export.h>
#include <enhanced/core/types.h>
#include <enhanced/core/Iterable.h>
#include <enhanced/core/Iterator.h>
#include <enhanced/core/generic.h>
#include <enhanced/core/collections/refer/ReferList.h>
#include <enhanced/core/collections/refer/ReferDeque.h>

#ifdef CXX_LANGUAGE

NAMESPACE_L4_BEGIN(enhanced_internal, core, collections, refer)

class ENHANCED_CORE_API ReferLinkedListImpl {
private:
    struct Node {
        void* value;

        Node* prev;

        Node* next;
    };

    Node* first;

    Node* last;

    sizetype size;

    static Node*& prevNode(Node*& node);

    static Node*& nextNode(Node*& node);

protected:
    struct GenericOperator {
        bool (*equals)(Generic&, Generic&);
    };

    class ENHANCED_CORE_API ReferLinkedListIteratorImpl {
        friend class ReferLinkedListImpl;

    private:
        const ReferLinkedListImpl* referLinkedList;

        mutable Node* indexer;

    protected:
        explicit ReferLinkedListIteratorImpl(const ReferLinkedListImpl* referLinkedList);

        virtual ~ReferLinkedListIteratorImpl() noexcept;

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

    explicit ReferLinkedListImpl(GenericOperator genericOperator);

    ReferLinkedListImpl(const ReferLinkedListImpl& other);

    virtual ~ReferLinkedListImpl() noexcept;

    NoIgnoreRet
    sizetype getSize0() const;

    NoIgnoreRet
    bool isEmpty0() const;

    NoIgnoreRet
    Generic& getLast0() const;

    NoIgnoreRet
    Generic& getFirst0() const;

    NoIgnoreRet
    Generic& get0(sizetype index) const;

    NoIgnoreRet
    bool contain0(Generic& value) const;

    void addLast0(Generic& element);

    void removeLast0();

    void addFirst0(Generic& element);

    void removeFirst0();
};

NAMESPACE_L4_END

NAMESPACE_L4_BEGIN(enhanced, core, collections, refer)

template <typename Type>
class ENHANCED_CORE_API ReferLinkedList final :
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
    public Collection<Type>,
#pragma warning(pop)
#endif
    public ReferList<Type>, public ReferDeque<Type>, private enhanced_internal::core::collections::refer::ReferLinkedListImpl {
private:
    using ReferLinkedListImpl = enhanced_internal::core::collections::refer::ReferLinkedListImpl;

    class ENHANCED_CORE_API ReferLinkedListIterator : public Iterator<Type>, private ReferLinkedListIteratorImpl {
        friend class ReferLinkedList<Type>;

    public:
        inline explicit ReferLinkedListIterator(const ReferLinkedList<Type>* referenceLinkedList) :
            ReferLinkedListIteratorImpl(referenceLinkedList) {}

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

    NoIgnoreRet
    static bool equals(Generic& element, Generic& value) {
        return ((Type&) (element)) == ((Type&) value);
    }

    ReferLinkedListIterator iter = ReferLinkedListIterator(this);

public:
    inline ReferLinkedList() : ReferLinkedListImpl({equals}) {}

    ReferLinkedList(const ReferLinkedList<Type>& other) : ReferLinkedListImpl(other) {}

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
    inline ReferLinkedList<Type>* copy() const override {
        return new ReferLinkedList<Type>(*this);
    }

    inline const Iterator<Type>& iterator() const override {
        iter.reset();
        return iter;
    }

    NoIgnoreRet
    inline typename Iterable<Type>::ForeachIterator begin() const override {
        return List<Type>::begin();
    }

    NoIgnoreRet
    inline constexpr byte end() const override {
        return List<Type>::end();
    }

    NoIgnoreRet
    inline Type& getLast() const override {
        return (Type&) getLast0();
    }

    NoIgnoreRet
    inline Type& getFirst() const override {
        return (Type&) getFirst0();
    }

    NoIgnoreRet
    inline Type& get(sizetype index) const override {
        return (Type&) get0(index);
    }

    NoIgnoreRet
    inline Type& operator[](sizetype index) const override {
        return (Type&) get0(index);
    }

    inline void addLast(const Type& element) override {
        addLast0((Generic&) element);
    }

    inline Type removeLast() override {
        Type value = getLast();
        removeLast0();
        return value;
    }

    inline void addFirst(const Type& element) override {
        addFirst0((Generic&) element);
    }

    inline Type removeFirst() override {
        Type value = getFirst();
        removeFirst0();
        return value;
    }

    inline void add(const Type& element) override {
        addLast(element);
    }

    inline Type remove() override {
        return removeLast();
    }

    inline void push(const Type& element) override {
        addFirst(element);
    }

    inline Type popup() override {
        return removeFirst();
    }
};

NAMESPACE_L4_END

#endif
