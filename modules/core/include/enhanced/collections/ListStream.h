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
#include <enhanced/Traits.h>
#include <enhanced/Iterator.h>
#include <enhanced/Function.h>
#include <enhanced/collections/List.h>
#include <enhanced/exceptions/InvalidStateException.h>

namespace enhanced::collections {
    // TODO: Testing

    template <template <typename> typename ListType, typename Element>
    requires isBaseOf<List<Element>, ListType<Element>> && (!isAbstractClass<ListType<Element>>)
    class ListStream {
    private:
        const ListType<Element> list {};

        Function<void ()> generator;

    public:
        class ListStreamIterator : public Iterator<Element> {
        private:
            Iterator<Element>& agent;

            mutable sizetype index = E_SIZE_TYPE_MAX;

            explicit ListStreamIterator(Iterator<Element>& agent) : agent(agent) {}

        public:
            E_RET_NO_DISCARD()
            bool isBegin() const override {
                return agent.isBegin();
            }

            E_RET_NO_DISCARD()
            bool isEnd() const override {
                if (index == agent.count() + 1) {
                    generator();
                    return agent.assume();
                }
                return false;
            }

            E_RET_NO_DISCARD()
            bool hasNext() const override {
                if (index == agent.count()) {
                    generator();
                    return agent.hasNext();
                }
                return true;
            }

            E_RETURN_SELF()
            const Iterator<Element>& next() const override {
                if (isEnd()) throw exceptions::InvalidStateException("The iterator is at the end of the list");
                ++index;
                return agent.next();
            }

            E_RETURN_SELF()
            const Iterator<Element>& prev() const override {
                if (isBegin()) throw exceptions::InvalidStateException("The iterator is at the begin of the list");
                --index;
                return agent.prev();
            }

            E_RET_NO_DISCARD()
            Element& get() const override {
                return agent.get();
            }

            void reset() const override {
                agent.reset();
                index = E_SIZE_TYPE_MAX;
            }

            E_RET_NO_DISCARD()
            sizetype count() const override {
                return agent.count();
            }

            E_RET_NO_DISCARD()
            sizetype getIndex() const {
                return index;
            }
        };

        ListStream() = default;

        E_RET_NO_DISCARD()
        inline ListStreamIterator iterator() const {
            return ListStreamIterator {list.iterator()};
        }

        E_RET_NO_DISCARD()
        inline ListStreamIterator begin() const {
            auto it = iterator();
            it.next();
            return it;
        }

        E_RET_NO_DISCARD()
        inline byte end() const {
            return 0;
        }
    };
}
