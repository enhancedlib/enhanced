/*
 * This file is part of Enhanced Framework.
 *
 * Copyright (C) 2023 Liu Baihao (sharedwonder). All rights reserved.
 *
 * Permission is hereby granted, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software,
 * including without limitation the rights to use, copy, modify, merge,
 * distribute. Unless you have obtained permission from the copyright holders,
 * subject to the following restrictions:
 *
 * 1. The above copyright notice and this permission notice shall be included in
 *    all copies of the Software and modified versions.
 *
 * 2. You may not misrepresent the source of the Software, and you may not claim
 *    that you wrote the original version.
 *
 * 3. You may not misrepresent the modified version as the original version.
 *
 * 4. You may not charge any fees or receive other compensation for the
 *    distribution of the Software, excluding distribution of modified versions
 *    and products using the Software.
 *
 * 5. If you use this Software in your product, you shall indicate it.
 *
 * 6. Neither the name of the author nor the names of its contributors may
 *    be used to endorse or promote products derived from the Software
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#include <enhanced/Defines.h>
#include <enhanced/ExportCore.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/Memory.h>
#include <enhanced/Iterator.h>
#include <enhanced/InitializerList.h>
#include <enhanced/util/Traits.h>
#include <enhanced/collections/List.h>

namespace enhancedInternal::collections {
    class E_CORE_API LinkedListImpl {
    protected:
        struct Node {
            void* value;

            Node* prev;

            Node* next;
        };

        Node* first;

        Node* last;

        enhanced::sizetype size;

        using OpCopy = void* (*)(void*);
        using OpMove = void* (*)(void*);
        using OpDestroy = void (*)(void*);
        using OpEqual = bool (*)(void*, void*);

        class E_CORE_API LinkedListIteratorImpl {
        protected:
            const LinkedListImpl* linkedList;

            mutable Node* indexer;

            LinkedListIteratorImpl(const LinkedListImpl* linkedList, Node* init);

            E_ANNOTATE(RetNotIgnored)
            void* get0() const;

            E_ANNOTATE(RetNotIgnored)
            bool hasNext0() const;

            E_ANNOTATE(RetNotIgnored)
            bool hasPrev0() const;

            E_ANNOTATE(RetNotIgnored)
            bool isBegin0() const;

            E_ANNOTATE(RetNotIgnored)
            bool isEnd0() const;

            void next0() const;

            void next0(enhanced::sizetype count) const;

            void prev0() const;

            void prev0(enhanced::sizetype count) const;

            void setBegin0() const;

            void setEnd0() const;
        };

        static inline Node*& prevNode(Node*& node) {
            return node = node->prev;
        }

        static inline Node*& nextNode(Node*& node) {
            return node = node->next;
        }

        LinkedListImpl();

        LinkedListImpl(const LinkedListImpl& other, OpCopy opCopy);

        LinkedListImpl(LinkedListImpl&& other) noexcept;

        E_ANNOTATE(RetNotIgnored)
        void* getLast0() const;

        E_ANNOTATE(RetNotIgnored)
        void* getFirst0() const;

        E_ANNOTATE(RetNotIgnored)
        void* get0(enhanced::sizetype index) const;

        E_ANNOTATE(RetNotIgnored)
        enhanced::sizetype indexOf0(void* value, OpEqual opEqual) const;

        void addFirst0(void* element, OpCopy opCopy);

        void addFirst1(void* element, OpMove opMove);

        void addLast0(void* element, OpCopy opCopy);

        void addLast1(void* element, OpMove opMove);

        void removeFirst0(OpDestroy opDestroy);

        void removeLast0(OpDestroy opDestroy);

        void clear0(OpDestroy opDestroy);
    };
}

namespace enhanced::collections {
    template <typename Type>
    class LinkedList : public List<Type>, private enhancedInternal::collections::LinkedListImpl {
    private:
        using LinkedListImpl = enhancedInternal::collections::LinkedListImpl;

        E_ANNOTATE(RetRequiresRelease)
        static void* copy(void* element) {
            return new Type(*reinterpret_cast<Type*>(element));
        }

        E_ANNOTATE(RetRequiresRelease)
        static void* move(void* element) {
            return new Type(util::move(*reinterpret_cast<Type*>(element)));
        }

        static void destroy(void* element) {
            delete reinterpret_cast<Type*>(element);
        }

        E_ANNOTATE(RetNotIgnored)
        static bool equal(void* element, void* value) {
            return *reinterpret_cast<Type*>(element) == *reinterpret_cast<Type*>(value);
        }

    public:
        class LinkedListIterator : public Iterator<Type>, private LinkedListImpl::LinkedListIteratorImpl {
        public:
            inline explicit LinkedListIterator(const LinkedList<Type>* linkedList, Node* init) : LinkedListIteratorImpl(linkedList, init) {}

            E_ANNOTATE(RetNotIgnored)
            inline Type& get() const override {
                return *reinterpret_cast<Type*>(get0());
            }

            E_ANNOTATE(RetNotIgnored)
            inline sizetype count() const override {
                return static_cast<const LinkedList<Type>*>(linkedList)->size;
            }

            E_ANNOTATE(RetNotIgnored)
            inline bool hasNext() const override {
                return hasNext0();
            }

            E_ANNOTATE(RetNotIgnored)
            inline bool hasPrev() const override {
                return hasPrev0();
            }

            E_ANNOTATE(RetNotIgnored)
            inline bool isBegin() const override {
                return isBegin0();
            }

            E_ANNOTATE(RetNotIgnored)
            inline bool isEnd() const override {
                return isEnd0();
            }

            E_ANNOTATE(ReturnSelf)
            inline const Iterator<Type>& next() const override {
                next0();
                return *this;
            }

            E_ANNOTATE(ReturnSelf)
            inline const Iterator<Type>& next(sizetype count) const override {
                next0(count);
                return *this;
            }

            E_ANNOTATE(ReturnSelf)
            inline const Iterator<Type>& prev() const override {
                prev0();
                return *this;
            }

            E_ANNOTATE(ReturnSelf)
            inline const Iterator<Type>& prev(sizetype count) const override {
                prev0(count);
                return *this;
            }

            E_ANNOTATE(ReturnSelf)
            inline const Iterator<Type>& setBegin() const override {
                setBegin0();
                return *this;
            }

            E_ANNOTATE(ReturnSelf)
            inline const Iterator<Type>& setEnd() const override {
                setBegin0();
                return *this;
            }
        };

        inline LinkedList() : LinkedListImpl() {}

        E_INIT_LIST_CONSTRUCTOR(LinkedList, Type)
        inline LinkedList(InitializerList<Type> list) : LinkedListImpl() {
            for (auto item : list) {
                addLast(util::move(item));
            }
        }

        inline LinkedList(const LinkedList<Type>& other) : LinkedListImpl(other, copy) {}

        inline LinkedList(LinkedList<Type>&& other) noexcept : LinkedListImpl(other) {}

        inline ~LinkedList() noexcept {
            clear();
        }

        E_ANNOTATE(RetNotIgnored)
        inline sizetype getSize() const override {
            return size;
        }

        E_ANNOTATE(RetNotIgnored)
        inline bool isEmpty() const override {
            return size == 0;
        }

        E_ANNOTATE(RetNotIgnored)
        inline bool contain(const Type& value) const override {
            return indexOf(value) != E_SIZE_TYPE_MAX;
        }

        E_ANNOTATE(RetNotIgnored)
        inline LinkedListIterator iterator() const {
            return forwardIterator();
        }

        E_ANNOTATE(RetNotIgnored)
        inline ForwardIterator<LinkedListIterator> forwardIterator() const {
            return LinkedListIterator {this, (Node*) E_SIZE_TYPE_MAX};
        }

        E_ANNOTATE(RetNotIgnored)
        inline ReverseIterator<LinkedListIterator> reverseIterator() const {
            return LinkedListIterator {this, nullptr};
        }

        E_DEFINE_FOREACH_FUNC(LinkedListIterator)

        E_ANNOTATE(RetNotIgnored)
        inline sizetype indexOf(const Type& value) const override {
            return indexOf0(util::removePtrConst(&value), equal);
        }

        E_ANNOTATE(RetNotIgnored)
        inline Type& getLast() const override {
            return *reinterpret_cast<Type*>(getLast0());
        }

        E_ANNOTATE(RetNotIgnored)
        inline Type& getFirst() const override {
            return *reinterpret_cast<Type*>(getFirst0());
        }

        E_ANNOTATE(RetNotIgnored)
        inline Type& get(sizetype index) const override {
            return *reinterpret_cast<Type*>(get0(index));
        }

        E_ANNOTATE(RetNotIgnored)
        inline Type& operator[](sizetype index) const override {
            return *reinterpret_cast<Type*>(get0(index));
        }

        inline void addFirst(const Type& element) override {
            addFirst0(util::removePtrConst(&element), copy);
        }

        inline void addFirst(Type&& element) override {
            addFirst1(util::removePtrConst(&element), move);
        }

        inline void addLast(const Type& element) override {
            addLast0(util::removePtrConst(&element), copy);
        }

        inline void addLast(Type&& element) override {
            addLast1(util::removePtrConst(&element), move);
        }

        inline void push(const Type& element) override {
            return addFirst(element);
        }

        inline void push(Type&& element) override {
            return addFirst(util::move(element));
        }

        inline void add(const Type& element) override {
            addLast(element);
        }

        inline void add(Type&& element) override {
            addLast(util::move(element));
        }

        inline Type removeFirst() override {
            Type value = getFirst();
            removeFirst0(destroy);
            return value;
        }

        inline Type removeLast() override {
            Type value = getLast();
            removeLast0(destroy);
            return value;
        }

        inline Type popup() override {
            return removeFirst();
        }

        inline Type remove() override {
            return removeLast();
        }

        inline bool removeFirstIf() override {
            if (size == 0) return false;
            removeFirst0(destroy);
            return true;
        }

        inline bool removeLastIf() override {
            if (size == 0) return false;
            removeLast0(destroy);
            return true;
        }

        inline bool popupIf() override {
            return removeFirstIf();
        }

        inline bool removeIf() override {
            return removeLastIf();
        }

        inline void clear() override {
            clear0(destroy);
        }
    };
}
