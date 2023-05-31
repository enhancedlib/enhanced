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