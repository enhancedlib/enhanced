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

#include "enhanced/core/annotations.h"
#include <enhanced/core/defines.h>
#include <enhanced/core/types.h>

namespace enhancedInternal::core::util::traits {
    template <typename RawType>
    struct RemoveConstImpl final {
        using Type = RawType;
    };
    template <typename RawType>
    struct RemoveConstImpl<const RawType> final {
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

    template <typename RawType>
    struct RemovePtrConstImpl final {
        using Type = RawType;
    };
    template <typename RemovePointerType>
    struct RemovePtrConstImpl<const RemovePointerType*> final {
        using Type = RemovePointerType*;
    };
    template <typename RemovePointerType>
    struct RemovePtrConstImpl<const RemovePointerType* const> final {
        using Type = RemovePointerType* const;
    };
    template <typename RemovePointerType>
    struct RemovePtrConstImpl<const RemovePointerType* volatile> final {
        using Type = RemovePointerType* volatile;
    };
    template <typename RemovePointerType>
    struct RemovePtrConstImpl<const RemovePointerType* const volatile> final {
        using Type = RemovePointerType* const volatile;
    };

    template <typename RawType>
    struct RemovePtrVolatileImpl final {
        using Type = RawType;
    };
    template <typename RemovePointerType>
    struct RemovePtrVolatileImpl<volatile RemovePointerType*> final {
        using Type = RemovePointerType*;
    };
    template <typename RemovePointerType>
    struct RemovePtrVolatileImpl<volatile RemovePointerType* const> final {
        using Type = RemovePointerType* const;
    };
    template <typename RemovePointerType>
    struct RemovePtrVolatileImpl<volatile RemovePointerType* volatile> final {
        using Type = RemovePointerType* volatile;
    };
    template <typename RemovePointerType>
    struct RemovePtrVolatileImpl<volatile RemovePointerType* const volatile> final {
        using Type = RemovePointerType* const volatile;
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
}

namespace enhanced::core::util::inline traits {
    // Functions whose names begin with "__" are compiler internal macro functions.

    template <typename Type>
    using RemoveConst = typename enhancedInternal::core::util::traits::RemoveConstImpl<Type>::Type;

    template <typename Type>
    using RemoveVolatile = typename enhancedInternal::core::util::traits::RemoveVolatileImpl<Type>::Type;

    template <typename Type>
    using RemoveCvQualifier = RemoveConst<RemoveVolatile<Type>>;

    template <typename Type>
    using RemoveRef = typename enhancedInternal::core::util::traits::RemoveRefImpl<Type>::Type;

    template <typename Type>
    using RemovePointer = typename enhancedInternal::core::util::traits::RemovePointerImpl<Type>::Type;

    template <typename Type>
    using RemovePtrConst = typename enhancedInternal::core::util::traits::RemovePtrConstImpl<Type>::Type;

    template <typename Type>
    using RemovePtrVolatile = typename enhancedInternal::core::util::traits::RemovePtrVolatileImpl<Type>::Type;

    template <typename Type>
    using RemovePtrCvQualifier = RemovePtrConst<RemovePtrVolatile<Type>>;

    template <bool condition, typename Type = void>
    using EnableIf = typename enhancedInternal::core::util::traits::EnableIfImpl<condition, Type>::Type;

    template <bool condition, typename Type1, typename Type2>
    using Conditional = typename enhancedInternal::core::util::traits::ConditionalImpl<condition, Type1, Type2>::Type;

    template <bool first, bool... conditions>
    inline constexpr bool allOfTrue = first;

    template <bool next, bool... conditions>
    inline constexpr bool allOfTrue<true, next, conditions...> = allOfTrue<next, conditions...>;

    template <bool first, bool... conditions>
    inline constexpr bool anyOfTrue = first;

    template <bool next, bool... conditions>
    inline constexpr bool anyOfTrue<false, next, conditions...> = anyOfTrue<next, conditions...>;

#ifdef COMPILER_MSVC
    template <typename, typename>
    inline constexpr bool isSame = false;

    template <typename Type>
    inline constexpr bool isSame<Type, Type> = true;
#else
    template <typename Type1, typename Type2>
    inline constexpr bool isSame = __is_same(Type1, Type2);
#endif

