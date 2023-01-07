/*
 * Copyright (C) 2023 Liu Baihao. All rights reserved.
 *
 * Licensed under the Enhanced Software License.
 *
 * This file is part of the Enhanced Software, and IT ALWAYS
 * PROVIDES "AS IS" WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 *
 * You may not use this file except in compliance with the License.
 * You should obtain a copy of the License in the distribution,
 * if not, see <https://sharedwonder.github.io/enhanced/LICENSE.txt>
 */

#pragma once

#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/Warnings.h>

#define _CV_OPT_TEMPLATE \
    _TEMPLATE(EMPTY_MACRO_ARG) \
    _TEMPLATE(const) \
    _TEMPLATE(volatile) \
    _TEMPLATE(const volatile)

#define _BASE_INT_TYPE_TEMPLATE \
    _TEMPLATE(char) \
    _TEMPLATE(short) \
    _TEMPLATE(int) \
    _TEMPLATE(long) \
    _TEMPLATE(long long)

// ======================================================================

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

#define _FUNC_TEMPLATE_CDECL(SUFFIX) _FUNC_TEMPLATE_ ## SUFFIX(enhanced::util::CallingConvention::Cdecl, CDECL)

#if defined(X86_ARCH) && !defined(MS_CLR_ABI)
    #define _FUNC_TEMPLATE_FASTCALL(SUFFIX) _FUNC_TEMPLATE_ ## SUFFIX(enhanced::util::CallingConvention::Fastcall, FASTCALL)
#else
    #define _FUNC_TEMPLATE_FASTCALL(SUFFIX)
#endif

#ifdef X86_ARCH
    #define _FUNC_TEMPLATE_STDCALL(SUFFIX) _FUNC_TEMPLATE_ ## SUFFIX(enhanced::util::CallingConvention::Stdcall, STDCALL)
    #define _FUNC_TEMPLATE_THISCALL(SUFFIX) _FUNC_TEMPLATE_ ## SUFFIX(enhanced::util::CallingConvention::Thiscall, THISCALL)
#else
    #define _FUNC_TEMPLATE_STDCALL(SUFFIX)
    #define _FUNC_TEMPLATE_THISCALL(SUFFIX)
#endif

#ifdef MSVC_ABI
    #ifdef MS_CLR_ABI
        #define _FUNC_TEMPLATE_VECTORCALL(SUFFIX)
        #define _FUNC_TEMPLATE_CLRCALL(SUFFIX) _FUNC_TEMPLATE_ ## SUFFIX(enhanced::util::CallingConvention::Clrcall, CLRCALL)
    #elif (defined(X86_ARCH) && _M_IX86_FP >= 2) || defined(X64_ARCH)
        #define _FUNC_TEMPLATE_VECTORCALL(SUFFIX) _FUNC_TEMPLATE_ ## SUFFIX(enhanced::util::CallingConvention::Vectorcall, VECTORCALL)
        #define _FUNC_TEMPLATE_CLRCALL(SUFFIX)
    #endif
#else
    #define _FUNC_TEMPLATE_VECTORCALL(SUFFIX)
    #define _FUNC_TEMPLATE_CLRCALL(SUFFIX)
#endif

// ======================================================================

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

namespace enhancedInternal::util::traits {
    template <bool, typename = void>
    struct EnableIfImpl final {};

    template <typename RawType>
    struct EnableIfImpl<true, RawType> final {
        using Type = RawType;
    };

    // ======================================================================

    template <bool, typename, typename Result>
    struct ConditionalImpl final {
        using Type = Result;
    };

    template <typename Result, typename AnotherType>
    struct ConditionalImpl<true, Result, AnotherType> final {
        using Type = Result;
    };

    // ======================================================================

    template <typename RawType>
    struct RemoveConstImpl final {
        using Type = RawType;
    };

    template <typename RawType>
    struct RemoveConstImpl<const RawType> final {
        using Type = RawType;
    };

    // ======================================================================

    template <typename RawType>
    struct RemoveVolatileImpl final {
        using Type = RawType;
    };

