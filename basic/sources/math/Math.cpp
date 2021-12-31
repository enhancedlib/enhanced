/*
 * Copyright (C) 2021 Liu Baihao.
 * This product is licensed under Enhanced License.
 *
 * This copyright disclaimer is subject to change without notice.
 *
 * This software is a free software,
 * everyone can change, copy, publication, demonstrate, use, etc.
 *
 * If you change and publication this software,
 * must credit the original software source and author's name,
 * and include this copyright disclaimer and
 * the license of this software in your software.
 *
 * This software and documentation may provide
 * third-party content, product and other information.
 * I am not responsible for any loss or damage caused
 * by your access to or use of third-party content, products, etc.
 */

#include "EnhancedBasic/math/Math.h"

using EnhancedBasic::Math::Math;

#ifdef CXX_11_OR_MORE

Math::Math() = default;

Math::~Math() = default;

#else

Math::Math() {}

Math::~Math() {}

#endif // CXX_11_OR_MORE

uint8 Math::abs(int8 number) {
    return (number < 0) ? -number : number;
}

uint16 Math::abs(int16 number) {
    return (number < 0) ? -number : number;
}

uint32 Math::abs(int32 number) {
    return (number < 0) ? -number : number;
}

uint64 Math::abs(int64 number) {
    return (number < 0) ? -number : number;
}
