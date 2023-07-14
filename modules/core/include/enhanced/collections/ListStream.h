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
 *    distribution of the Software, except for distributing modified versions and
 *    products that use the Software.
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
#include <enhanced/CoreAPI.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/Traits.h>
#include <enhanced/Iterable.h>
#include <enhanced/Iterator.h>
#include <enhanced/Function.h>
#include <enhanced/collections/List.h>
#include <enhanced/exceptions/OperationException.h>

namespace enhanced::collections {
    template <template <typename> typename ListType, typename Element>
    requires isBaseOf<List<Element>, ListType<Element>> && (!isAbstractClass<ListType<Element>>)
    class ListStream : public Iterable<ListStream<ListType, Element>> {
        E_CLASS(ListStream)

    E_CLASS_BODY
    private:
        ListType<Element> list {};

        const Function<bool (ListType<Element>&)> generator;

        bool isCompleted = false;

    public:
        class ListStreamIterator : public Iterator<Element> {
            E_CLASS(ListStreamIterator)

        E_CLASS_BODY
        private:
            ListStream* stream;

            decltype(stream->list.iterator()) delegate;

            mutable sizetype index = E_SIZE_TYPE_MAX;

        public:
            explicit ListStreamIterator(const ListStream* stream) : stream(const_cast<ListStream*>(stream)), delegate(stream->list.iterator()) {}

            E_RET_NO_DISCARD()
            Element& get() const override {
                return delegate.get();
            }

            E_RET_NO_DISCARD()
            sizetype count() const override {
                return delegate.count();
            }

            E_RET_NO_DISCARD()
            bool isBegin() const override {
                return index == E_SIZE_TYPE_MAX;
            }

            E_RET_NO_DISCARD()
            bool isEnd() const override {
                return index == count();
            }

            E_RET_NO_DISCARD()
            bool hasPrev() const override {
                return index != E_SIZE_TYPE_MAX;
            }

            E_RET_NO_DISCARD()
            bool hasNext() const override {
                return index == E_SIZE_TYPE_MAX || index < count();
            }

            E_RETURN_SELF()
            const Iterator<Element>& prev() const override {
                if (isBegin()) throw exceptions::OperationException("The iterator is at the begin of the list");
                --index;
                return delegate.prev();
            }

            E_RETURN_SELF()
            const Iterator<Element>& prev(sizetype count) const override {
                if (count > (index + 1)) throw exceptions::OperationException("Out of range");
                index -= count;
                return delegate.prev(count);
            }

            E_RETURN_SELF()
            const Iterator<Element>& next() const override {
                if (isEnd()) throw exceptions::OperationException("The iterator is at the end of the list");
                if (!stream->isCompleted && (count() == 0 || index == count() - 1)) {
                    if (!stream->generator(stream->list)) stream->isCompleted = true;
                }

                if (isBegin()) index = 0;
                else ++index;
                return delegate.next();
            }

            E_RETURN_SELF()
            const Iterator<Element>& next(sizetype count) const override {
                sizetype generationCount = ((index != E_SIZE_TYPE_MAX) ? index + 1 : 0) + count - this->count();
                if (!stream->isCompleted) {
                    while (--generationCount > 0) {
                        if (!stream->generator(stream->list)) {
                            stream->isCompleted = true;
                            break;
                        }
                    }
                }

                if (isBegin()) index = count - 1;
                else index += count;
                return delegate.next(count);
            }

            E_RETURN_SELF()
            const Iterator<Element>& setBegin() const override {
                if (!stream->isCompleted) throw exceptions::OperationException("ListStream is not completed");
                delegate.setBegin();
                index = E_SIZE_TYPE_MAX;
                return *this;
            }

            E_RETURN_SELF()
            const Iterator<Element>& setEnd() const override {
                if (!stream->isCompleted) throw exceptions::OperationException("ListStream is not completed");
                delegate.setEnd();
                index = count() + 1;
                return *this;
            }

            E_RET_NO_DISCARD()
            sizetype indexOf() const {
                return index;
            }
        };

        template <typename Type>
        ListStream(Type generator)
        requires testValid<decltype(Function<bool (ListType<Element>&)>(move(generator)))> : generator(move(generator)) {}

        E_RET_NO_DISCARD()
        inline ListStreamIterator iterator() const noexcept {
            return ListStreamIterator {this};
        }

        E_RET_NO_DISCARD()
        inline ForwardIterator<ListStreamIterator> forwardIterator() const noexcept {
            return ListStreamIterator {this};
        }

        inline const ListType<Element>& complete() const {
            if (!isCompleted) {
                auto iter = iterator();
                while (!isCompleted) {
                    iter.next();
                }
            }
            return list;
        }
    };
}
