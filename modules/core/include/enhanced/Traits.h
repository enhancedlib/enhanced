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
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/Warnings.h>

#define _FUNC_TEMPLATE_CV(CALLING_CONVENTION, CALL_OPT, REF_OPT, NOEXCEPT_OPT) \
    _TEMPLATE(CALLING_CONVENTION, CALL_OPT, , REF_OPT, NOEXCEPT_OPT) \
    _TEMPLATE(CALLING_CONVENTION, CALL_OPT, const, REF_OPT, NOEXCEPT_OPT) \
    _TEMPLATE(CALLING_CONVENTION, CALL_OPT, volatile, REF_OPT, NOEXCEPT_OPT) \
    _TEMPLATE(CALLING_CONVENTION, CALL_OPT, const volatile, REF_OPT, NOEXCEPT_OPT)

#define _FUNC_TEMPLATE_CV_REF(CALLING_CONVENTION, CALL_OPT, NOEXCEPT_OPT) \
    _FUNC_TEMPLATE_CV(CALLING_CONVENTION, CALL_OPT, , NOEXCEPT_OPT) \
    _FUNC_TEMPLATE_CV(CALLING_CONVENTION, CALL_OPT, &, NOEXCEPT_OPT) \
    _FUNC_TEMPLATE_CV(CALLING_CONVENTION, CALL_OPT, &&, NOEXCEPT_OPT)

#define _FUNC_TEMPLATE_CV_REF_NOEXCEPT(CALLING_CONVENTION, CALL_OPT) \
    _FUNC_TEMPLATE_CV_REF(CALLING_CONVENTION, CALL_OPT, ) \
    _FUNC_TEMPLATE_CV_REF(CALLING_CONVENTION, CALL_OPT, noexcept)

// ======================================================================

#define _FUNC_TEMPLATE_PTR(CALLING_CONVENTION, CALL_OPT, NOEXCEPT_OPT) \
    _TEMPLATE(, CALLING_CONVENTION, CALL_OPT, NOEXCEPT_OPT) \
    _TEMPLATE(const, CALLING_CONVENTION, CALL_OPT, NOEXCEPT_OPT) \
    _TEMPLATE(volatile, CALLING_CONVENTION, CALL_OPT, NOEXCEPT_OPT) \
    _TEMPLATE(const volatile, CALLING_CONVENTION, CALL_OPT, NOEXCEPT_OPT)

#define _FUNC_TEMPLATE_PTR_NOEXCEPT(CALLING_CONVENTION, CALL_OPT) \
    _FUNC_TEMPLATE_PTR(CALLING_CONVENTION, CALL_OPT, ) \
    _FUNC_TEMPLATE_PTR(CALLING_CONVENTION, CALL_OPT, noexcept)

// ======================================================================

#define _FUNC_TEMPLATE_MEMBER_PTR(CALLING_CONVENTION, CALL_OPT, CV_OPT, REF_OPT, NOEXCEPT_OPT) \
    _TEMPLATE(, CALLING_CONVENTION, CALL_OPT, CV_OPT, REF_OPT, NOEXCEPT_OPT) \
    _TEMPLATE(const, CALLING_CONVENTION, CALL_OPT, CV_OPT, REF_OPT, NOEXCEPT_OPT) \
    _TEMPLATE(volatile, CALLING_CONVENTION, CALL_OPT, CV_OPT, REF_OPT, NOEXCEPT_OPT) \
    _TEMPLATE(const volatile, CALLING_CONVENTION, CALL_OPT, CV_OPT, REF_OPT, NOEXCEPT_OPT)

#define _FUNC_TEMPLATE_MEMBER_PTR_CV(CALLING_CONVENTION, CALL_OPT, REF_OPT, NOEXCEPT_OPT) \
    _FUNC_TEMPLATE_MEMBER_PTR(CALLING_CONVENTION, CALL_OPT, , REF_OPT, NOEXCEPT_OPT) \
    _FUNC_TEMPLATE_MEMBER_PTR(CALLING_CONVENTION, CALL_OPT, const, REF_OPT, NOEXCEPT_OPT) \
    _FUNC_TEMPLATE_MEMBER_PTR(CALLING_CONVENTION, CALL_OPT, volatile, REF_OPT, NOEXCEPT_OPT) \
    _FUNC_TEMPLATE_MEMBER_PTR(CALLING_CONVENTION, CALL_OPT, const volatile, REF_OPT, NOEXCEPT_OPT)

#define _FUNC_TEMPLATE_MEMBER_PTR_CV_REF(CALLING_CONVENTION, CALL_OPT, NOEXCEPT_OPT) \
    _FUNC_TEMPLATE_MEMBER_PTR_CV(CALLING_CONVENTION, CALL_OPT, , NOEXCEPT_OPT) \
    _FUNC_TEMPLATE_MEMBER_PTR_CV(CALLING_CONVENTION, CALL_OPT, &, NOEXCEPT_OPT) \
    _FUNC_TEMPLATE_MEMBER_PTR_CV(CALLING_CONVENTION, CALL_OPT, &&, NOEXCEPT_OPT)

#define _FUNC_TEMPLATE_MEMBER_PTR_CV_REF_NOEXCEPT(CALLING_CONVENTION, CALL_OPT) \
    _FUNC_TEMPLATE_MEMBER_PTR_CV_REF(CALLING_CONVENTION, CALL_OPT, ) \
    _FUNC_TEMPLATE_MEMBER_PTR_CV_REF(CALLING_CONVENTION, CALL_OPT, noexcept)

// ======================================================================

#define _FUNC_TEMPLATE_CDECL(SUFFIX) _FUNC_TEMPLATE_ ## SUFFIX(enhanced::CallingConvention::Cdecl, E_CDECL)

#if defined(E_SM_ARCH_X86) && !defined(E_SM_MS_CLR)
    #define _FUNC_TEMPLATE_FASTCALL(SUFFIX) _FUNC_TEMPLATE_ ## SUFFIX(enhanced::CallingConvention::Fastcall, E_FASTCALL)
#else
    #define _FUNC_TEMPLATE_FASTCALL(SUFFIX)
#endif

#ifdef E_SM_ARCH_X86
    #define _FUNC_TEMPLATE_STDCALL(SUFFIX) _FUNC_TEMPLATE_ ## SUFFIX(enhanced::CallingConvention::Stdcall, E_STDCALL)
    #define _FUNC_TEMPLATE_THISCALL(SUFFIX) _FUNC_TEMPLATE_ ## SUFFIX(enhanced::CallingConvention::Thiscall, E_THISCALL)
#else
    #define _FUNC_TEMPLATE_STDCALL(SUFFIX)
    #define _FUNC_TEMPLATE_THISCALL(SUFFIX)
#endif

#ifdef E_SM_COMPATIBILITY_MS
    #ifdef E_SM_MS_CLR
        #define _FUNC_TEMPLATE_VECTORCALL(SUFFIX)
        #define _FUNC_TEMPLATE_CLRCALL(SUFFIX) _FUNC_TEMPLATE_ ## SUFFIX(enhanced::CallingConvention::Clrcall, E_CLRCALL)
    #elif (defined(E_SM_ARCH_X86) && _M_IX86_FP >= 2) || defined(E_SM_ARCH_X64)
        #define _FUNC_TEMPLATE_VECTORCALL(SUFFIX) _FUNC_TEMPLATE_ ## SUFFIX(enhanced::CallingConvention::Vectorcall, E_VECTORCALL)
        #define _FUNC_TEMPLATE_CLRCALL(SUFFIX)
    #endif
#else
    #define _FUNC_TEMPLATE_VECTORCALL(SUFFIX)
    #define _FUNC_TEMPLATE_CLRCALL(SUFFIX)
#endif

// ======================================================================