    template <typename RawType>
    struct RemoveVolatileImpl<volatile RawType> final {
        using Type = RawType;
    };

    // ======================================================================

    template <typename RawType>
    struct RemoveRefImpl final {
        using Type = RawType;
    };

    template <typename RawType>
    struct RemoveRefImpl<RawType&> final {
        using Type = RawType;
    };

    template <typename RawType>
    struct RemoveRefImpl<RawType&&> final {
        using Type = RawType;
    };

    // ======================================================================

    template <typename RawType>
    struct RemoveRefConstImpl final {
        using Type = RawType;
    };

    template <typename RawType>
    struct RemoveRefConstImpl<const RawType&> final {
        using Type = RawType&;
    };

    template <typename RawType>
    struct RemoveRefConstImpl<const RawType&&> final {
        using Type = RawType&&;
    };

    // ======================================================================

    template <typename RawType>
    struct RemoveRefVolatileImpl final {
        using Type = RawType;
    };

    template <typename RawType>
    struct RemoveRefVolatileImpl<volatile RawType&> final {
        using Type = RawType&;
    };

    template <typename RawType>
    struct RemoveRefVolatileImpl<volatile RawType&&> final {
        using Type = RawType&&;
    };

    // ======================================================================

    template <typename RawType>
    struct RemovePointerImpl final {
        using Type = RawType;
    };

#define _TEMPLATE(CV_OPT) \
    template <typename RawType> \
    struct RemovePointerImpl<RawType* CV_OPT> final { \
        using Type = RawType; \
    };

    template <typename RawType>
    struct RemovePointerImpl<RawType*> final {
        using Type = RawType;
    };

    template <typename RawType>
    struct RemovePointerImpl<RawType* const> final {
        using Type = RawType;
    };

    template <typename RawType>
    struct RemovePointerImpl<RawType* volatile> final {
        using Type = RawType;
    };

    template <typename RawType>
    struct RemovePointerImpl<RawType* const volatile> final {
        using Type = RawType;
    };
#undef _TEMPLATE

    // ======================================================================

    template <bool, typename RawType>
    struct AddReferenceImpl final {
        using LvalueRef = RawType;
        using RvalueRef = RawType;
    };

    template <typename RawType>
    struct AddReferenceImpl<true, RawType> final {
        using LvalueRef = RawType&;
        using RvalueRef = RawType&&;
    };

    // ======================================================================

    template <typename RawType>
    struct RemovePtrConstImpl final {
        using Type = RawType;
    };

#define _TEMPLATE(CV_OPT) \
    template <typename RawType> \
    struct RemovePtrConstImpl<const RawType* CV_OPT> final { \
        using Type = RawType* CV_OPT; \
    };

    _CV_OPT_TEMPLATE
#undef _TEMPLATE

    // ======================================================================

    template <typename RawType>
    struct RemovePtrVolatileImpl final {
        using Type = RawType;
    };

#define _TEMPLATE(CV_OPT) \
    template <typename RawType> \
    struct RemovePtrVolatileImpl<volatile RawType* CV_OPT> final { \
        using Type = RawType* CV_OPT; \
    };

    _CV_OPT_TEMPLATE
#undef _TEMPLATE

    template <typename RawType>
    struct ToSignedImpl final {
        using Type = RawType;
    };

    template <>
    struct ToSignedImpl<char> final {
        using Type = schar;
    };

#define _TEMPLATE(BASE_INT_TYPE) \
    template <> \
    struct ToSignedImpl<unsigned BASE_INT_TYPE> final { \
        using Type = signed BASE_INT_TYPE; \
    };

    _BASE_INT_TYPE_TEMPLATE
#undef _TEMPLATE

    template <typename RawType>
    struct ToUnsignedImpl final {
        using Type = RawType;
    };

    template <>
    struct ToUnsignedImpl<char> final {
        using Type = uchar;
    };

#define _TEMPLATE(BASE_INT_TYPE) \
    template <> \
    struct ToUnsignedImpl<signed BASE_INT_TYPE> final { \
        using Type = unsigned BASE_INT_TYPE; \
    };

    _BASE_INT_TYPE_TEMPLATE
#undef _TEMPLATE
}