    template <typename Type, typename... OthersType>
    inline constexpr bool isAnyOf = anyOfTrue<isSame<Type, OthersType>...>;

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
    inline constexpr bool isIntegralType =
        isAnyOf<Type, char,
    #ifdef WCHAR_IS_BUILTIN_TYPE
        wchar,
    #endif
        u8char, u16char, u32char, bool, schar, uchar, short, ushort, int, uint, long, ulong, llong, ullong>;

    template <typename Type>
    inline constexpr bool isFloatType = isAnyOf<Type, float, double, ldouble>;

    template <typename Type>
    inline constexpr bool isCharType =
        isAnyOf<Type, char,
    #ifdef WCHAR_IS_BUILTIN_TYPE
        wchar,
    #endif
        u8char, u16char, u32char>;

    template <typename Type>
    requires isIntegralType<Type>
    inline constexpr bool isSigned = static_cast<RemoveCvQualifier<Type>>(-1) < static_cast<Type>(0);

    template <typename Type>
    requires isIntegralType<Type>
    inline constexpr bool isUnsigned = static_cast<RemoveCvQualifier<Type>>(-1) >= static_cast<Type>(0);

    template <typename Type>
    inline constexpr bool isArithmeticType = isIntegralType<Type> || isFloatType<Type>;

    template <typename Type>
    inline constexpr bool isEmptyType = __is_empty(Type);

    template <typename Type>
    inline constexpr bool isVoidType = isSame<RemoveCvQualifier<Type>, void>;

    template <typename Type>
    inline constexpr bool isNullType = isSame<RemoveCvQualifier<Type>, nulltype>;

    template <typename Type>
    inline constexpr bool isBasicType = isArithmeticType<Type> || isVoidType<Type> || isNullType<Type>;

    template <typename Type>
    inline constexpr bool isEnum = __is_enum(Type);

    template <typename Type>
    inline constexpr bool isStruct = __is_class(Type);

    template <typename Type>
    inline constexpr bool isClass = isStruct<Type>;

    template <typename Type>
    inline constexpr bool isUnion = __is_union(Type);

    // Only function types and reference types cannot be const qualified.

    template <typename Type>
    inline constexpr bool isObject = isConst<const Type> && !isVoidType<Type>;

    template <typename Type>
    inline constexpr bool isFunction = !isConst<const Type> && !isReference<Type>;

#ifndef COMPILER_CLANG
}

namespace enhancedInternal::core::util::traits {
    template <typename Type>
    inline constexpr bool isMemberObjectPointerImpl = false;

    template <typename Type, typename Class>
    inline constexpr bool isMemberObjectPointerImpl<Type Class::*> = !enhanced::core::util::isFunction<Type>;
}

namespace enhanced::core::util::inline traits {

    template <typename Type>
    inline constexpr bool isMemberObjectPointer = enhancedInternal::core::util::traits::isMemberObjectPointerImpl<RemoveCvQualifier<Type>>;
#else
    template <typename Type>
    inline constexpr bool isMemberObjectPointer = __is_member_object_pointer(Type);
#endif

#ifndef COMPILER_CLANG
}

namespace enhancedInternal::core::util::traits {
    template <typename Type>
    inline constexpr bool isMemberFunctionPointerImpl = false;

    template <typename Type, typename Class>
    inline constexpr bool isMemberFunctionPointerImpl<Type Class::*> = enhanced::core::util::isFunction<Type>;
}

namespace enhanced::core::util::inline traits {

    template <typename Type>
    inline constexpr bool isMemberFunctionPointer = enhancedInternal::core::util::traits::isMemberFunctionPointerImpl<RemoveCvQualifier<Type>>;
#else
    template <typename Type>
    inline constexpr bool isMemberFunctionPointer = __is_member_function_pointer(Type);
#endif

#ifndef COMPILER_CLANG
    template <typename Type>
    inline constexpr bool isMemberPointer = isMemberObjectPointer<Type> || isMemberFunctionPointer<Type>;
#else
    template <typename Type>
    inline constexpr bool isMemberPointer = __is_member_pointer(Type);
#endif

    template <typename Type>
    inline constexpr bool isScalarType = isArithmeticType<Type> || isEnum<Type> || isPointer<Type> || isMemberPointer<Type> || isNullType<Type>;

    template <typename Type>
    inline constexpr bool isPolymorphicClass = __is_polymorphic(Type);

