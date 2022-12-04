/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 *
 * Licensed under the Enhanced Software License.
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://sharedwonder.github.io/enhanced/LICENSE.txt
 *
 * UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING,
 * THE SOFTWARE IS ALWAYS PROVIDED "AS IS",
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#pragma once

#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>

#define _IMPL_CV_OPT_TEMPLATE \
    _IMPL_TEMPLATE(); \
    _IMPL_TEMPLATE(const); \
    _IMPL_TEMPLATE(volatile); \
    _IMPL_TEMPLATE(const volatile);

namespace enhancedInternal::util::traits {
    template <typename RawType>
    struct RemoveConstImpl final {
        using Type = RawType;
    };

    template <typename RawType>
    struct RemoveConstImpl<const RawType> final {
        using Type = RawType;
    };

    // ----------------------------------------------------------------------

    template <typename RawType>
    struct RemoveVolatileImpl final {
        using Type = RawType;
    };

    template <typename RawType>
    struct RemoveVolatileImpl<volatile RawType> final {
        using Type = RawType;
    };

    // ----------------------------------------------------------------------

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

    // ----------------------------------------------------------------------

    template <typename RawType>
    struct RemoveRefConstImpl final {
        using Type = RawType;
    };

    template <typename RwaType>
    struct RemoveRefConstImpl<const RwaType&> final {
        using Type = RwaType&;
    };

    template <typename RwaType>
    struct RemoveRefConstImpl<const RwaType&&> final {
        using Type = RwaType&&;
    };

    // ----------------------------------------------------------------------

    template <typename RawType>
    struct RemoveRefVolatileImpl final {
        using Type = RawType;
    };

    template <typename RwaType>
    struct RemoveRefVolatileImpl<volatile RwaType&> final {
        using Type = RwaType&;
    };

    template <typename RwaType>
    struct RemoveRefVolatileImpl<volatile RwaType&&> final {
        using Type = RwaType&&;
    };

    // ----------------------------------------------------------------------

    template <typename RawType>
    struct RemovePointerImpl final {
        using Type = RawType;
    };

#define _IMPL_TEMPLATE(...) \
    template <typename RawType> \
    struct RemovePointerImpl<RawType* __VA_ARGS__> final { \
        using Type = RawType; \
    };

    _IMPL_CV_OPT_TEMPLATE
#undef _IMPL_TEMPLATE

    // ----------------------------------------------------------------------

    template <typename RawType>
    struct RemovePtrConstImpl final {
        using Type = RawType;
    };

#define _IMPL_TEMPLATE(...) \
    template <typename RwaType> \
    struct RemovePtrConstImpl<const RwaType* __VA_ARGS__> final { \
        using Type = RwaType* __VA_ARGS__; \
    };

    _IMPL_CV_OPT_TEMPLATE
#undef _IMPL_TEMPLATE

    // ----------------------------------------------------------------------

    template <typename RawType>
    struct RemovePtrVolatileImpl final {
        using Type = RawType;
    };

#define _IMPL_TEMPLATE(...) \
    template <typename RwaType> \
    struct RemovePtrVolatileImpl<volatile RwaType* __VA_ARGS__> final { \
        using Type = RwaType* __VA_ARGS__; \
    };

    _IMPL_CV_OPT_TEMPLATE
#undef _IMPL_TEMPLATE

    // ----------------------------------------------------------------------

    template <bool, typename = void>
    struct EnableIfImpl final {};

    template <typename RawType>
    struct EnableIfImpl<true, RawType> final {
        using Type = RawType;
    };

    // ----------------------------------------------------------------------

    template <bool, typename, typename Result>
    struct ConditionalImpl final {
        using Type = Result;
    };

    template <typename Result, typename AnotherType>
    struct ConditionalImpl<true, Result, AnotherType> final {
        using Type = Result;
    };
}

namespace enhanced::util::inline traits {
    // Functions whose names begin with "__" are compiler internal macro functions.

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

    template <bool condition, typename Type = void>
    using EnableIf = typename enhancedInternal::util::traits::EnableIfImpl<condition, Type>::Type;

    template <bool condition, typename Type1, typename Type2>
    using Conditional = typename enhancedInternal::util::traits::ConditionalImpl<condition, Type1, Type2>::Type;

    template <bool first, bool... conditions>
    inline constexpr bool allOfTrue = first;

    template <bool next, bool... conditions>
    inline constexpr bool allOfTrue<true, next, conditions...> = allOfTrue<next, conditions...>;