namespace enhanced::util::inline traits {
    template <typename>
    using VoidTemplate $DeprecatedExt("Recommended to use C++20 concepts") = void;

    template <bool condition, typename Type = void>
    using EnableIf $DeprecatedExt("Recommended to use C++20 concepts") =
        typename enhancedInternal::util::traits::EnableIfImpl<condition, Type>::Type;

    template <bool condition, typename Type1, typename Type2>
    using Conditional = typename enhancedInternal::util::traits::ConditionalImpl<condition, Type1, Type2>::Type;

    template <typename Type>
    using RemoveRef = typename enhancedInternal::util::traits::RemoveRefImpl<Type>::Type;

    template <typename Type>
    using RemovePointer = typename enhancedInternal::util::traits::RemovePointerImpl<Type>::Type;

    template <typename Type>
    using RemoveConst = typename enhancedInternal::util::traits::RemoveConstImpl<Type>::Type;

    template <typename Type>
    using RemoveVolatile = typename enhancedInternal::util::traits::RemoveVolatileImpl<Type>::Type;

    template <typename Type>
    using RemoveCv = RemoveConst<RemoveVolatile<Type>>;

    template <bool first, bool... conditions>
    inline constexpr bool allOfTrue = first;

    template <bool next, bool... conditions>
    inline constexpr bool allOfTrue<true, next, conditions...> = allOfTrue<next, conditions...>;

    template <bool first, bool... conditions>
    inline constexpr bool anyOfTrue = first;

    template <bool next, bool... conditions>
    inline constexpr bool anyOfTrue<false, next, conditions...> = anyOfTrue<next, conditions...>;

    template <typename...>
    inline constexpr sizetype typeCounter = 0;

    template <typename First>
    inline constexpr sizetype typeCounter<First> = 1;

    template <typename First, typename... Others>
    inline constexpr sizetype typeCounter<First, Others...> = typeCounter<Others...> + 1;

#if defined(MSVC_COMPILER)
    template <typename, typename>
    inline constexpr bool isSame = false;

    template <typename Type>
    inline constexpr bool isSame<Type, Type> = true;
#else
    template <typename Type1, typename Type2>
    inline constexpr bool isSame = __is_same(Type1, Type2);
#endif

    template <typename Type, typename... Others>
    inline constexpr bool isAnyOf = anyOfTrue<isSame<Type, Others>...>;

    template <typename Base, typename Derived>
    inline constexpr bool isBaseOf = __is_base_of(Base, Derived);

    template <typename Base, typename... Derived>
    inline constexpr bool isAllBaseOf = allOfTrue<isBaseOf<Base, Derived>...>;

    template <typename Base, typename... Derived>
    inline constexpr bool isAnyBaseOf = anyOfTrue<isBaseOf<Base, Derived>...>;

    template <typename Base, typename Derived>
    inline constexpr bool isBaseOfNs = isBaseOf<Base, Derived> && !isSame<Base, Derived>;

    template <typename Base, typename... Derived>
    inline constexpr bool isAllBaseOfNs = allOfTrue<isBaseOfNs<Base, Derived>...>;

    template <typename Base, typename... Derived>
    inline constexpr bool isAnyBaseOfNs = anyOfTrue<isBaseOfNs<Base, Derived>...>;

    template <typename...>
    inline constexpr bool isValid = true; // Used for C++20 concepts determines type expression is valid.

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
    requires isValid<Type&>
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
    using AddLvalueRef = typename enhancedInternal::util::traits::AddReferenceImpl<isReferenceable<Type>, Type>::LvalueRef;

    template <typename Type>
    using AddRvalueRef = typename enhancedInternal::util::traits::AddReferenceImpl<isReferenceable<Type>, Type>::RvalueRef;

    template <typename Type>
    requires isReference<Type>
    using RemoveRefConst = typename enhancedInternal::util::traits::RemoveRefConstImpl<Type>::Type;

    template <typename Type>
    requires isReference<Type>
    using RemoveRefVolatile = typename enhancedInternal::util::traits::RemoveRefVolatileImpl<Type>::Type;