#define _CV_OPT_TEMPLATE \
    _TEMPLATE(E_EMPTY_MACRO_ARG) \
    _TEMPLATE(const) \
    _TEMPLATE(volatile) \
    _TEMPLATE(const volatile)

#define _BASE_INT_TYPE_TEMPLATE \
    _TEMPLATE(char) \
    _TEMPLATE(short) \
    _TEMPLATE(int) \
    _TEMPLATE(long) \
    _TEMPLATE(long long)

#define _FUNC_TEMPLATE \
    _FUNC_TEMPLATE_CDECL(CV_REF_NOEXCEPT) \
    _FUNC_TEMPLATE_FASTCALL(CV_REF_NOEXCEPT) \
    _FUNC_TEMPLATE_STDCALL(CV_REF_NOEXCEPT) \
    _FUNC_TEMPLATE_VECTORCALL(CV_REF_NOEXCEPT) \
    _FUNC_TEMPLATE_CLRCALL(CV_REF_NOEXCEPT)

#define _FUNC_WITH_VARARGS_TEMPLATE \
    _FUNC_TEMPLATE_CDECL(CV_REF_NOEXCEPT)

#define _FUNC_PTR_TEMPLATE \
    _FUNC_TEMPLATE_CDECL(PTR_NOEXCEPT) \
    _FUNC_TEMPLATE_FASTCALL(PTR_NOEXCEPT) \
    _FUNC_TEMPLATE_STDCALL(PTR_NOEXCEPT) \
    _FUNC_TEMPLATE_VECTORCALL(PTR_NOEXCEPT) \
    _FUNC_TEMPLATE_CLRCALL(PTR_NOEXCEPT)

#define _FUNC_WITH_VARARGS_PTR_TEMPLATE \
    _FUNC_TEMPLATE_CDECL(PTR_NOEXCEPT)

#define _MEMBER_FUNC_PTR_TEMPLATE \
    _FUNC_TEMPLATE_CDECL(MEMBER_PTR_CV_REF_NOEXCEPT) \
    _FUNC_TEMPLATE_FASTCALL(MEMBER_PTR_CV_REF_NOEXCEPT) \
    _FUNC_TEMPLATE_STDCALL(MEMBER_PTR_CV_REF_NOEXCEPT) \
    _FUNC_TEMPLATE_THISCALL(MEMBER_PTR_CV_REF_NOEXCEPT) \
    _FUNC_TEMPLATE_VECTORCALL(MEMBER_PTR_CV_REF_NOEXCEPT) \
    _FUNC_TEMPLATE_CLRCALL(MEMBER_PTR_CV_REF_NOEXCEPT)

#define _MEMBER_FUNC_WITH_VARARGS_PTR_TEMPLATE \
    _FUNC_TEMPLATE_CDECL(MEMBER_PTR_CV_REF_NOEXCEPT)

// ======================================================================

E_CTIDY_NOLINTBEGIN(bugprone-macro-parentheses)

namespace enhancedInternal::traits {
    template <bool, typename, typename Result>
    struct ConditionalImpl final {
        using Type = Result;
    };

    template <typename Result, typename AnotherType>
    struct ConditionalImpl<true, Result, AnotherType> final {
        using Type = Result;
    };

    // ======================================================================

    template <enhanced::sizetype index, typename, typename... OtherTypes>
    struct TypeAtImpl final {
        using Type = typename TypeAtImpl<index - 1, OtherTypes...>::Type;
    };

    template <typename Result, typename... OtherTypes>
    struct TypeAtImpl<0, Result, OtherTypes...> final {
        using Type = Result;
    };

    // ======================================================================

    template <typename Result>
    struct RemoveConstImpl final {
        using Type = Result;
    };

    template <typename Result>
    struct RemoveConstImpl<const Result> final {
        using Type = Result;
    };

    // ======================================================================

    template <typename Result>
    struct RemoveVolatileImpl final {
        using Type = Result;
    };

    template <typename Result>
    struct RemoveVolatileImpl<volatile Result> final {
        using Type = Result;
    };

    // ======================================================================

    template <typename Result>
    struct RemoveRefImpl final {
        using Type = Result;
    };

    template <typename Result>
    struct RemoveRefImpl<Result&> final {
        using Type = Result;
    };

    template <typename Result>
    struct RemoveRefImpl<Result&&> final {
        using Type = Result;
    };

    // ======================================================================

    template <typename Result>
    struct RemoveRefConstImpl final {
        using Type = Result;
    };

    template <typename InterType>
    struct RemoveRefConstImpl<const InterType&> final {
        using Type = InterType&;
    };

    template <typename InterType>
    struct RemoveRefConstImpl<const InterType&&> final {
        using Type = InterType&&;
    };

    // ======================================================================

    template <typename Result>
    struct RemoveRefVolatileImpl final {
        using Type = Result;
    };

    template <typename InterType>
    struct RemoveRefVolatileImpl<volatile InterType&> final {
        using Type = InterType&;
    };

    template <typename InterType>
    struct RemoveRefVolatileImpl<volatile InterType&&> final {
        using Type = InterType&&;
    };

    // ======================================================================

    template <typename Result>
    struct RemovePointerImpl final {
        using Type = Result;
    };

#define _TEMPLATE(CV_OPT) \
    template <typename Result> \
    struct RemovePointerImpl<Result* CV_OPT> final { \
        using Type = Result; \
    };

    _CV_OPT_TEMPLATE
#undef _TEMPLATE

    // ======================================================================

    template <bool, typename Type>
    struct ReferenceImpl final {
        using LvalueRef = Type;
        using RvalueRef = Type;
    };

    template <typename Type>
    struct ReferenceImpl<true, Type> final {
        using LvalueRef = Type&;
        using RvalueRef = Type&&;
    };

    // ======================================================================

    template <typename Result>
    struct RemovePtrConstImpl final {
        using Type = Result;
    };

#define _TEMPLATE(CV_OPT) \
    template <typename InterType> \
    struct RemovePtrConstImpl<const InterType* CV_OPT> final { \
        using Type = InterType* CV_OPT; \
    };

    _CV_OPT_TEMPLATE
#undef _TEMPLATE

    // ======================================================================

    template <typename Result>
    struct RemovePtrVolatileImpl final {
        using Type = Result;
    };

#define _TEMPLATE(CV_OPT) \
    template <typename InterType> \
    struct RemovePtrVolatileImpl<volatile InterType* CV_OPT> final { \
        using Type = InterType* CV_OPT; \
    };

    _CV_OPT_TEMPLATE
#undef _TEMPLATE

    // ======================================================================

    template <typename, enhanced::sizetype>
    struct RemoveExtentImpl final {};

    template <typename Result>
    struct RemoveExtentImpl<Result[], 0> final {
        using Type = Result;
    };

    template <typename InterType, enhanced::sizetype extent>
    struct RemoveExtentImpl<InterType[], extent> final {
        using Type = typename RemoveExtentImpl<InterType, extent - 1>::Type[];
    };

    template <typename Result, enhanced::sizetype size>
    struct RemoveExtentImpl<Result[size], 0> final {
        using Type = Result;
    };

    template <typename InterType, enhanced::sizetype extent, enhanced::sizetype size>
    struct RemoveExtentImpl<InterType[size], extent> final {
        using Type = typename RemoveExtentImpl<InterType, extent - 1>::Type[size];
    };

    // ======================================================================

    template <typename Result>
    struct RemoveAllExtentsImpl final {
        using Type = Result;
    };

    template <typename InterType>
    struct RemoveAllExtentsImpl<InterType[]> final {
        using Type = typename RemoveAllExtentsImpl<InterType>::Type;
    };

    template <typename InterType, enhanced::sizetype size>
    struct RemoveAllExtentsImpl<InterType[size]> final {
        using Type = typename RemoveAllExtentsImpl<InterType>::Type;
    };

