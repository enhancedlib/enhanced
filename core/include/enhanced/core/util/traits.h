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

#include <enhanced/core/defines.h>
#include <enhanced/core/types.h>

#ifdef CXX_11_OR_LATER

NAMESPACE_L4_BEGIN(enhanced_internal, core, util, traits)

template <typename RawType>
struct RemoveConstImpl final {
    using Type = RawType;
};
template <typename RawType>
struct RemoveConstImpl<volatile RawType> final {
    using Type = RawType;
};

template <typename RawType>
struct RemoveVolatileImpl final {
    using Type = RawType;
};
template <typename RawType>
struct RemoveVolatileImpl<volatile RawType> final {
    using Type = RawType;
};

template <typename RawType>
struct RemoveModifersImpl final {
    using Type = RawType;
};
template <typename RawType>
struct RemoveModifersImpl<const RawType> final {
    using Type = RawType;
};
template <typename RawType>
struct RemoveModifersImpl<volatile RawType> final {
    using Type = RawType;
};
template <typename RawType>
struct RemoveModifersImpl<const volatile RawType> final {
    using Type = RawType;
};

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

template <typename RawType>
struct RemovePointerImpl final {
    using Type = RawType;
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

template <bool condition, typename RawType = void>
struct EnableIfImpl final {};
template <typename RawType>
struct EnableIfImpl<true, RawType> final {
    using Type = RawType;
};

template <bool condition, typename Type1, typename Type2>
struct ConditionalImpl final {
    using Type = Type2;
};
template <typename Type1, typename Type2>
struct ConditionalImpl<true, Type1, Type2> final {
    using Type = Type1;
};

NAMESPACE_L4_END

NAMESPACE_L4_BEGIN(enhanced, core, util, traits)

// Functions whose names begin with "__" are compiler internal macro functions.

template <typename Type>
using RemoveConst = typename enhanced_internal::core::util::traits::RemoveConstImpl<Type>::Type;

template <typename Type>
using RemoveVolatile = typename enhanced_internal::core::util::traits::RemoveVolatileImpl<Type>::Type;

template <typename Type>
using RemoveModifers = typename enhanced_internal::core::util::traits::RemoveModifersImpl<Type>::Type;

template <typename Type>
using RemoveRef = typename enhanced_internal::core::util::traits::RemoveRefImpl<Type>::Type;

template <typename Type>
using RemovePointer = typename enhanced_internal::core::util::traits::RemovePointerImpl<Type>::Type;

template <bool condition, typename Type = void>
using EnableIf = typename enhanced_internal::core::util::traits::EnableIfImpl<condition, Type>::Type;

template <bool condition, typename Type1, typename Type2>
using Conditional = typename enhanced_internal::core::util::traits::ConditionalImpl<condition, Type1, Type2>::Type;

template <bool first, bool... conditions>
INLINE_VAR constexpr bool allTrue = first;

template <bool next, bool... conditions>
INLINE_VAR constexpr bool allTrue<true, next, conditions...> = allTrue<next, conditions...>;

template <bool first, bool... conditions>
INLINE_VAR constexpr bool anyoneTrue = first;

template <bool next, bool... conditions>
INLINE_VAR constexpr bool anyoneTrue<false, next, conditions...> = anyoneTrue<next, conditions...>;

#ifdef COMPILER_MSVC
template <typename, typename>
INLINE_VAR constexpr bool isSame = false;

template <typename Type>
INLINE_VAR constexpr bool isSame<Type, Type> = true;
#else
template <typename Type1, typename Type2>
INLINE_VAR constexpr bool isSame = __is_same(Type1, Type2);
#endif

template <typename Type, typename... OthersType>
INLINE_VAR constexpr bool isAnyOf = anyoneTrue<isSame<Type, OthersType>...>;

template <typename Base, typename Derived>
INLINE_VAR constexpr bool isBaseOf = __is_base_of(Base, Derived);

template <typename>
INLINE_VAR constexpr bool isConst = false;
template <typename Type>
INLINE_VAR constexpr bool isConst<const Type> = true;

template <typename>
INLINE_VAR constexpr bool isVolatile = false;
template <typename Type>
INLINE_VAR constexpr bool isVolatile<volatile Type> = true;

template <typename>
INLINE_VAR constexpr bool isPointer = false;
template <typename Type>
INLINE_VAR constexpr bool isPointer<Type*> = true;
template <typename Type>
INLINE_VAR constexpr bool isPointer<Type* const> = true;
template <typename Type>
INLINE_VAR constexpr bool isPointer<Type* volatile> = true;
template <typename Type>
INLINE_VAR constexpr bool isPointer<Type* const volatile> = true;

template <typename Type>
INLINE_VAR constexpr bool isLvalueRef = false;
template <typename Type>
INLINE_VAR constexpr bool isLvalueRef<Type&> = true;

template <typename Type>
INLINE_VAR constexpr bool isRvalueRef = false;
template <typename Type>
INLINE_VAR constexpr bool isRvalueRef<Type&&> = true;

template <typename Type>
INLINE_VAR constexpr bool isReference = false;
template <typename Type>
INLINE_VAR constexpr bool isReference<Type&> = true;
template <typename Type>
INLINE_VAR constexpr bool isReference<Type&&> = true;

template <typename Type>
INLINE_VAR constexpr bool isMemberPointer = false; // TODO

template <typename Type>
INLINE_VAR constexpr bool isIntegralType =
    isAnyOf<Type, bool, char, schar, uchar, wchar,
#ifdef CXX_U8CHAR_SUPPORTED
    u8char,
#endif
    u16char, u32char, short, ushort, int, uint, long, ulong, llong, ullong>;

template <typename Type>
INLINE_VAR constexpr bool isFloatType = isAnyOf<Type, float, double, ldouble>;

template <typename Type>
INLINE_VAR constexpr bool isArithmeticType = isIntegralType<Type> || isFloatType<Type>;

template <typename Type>
INLINE_VAR constexpr bool isEmptyType = __is_empty(Type);

template <typename Type>
INLINE_VAR constexpr bool isVoidType = isSame<RemoveModifers<Type>, void>;

template <typename Type>
INLINE_VAR constexpr bool isNullType = isSame<RemoveModifers<Type>, NullType>;

template <typename Type>
INLINE_VAR constexpr bool isBasicType = isArithmeticType<Type> || isVoidType<Type> || isNullType<Type>;

template <typename Type>
INLINE_VAR constexpr bool isEnumType = __is_enum(Type);

template <typename Type>
INLINE_VAR constexpr bool isStructType = __is_class(Type);

template <typename Type>
INLINE_VAR constexpr bool isClassType = isStructType<Type>;

template <typename Type>
INLINE_VAR constexpr bool isUnionType = __is_union(Type);

template <typename Type>
INLINE_VAR constexpr bool isScalarType = isArithmeticType<Type> || isEnumType<Type> ||
                                            isPointer<Type> || isMemberPointer<Type> || isNullType<Type>;

template <typename Type>
INLINE_VAR constexpr bool isPolymorphicClass = __is_polymorphic(Type);

template <typename Type>
INLINE_VAR constexpr bool isAbstractClass = __is_abstract(Type);

template <typename Type>
INLINE_VAR constexpr bool isFinalClass = __is_final(Type);

template <typename Derived, typename Base>
inline bool isInstanceOf(Base&& value) {
    static_assert(!isSame<Derived, RemoveRef<Base>>, "The specified class and the class of the value are the same");
    static_assert(isBaseOf<RemoveRef<Base>, Derived>, "The specified class must be base of the class of the value");
    static_assert(isPolymorphicClass<RemoveRef<Base>>, "The class of the value is not polymorphic");

    return dynamic_cast<Derived*>(&value) != null;
}

NAMESPACE_L4_END

#endif