    template <typename Type>
    requires isReference<Type>
    using RemoveRefCv = RemoveRefConst<RemoveRefVolatile<Type>>;

    template <typename Type>
    using RemoveRefAndCv = RemoveCv<RemoveRef<Type>>;

    template <typename Type>
    requires isPointer<Type>
    using RemovePtrConst = typename enhancedInternal::util::traits::RemovePtrConstImpl<Type>::Type;

    template <typename Type>
    requires isPointer<Type>
    using RemovePtrVolatile = typename enhancedInternal::util::traits::RemovePtrVolatileImpl<Type>::Type;

    template <typename Type>
    requires isPointer<Type>
    using RemovePtrCv = RemovePtrConst<RemovePtrVolatile<Type>>;

    template <typename Type>
    using RemovePtrAndCv = RemoveCv<RemovePointer<Type>>;

    template <typename Type>
    $NoIgnoreReturn
    constexpr Type declvalue() noexcept; // Used for compile-time type inference, no implementation required.

    template <typename Type>
    $NoIgnoreReturn
    inline constexpr Type& weakCast(Type&& value) noexcept {
        return value;
    }

#define _TEMPLATE(CV_OPT) \
    template <typename Type> \
    $NoIgnoreReturn \
    inline constexpr Type& weakCast(CV_OPT Type& value) noexcept { \
        return const_cast<Type&>(value); \
    }

    _CV_OPT_TEMPLATE
#undef _TEMPLATE

    template <typename Type>
    $NoIgnoreReturn
    inline constexpr Type& forceCast(auto&& value) noexcept {
        return *((Type*) &value);
    }

    template <typename... Types>
    inline constexpr sizetype valueCounter(Types&&...) noexcept {
        return typeCounter<Types...>;
    }

    template <typename Type>
    inline constexpr bool isIntegralType =
        isAnyOf<RemoveCv<Type>, char,
    #ifdef WCHAR_IS_BUILTIN_TYPE
        wchar,
    #endif
        u8char, u16char, u32char, bool, schar, uchar, short, ushort, int, uint, long, ulong, llong, ullong>;

    template <typename Type>
    inline constexpr bool isFloatType = isAnyOf<RemoveCv<Type>, float, double, ldouble>;

    template <typename Type>
    inline constexpr bool isCharType =
        isAnyOf<RemoveCv<Type>, char,
    #ifdef WCHAR_IS_BUILTIN_TYPE
        wchar,
    #endif
        u8char, u16char, u32char>;

    template <typename Type>
    inline constexpr bool isIntegralTypeNc = isIntegralType<Type> && !isCharType<Type>;

    template <typename Type>
    inline constexpr bool isIntegralTypeNs = isIntegralTypeNc<Type> && !isSame<Type, bool>;

    template <typename Type>
    requires isIntegralType<Type>
    inline constexpr bool isSigned = static_cast<RemoveCv<Type>>(-1) < static_cast<Type>(0);

    template <typename Type>
    requires isIntegralType<Type>
    inline constexpr bool isUnsigned = static_cast<RemoveCv<Type>>(-1) >= static_cast<Type>(0);

    template <typename Type>
    requires isIntegralType<Type>
    using ToSigned = typename enhancedInternal::util::traits::ToSignedImpl<Type>::Type;

    template <typename Type>
    requires isIntegralType<Type>
    using ToUnsigned = typename enhancedInternal::util::traits::ToUnsignedImpl<Type>::Type;

    template <typename Type>
    inline constexpr bool isArithmeticType = isIntegralType<Type> || isFloatType<Type>;

    template <typename Type>
    inline constexpr bool isEmptyType = __is_empty(Type);

    template <typename Type>
    inline constexpr bool isVoidType = isSame<RemoveCv<Type>, void>;

    template <typename Type>
    inline constexpr bool isNullType = isSame<RemoveCv<Type>, nulltype>;

    template <typename Type>
    inline constexpr bool isBasicType = isArithmeticType<Type> || isVoidType<Type> || isNullType<Type>;

    template <typename Type>
    inline constexpr bool isCompoundType = !isBasicType<Type>;