    // ======================================================================

    template <typename Result>
    struct ToSignedImpl final {
        using Type = Result;
    };

    template <>
    struct ToSignedImpl<char> final {
        using Type = enhanced::schar;
    };

#define _TEMPLATE(BASE_INT_TYPE) \
    template <> \
    struct ToSignedImpl<unsigned BASE_INT_TYPE> final { \
        using Type = signed BASE_INT_TYPE; \
    };

    _BASE_INT_TYPE_TEMPLATE
#undef _TEMPLATE

    // ======================================================================

    template <typename Result>
    struct ToUnsignedImpl final {
        using Type = Result;
    };

    template <>
    struct ToUnsignedImpl<char> final {
        using Type = enhanced::uchar;
    };

#define _TEMPLATE(BASE_INT_TYPE) \
    template <> \
    struct ToUnsignedImpl<signed BASE_INT_TYPE> final { \
        using Type = unsigned BASE_INT_TYPE; \
    };

    _BASE_INT_TYPE_TEMPLATE
#undef _TEMPLATE

    struct FunctionParserImpl {
        template <enhanced::sizetype size>
        static consteval bool isNothrowImpl(const enhanced::wrap<char[size]>& arg) {
            return arg[0] == 'n'; // "noexcept"
        }

        template <enhanced::sizetype size>
        static consteval bool isObjectConstImpl(const enhanced::wrap<char[size]>& arg) {
            return arg[0] == 'c'; // "const" or "const volatile"
        }

        template <enhanced::sizetype size>
        static consteval bool isObjectVolatileImpl(const enhanced::wrap<char[size]>& arg) {
            return arg[0] == 'v' || (arg[0] != '\0' && arg[5] != '\0' && arg[6] == 'v'); // "volatile" or "const volatile"
        }

        template <enhanced::sizetype size>
        static consteval bool isObjectReferenceImpl(const enhanced::wrap<char[size]>& arg) {
            return arg[0] == '&'; // "&" or "&&"
        }

        template <enhanced::sizetype size>
        static consteval bool isObjectLvalueRefImpl(const enhanced::wrap<char[size]>& arg) {
            return arg[0] == '&' && arg[1] == '\0'; // "&"
        }

        template <enhanced::sizetype size>
        static consteval bool isObjectRvalueRefImpl(const enhanced::wrap<char[size]>& arg) {
            return arg[0] == '&' && arg[1] == '&'; // "&&"
        }
    };
}

E_CLANG_WARNING_PAD("-Wdeprecated-volatile") E_MSVC_WARNING_PAD(4180) E_GCC_WARNING_PAD("-Wattributes")

namespace enhanced::inline traits {
    template <bool condition, typename Type1, typename Type2>
    using Conditional = typename enhancedInternal::traits::ConditionalImpl<condition, Type1, Type2>::Type;

    template <sizetype index, typename... Types>
    using TypeAt = typename enhancedInternal::traits::TypeAtImpl<index, Types...>::Type;

    template <bool first, bool... conditions>
    inline constexpr bool allOf = first;

    template <bool next, bool... conditions>
    inline constexpr bool allOf<true, next, conditions...> = allOf<next, conditions...>;

    template <bool first, bool... conditions>
    inline constexpr bool anyOf = first;

    template <bool next, bool... conditions>
    inline constexpr bool anyOf<false, next, conditions...> = anyOf<next, conditions...>;

    template <typename...>
    inline constexpr bool testValid = true; // Uses to test whether a type expression is valid

    template <typename... Types>
    struct TypeVector {
        template <sizetype index>
        using At = TypeAt<index, Types...>;

        template <template <typename...> typename Type, typename... TypeArgs>
        using Expand = Type<TypeArgs..., Types...>;

        template <template <auto, typename...> typename Type, auto arg, typename... TypeArgs>
        using ExpandWith = Type<arg, TypeArgs..., Types...>;

        static inline constexpr sizetype count = sizeof...(Types);
    };

    template <typename Type>
    E_RET_NO_DISCARD()
    constexpr Type declvalue() noexcept; // Uses for compile-time type inference, no implementation required

    template <typename Type>
    E_RET_NO_DISCARD()
    inline constexpr Type& weakCast(Type&& value) noexcept {
        return value;
    }

#define _TEMPLATE(CV_OPT) \
    template <typename Type> \
    E_RET_NO_DISCARD() \
    inline constexpr Type& weakCast(CV_OPT Type& value) noexcept { \
        return const_cast<Type&>(value); \
    }

    _CV_OPT_TEMPLATE
#undef _TEMPLATE

    template <typename Type>
    E_RET_NO_DISCARD()
    inline constexpr Type& forceCast(auto&& value) noexcept {
        return *((Type*) &value);
    }

    template <sizetype index>
    E_RET_NO_DISCARD()
    inline constexpr auto& valueAt(auto&& result, auto&&...) noexcept {
        return result;
    }

    template <sizetype index>
    requires (index > 0)
    E_RET_NO_DISCARD()
    inline constexpr auto& valueAt(auto&&, auto&&... values) noexcept {
        return valueAt<index - 1>(values...);
    }

#ifdef E_SM_COMPILER_MSVC
    template <typename, typename>
    inline constexpr bool isSame = false;

    template <typename Type>
    inline constexpr bool isSame<Type, Type> = true;
#else
    template <typename Type1, typename Type2>
    inline constexpr bool isSame = __is_same(Type1, Type2);
#endif

    template <typename Type, typename... Others>
    inline constexpr bool isAnyOf = anyOf<isSame<Type, Others>...>;

    template <typename Base, typename Derived>
    inline constexpr bool isBaseOf = __is_base_of(Base, Derived);

    template <typename Base, typename... Derived>
    inline constexpr bool isAllBaseOf = allOf<isBaseOf<Base, Derived>...>;

    template <typename Base, typename... Derived>
    inline constexpr bool isAnyBaseOf = anyOf<isBaseOf<Base, Derived>...>;

    template <typename Base, typename Derived>
    inline constexpr bool isBaseOfNs = isBaseOf<Base, Derived> && !isSame<Base, Derived>;

    template <typename Base, typename... Derived>
    inline constexpr bool isAllBaseOfNs = allOf<isBaseOfNs<Base, Derived>...>;

    template <typename Base, typename... Derived>
    inline constexpr bool isAnyBaseOfNs = anyOf<isBaseOfNs<Base, Derived>...>;

    template <typename>
    inline constexpr bool isConst = false;

    template <typename Type>
    inline constexpr bool isConst<const Type> = true;

    template <typename>
    inline constexpr bool isVolatile = false;

    template <typename Type>
    inline constexpr bool isVolatile<volatile Type> = true;

    template <typename Type>
    inline constexpr bool isLvalueRef = false;

    template <typename Type>
    inline constexpr bool isLvalueRef<Type&> = true;

    template <typename Type>
    inline constexpr bool isRvalueRef = false;

    template <typename Type>
    inline constexpr bool isRvalueRef<Type&&> = true;

    template <typename Type>
    inline constexpr bool isReference = isLvalueRef<Type> || isRvalueRef<Type>;

    template <typename Type>
    inline constexpr bool isLvaRefConst = false;

    template <typename Type>
    inline constexpr bool isLvaRefConst<const Type&> = true;

    template <typename Type>
    inline constexpr bool isLvaRefVolatile = false;

    template <typename Type>
    inline constexpr bool isLvaRefVolatile<volatile Type&> = true;

    template <typename Type>
    inline constexpr bool isLvaRefCvAnd = isLvaRefConst<Type> && isLvaRefVolatile<Type>;

    template <typename Type>
    inline constexpr bool isLvaRefCvOr = isLvaRefConst<Type> || isLvaRefVolatile<Type>;

