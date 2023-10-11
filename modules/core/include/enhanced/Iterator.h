/*
 * This file is part of Enhanced Framework.
 *
 * Copyright (C) 2023 sharedwonder (Liu Baihao). All rights reserved.
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
 *    be used to endorse or promote products derived from the Software.
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
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/Traits.h>

#define E_DEFINE_FOREACH_FUNC(TYPE) \
    E_RET_NO_DISCARD() \
    inline ForEachIterator<TYPE> begin() const noexcept { \
        auto it = iterator(); \
        it.step(); \
        return it; \
    } \
    E_RET_NO_DISCARD() \
    inline constexpr byte end() const noexcept { \
        return 0; \
    }

namespace enhanced {
    template <typename Type>
    class Iterator {
        E_CLASS(Iterator)

    E_CLASS_BODY
        using Element = Type;

        virtual ~Iterator() noexcept = default;

        /*!
         * Gets the current element.
         */
        E_RET_NO_DISCARD()
        virtual Type& get() const = 0;

        /*!
         * Gets the number of elements.
         */
        E_RET_NO_DISCARD()
        virtual sizetype count() const = 0;

        E_RET_NO_DISCARD()
        virtual bool hasNext() const = 0;

        E_RET_NO_DISCARD()
        virtual bool hasPrev() const = 0;

        E_RET_NO_DISCARD()
        virtual bool isBegin() const = 0;

        E_RET_NO_DISCARD()
        virtual bool isEnd() const = 0;

        /*!
         * Let the iterator pointer return to the previous element.
         */
        E_RETURN("self")
        virtual const Iterator<Type>& prev() const = 0;

        E_RETURN("self")
        virtual const Iterator<Type>& prev(sizetype count) const = 0;

        /*!
         * Let the iterator pointer return to the next element.
         */
        E_RETURN("self")
        virtual const Iterator<Type>& next() const = 0;

        E_RETURN("self")
        virtual const Iterator<Type>& next(sizetype count) const = 0;

        /*!
         * Let the iterator pointer return to the begin.
         */
        E_RETURN("self")
        virtual const Iterator<Type>& setBegin() const = 0;

        /*!
         * Let the iterator pointer return to the end.
         */
        E_RETURN("self")
        virtual const Iterator<Type>& setEnd() const = 0;
    };

    template <typename Iter>
    requires isBaseOf<Iterator<typename Iter::Element>, Iter>
    class DirectedIterator : public Iter {
        E_CLASS(DirectedIterator)

    E_CLASS_BODY
        using BaseIterator = Iter;

        template <typename... Args>
        inline DirectedIterator(Args&&... args) : Iter(forward<Args>(args)...) {}

        virtual const DirectedIterator& step() const = 0;

        virtual const DirectedIterator& step(sizetype count) const = 0;

        virtual const DirectedIterator& back() const = 0;

        virtual const DirectedIterator& back(sizetype count) const = 0;

        virtual const DirectedIterator& reset() const = 0;

        E_RET_NO_DISCARD()
        virtual bool continueable() const = 0;
    };

    template <typename Iter>
    class ForwardIterator : public DirectedIterator<Iter> {
        E_CLASS(ForwardIterator)

    E_CLASS_BODY
        template <typename... Args>
        inline ForwardIterator(Args&&... args) : DirectedIterator<Iter>(forward<Args>(args)...) {}

        E_RETURN("self")
        inline const ForwardIterator& step() const {
            Iter::next();
            return *this;
        }

        E_RETURN("self")
        inline const ForwardIterator& step(sizetype count) const {
            Iter::next(count);
            return *this;
        }

        inline const ForwardIterator& back() const {
            Iter::prev();
            return *this;
        }

        inline const ForwardIterator& back(sizetype count) const {
            Iter::prev(count);
            return *this;
        }

        E_RETURN("self")
        inline const ForwardIterator& reset() const {
            Iter::setBegin();
            return *this;
        }

        E_RET_NO_DISCARD()
        inline bool continueable() const {
            return !Iter::isEnd();
        }
    };

    template <typename Iter>
    class ReverseIterator : public DirectedIterator<Iter> {
        E_CLASS(ReverseIterator)

    E_CLASS_BODY
        template <typename... Args>
        inline ReverseIterator(Args&&... args) : DirectedIterator<Iter>(forward<Args>(args)...) {}

        E_RETURN("self")
        inline const ReverseIterator& step() const {
            Iter::prev();
            return *this;
        }

        E_RETURN("self")
        inline const ReverseIterator& step(sizetype count) const {
            Iter::prev(count);
            return *this;
        }

        E_RETURN("self")
        inline const ReverseIterator& back() const {
            Iter::next();
            return *this;
        }

        E_RETURN("self")
        inline const ReverseIterator& back(sizetype count) const {
            Iter::next(count);
            return *this;
        }

        E_RETURN("self")
        inline const ReverseIterator& reset() const {
            Iter::setEnd();
            return *this;
        }

        E_RET_NO_DISCARD()
        inline bool continueable() const {
            return !Iter::isBegin();
        }
    };

    template <typename Iter>
    requires isBaseOf<DirectedIterator<typename Iter::BaseIterator>, Iter>
    class ForEachIterator : public Iter {
        E_CLASS(ForEachIterator)

    E_CLASS_BODY
        inline ForEachIterator(Iter&& iter) : Iter(move(iter)) {}

        inline void operator++() const {
            Iter::step();
        }

        inline auto operator*() const -> decltype(Iter::get()) {
            return Iter::get();
        }

        inline bool operator!=(byte) const {
            return Iter::continueable();
        }
    };
}