    template <typename Type>
    inline constexpr bool isEnum = __is_enum(Type);

    template <typename Type>
    inline constexpr bool isClass = __is_class(Type);

    template <typename Type>
    inline constexpr bool isStruct = isClass<Type>;

    template <typename Type>
    inline constexpr bool isUnion = __is_union(Type);

    template <typename, template <typename...> typename>
    inline constexpr bool isSpecialization = false;

    template <template <typename...> typename Template, typename... Types>
    inline constexpr bool isSpecialization<Template<Types...>, Template> = true;

    // Only function types and reference types cannot be const qualified.

    MSVC_WARNING_PUSH_AND_DISABLE(4180)

    template <typename Type>
    inline constexpr bool isObject = !isVoidType<Type> && isConst<const Type>;

    template <typename Type>
    inline constexpr bool isFunction = !isReference<Type> && !isConst<const Type>;

    MSVC_WARNING_POP

    enum class CallingConvention {
        Cdecl, Fastcall, Stdcall, Thiscall,
    #ifdef MSVC_ABI
        Vectorcall,
        #ifdef MS_CLR_ABI
        Clrcall
        #endif
    #endif
    };

    template <typename Type>
    requires isFunction<Type>
    struct FunctionParser {};

#define _TEMPLATE(CALLING_CONVENTION, CALL_OPT, CV_OPT, REF_OPT, NOEXCEPT_OPT) \
    template <typename Return, typename... Args> \
    struct FunctionParser<Return CALL_OPT (Args...) CV_OPT REF_OPT NOEXCEPT_OPT> { \
        using Type = Return CALL_OPT (Args...) CV_OPT REF_OPT NOEXCEPT_OPT; \
        using ReturnType = Return; \
        using NeatFunctionType = Return (Args...); \
        static constexpr CallingConvention callingConvention = CALLING_CONVENTION; \
        static constexpr bool hasVarargs = false; \
    };

    _FUNC_TEMPLATE
#undef _TEMPLATE

#define _TEMPLATE(CALLING_CONVENTION, CALL_OPT, CV_OPT, REF_OPT, NOEXCEPT_OPT) \
    template <typename Return, typename... Args> \
    struct FunctionParser<Return CALL_OPT (Args..., ...) CV_OPT REF_OPT NOEXCEPT_OPT> { \
        using Type = Return CALL_OPT (Args..., ...) CV_OPT REF_OPT NOEXCEPT_OPT; \
        using ReturnType = Return; \
        using NeatFunctionType = Return (Args..., ...); \
        static constexpr CallingConvention callingConvention = CALLING_CONVENTION; \
        static constexpr bool hasVarargs = true; \
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
        using NeatFunctionType = Return (Args...); \
        static constexpr CallingConvention callingConvention = CALLING_CONVENTION; \
        static constexpr bool hasVarargs = false; \
    };

    _FUNC_PTR_TEMPLATE
#undef _TEMPLATE

#define _TEMPLATE(PTR_CV_OPT, CALLING_CONVENTION, CALL_OPT, NOEXCEPT_OPT) \
    template <typename Return, typename... Args> \
    struct FunctionPtrParser<Return (CALL_OPT* PTR_CV_OPT)(Args..., ...) NOEXCEPT_OPT> { \
        using Type = Return (CALL_OPT* PTR_CV_OPT)(Args..., ...) NOEXCEPT_OPT; \
        using ReturnType = Return; \
        using NeatFunctionType = Return (Args..., ...); \
        static constexpr CallingConvention callingConvention = CALLING_CONVENTION; \
        static constexpr bool hasVarargs = true; \
    };

    _FUNC_WITH_VARARGS_PTR_TEMPLATE
#undef _TEMPLATE

#ifdef CLANG_COMPILER
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
    inline constexpr bool isMemObjPtr<Type Class::* CV_OPT> = enhanced::util::isObject<Type>;

    _CV_OPT_TEMPLATE
#undef _TEMPLATE

