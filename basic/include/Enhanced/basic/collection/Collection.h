/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 * This software is licensed under Enhanced License.
 *
 * This copyright notice is subject to change without notice.
 *
 * This software is a free software, everyone can change,
 * copy, publication, demonstrate, use, etc.
 *
 * This software and documentation may provide
 * third-party content, product and other information.
 * The Licensor is not responsible for any loss or damage
 * caused by your access to or use of third-party content, products, etc.
 *
 * For any loss or damage caused by this software,
 * the licensor may provide possible solutions,
 * but it does not mean that the licensor will definitely solve the problem.
 * In no event shall the licensor be liable for any claims,
 * damages or other liabilities.
 *
 * You should see a copy of Enhanced License in this software, if not, visit
 * <https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt>
 */

#pragma once

#include "Enhanced/core/defines.h"
#include "Enhanced/core/types.h"
#include "Enhanced/core/annotations.h"

#include "Enhanced/basic/core/Iterable.h"

#ifdef CXX_LANGUAGE // C++ language

namespace Enhanced::basic::collection {
    template <typename Type>
    struct Collection : public core::Iterable<Type> {
        virtual ~Collection() noexcept = default;

        RetNotIgnored()
        virtual Size getLength() const = 0;

        RetNotIgnored()
        virtual bool isEmpty() const = 0;

        RetNotIgnored()
        virtual bool contain(const Type& value) const = 0;

        RetRequiresRelease()
        virtual Collection<Type>* copy() const = 0;
    };
}

#endif // CXX_LANGUAGE