    template <typename Type>
    inline constexpr bool isRvaRefConst = false;

    template <typename Type>
    inline constexpr bool isRvaRefConst<const Type&&> = true;

    template <typename Type>
    inline constexpr bool isRvaRefVolatile = false;

    template <typename Type>
    inline constexpr bool isRvaRefVolatile<volatile Type&&> = true;

    template <typename Type>
    inline constexpr bool isRvaRefCvAnd = isRvaRefConst<Type> && isRvaRefVolatile<Type>;

    template <typename Type>
    inline constexpr bool isRvaRefCvOr = isRvaRefConst<Type> || isRvaRefVolatile<Type>;

    template <typename Type>
    inline constexpr bool isRefConst = isLvaRefConst<Type> || isRvaRefConst<Type>;

    template <typename Type>
    inline constexpr bool isRefVolatile = isLvaRefVolatile<Type> || isRvaRefVolatile<Type>;

    template <typename Type>
    inline constexpr bool isRefCvAnd = isRefConst<Type> && isRefVolatile<Type>;

    template <typename Type>
    inline constexpr bool isRefCvOr = isRefConst<Type> || isRefVolatile<Type>;

    template <typename Type>
    inline constexpr bool isReferenceable = false;

    template <typename Type>
    requires testValid<Type&>
    inline constexpr bool isReferenceable<Type> = true;

    template <typename>
    inline constexpr bool isPointer = false;

#define _TEMPLATE(CV_OPT) \
    template <typename Type> \
    inline constexpr bool isPointer<Type* CV_OPT> = true;

    _CV_OPT_TEMPLATE
#undef _TEMPLATE

    template <typename Type>
    inline constexpr bool isPtrConst = false;

    template <typename Type>
    inline constexpr bool isPtrConst<const Type*> = true;

    template <typename Type>
    inline constexpr bool isPtrVolatile = false;

    template <typename Type>
    inline constexpr bool isPtrVolatile<volatile Type*> = true;

    template <typename Type>
    inline constexpr bool isPtrCvAnd = isPtrConst<Type> && isPtrVolatile<Type>;

    template <typename Type>
    inline constexpr bool isPtrCvOr = isPtrConst<Type> || isPtrVolatile<Type>;

    template <typename Type>
    inline constexpr bool isBoundedArray = false;

    template <typename Type, sizetype size>
    inline constexpr bool isBoundedArray<Type[size]> = true;

    template <typename Type>
    inline constexpr bool isUnboundedArray = false;

    template <typename Type>
    inline constexpr bool isUnboundedArray<Type[]> = true;

    template <typename Type>
    inline constexpr bool isArray = isBoundedArray<Type> || isUnboundedArray<Type>;

    template <typename Type>
    using LvalueRef = typename enhancedInternal::traits::ReferenceImpl<isReferenceable<Type>, Type>::LvalueRef;

    template <typename Type>
    using RvalueRef = typename enhancedInternal::traits::ReferenceImpl<isReferenceable<Type>, Type>::RvalueRef;

    template <typename Type>
    using Const = const Type; // Use this type-alias to constify the type to prevent the MSVC C4180 warning.

    template <typename Type>
    using ConstLvaRef = LvalueRef<const Type>;

    template <typename Type>
    using ConstRvaRef = RvalueRef<const Type>;

    template <typename Type>
    using RemoveConst = typename enhancedInternal::traits::RemoveConstImpl<Type>::Type;

    template <typename Type>
    using RemoveVolatile = typename enhancedInternal::traits::RemoveVolatileImpl<Type>::Type;

    template <typename Type>
    using RemoveCv = RemoveConst<RemoveVolatile<Type>>;

    template <typename Type>
    using RemoveRef = typename enhancedInternal::traits::RemoveRefImpl<Type>::Type;

    template <typename Type>
    requires isReference<Type>
    using RemoveRefConst = typename enhancedInternal::traits::RemoveRefConstImpl<Type>::Type;

    template <typename Type>
    requires isReference<Type>
    using RemoveRefVolatile = typename enhancedInternal::traits::RemoveRefVolatileImpl<Type>::Type;

    template <typename Type>
    requires isReference<Type>
    using RemoveRefCv = RemoveRefConst<RemoveRefVolatile<Type>>;

    template <typename Type>
    using RemoveRefAndCv = RemoveCv<RemoveRef<Type>>;

    template <typename Type>
    using RemovePointer = typename enhancedInternal::traits::RemovePointerImpl<Type>::Type;

    template <typename Type>
    requires isPointer<Type>
    using RemovePtrConst = typename enhancedInternal::traits::RemovePtrConstImpl<Type>::Type;

    template <typename Type>
    requires isPointer<Type>
    using RemovePtrVolatile = typename enhancedInternal::traits::RemovePtrVolatileImpl<Type>::Type;

    template <typename Type>
    requires isPointer<Type>
    using RemovePtrCv = RemovePtrConst<RemovePtrVolatile<Type>>;

    template <typename Type>
    using RemovePtrAndCv = RemoveCv<RemovePointer<Type>>;

    template <typename Type, sizetype extent = 0>
    using RemoveExtent = typename enhancedInternal::traits::RemoveExtentImpl<Type, extent>::Type;

    template <typename Type>
    using RemoveAllExtents = typename enhancedInternal::traits::RemoveAllExtentsImpl<Type>::Type;

    template <typename Type, sizetype extent = 0>
    inline constexpr sizetype arrayExtent = arrayExtent<RemoveExtent<Type>, extent - 1>;

    template <typename Type, sizetype size>
    inline constexpr sizetype arrayExtent<Type[size], 0> = size;

    template <typename Type>
    inline constexpr sizetype arrayRank = 0;

    template <typename Type>
    requires isArray<Type>
    inline constexpr sizetype arrayRank<Type> = arrayRank<RemoveExtent<Type>> + 1;

    template <typename Type>
    inline constexpr bool isCharType =
        isAnyOf<RemoveCv<Type>, char,
    #ifdef E_SM_WCHAR_IS_BUILTIN_TYPE
        wchar,
    #endif
        u8char, u16char, u32char>;

    template <typename Type>
    inline constexpr bool isIntegralType =
        isAnyOf<RemoveCv<Type>, char,
    #ifdef E_SM_WCHAR_IS_BUILTIN_TYPE
        wchar,
    #endif
        u8char, u16char, u32char, bool, schar, uchar, short, ushort, int, uint, long, ulong, llong, ullong>;

    template <typename Type>
    inline constexpr bool isIntegralTypeNc = isIntegralType<Type> && !isCharType<Type>;

    template <typename Type>
    inline constexpr bool isIntegralTypeNs = isIntegralTypeNc<Type> && !isSame<Type, bool>;

    template <typename Type>
    inline constexpr bool isFloatType = isAnyOf<RemoveCv<Type>, float, double, ldouble>;

    template <typename Type>
    requires isIntegralType<Type>
    inline constexpr bool isSigned = static_cast<RemoveCv<Type>>(-1) < static_cast<Type>(0);

    template <typename Type>
    requires isIntegralType<Type>
    inline constexpr bool isUnsigned = static_cast<RemoveCv<Type>>(-1) >= static_cast<Type>(0);

    template <typename Type>
    requires isIntegralType<Type>
    using ToSigned = typename enhancedInternal::traits::ToSignedImpl<Type>::Type;

    template <typename Type>
    requires isIntegralType<Type>
    using ToUnsigned = typename enhancedInternal::traits::ToUnsignedImpl<Type>::Type;

    template <typename Type>
    inline constexpr bool isEmptyType = __is_empty(Type);

    template <typename Type>
    inline constexpr bool isVoidType = isSame<RemoveCv<Type>, void>;

    template <typename Type>
    inline constexpr bool isNullType = isSame<RemoveCv<Type>, nulltype>;

