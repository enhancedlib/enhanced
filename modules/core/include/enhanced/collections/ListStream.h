/*
 * Copyright (C) 2023 Liu Baihao. All rights reserved.
 *
 * Licensed under the MIT License with the Distribution Exception.
 * You may not use this file except in compliance with the License.
 *
 * THIS FILE IS PART OF THE ENHANCED SOFTWARE, and IT ALWAYS
 * PROVIDES "AS IS" WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
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

        util::Function<void ()> generator;

    public:
        class ListStreamIterator : public Iterator<Element> {
        private:
            Iterator<Element>& agent;

            mutable sizetype index = SIZE_TYPE_MAX;

            explicit ListStreamIterator(Iterator<Element>& agent) : agent(agent) {}

        public:
            E_ANNOTATE(RetNotIgnored)
            bool isBegin() const override {
                return agent.isBegin();
            }

            E_ANNOTATE(RetNotIgnored)
            bool isEnd() const override {
                if (index == agent.count() + 1) {
                    generator();
                    return agent.assume();
                }
                return false;
            }

            E_ANNOTATE(RetNotIgnored)
            bool hasNext() const override {
                if (index == agent.count()) {
                    generator();
                    return agent.hasNext();
                }
                return true;
            }

            E_ANNOTATE(ReturnSelf)
            const Iterator<Element>& next() const override {
                if (isEnd()) throw exceptions::InvalidStateException("The iterator is at the end of the list");
                ++index;
                return agent.next();
            }

            E_ANNOTATE(ReturnSelf)
            const Iterator<Element>& prev() const override {
                if (isBegin()) throw exceptions::InvalidStateException("The iterator is at the begin of the list");
                --index;
                return agent.prev();
            }

            E_ANNOTATE(RetNotIgnored)
            Element& get() const override {
                return agent.get();
            }

            void reset() const override {
                agent.reset();
                index = SIZE_TYPE_MAX;
            }

            E_ANNOTATE(RetNotIgnored)
            sizetype count() const override {
                return agent.count();
            }

            E_ANNOTATE(RetNotIgnored)
            sizetype getIndex() const {
                return index;
            }
        };

        ListStream() = default;

        E_ANNOTATE(RetNotIgnored)
        inline ListStreamIterator iterator() const {
            return ListStreamIterator {list.iterator()};
        }

        E_ANNOTATE(RetNotIgnored)
        inline ListStreamIterator begin() const {
            auto it = iterator();
            it.next();
            return it;
        }

        E_ANNOTATE(RetNotIgnored)
        inline byte end() const {
            return 0;
        }
    };
}