    template <bool first, bool... conditions>
    inline constexpr bool anyOfTrue = first;

    template <bool next, bool... conditions>
    inline constexpr bool anyOfTrue<false, next, conditions...> = anyOfTrue<next, conditions...>;

#ifdef MSVC_COMPILER
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

    template <typename>
    inline constexpr bool isConst = false;

    template <typename Type>
    inline constexpr bool isConst<const Type> = true;

    template <typename>
    inline constexpr bool isVolatile = false;

    template <typename Type>
    inline constexpr bool isVolatile<volatile Type> = true;

    template <typename>
    inline constexpr bool isPointer = false;

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
    requires isReference<Type>
    using RemoveRefConst = typename enhancedInternal::util::traits::RemoveRefConstImpl<Type>::Type;

    template <typename Type>
    requires isReference<Type>
    using RemoveRefVolatile = typename enhancedInternal::util::traits::RemoveRefVolatileImpl<Type>::Type;

    template <typename Type>
    requires isReference<Type>
    using RemoveRefCv = RemoveRefConst<RemoveRefVolatile<Type>>;

#define _IMPL_TEMPLATE(...) \
    template <typename Type> \
    inline constexpr bool isPointer<Type* __VA_ARGS__> = true;

    _IMPL_CV_OPT_TEMPLATE
#undef _IMPL_TEMPLATE

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
    using RemoveRefAndCv = RemoveCv<RemoveRef<Type>>;

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
    requires isIntegralType<Type>
    inline constexpr bool isSigned = static_cast<RemoveCv<Type>>(-1) < static_cast<Type>(0);

    template <typename Type>
    requires isIntegralType<Type>
    inline constexpr bool isUnsigned = static_cast<RemoveCv<Type>>(-1) >= static_cast<Type>(0);

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

    MSVC_WARNING_PUSH MSVC_WARNING_DISABLE(4180)

    template <typename Type>
    inline constexpr bool isObject = !isVoidType<Type> && isConst<const Type>;

    template <typename Type>
    inline constexpr bool isFunction = !isReference<Type> && !isConst<const Type>;

    MSVC_WARNING_POP

    template <typename Type>
    requires isFunction<Type>
    struct FunctionParser {};

    template <typename Return, typename... Args>
    struct FunctionParser<Return (Args...)> {
        using ReturnType = Return;
    };

    template <typename Type>
    inline constexpr bool isFunctionPtr = false;

    template <typename Return, typename... Args>
    inline constexpr bool isFunctionPtr<Return (*)(Args...)> = true;

    template <typename Type>
    requires isFunctionPtr<Type>
    struct FunctionPtrParser {};

    template <typename Return, typename... Args>
    struct FunctionPtrParser<Return (*)(Args...)> {
        using FunctionType = Return (Args...);
        using ReturnType = Return;
    };

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

#define _IMPL_TEMPLATE(...) \
    template <typename Type, typename Class> \
    inline constexpr bool isMemObjPtr<Type Class::* __VA_ARGS__> = enhanced::util::isObject<Type>;

    _IMPL_CV_OPT_TEMPLATE
#undef _IMPL_TEMPLATE

    template <typename Type>
    inline constexpr bool isMemFuncPtr = false;

#define _IMPL_TEMPLATE(...) \
    template <typename Type, typename Class> \
    inline constexpr bool isMemFuncPtr<Type Class::* __VA_ARGS__> = enhanced::util::isFunction<Type>;

    _IMPL_CV_OPT_TEMPLATE
#undef _IMPL_TEMPLATE

    template <typename Type>
    inline constexpr bool isMemberPointer = isMemObjPtr<Type> || isMemFuncPtr<Type>;
#endif

    template <typename Type>
    requires isMemberPointer<Type>
    struct MemberPointerParser {};

#define _IMPL_TEMPLATE(...) \
    template <typename Type, typename Class> \
    struct MemberPointerParser<Type Class::* __VA_ARGS__> { \
        using MemberType = Type; \
        using ClassType = Class; \
    }

    _IMPL_CV_OPT_TEMPLATE
#undef _IMPL_TEMPLATE

    template <typename Type>
    requires isMemObjPtr<Type>
    struct MemObjPtrParser : MemberPointerParser<Type> {};

