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

#include <enhanced/util/SharedPtr.h>

#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/Memory.h>

using enhanced::sizetype;

namespace enhancedInternal::util {
    SharedPtrImpl::SharedPtrImpl(void* ptr) : referenceCount(ptr != nullptr ? new sizetype(1) : nullptr), pointer(ptr), end(ptr) {}

    SharedPtrImpl::SharedPtrImpl(void* ptr, void* end) : referenceCount(ptr != nullptr ? new sizetype(1) : nullptr), pointer(ptr), end(end) {}

    SharedPtrImpl::SharedPtrImpl(const SharedPtrImpl& other) noexcept :
        referenceCount(other.referenceCount), pointer(other.pointer), end(other.end) {
        if (other.referenceCount != nullptr) ++(*other.referenceCount);
    }

    SharedPtrImpl::SharedPtrImpl(SharedPtrImpl&& other) noexcept :
        referenceCount(other.referenceCount), pointer(other.pointer), end(other.end) {
        other.pointer = nullptr;
        other.end = nullptr;
        other.referenceCount = nullptr;
    }

    void SharedPtrImpl::release0(OpDestroy opDestroy) const noexcept {
        if (referenceCount != nullptr && (--(*referenceCount)) == 0) {
            opDestroy(pointer, end);
            delete referenceCount;
            referenceCount = nullptr;
        }
    }

    void SharedPtrImpl::assign0(const SharedPtrImpl& other, OpDestroy opDestroy) noexcept {
        release0(opDestroy);

        pointer = other.pointer;
        end = other.end;
        referenceCount = other.referenceCount;

        if (referenceCount != nullptr) ++(*referenceCount);
    }

    void SharedPtrImpl::assign0(SharedPtrImpl&& other, OpDestroy opDestroy) noexcept {
        release0(opDestroy);

        pointer = other.pointer;
        end = other.end;
        referenceCount = other.referenceCount;

        other.pointer = nullptr;
        other.end = nullptr;
        other.referenceCount = nullptr;
    }
}
