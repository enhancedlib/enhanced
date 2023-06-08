/*
 * This file is part of Enhanced Framework.
 *
 * Copyright (C) 2023 Liu Baihao (sharedwonder). All rights reserved.
 *
 * Permission is hereby granted, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software,
 * including without limitation the rights to use, copy, modify, merge,
 * distribute, subject to the following restrictions:
 *
 * 1. The above copyright notice and this permission notice shall be included in
 *    all copies of the Software and modified versions.
 *
 * 2. You may not charge any fees or receive other compensation for the
 *    distribution of the Software.
 *
 * 3. You may not misrepresent the source of the Software, and you may not claim
 *    that you wrote the original version.
 *
 * 4. If you use this Software in your product, you should indicate the it in
 *    the product documentation.
 *
 * Unless you have obtained the written consent of the copyright holders,
 * you may not break these restrictions.
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
#include <enhanced/util/Traits.h>

#define E_DEFINE_FOREACH_FUNC(TYPE) \
    E_ANNOTATE(RetNotIgnored) \
    inline ForEachIterator<TYPE> begin() const noexcept { \
        auto it = forwardIterator(); \
        it.step(); \
        return it; \
    } \
    E_ANNOTATE(RetNotIgnored) \
    inline constexpr byte end() const noexcept { \
        return 0; \
    }

#ifdef E_SM_MACRO_NO_PREFIX_ALIAS
    #define DEFINE_FOREACH_FUNC E_DEFINE_FOREACH_FUNC
#endif

namespace enhanced {
    template <typename Type>
    struct Iterator {
        using Element = Type;

        virtual ~Iterator() noexcept = default;

        /*!
         * Gets the current element.
         */
        E_ANNOTATE(RetNotIgnored)
        virtual Type& get() const = 0;

        /*!
         * Gets the number of elements.
         */
        E_ANNOTATE(RetNotIgnored)
        virtual sizetype count() const = 0;

        E_ANNOTATE(RetNotIgnored)
        virtual bool hasNext() const = 0;

        E_ANNOTATE(RetNotIgnored)
        virtual bool hasPrev() const = 0;

        E_ANNOTATE(RetNotIgnored)
        virtual bool isBegin() const = 0;

        E_ANNOTATE(RetNotIgnored)
        virtual bool isEnd() const = 0;

        /*!
         * Let the iterator pointer return to the next element.
         */
        E_ANNOTATE(ReturnSelf)
        virtual const Iterator<Type>& next() const = 0;

        E_ANNOTATE(ReturnSelf)
        virtual const Iterator<Type>& next(sizetype count) const = 0;

        /*!
         * Let the iterator pointer return to the previous element.
         */
        E_ANNOTATE(ReturnSelf)
        virtual const Iterator<Type>& prev() const = 0;

        E_ANNOTATE(ReturnSelf)
        virtual const Iterator<Type>& prev(sizetype count) const = 0;

        /*!
         * Let the iterator pointer return to the begin.
         */
        E_ANNOTATE(ReturnSelf)
        virtual const Iterator<Type>& setBegin() const = 0;

        /*!
         * Let the iterator pointer return to the end.
         */
        E_ANNOTATE(ReturnSelf)
        virtual const Iterator<Type>& setEnd() const = 0;
    };

    template <typename Iter>
    requires util::isBaseOf<Iterator<typename Iter::Element>, Iter>
    struct DirectedIterator : Iter {
        template <typename... Args>
        inline DirectedIterator(Args&&... args) : Iter(args...) {}

        virtual const DirectedIterator& step() const = 0;

        virtual const DirectedIterator& step(sizetype count) const = 0;

        virtual const DirectedIterator& back() const = 0;

        virtual const DirectedIterator& back(sizetype count) const = 0;

        virtual const DirectedIterator& reset() const = 0;

        E_ANNOTATE(RetNotIgnored)
        virtual bool continueable() const = 0;
    };

    template <typename Iter>
    struct ForwardIterator : DirectedIterator<Iter> {
        template <typename... Args>
        inline ForwardIterator(Args&&... args) : DirectedIterator<Iter>(args...) {}

        E_ANNOTATE(ReturnSelf)
        inline const ForwardIterator& step() const {
            Iter::next();
            return *this;
        }

        E_ANNOTATE(ReturnSelf)
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

        E_ANNOTATE(ReturnSelf)
        inline const ForwardIterator& reset() const {
            Iter::setBegin();
            return *this;
        }

        E_ANNOTATE(RetNotIgnored)
        inline bool continueable() const {
            return !Iter::isEnd();
        }
    };

    template <typename Iter>
    struct ReverseIterator : DirectedIterator<Iter> {
        template <typename... Args>
        inline ReverseIterator(Args&&... args) : DirectedIterator<Iter>(args...) {}

        E_ANNOTATE(ReturnSelf)
        inline const ReverseIterator& step() const {
            Iter::prev();
            return *this;
        }

        E_ANNOTATE(ReturnSelf)
        inline const ReverseIterator& step(sizetype count) const {
            Iter::prev(count);
            return *this;
        }

        E_ANNOTATE(ReturnSelf)
        inline const ReverseIterator& back() const {
            Iter::next();
            return *this;
        }

        E_ANNOTATE(ReturnSelf)
        inline const ReverseIterator& back(sizetype count) const {
            Iter::next(count);
            return *this;
        }

        E_ANNOTATE(ReturnSelf)
        inline const ReverseIterator& reset() const {
            Iter::setEnd();
            return *this;
        }

        E_ANNOTATE(RetNotIgnored)
        inline bool continueable() const {
            return !Iter::isBegin();
        }
    };

    template <typename Iter>
    struct ForEachIterator : ForwardIterator<Iter> {
        inline ForEachIterator(ForwardIterator<Iter> iter) : ForwardIterator<Iter>(iter) {}

        inline void operator++() const {
            ForwardIterator<Iter>::step();
        }

        inline auto operator*() const -> decltype(Iter::get()) {
            return Iter::get();
        }

        inline bool operator!=(byte) const {
            return ForwardIterator<Iter>::continueable();
        }
    };
}
