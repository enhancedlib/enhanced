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

#include <enhanced/Defines.h>
#include <enhanced/ExportCore.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/Iterator.h>
#include <enhanced/collections/List.h>
#include <enhanced/util/Traits.h>
#include <enhanced/util/Function.h>
#include <enhanced/exceptions/InvalidStateException.h>

namespace enhanced::collections {
    // TODO: Testing

    template <template <typename> typename ListType, typename Element>
    requires util::isBaseOf<List<Element>, ListType<Element>> && (!util::isAbstractClass<ListType<Element>>)
    class ListStream {
    private:
        const ListType<Element> list {};

        util::Function<void()> generator;

    public:
        class ListStreamIterator : public Iterator<Element> {
        private:
            Iterator<Element>& agent;

            mutable sizetype index = INVALID_SIZE;

            explicit ListStreamIterator(Iterator<Element>& agent) : agent(agent) {}

        public:
            $NoIgnoreReturn
            bool isBegin() const override {
                return agent.isBegin();
            }

            $NoIgnoreReturn
            bool isEnd() const override {
                if (index == agent.count() + 1) {
                    generator();
                    return agent.isValid();
                }
                return false;
            }

            $NoIgnoreReturn
            bool hasNext() const override {
                if (index == agent.count()) {
                    generator();
                    return agent.hasNext();
                }
                return true;
            }

            $RetSelf
            const Iterator<Element>& next() const override {
                if (isEnd()) throw exceptions::InvalidStateException("The iterator is at the end of the list");
                ++index;
                return agent.next();
            }

            $RetSelf
            const Iterator<Element>& prev() const override {
                if (isBegin()) throw exceptions::InvalidStateException("The iterator is at the begin of the list");
                --index;
                return agent.prev();
            }

            $NoIgnoreReturn
            Element& get() const override {
                return agent.get();
            }

            void reset() const override {
                agent.reset();
                index = INVALID_SIZE;
            }

            $NoIgnoreReturn
            sizetype count() const override {
                return agent.count();
            }

            $NoIgnoreReturn
            sizetype getIndex() const {
                return index;
            }
        };

        ListStream() = default;

        $NoIgnoreReturn
        inline ListStreamIterator iterator() const {
            return ListStreamIterator {list.iterator()};
        }

        $NoIgnoreReturn
        inline ListStreamIterator begin() const {
            auto it = iterator();
            it.next();
            return it;
        }

        $NoIgnoreReturn
        inline byte end() const {
            return 0;
        }
    };
}