    template <typename Type>
    inline constexpr bool isMemFuncPtr = false;

#define _TEMPLATE(CV_OPT) \
    template <typename Type, typename Class> \
    inline constexpr bool isMemFuncPtr<Type Class::* CV_OPT> = enhanced::util::isFunction<Type>;

    _CV_OPT_TEMPLATE
#undef _TEMPLATE

    template <typename Type>
    inline constexpr bool isMemberPointer = isMemObjPtr<Type> || isMemFuncPtr<Type>;
#endif

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
        using NeatFunctionType = Return (Args...); \
        static constexpr CallingConvention callingConvention = CALLING_CONVENTION; \
        static constexpr bool hasVarargs = false; \
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
        using NeatFunctionType = Return (Args..., ...); \
        static constexpr CallingConvention callingConvention = CALLING_CONVENTION; \
        static constexpr bool hasVarargs = true; \
    };

    _MEMBER_FUNC_WITH_VARARGS_PTR_TEMPLATE
#undef _TEMPLATE

    template <typename Type>
    inline constexpr bool isScalarType = isArithmeticType<Type> || isEnum<Type> || isPointer<Type> || isMemberPointer<Type> || isNullType<Type>;

    template <typename Type>
    inline constexpr bool isPolymorphicClass = __is_polymorphic(Type);

    template <typename Type>
    inline constexpr bool isAbstractClass = __is_abstract(Type);

    template <typename Type>
    inline constexpr bool isFinalClass = __is_final(Type);

#ifdef GCC_COMPILER
    template <typename From, typename To>
    inline constexpr bool isConvertible = false;

    template <typename From, typename To>
    requires isVoidType<From> && isVoidType<To>
    inline constexpr bool isConvertible<From, To> = true;

    template <typename From, typename To>
    requires (!isVoidType<From> && !isVoidType<To>) && isValid<decltype(weakCast<To>(declvalue<From>()))>
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
    requires (!isVoidType<From> && !isVoidType<To>) && isValid<decltype((To) declvalue<From>())>
    inline constexpr bool isGeneralConvertible<From, To> = true;

    template <typename From, typename To>
    inline constexpr bool isStaticConvertible = false;

    template <typename From, typename To>
    requires isVoidType<To>
    inline constexpr bool isStaticConvertible<From, To> = true;

    template <typename From, typename To>
    requires (!isVoidType<From> && !isVoidType<To>) && isValid<decltype(static_cast<To>(declvalue<From>()))>
    inline constexpr bool isStaticConvertible<From, To> = true;

    template <typename From, typename To>
    inline constexpr bool isReintConvertible = false;

    template <typename From, typename To>
    requires isVoidType<From> && isVoidType<To>
    inline constexpr bool isReintConvertible<From, To> = true;

    template <typename From, typename To>
    requires (!isVoidType<From> && !isVoidType<To>) && isValid<decltype(reinterpret_cast<To>(declvalue<From>()))>
    inline constexpr bool isReintConvertible<From, To> = true;

    template <typename From, typename To>
    inline constexpr bool isCvConvertible = false;

    template <typename From, typename To>
    requires isVoidType<From> && isVoidType<To>
    inline constexpr bool isCvConvertible<From, To> = true;

    template <typename From, typename To>
    requires (!isVoidType<From> && !isVoidType<To>) && isValid<decltype(const_cast<To>(declvalue<From>()))>
    inline constexpr bool isCvConvertible<From, To> = true;

    template <typename Type, typename... Args>
    inline constexpr bool isConstructible = __is_constructible(Type, Args...);

    template <typename Type>
    inline constexpr bool isDefaultConstructible = isConstructible<Type>;

    MSVC_WARNING_PUSH_AND_DISABLE(4180)

    template <typename Type>
    inline constexpr bool isCopyConstructible = isConstructible<Type, AddLvalueRef<const Type>>;

    template <typename Type>
    inline constexpr bool isMoveConstructible = isConstructible<Type, AddRvalueRef<Type>>;

    MSVC_WARNING_POP

#ifdef GCC_ABI
    template <typename Type>
    inline constexpr bool isDestructible = false;

    template <typename Type>
    requires isObject<Type> && (!isClass<Type>)
    inline constexpr bool isDestructible<Type> = true;

    template <typename Type>
    requires isClass<Type> && (isValidValue(declvalue<Type>().~Type()))
    inline constexpr bool isDestructible<Type> = true;
