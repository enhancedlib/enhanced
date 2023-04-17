/*
 * Copyright (C) 2023 Liu Baihao. All rights reserved.
 *
 * Licensed under the MIT License with "Fairness" Exception.
 *
 * You may not use this file except in compliance with the License.
 *
 * This file is part of The Enhanced Software, and IT ALWAYS
 * PROVIDES "AS IS" WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#pragma once

#include "enhanced/Iterator.h"
#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/util/Traits.h>

#define E_DEFINE_FOREACH_FUNC(TYPE) \
    [[RetNotIgnored]] \
    inline ForEachIterator<TYPE> begin() const noexcept { \
        auto it = forwardIterator(); \
        it.step(); \
        return it; \
    } \
    [[RetNotIgnored]] \
    inline constexpr byte end() const noexcept { \
        return 0; \
    }

#ifdef ENHANCED_MACRO_NO_PREFIX_ALIAS
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
        [[RetNotIgnored]]
        virtual Type& get() const = 0;

        /*!
         * Gets the number of elements.
         */
        [[RetNotIgnored]]
        virtual sizetype count() const = 0;

        [[RetNotIgnored]]
        virtual bool hasNext() const = 0;

        [[RetNotIgnored]]
        virtual bool hasPrev() const = 0;

        [[RetNotIgnored]]
        virtual bool isBegin() const = 0;

        [[RetNotIgnored]]
        virtual bool isEnd() const = 0;

        /*!
         * Let the iterator pointer return to the next element.
         */
        [[ReturnSelf]]
        virtual const Iterator<Type>& next() const = 0;

        [[ReturnSelf]]
        virtual const Iterator<Type>& next(sizetype count) const = 0;

        /*!
         * Let the iterator pointer return to the previous element.
         */
        [[ReturnSelf]]
        virtual const Iterator<Type>& prev() const = 0;

        [[ReturnSelf]]
        virtual const Iterator<Type>& prev(sizetype count) const = 0;

        /*!
         * Let the iterator pointer return to the begin.
         */
        [[ReturnSelf]]
        virtual const Iterator<Type>& setBegin() const = 0;

        /*!
         * Let the iterator pointer return to the end.
         */
        [[ReturnSelf]]
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

        [[RetNotIgnored]]
        virtual bool continueable() const = 0;
    };

    template <typename Iter>
    struct ForwardIterator : DirectedIterator<Iter> {
        template <typename... Args>
        inline ForwardIterator(Args&&... args) : DirectedIterator<Iter>(args...) {}

        [[ReturnSelf]]
        inline const ForwardIterator& step() const {
            Iter::next();
            return *this;
        }

        [[ReturnSelf]]
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

        [[ReturnSelf]]
        inline const ForwardIterator& reset() const {
            Iter::setBegin();
            return *this;
        }

        [[RetNotIgnored]]
        inline bool continueable() const {
            return !Iter::isEnd();
        }
    };

    template <typename Iter>
    struct ReverseIterator : DirectedIterator<Iter> {
        template <typename... Args>
        inline ReverseIterator(Args&&... args) : DirectedIterator<Iter>(args...) {}

        [[ReturnSelf]]
        inline const ReverseIterator& step() const {
            Iter::prev();
            return *this;
        }

        [[ReturnSelf]]
        inline const ReverseIterator& step(sizetype count) const {
            Iter::prev(count);
            return *this;
        }

        [[ReturnSelf]]
        inline const ReverseIterator& back() const {
            Iter::next();
            return *this;
        }

        [[ReturnSelf]]
        inline const ReverseIterator& back(sizetype count) const {
            Iter::next(count);
            return *this;
        }

        [[ReturnSelf]]
        inline const ReverseIterator& reset() const {
            Iter::setEnd();
            return *this;
        }

        [[RetNotIgnored]]
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
