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

#ifdef CXX_11_OR_MORE

namespace enhanced_internal::core::util::traits {
    template <typename RawType>
    struct RemoveRefImpl {
        using Type = RawType;
    };
    template <typename RawType>
    struct RemoveRefImpl<RawType&> {
        using Type = RawType;
    };
    template <typename RawType>
    struct RemoveRefImpl<RawType&&> {
        using Type = RawType;
    };

    template <typename RawType>
    struct RemoveConstImpl {
        using Type = RawType;
    };
    template <typename RawType>
    struct RemoveConstImpl<volatile RawType> {
        using Type = RawType;
    };

    template <typename RawType>
    struct RemoveVolatileImpl {
        using Type = RawType;
    };
    template <typename RawType>
    struct RemoveVolatileImpl<volatile RawType> {
        using Type = RawType;
    };

    template <typename RawType>
    struct RemoveModifersImpl {
        using Type = RawType;
    };
    template <typename RawType>
    struct RemoveModifersImpl<const RawType> {
        using Type = RawType;
    };
    template <typename RawType>
    struct RemoveModifersImpl<volatile RawType> {
        using Type = RawType;
    };
    template <typename RawType>
    struct RemoveModifersImpl<const volatile RawType> {
        using Type = RawType;
    };

    template <bool condition, typename RawType = void>
    struct EnableIfImpl {};
    template <typename RawType>
    struct EnableIfImpl<true, RawType> {
        using Type = RawType;
    };

    template <bool condition, typename Type1, typename Type2>
    struct ConditionalImpl {
        using Type = Type2;
    };
    template <typename Type1, typename Type2>
    struct ConditionalImpl<true, Type1, Type2> {
        using Type = Type1;
    };
}

namespace enhanced::core::util::traits {
    // TODO

    // Functions whose names begin with "__" are compiler internal macro functions.

    template <typename Type>
    using RemoveRef = typename enhanced_internal::core::util::traits::RemoveRefImpl<Type>::Type;

    template <typename Type>
    using RemoveConst = typename enhanced_internal::core::util::traits::RemoveConstImpl<Type>::Type;

    template <typename Type>
    using RemoveVolatile = typename enhanced_internal::core::util::traits::RemoveVolatileImpl<Type>::Type;

    template <typename Type>
    using RemoveModifers = typename enhanced_internal::core::util::traits::RemoveModifersImpl<Type>::Type;

    template <bool condition, typename Type = void>
    using EnableIf = typename enhanced_internal::core::util::traits::EnableIfImpl<condition, Type>::Type;

    template <bool condition, typename Type1, typename Type2>
    using Conditional = typename enhanced_internal::core::util::traits::ConditionalImpl<condition, Type1, Type2>::Type;

#ifdef COMPILER_MSVC
    template <typename, typename>
    inline constexpr bool isSameType = false;

    template <typename Type>
    inline constexpr bool isSameType<Type, Type> = true;
#else
    template <typename Type1, typename Type2>
    inline constexpr bool isSameType = __is_same(Type1, Type2);
#endif

    template <typename Base, typename Derived>
    inline constexpr bool isBaseOf = __is_base_of(Base, Derived);

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
    inline constexpr bool isPointer<Type*> = true;
    template <typename Type>
    inline constexpr bool isPointer<Type* const> = true;
    template <typename Type>
    inline constexpr bool isPointer<Type* volatile> = true;
    template <typename Type>
    inline constexpr bool isPointer<Type* const volatile> = true;

    template <typename Type>
    inline constexpr bool isLvalueRef = false;
    template <typename Type>
    inline constexpr bool isLvalueRef<Type&> = true;

    template <typename Type>
    inline constexpr bool isRvalueRef = false;
    template <typename Type>
    inline constexpr bool isRvalueRef<Type&&> = true;

    template <typename Type>
    inline constexpr bool isReference = false;
    template <typename Type>
    inline constexpr bool isReference<Type&> = true;
    template <typename Type>
    inline constexpr bool isReference<Type&&> = true;

    template <typename Type>
    inline constexpr bool isMemberPointer = false; // TODO

    template <typename Type>
    inline constexpr bool isEmptyType = __is_empty(Type);

    template <typename Type>
    inline constexpr bool isIntegralType = false; // TODO

    template <typename Type>
    inline constexpr bool isFloatType = false; // TODO

    template <typename Type>
    inline constexpr bool isArithmeticType = isIntegralType<Type> || isFloatType<Type>;

    template <typename Type>
    inline constexpr bool isVoidType = isSameType<RemoveModifers<Type>, void>;

    template <typename Type>
    inline constexpr bool isNullType = isSameType<RemoveModifers<Type>, NullType>;

    template <typename Type>
    inline constexpr bool isBasicType = isArithmeticType<Type> || isVoidType<Type> || isNullType<Type>;

    template <typename Type>
    inline constexpr bool isEnumType = __is_enum(Type);

    template <typename Type>
    inline constexpr bool isStructType = __is_class(Type);

    template <typename Type>
    inline constexpr bool isClassType = isStructType<Type>;

    template <typename Type>
    inline constexpr bool isUnionType = __is_union(Type);

    template <typename Type>
    inline constexpr bool isScalarType = isArithmeticType<Type> || isEnumType<Type> || isPointer<Type> || isMemberPointer<Type> || isNullType<Type>; // TODO

    template <typename Type>
    inline constexpr bool isPolymorphicClass = __is_polymorphic(Type);

    template <typename Type>
    inline constexpr bool isAbstractClass = __is_abstract(Type);

    template <typename Type>
    inline constexpr bool isFinalClass = __is_final(Type);

    template <typename Derived, typename Base>
    bool isInstanceOf(Base&& value) {
        // TODO
        static_assert(!isSameType<Derived, RemoveRef<Base>>, "The specified class and the class of the value are the same");
        static_assert(isBaseOf<RemoveRef<Base>, Derived>, "The specified class must be base of the class of the value");
        static_assert(isPolymorphicClass<RemoveRef<Base>>, "The class of the value is not polymorphic");

        return dynamic_cast<Derived*>(&value) != null;
    }
}

#endif