    template <typename Type>
    inline constexpr bool isEnum = __is_enum(Type);

    template <typename Type>
    inline constexpr bool isClass = __is_class(Type);

    template <typename Type>
    inline constexpr bool isPolymorphicClass = __is_polymorphic(Type);

    template <typename Type>
    inline constexpr bool isAbstractClass = __is_abstract(Type);

    template <typename Type>
    inline constexpr bool isFinalClass = __is_final(Type);

    template <typename Type>
    inline constexpr bool isUnion = __is_union(Type);

    template <typename Type>
    inline constexpr bool isArithmeticType = isIntegralType<Type> || isFloatType<Type>;

    template <typename Type>
    inline constexpr bool isBasicType = isArithmeticType<Type> || isVoidType<Type> || isNullType<Type>;

    template <typename Type>
    inline constexpr bool isCompoundType = !isBasicType<Type>;

#ifdef E_SM_COMPILER_GCC
    template <typename From, typename To>
    inline constexpr bool isConvertible = false;

    template <typename From, typename To>
    requires isVoidType<From> && isVoidType<To>
    inline constexpr bool isConvertible<From, To> = true;

    template <typename From, typename To>
    requires (!isVoidType<From> && !isVoidType<To>) && testValid<decltype(weakCast<To>(declvalue<From>()))>
    inline constexpr bool isConvertible<From, To> = true;
#else
    template <typename From, typename To>
    inline constexpr bool isConvertible = __is_convertible_to(From, To);
#endif

    template <typename From, typename To>
    inline constexpr bool isGeneralConvertible = false;

    template <typename From, typename To>
    requires isVoidType<To>
    inline constexpr bool isGeneralConvertible<From, To> = true;

    template <typename From, typename To>
    requires (!isVoidType<From> && !isVoidType<To>) && testValid<decltype((To) declvalue<From>())>
    inline constexpr bool isGeneralConvertible<From, To> = true;

    template <typename From, typename To>
    inline constexpr bool isStaticConvertible = false;

    template <typename From, typename To>
    requires isVoidType<To>
    inline constexpr bool isStaticConvertible<From, To> = true;

    template <typename From, typename To>
    requires (!isVoidType<From> && !isVoidType<To>) && testValid<decltype(static_cast<To>(declvalue<From>()))>
    inline constexpr bool isStaticConvertible<From, To> = true;

    template <typename From, typename To>
    inline constexpr bool isReintConvertible = false;

    template <typename From, typename To>
    requires testValid<decltype(reinterpret_cast<To>(declvalue<From>()))>
    inline constexpr bool isReintConvertible<From, To> = true;

    template <typename From, typename To>
    inline constexpr bool isCvConvertible = false;

    template <typename From, typename To>
    requires testValid<decltype(const_cast<To>(declvalue<From>()))>
    inline constexpr bool isCvConvertible<From, To> = true;

    template <typename Type>
    inline constexpr bool isScopedEnum = false;

    template <typename Type>
    requires isEnum<Type> && testValid<decltype(sizeof(Type))> && (!isConvertible<Type, int>)
    inline constexpr bool isScopedEnum<Type> = true;

    template <typename, template <typename...> typename>
    inline constexpr bool isSpecialization = false;

    template <template <typename...> typename Template, typename... Types>
    inline constexpr bool isSpecialization<Template<Types...>, Template> = true;

    template <typename Type>
    inline constexpr bool isComparable = false;

    template <typename Type>
    requires testValid<decltype(declvalue<Type>() == declvalue<Type>()), decltype(declvalue<Type>() != declvalue<Type>()),
                       decltype(declvalue<Type>() < declvalue<Type>()), decltype(declvalue<Type>() > declvalue<Type>()),
                       decltype(declvalue<Type>() <= declvalue<Type>()), decltype(declvalue<Type>() >= declvalue<Type>())>
    inline constexpr bool isComparable<Type> = true;

    // Only function types and reference types cannot be const qualified.

    template <typename Type>
    inline constexpr bool isObject = !isVoidType<Type> && isConst<const Type>;

    template <typename Type>
    inline constexpr bool isFunction = !isReference<Type> && !isConst<const Type>;

    template <typename Type, typename... Args>
    inline constexpr bool isConstructible = __is_constructible(Type, Args...);

    template <typename Type>
    inline constexpr bool isCopyConstructible = isConstructible<Type, LvalueRef<const Type>>;

    template <typename Type>
    inline constexpr bool isMoveConstructible = isConstructible<Type, RvalueRef<Type>>;

    template <typename Type, typename... Args>
    inline constexpr bool isTriviallyConstructible = __is_trivially_constructible(Type, Args...);

    template <typename Type>
    inline constexpr bool isTriviallyCopyConstructible = isTriviallyConstructible<Type, LvalueRef<const Type>>;

    template <typename Type>
    inline constexpr bool isTriviallyMoveConstructible = isTriviallyConstructible<Type, RvalueRef<Type>>;

    template <typename Type, typename... Args>
    inline constexpr bool isNothrowConstructible = __is_nothrow_constructible(Type, Args...);

    template <typename Type>
    inline constexpr bool isNothrowCopyConstructible = isNothrowConstructible<Type, LvalueRef<const Type>>;

    template <typename Type>
    inline constexpr bool isNothrowMoveConstructible = isNothrowConstructible<Type, RvalueRef<Type>>;

    template <typename From, typename To>
    inline constexpr bool isAssignable = __is_assignable(To, From);

    template <typename From, typename To>
    inline constexpr bool isCopyAssignable = isAssignable<LvalueRef<const From>, LvalueRef<To>>;

    template <typename From, typename To>
    inline constexpr bool isMoveAssignable = isAssignable<From, LvalueRef<To>>;

    template <typename From, typename To>
    inline constexpr bool isTriviallyAssignable = __is_trivially_assignable(To, From);

    template <typename From, typename To>
    inline constexpr bool isTriviallyCopyAssignable = isTriviallyAssignable<LvalueRef<const From>, LvalueRef<To>>;

    template <typename From, typename To>
    inline constexpr bool isTriviallyMoveAssignable = isTriviallyAssignable<From, LvalueRef<To>>;

    template <typename From, typename To = From>
    inline constexpr bool isNothrowAssignable = __is_nothrow_assignable(To, From);

    template <typename From, typename To = From>
    inline constexpr bool isNothrowCopyAssignable = isNothrowAssignable<LvalueRef<const From>, LvalueRef<To>>;

    template <typename From, typename To = From>
    inline constexpr bool isNothrowMoveAssignable = isNothrowAssignable<From, LvalueRef<To>>;

#ifdef E_SM_COMPATIBILITY_MS
    template <typename Type>
    inline constexpr bool isDestructible = __is_destructible(Type);
#else
    template <typename Type>
    inline constexpr bool isDestructible = false;

    template <typename Type>
    requires isObject<Type> && (!isClass<Type>)
    inline constexpr bool isDestructible<Type> = true;

    template <typename Type>
    requires isClass<Type> && testValid<decltype(declvalue<Type>().~Type())>
    inline constexpr bool isDestructible<Type> = true;
#endif

#ifdef E_SM_COMPILER_GCC
    template <typename Type>
    inline constexpr bool isTriviallyDestructible = __has_trivial_destructor(Type);
#else
    template <typename Type>
    inline constexpr bool isTriviallyDestructible = __is_trivially_destructible(Type);
#endif

#ifdef E_SM_COMPILER_GCC
    template <typename Type>
    inline constexpr bool isNothrowDestructible = false;

    template <typename Type>
    requires isObject<Type> && (!isClass<Type>)
    inline constexpr bool isNothrowDestructible<Type> = true;