    template <typename Type>
    inline constexpr bool isAbstractClass = __is_abstract(Type);

    template <typename Type>
    inline constexpr bool isFinalClass = __is_final(Type);

    template <typename Type>
    inline constexpr func move(Type&& value) noexcept -> RemoveRef<Type>&& {
        return static_cast<RemoveRef<Type>&&>(value);
    }

    template <typename Case, typename First, typename... Types>
    requires isSame<Case, First>
    inline constexpr func switchType(First&& first, Types&&... values) noexcept -> Case& {
        return first;
    }

    template <typename Case, typename First, typename... Types>
    requires (!isSame<Case, First>)
    inline constexpr func switchType(First&& first, Types&&... values) noexcept -> Case& {
        return switchType<Case, Types...>(static_cast<Types&&>(values)...);
    }

    template <typename Type>
    inline constexpr func addConst(Type&& value) noexcept -> const RemoveRef<Type>& {
        return const_cast<const RemoveRef<Type>&>(value);
    }

    template <typename Type>
    inline constexpr func addVolatile(Type&& value) noexcept -> volatile RemoveRef<Type>& {
        return const_cast<volatile RemoveRef<Type>&>(value);
    }

    template <typename Type>
    inline constexpr func addCvQualifier(Type&& value) noexcept -> const volatile RemoveRef<Type>& {
        return const_cast<const volatile RemoveRef<Type>&>(value);
    }

    template <typename Type>
    requires isPointer<Type>
    inline constexpr func addPtrConst(Type&& value) noexcept -> const RemovePointer<RemoveRef<Type>>*& {
        return const_cast<const RemovePointer<RemoveRef<Type>>*&>(value);
    }

    template <typename Type>
    requires isPointer<Type>
    inline constexpr func addPtrVolatile(Type&& value) noexcept -> volatile RemovePointer<RemoveRef<Type>>*& {
        return const_cast<volatile RemovePointer<RemoveRef<Type>>*&>(value);
    }

    template <typename Type>
    requires isPointer<Type>
    inline constexpr func addPtrCvQualifier(Type&& value) noexcept -> const volatile RemovePointer<RemoveRef<Type>>*& {
        return const_cast<const volatile RemovePointer<RemoveRef<Type>>*&>(value);
    }

    template <typename Type>
    inline constexpr func removeConst(Type&& value) noexcept -> RemoveConst<RemoveRef<Type>>& {
        return const_cast<RemoveConst<RemoveRef<Type>>&>(value);
    }

    template <typename Type>
    inline constexpr func removeVolatile(Type&& value) noexcept -> RemoveVolatile<RemoveRef<Type>>& {
        return const_cast<RemoveVolatile<RemoveRef<Type>>&>(value);
    }

    template <typename Type>
    inline constexpr func removeCvQualifier(Type&& value) noexcept -> RemoveCvQualifier<RemoveRef<Type>>& {
        return const_cast<RemoveCvQualifier<RemoveRef<Type>>&>(value);
    }

    template <typename Type>
    inline constexpr func removePtrConst(Type&& value) noexcept -> RemovePtrConst<RemoveRef<Type>>& {
        return const_cast<RemovePtrConst<RemoveRef<Type>>&>(value);
    }

    template <typename Type>
    inline constexpr func removePtrVolatile(Type&& value) noexcept -> RemovePtrVolatile<RemoveRef<Type>>& {
        return const_cast<RemovePtrVolatile<RemoveRef<Type>>&>(value);
    }

    template <typename Type>
    inline constexpr func removePtrCvQualifier(Type&& value) noexcept -> RemovePtrCvQualifier<RemoveRef<Type>>& {
        return const_cast<RemovePtrCvQualifier<RemoveRef<Type>&>>(value);
    }

    template <typename Derived, typename Base>
    requires isPolymorphicClass<RemoveRef<Base>> && isSame<Derived, RemoveRef<Base>>
    inline constexpr func isInstanceOf(Base&& value) noexcept -> bool {
        return true;
    }

    template <typename Derived, typename Base>
    requires isPolymorphicClass<RemoveRef<Base>> && (!isSame<Derived, RemoveRef<Base>> && isBaseOf<RemoveRef<Base>, Derived>)
    inline func isInstanceOf(Base&& value) noexcept -> bool {
        return dynamic_cast<Derived*>(&value) != null;
    }
}