    template <typename Type>
    requires isMemFuncPtr<Type>
    struct MemFuncPtrParser : MemberPointerParser<Type> {};

#define _IMPL_TEMPLATE(...) \
    template <typename Return, typename Class, typename... Args> \
    struct MemFuncPtrParser<Return (Class::* __VA_ARGS__)(Args...)> : MemberPointerParser<Return (Class::* __VA_ARGS__)(Args...)> { \
        using FunctinoType = typename MemberPointerParser<Return (Class::*)(Args...)>::MemberType; \
        using ReturnType = Return; \
    };

    _IMPL_CV_OPT_TEMPLATE
#undef _IMPL_TEMPLATE

    template <typename Type>
    inline constexpr bool isScalarType = isArithmeticType<Type> || isEnum<Type> || isPointer<Type> || isMemberPointer<Type> || isNullType<Type>;

    template <typename Type>
    inline constexpr bool isPolymorphicClass = __is_polymorphic(Type);

    template <typename Type>
    inline constexpr bool isAbstractClass = __is_abstract(Type);

    template <typename Type>
    inline constexpr bool isFinalClass = __is_final(Type);

    template <typename...>
    inline constexpr bool isValid = true; // Used for template-requires determines type expression is valid.

    template <typename Type>
    inline constexpr Type&& declvalue() noexcept; // Used for compile-time type inference, no implementation required.

    template <typename Type>
    inline constexpr Type& weakCast(Type&& value) noexcept {
        return value;
    }

    template <typename Type>
    inline constexpr Type& forceCast(auto&& value) noexcept {
        return *((Type*) &value);
    }

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
    inline constexpr bool isQualiConvertible = false;

    template <typename From, typename To>
    requires isVoidType<From> && isVoidType<To>
    inline constexpr bool isQualiConvertible<From, To> = true;

    template <typename From, typename To>
    requires (!isVoidType<From> && !isVoidType<To>) && isValid<decltype(const_cast<To>(declvalue<From>()))>
    inline constexpr bool isQualiConvertible<From, To> = true;

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
    inline constexpr Case& switchType(First&& first, Types&&... values) noexcept {
        return first;
    }

    template <typename Case, typename First, typename... Types>
    requires (!isSame<Case, First>)
    $NoIgnoreReturn
    inline constexpr Case& switchType(First&& first, Types&&... values) noexcept {
        return switchType<Case, Types...>(static_cast<Types&&>(values)...);
    }

    template <typename Callable, typename... Args>
    requires (!isMemberPointer<RemoveRef<Callable>>)
    inline constexpr auto invoke(Callable&& callable, Args&&... args)
        noexcept(noexcept(static_cast<Callable&&>(callable)(static_cast<Args&&>(args)...))){
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

    template <typename Member, typename Class, typename... Args>
    requires (isMemObjPtr<RemoveRef<Member>> && isBaseOf<typename MemObjPtrParser<RemoveRef<Member>>::ClassType, RemoveRef<Class>>)
    inline constexpr auto invoke(Member&& member, Class&& object, Args&&... args) noexcept {
        return static_cast<Class&&>(object).*member;
    }

    template <typename Member, typename Class, typename... Args>
    requires (isMemObjPtr<RemoveRef<Member>> && !isBaseOf<typename MemObjPtrParser<RemoveRef<Member>>::ClassType, RemoveRef<Class>>)
    inline constexpr auto invoke(Member&& member, Class&& object, Args&&... args) noexcept(noexcept((*static_cast<Class&&>(object)).*member)) {
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
    requires isPointer<Type>
    $NoIgnoreReturn
    inline constexpr const RemovePointer<RemoveRef<Type>>*& addPtrConst(Type&& value) noexcept {
        return const_cast<const RemovePointer<RemoveRef<Type>>*&>(value);
    }

    template <typename Type>
    requires isPointer<Type>
    $NoIgnoreReturn
    inline constexpr volatile RemovePointer<RemoveRef<Type>>*& addPtrVolatile(Type&& value) noexcept {
        return const_cast<volatile RemovePointer<RemoveRef<Type>>*&>(value);
    }

    template <typename Type>
    requires isPointer<Type>
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
    inline constexpr bool isInstanceOf(Base&& value) noexcept {
        return true;
    }

    template <typename Derived, typename Base>
    requires isPolymorphicClass<RemoveRef<Base>> && (!isSame<Derived, RemoveRef<Base>> && isBaseOf<RemoveRef<Base>, Derived>)
    $NoIgnoreReturn
    inline constexpr bool isInstanceOf(Base&& value) noexcept {
        return dynamic_cast<Derived*>(&value) != nullptr;
    }
}

#undef _IMPL_CV_OPT_TEMPLATE