    template <typename Type>
    requires isClass<Type> && testValid<decltype(declvalue<Type>().~Type())>
    inline constexpr bool isNothrowDestructible<Type> = noexcept(declvalue<Type>().~Type());
#else
    template <typename Type>
    inline constexpr bool isNothrowDestructible = __is_nothrow_destructible(Type);
#endif

    template <typename Type>
    inline constexpr bool isTriviallyCopyable = __is_trivially_copyable(Type);

#ifdef E_SM_COMPATIBILITY_GNU
    template <typename Type>
    inline constexpr bool isTrivial = __is_trivial(Type);
#else
    template <typename Type>
    inline constexpr bool isTrivial = isTriviallyConstructible<Type> && isTriviallyCopyable<Type>;
#endif

    template <typename Type>
    inline constexpr bool hasVirtualDestructor = __has_virtual_destructor(Type);

    enum class CallingConvention : uint8 {
        Cdecl, Fastcall, Stdcall, Thiscall, Vectorcall, Clrcall
    };

    template <typename Type>
    requires isFunction<Type>
    struct FunctionParser {};

#define _TEMPLATE(CALLING_CONVENTION, CALL_OPT, CV_OPT, REF_OPT, NOEXCEPT_OPT) \
    template <typename Return, typename... Args> \
    struct FunctionParser<Return CALL_OPT (Args...) CV_OPT REF_OPT NOEXCEPT_OPT> { \
        using Type = Return CALL_OPT (Args...) CV_OPT REF_OPT NOEXCEPT_OPT; \
        using ReturnType = Return; \
        using ParameterTypes = TypeVector<Args...>; \
        using NeatFunctionType = Return (Args...); \
        static inline constexpr CallingConvention callingConvention = CALLING_CONVENTION; \
        static inline constexpr bool hasVarargs = false; \
        static inline constexpr bool isNothrow = enhancedInternal::traits::FunctionParserImpl::isNothrowImpl(#NOEXCEPT_OPT); \
        static inline constexpr bool isObjectConst = enhancedInternal::traits::FunctionParserImpl::isObjectConstImpl(#CV_OPT); \
        static inline constexpr bool isObjectVolatile = enhancedInternal::traits::FunctionParserImpl::isObjectVolatileImpl(#CV_OPT); \
        static inline constexpr bool isObjectReference = enhancedInternal::traits::FunctionParserImpl::isObjectReferenceImpl(#REF_OPT); \
        static inline constexpr bool isObjectLvalueRef = enhancedInternal::traits::FunctionParserImpl::isObjectLvalueRefImpl(#REF_OPT); \
        static inline constexpr bool isObjectRvalueRef = enhancedInternal::traits::FunctionParserImpl::isObjectRvalueRefImpl(#REF_OPT); \
    };

    _FUNC_TEMPLATE
#undef _TEMPLATE

#define _TEMPLATE(CALLING_CONVENTION, CALL_OPT, CV_OPT, REF_OPT, NOEXCEPT_OPT) \
    template <typename Return, typename... Args> \
    struct FunctionParser<Return CALL_OPT (Args..., ...) CV_OPT REF_OPT NOEXCEPT_OPT> { \
        using Type = Return CALL_OPT (Args..., ...) CV_OPT REF_OPT NOEXCEPT_OPT; \
        using ReturnType = Return; \
        using ParameterTypes = TypeVector<Args...>; \
        using NeatFunctionType = Return (Args..., ...); \
        static inline constexpr CallingConvention callingConvention = CALLING_CONVENTION; \
        static inline constexpr bool hasVarargs = true; \
        static inline constexpr bool isNothrow = enhancedInternal::traits::FunctionParserImpl::isNothrowImpl(#NOEXCEPT_OPT); \
        static inline constexpr bool isObjectConst = enhancedInternal::traits::FunctionParserImpl::isObjectConstImpl(#CV_OPT); \
        static inline constexpr bool isObjectVolatile = enhancedInternal::traits::FunctionParserImpl::isObjectVolatileImpl(#CV_OPT); \
        static inline constexpr bool isObjectReference = enhancedInternal::traits::FunctionParserImpl::isObjectReferenceImpl(#REF_OPT); \
        static inline constexpr bool isObjectLvalueRef = enhancedInternal::traits::FunctionParserImpl::isObjectLvalueRefImpl(#REF_OPT); \
        static inline constexpr bool isObjectRvalueRef = enhancedInternal::traits::FunctionParserImpl::isObjectRvalueRefImpl(#REF_OPT); \
    };

    _FUNC_WITH_VARARGS_TEMPLATE
#undef _TEMPLATE

    template <typename Type>
    inline constexpr bool isFunctionPtr = false;

#define _TEMPLATE(CV_OPT) \
    template <typename Type> \
    requires isFunction<Type> \
    inline constexpr bool isFunctionPtr<Type* CV_OPT> = true;

    _CV_OPT_TEMPLATE
#undef _TEMPLATE

    template <typename Type>
    requires isFunctionPtr<Type>
    struct FunctionPtrParser {};

#define _TEMPLATE(PTR_CV_OPT, CALLING_CONVENTION, CALL_OPT, NOEXCEPT_OPT) \
    template <typename Return, typename... Args> \
    struct FunctionPtrParser<Return (CALL_OPT* PTR_CV_OPT)(Args...) NOEXCEPT_OPT> { \
        using Type = Return (CALL_OPT* PTR_CV_OPT)(Args...) NOEXCEPT_OPT; \
        using ReturnType = Return; \
        using ParameterTypes = TypeVector<Args...>; \
        using NeatFunctionType = Return (Args...); \
        static inline constexpr CallingConvention callingConvention = CALLING_CONVENTION; \
        static inline constexpr bool hasVarargs = false; \
        static inline constexpr bool isNothrow = enhancedInternal::traits::FunctionParserImpl::isNothrowImpl(#NOEXCEPT_OPT); \
    };

    _FUNC_PTR_TEMPLATE
#undef _TEMPLATE

#define _TEMPLATE(PTR_CV_OPT, CALLING_CONVENTION, CALL_OPT, NOEXCEPT_OPT) \
    template <typename Return, typename... Args> \
    struct FunctionPtrParser<Return (CALL_OPT* PTR_CV_OPT)(Args..., ...) NOEXCEPT_OPT> { \
        using Type = Return (CALL_OPT* PTR_CV_OPT)(Args..., ...) NOEXCEPT_OPT; \
        using ReturnType = Return; \
        using ParameterTypes = TypeVector<Args...>; \
        using NeatFunctionType = Return (Args..., ...); \
        static inline constexpr CallingConvention callingConvention = CALLING_CONVENTION; \
        static inline constexpr bool hasVarargs = true; \
        static inline constexpr bool isNothrow = enhancedInternal::traits::FunctionParserImpl::isNothrowImpl(#NOEXCEPT_OPT); \
    };

    _FUNC_WITH_VARARGS_PTR_TEMPLATE
#undef _TEMPLATE

#ifdef E_SM_COMPILER_CLANG
    template <typename Type>
    inline constexpr bool isMemObjPtr = __is_member_object_pointer(Type);

    template <typename Type>
    inline constexpr bool isMemFuncPtr = __is_member_function_pointer(Type);

    template <typename Type>
    inline constexpr bool isMemberPointer = __is_member_pointer(Type);
#else
    template <typename Type>
    inline constexpr bool isMemObjPtr = false;

#define _TEMPLATE(CV_OPT) \
    template <typename Type, typename Class> \
    inline constexpr bool isMemObjPtr<Type Class::* CV_OPT> = enhanced::isObject<Type>;

    _CV_OPT_TEMPLATE
#undef _TEMPLATE

    template <typename Type>
    inline constexpr bool isMemFuncPtr = false;

#define _TEMPLATE(CV_OPT) \
    template <typename Type, typename Class> \
    inline constexpr bool isMemFuncPtr<Type Class::* CV_OPT> = enhanced::isFunction<Type>;

    _CV_OPT_TEMPLATE
#undef _TEMPLATE

    template <typename Type>
    inline constexpr bool isMemberPointer = isMemObjPtr<Type> || isMemFuncPtr<Type>;
#endif

    template <typename Type>
    inline constexpr bool isScalarType = isArithmeticType<Type> || isEnum<Type> || isPointer<Type> || isMemberPointer<Type> || isNullType<Type>;

    template <typename Type>
    requires isMemberPointer<Type>
    struct MemberPointerParser {};

#define _TEMPLATE(CV_OPT) \
    template <typename Member, typename Class> \
    struct MemberPointerParser<Member Class::* CV_OPT> { \
        using Type = Member Class::* CV_OPT; \
        using MemberType = Member; \
        using ClassType = Class; \
    };

    _CV_OPT_TEMPLATE
#undef _TEMPLATE

    template <typename Type>
    requires isMemObjPtr<Type>
    struct MemObjPtrParser final : MemberPointerParser<Type> {};

    template <typename Type>
    requires isMemFuncPtr<Type>
    struct MemFuncPtrParser final : MemberPointerParser<Type> {};

#define _TEMPLATE(PTR_CV_OPT, CALLING_CONVENTION, CALL_OPT, CV_OPT, REF_OPT, NOEXCEPT_OPT) \
    template <typename Return, typename Class, typename... Args> \
    struct MemFuncPtrParser<Return (CALL_OPT Class::* PTR_CV_OPT)(Args...) CV_OPT REF_OPT NOEXCEPT_OPT> final : \
        MemberPointerParser<Return (CALL_OPT Class::* PTR_CV_OPT)(Args...) CV_OPT REF_OPT NOEXCEPT_OPT> { \
        using Type = Return (CALL_OPT Class::* PTR_CV_OPT)(Args...) CV_OPT REF_OPT NOEXCEPT_OPT; \
        using FunctinoType = typename MemberPointerParser<Type>::MemberType; \
        using ReturnType = Return; \
        using ParameterTypes = TypeVector<Args...>; \
        using NeatFunctionType = Return (Args...); \
        static inline constexpr CallingConvention callingConvention = CALLING_CONVENTION; \
        static inline constexpr bool hasVarargs = false; \
        static inline constexpr bool isNothrow = enhancedInternal::traits::FunctionParserImpl::isNothrowImpl(#NOEXCEPT_OPT); \
        static inline constexpr bool isObjectConst = enhancedInternal::traits::FunctionParserImpl::isObjectConstImpl(#CV_OPT); \
        static inline constexpr bool isObjectVolatile = enhancedInternal::traits::FunctionParserImpl::isObjectVolatileImpl(#CV_OPT); \
        static inline constexpr bool isObjectReference = enhancedInternal::traits::FunctionParserImpl::isObjectReferenceImpl(#REF_OPT); \
        static inline constexpr bool isObjectLvalueRef = enhancedInternal::traits::FunctionParserImpl::isObjectLvalueRefImpl(#REF_OPT); \
        static inline constexpr bool isObjectRvalueRef = enhancedInternal::traits::FunctionParserImpl::isObjectRvalueRefImpl(#REF_OPT); \
    };

    _MEMBER_FUNC_PTR_TEMPLATE
#undef _TEMPLATE

#define _TEMPLATE(PTR_CV_OPT, CALLING_CONVENTION, CALL_OPT, CV_OPT, REF_OPT, NOEXCEPT_OPT) \
    template <typename Return, typename Class, typename... Args> \
    struct MemFuncPtrParser<Return (CALL_OPT Class::* PTR_CV_OPT)(Args..., ...) CV_OPT REF_OPT NOEXCEPT_OPT> final : \
        MemberPointerParser<Return (CALL_OPT Class::* PTR_CV_OPT)(Args..., ...) CV_OPT REF_OPT NOEXCEPT_OPT> { \
        using Type = Return (CALL_OPT Class::* PTR_CV_OPT)(Args..., ...) CV_OPT REF_OPT NOEXCEPT_OPT; \
        using FunctinoType = typename MemberPointerParser<Type>::MemberType; \
        using ReturnType = Return; \
        using ParameterTypes = TypeVector<Args...>; \
        using NeatFunctionType = Return (Args..., ...); \
        static inline constexpr CallingConvention callingConvention = CALLING_CONVENTION; \
        static inline constexpr bool hasVarargs = false; \
        static inline constexpr bool isNothrow = enhancedInternal::traits::FunctionParserImpl::isNothrowImpl(#NOEXCEPT_OPT); \
        static inline constexpr bool isObjectConst = enhancedInternal::traits::FunctionParserImpl::isObjectConstImpl(#CV_OPT); \
        static inline constexpr bool isObjectVolatile = enhancedInternal::traits::FunctionParserImpl::isObjectVolatileImpl(#CV_OPT); \
        static inline constexpr bool isObjectReference = enhancedInternal::traits::FunctionParserImpl::isObjectReferenceImpl(#REF_OPT); \
        static inline constexpr bool isObjectLvalueRef = enhancedInternal::traits::FunctionParserImpl::isObjectLvalueRefImpl(#REF_OPT); \
        static inline constexpr bool isObjectRvalueRef = enhancedInternal::traits::FunctionParserImpl::isObjectRvalueRefImpl(#REF_OPT); \
    };

    _MEMBER_FUNC_WITH_VARARGS_PTR_TEMPLATE
#undef _TEMPLATE

    template <typename Type>
    E_RET_NO_DISCARD()
    inline constexpr RemoveCv<RemoveRef<Type>>&& move(Type&& value) noexcept {
        return const_cast<RemoveCv<RemoveRef<Type>>&&>(value);
    }

    template <typename Type>
    E_RET_NO_DISCARD()
    inline constexpr RemoveRef<Type>&& moveIf(Type&& value) noexcept {
        return static_cast<RemoveRef<Type>&&>(value);
    }

    template <typename Type>
    E_RET_NO_DISCARD()
    inline constexpr Type&& forward(RemoveRef<Type>& value) noexcept {
        return static_cast<Type&&>(value);
    }

    template <typename Type>
    requires (!isLvalueRef<Type>)
    E_RET_NO_DISCARD()
    inline constexpr Type&& forward(RemoveRef<Type>&& value) noexcept {
        return static_cast<Type&&>(value);
    }

    template <typename Result, typename First, typename... Cases>
    requires isSame<Result, First>
    E_RET_NO_DISCARD()
    inline constexpr Result& select(First&& result, Cases&&...) noexcept {
        return result;
    }

    template <typename Result, typename First, typename... Cases>
    requires (!isSame<Result, First>)
    E_RET_NO_DISCARD()
    inline constexpr Result& select(First&&, Cases&&... values) noexcept {
        return select<Result, Cases...>(static_cast<Cases&&>(values)...);
    }

    template <typename Type>
    E_RET_NO_DISCARD()
    inline constexpr const RemoveRef<Type>& addConst(Type&& value) noexcept {
        return const_cast<const RemoveRef<Type>&>(value);
    }

    template <typename Type>
    E_RET_NO_DISCARD()
    inline constexpr volatile RemoveRef<Type>& addVolatile(Type&& value) noexcept {
        return const_cast<volatile RemoveRef<Type>&>(value);
    }

    template <typename Type>
    E_RET_NO_DISCARD()
    inline constexpr const volatile RemoveRef<Type>& addCv(Type&& value) noexcept {
        return const_cast<const volatile RemoveRef<Type>&>(value);
    }

    template <typename Type>
    requires isPointer<RemoveRef<Type>>
    E_RET_NO_DISCARD()
    inline constexpr const RemovePointer<RemoveRef<Type>>*& addPtrConst(Type&& value) noexcept {
        return const_cast<const RemovePointer<RemoveRef<Type>>*&>(value);
    }

    template <typename Type>
    requires isPointer<RemoveRef<Type>>
    E_RET_NO_DISCARD()
    inline constexpr volatile RemovePointer<RemoveRef<Type>>*& addPtrVolatile(Type&& value) noexcept {
        return const_cast<volatile RemovePointer<RemoveRef<Type>>*&>(value);
    }

    template <typename Type>
    requires isPointer<RemoveRef<Type>>
    E_RET_NO_DISCARD()
    inline constexpr const volatile RemovePointer<RemoveRef<Type>>*& addPtrCv(Type&& value) noexcept {
        return const_cast<const volatile RemovePointer<RemoveRef<Type>>*&>(value);
    }

    template <typename Type>
    E_RET_NO_DISCARD()
    inline constexpr RemoveConst<RemoveRef<Type>>& removeConst(Type&& value) noexcept {
        return const_cast<RemoveConst<RemoveRef<Type>>&>(value);
    }

    template <typename Type>
    E_RET_NO_DISCARD()
    inline constexpr RemoveVolatile<RemoveRef<Type>>& removeVolatile(Type&& value) noexcept {
        return const_cast<RemoveVolatile<RemoveRef<Type>>&>(value);
    }

    template <typename Type>
    E_RET_NO_DISCARD()
    inline constexpr RemoveCv<RemoveRef<Type>>& removeCv(Type&& value) noexcept {
        return const_cast<RemoveCv<RemoveRef<Type>>&>(value);
    }

    template <typename Type>
    E_RET_NO_DISCARD()
    inline constexpr RemoveRefConst<Type> removeRefConst(Type&& value) noexcept {
        return const_cast<RemoveRefConst<Type>>(value);
    }

    template <typename Type>
    E_RET_NO_DISCARD()
    inline constexpr RemoveRefVolatile<Type> removeRefVolatile(Type&& value) noexcept {
        return const_cast<RemoveRefVolatile<Type>>(value);
    }

    template <typename Type>
    E_RET_NO_DISCARD()
    inline constexpr RemoveRefCv<Type> removeRefCv(Type&& value) noexcept {
        return const_cast<RemoveRefCv<Type>>(value);
    }

    template <typename Type>
    E_RET_NO_DISCARD()
    inline constexpr RemovePtrConst<RemoveRef<Type>> removePtrConst(Type&& value) noexcept {
        return const_cast<RemovePtrConst<RemoveRef<Type>>&>(value);
    }

    template <typename Type>
    E_RET_NO_DISCARD()
    inline constexpr RemovePtrVolatile<RemoveRef<Type>> removePtrVolatile(Type&& value) noexcept {
        return const_cast<RemovePtrVolatile<RemoveRef<Type>>&>(value);
    }

    template <typename Type>
    E_RET_NO_DISCARD()
    inline constexpr RemovePtrCv<RemoveRef<Type>>& removePtrCv(Type&& value) noexcept {
        return const_cast<RemovePtrCv<RemoveRef<Type>&>>(value);
    }

    template <typename Type>
    inline constexpr void ignore(Type&&) noexcept {}

    template <typename Callable, typename... Args>
    requires (!isMemberPointer<RemoveRef<Callable>>)
    inline constexpr auto invoke(Callable&& callable, Args&&... args)
        noexcept(noexcept(static_cast<Callable&&>(callable)(forward<Args&&>(args)...))) {
        return static_cast<Callable&&>(callable)(forward<Args&&>(args)...);
    }

    template <typename Callable, typename Class, typename... Args>
    requires (isMemFuncPtr<RemoveRef<Callable>> && isBaseOf<typename MemFuncPtrParser<RemoveRef<Callable>>::ClassType, RemoveRef<Class>>)
    inline constexpr auto invoke(Callable&& callable, Class&& object, Args&&... args)
        noexcept(noexcept((static_cast<Class&&>(object).*callable)(forward<Args&&>(args)...))) {
        return (static_cast<Class&&>(object).*callable)(forward<Args&&>(args)...);
    }

    template <typename Callable, typename Class, typename... Args>
    requires (isMemFuncPtr<RemoveRef<Callable>> && !isBaseOf<typename MemFuncPtrParser<RemoveRef<Callable>>::ClassType, RemoveRef<Class>>)
    inline constexpr auto invoke(Callable&& callable, Class&& object, Args&&... args)
        noexcept(noexcept(((*static_cast<Class&&>(object)).*callable)(forward<Args&&>(args)...))) {
        return ((*static_cast<Class&&>(object)).*callable)(forward<Args&&>(args)...);
    }

    template <typename Member, typename Class>
    requires (isMemObjPtr<RemoveRef<Member>> && isBaseOf<typename MemObjPtrParser<RemoveRef<Member>>::ClassType, RemoveRef<Class>>)
    inline constexpr auto invoke(Member&& member, Class&& object) noexcept {
        return static_cast<Class&&>(object).*member;
    }

    template <typename Member, typename Class>
    requires (isMemObjPtr<RemoveRef<Member>> && !isBaseOf<typename MemObjPtrParser<RemoveRef<Member>>::ClassType, RemoveRef<Class>>)
    inline constexpr auto invoke(Member&& member, Class&& object) noexcept(noexcept((*static_cast<Class&&>(object)).*member)) {
        return (*static_cast<Class&&>(object)).*member;
    }

    template <typename Derived, typename Base>
    requires isPolymorphicClass<RemoveRef<Base>> && isSame<Derived, RemoveRef<Base>>
    E_RET_NO_DISCARD()
    inline constexpr bool isInstanceOf(Base&&) noexcept {
        return true;
    }

    template <typename Derived, typename Base>
    requires isPolymorphicClass<RemoveRef<Base>> && isBaseOfNs<RemoveRef<Base>, Derived>
    E_RET_NO_DISCARD()
    inline constexpr bool isInstanceOf(Base&& value) noexcept {
        return dynamic_cast<Derived*>(&value) != nullptr;
    }
}

E_CLANG_WARNING_POP E_MSVC_WARNING_POP E_GCC_WARNING_POP

E_CTIDY_NOLINTEND(bugprone-macro-parentheses)

#undef _FUNC_TEMPLATE_CV
#undef _FUNC_TEMPLATE_CV_REF
#undef _FUNC_TEMPLATE_CV_REF_NOEXCEPT

#undef _FUNC_TEMPLATE_PTR
#undef _FUNC_TEMPLATE_PTR_NOEXCEPT

#undef _FUNC_TEMPLATE_MEMBER_PTR
#undef _FUNC_TEMPLATE_MEMBER_PTR_CV
#undef _FUNC_TEMPLATE_MEMBER_PTR_CV_REF
#undef _FUNC_TEMPLATE_MEMBER_PTR_CV_REF_NOEXCEPT

#undef _FUNC_TEMPLATE_CDECL
#undef _FUNC_TEMPLATE_FASTCALL
#undef _FUNC_TEMPLATE_STDCALL
#undef _FUNC_TEMPLATE_THISCALL
#undef _FUNC_TEMPLATE_VECTORCALL
#undef _FUNC_TEMPLATE_CLRCALL

#undef _CV_OPT_TEMPLATE
#undef _BASE_INT_TYPE_TEMPLATE
#undef _FUNC_TEMPLATE
#undef _FUNC_WITH_VARARGS_TEMPLATE
#undef _FUNC_PTR_TEMPLATE
#undef _FUNC_WITH_VARARGS_PTR_TEMPLATE
#undef _MEMBER_FUNC_PTR_TEMPLATE
#undef _MEMBER_FUNC_WITH_VARARGS_PTR_TEMPLATE