#else
    template <typename Type>
    inline constexpr bool isDestructible = __is_destructible(Type);
#endif

    template <typename Type>
    $NoIgnoreReturn
    inline constexpr RemoveCv<RemoveRef<Type>>&& move(Type&& value) noexcept {
        return const_cast<RemoveCv<RemoveRef<Type>>&&>(value);
    }

    template <typename Type>
    $NoIgnoreReturn
    inline constexpr RemoveRef<Type>&& moveIf(Type&& value) noexcept {
        return static_cast<RemoveRef<Type>&&>(value);
    }

    template <typename Type>
    $NoIgnoreReturn
    inline constexpr Type&& forward(RemoveRef<Type>& value) noexcept {
        return static_cast<Type&&>(value);
    }

    template <typename Type>
    requires (!isLvalueRef<Type>)
    $NoIgnoreReturn
    inline constexpr Type&& forward(RemoveRef<Type>&& value) noexcept {
        return static_cast<Type&&>(value);
    }

    template <typename Case, typename First, typename... Types>
    requires isSame<Case, First>
    $NoIgnoreReturn
    inline constexpr Case& switchType(First&& first, Types&&...) noexcept {
        return first;
    }

    template <typename Case, typename First, typename... Types>
    requires (!isSame<Case, First>)
    $NoIgnoreReturn
    inline constexpr Case& switchType(First&&, Types&&... values) noexcept {
        return switchType<Case, Types...>(static_cast<Types&&>(values)...);
    }

    template <typename Callable, typename... Args>
    requires (!isMemberPointer<RemoveRef<Callable>>)
    inline constexpr auto invoke(Callable&& callable, Args&&... args)
        noexcept(noexcept(static_cast<Callable&&>(callable)(static_cast<Args&&>(args)...))) {
        return static_cast<Callable&&>(callable)(static_cast<Args&&>(args)...);
    }

    template <typename Callable, typename Class, typename... Args>
    requires (isMemFuncPtr<RemoveRef<Callable>> && isBaseOf<typename MemFuncPtrParser<RemoveRef<Callable>>::ClassType, RemoveRef<Class>>)
    inline constexpr auto invoke(Callable&& callable, Class&& object, Args&&... args)
        noexcept(noexcept((static_cast<Class&&>(object).*callable)(static_cast<Args&&>(args)...))) {
        return (static_cast<Class&&>(object).*callable)(static_cast<Args&&>(args)...);
    }

    template <typename Callable, typename Class, typename... Args>
    requires (isMemFuncPtr<RemoveRef<Callable>> && !isBaseOf<typename MemFuncPtrParser<RemoveRef<Callable>>::ClassType, RemoveRef<Class>>)
    inline constexpr auto invoke(Callable&& callable, Class&& object, Args&&... args)
        noexcept(noexcept(((*static_cast<Class&&>(object)).*callable)(static_cast<Args&&>(args)...))) {
        return ((*static_cast<Class&&>(object)).*callable)(static_cast<Args&&>(args)...);
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

    template <typename Type>
    $NoIgnoreReturn
    inline constexpr const RemoveRef<Type>& addConst(Type&& value) noexcept {
        return const_cast<const RemoveRef<Type>&>(value);
    }

    template <typename Type>
    $NoIgnoreReturn
    inline constexpr volatile RemoveRef<Type>& addVolatile(Type&& value) noexcept {
        return const_cast<volatile RemoveRef<Type>&>(value);
    }

    template <typename Type>
    $NoIgnoreReturn
    inline constexpr const volatile RemoveRef<Type>& addCv(Type&& value) noexcept {
        return const_cast<const volatile RemoveRef<Type>&>(value);
    }

    template <typename Type>
    requires isPointer<RemoveRef<Type>>
    $NoIgnoreReturn
    inline constexpr const RemovePointer<RemoveRef<Type>>*& addPtrConst(Type&& value) noexcept {
        return const_cast<const RemovePointer<RemoveRef<Type>>*&>(value);
    }

    template <typename Type>
    requires isPointer<RemoveRef<Type>>
    $NoIgnoreReturn
    inline constexpr volatile RemovePointer<RemoveRef<Type>>*& addPtrVolatile(Type&& value) noexcept {
        return const_cast<volatile RemovePointer<RemoveRef<Type>>*&>(value);
    }

    template <typename Type>
    requires isPointer<RemoveRef<Type>>
    $NoIgnoreReturn
    inline constexpr const volatile RemovePointer<RemoveRef<Type>>*& addPtrCv(Type&& value) noexcept {
        return const_cast<const volatile RemovePointer<RemoveRef<Type>>*&>(value);
    }

    template <typename Type>
    $NoIgnoreReturn
    inline constexpr RemoveConst<RemoveRef<Type>>& removeConst(Type&& value) noexcept {
        return const_cast<RemoveConst<RemoveRef<Type>>&>(value);
    }

    template <typename Type>
    $NoIgnoreReturn
    inline constexpr RemoveVolatile<RemoveRef<Type>>& removeVolatile(Type&& value) noexcept {
        return const_cast<RemoveVolatile<RemoveRef<Type>>&>(value);
    }

    template <typename Type>
    $NoIgnoreReturn
    inline constexpr RemoveCv<RemoveRef<Type>>& removeCv(Type&& value) noexcept {
        return const_cast<RemoveCv<RemoveRef<Type>>&>(value);
    }

    template <typename Type>
    $NoIgnoreReturn
    inline constexpr RemoveRefConst<Type> removeRefConst(Type&& value) noexcept {
        return const_cast<RemoveRefConst<Type>>(value);
    }

    template <typename Type>
    $NoIgnoreReturn
    inline constexpr RemoveRefVolatile<Type> removeRefVolatile(Type&& value) noexcept {
        return const_cast<RemoveRefVolatile<Type>>(value);
    }

    template <typename Type>
    $NoIgnoreReturn
    inline constexpr RemoveRefCv<Type> removeRefCv(Type&& value) noexcept {
        return const_cast<RemoveRefCv<Type>>(value);
    }

    template <typename Type>
    $NoIgnoreReturn
    inline constexpr RemovePtrConst<RemoveRef<Type>> removePtrConst(Type&& value) noexcept {
        return const_cast<RemovePtrConst<RemoveRef<Type>>&>(value);
    }

    template <typename Type>
    $NoIgnoreReturn
    inline constexpr RemovePtrVolatile<RemoveRef<Type>> removePtrVolatile(Type&& value) noexcept {
        return const_cast<RemovePtrVolatile<RemoveRef<Type>>&>(value);
    }

    template <typename Type>
    $NoIgnoreReturn
    inline constexpr RemovePtrCv<RemoveRef<Type>>& removePtrCv(Type&& value) noexcept {
        return const_cast<RemovePtrCv<RemoveRef<Type>&>>(value);
    }

    template <typename Derived, typename Base>
    requires isPolymorphicClass<RemoveRef<Base>> && isSame<Derived, RemoveRef<Base>>
    $NoIgnoreReturn
    inline constexpr bool isInstanceOf(Base&&) noexcept {
        return true;
    }

    template <typename Derived, typename Base>
    requires isPolymorphicClass<RemoveRef<Base>> && isBaseOfNs<RemoveRef<Base>, Derived>
    $NoIgnoreReturn
    inline constexpr bool isInstanceOf(Base&& value) noexcept {
        return dynamic_cast<Derived*>(&value) != nullptr;
    }
}

#undef _CV_OPT_TEMPLATE
#undef _BASE_INT_TYPE_TEMPLATE
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
#undef _FUNC_TEMPLATE
#undef _FUNC_WITH_VARARGS_TEMPLATE
#undef _FUNC_PTR_TEMPLATE
#undef _FUNC_WITH_VARARGS_PTR_TEMPLATE
#undef _MEMBER_FUNC_PTR_TEMPLATE
#undef _MEMBER_FUNC_WITH_VARARGS_PTR_TEMPLATE
