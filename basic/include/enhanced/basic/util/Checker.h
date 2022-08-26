/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 *
 * Licensed under the Enhanced License, Version 0.5.4 (the "License").
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt
 *
 * UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING,
 * THE SOFTWARE IS ALWAYS PROVIDED "AS IS",
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#pragma once

#include "enhanced/core/defines.h"
#include "enhanced/core/types.h"
#include "enhanced/core/annotations.h"

#ifdef CXX_LANGUAGE

namespace enhanced::basic::util {
    template <typename Type>
    class Checker {
    private:
        Type& value;

    protected:
        virtual void readCheck() const {}

        virtual void writeCheck() const {}

        virtual void invokeCheck() const {}

    public:
        Checker(const Type& value) : value((Type&) value) {}

        Checker(Type&& value) : value(value) {}

        virtual Type* operator->() const {
            invokeCheck();
            return &value;
        }

        virtual Checker<Type> operator+() const {
            readCheck();
            return +value;
        }

        virtual Checker<Type> operator-() const {
            readCheck();
            return -value;
        }

        virtual Checker<Type> operator!() const {
            readCheck();
            return !value;
        }

        virtual Checker<Type> operator~() const {
            readCheck();
            return ~value;
        }

        virtual Checker<Type> operator+(const Checker<Type>& other) const {
            readCheck();
            return value + other.value;
        }

        virtual Checker<Type> operator-(const Checker<Type>& other) const {
            readCheck();
            return value - other.value;
        }

        virtual Checker<Type> operator*(const Checker<Type>& other) const {
            readCheck();
            return value * other.value;
        }

        virtual Checker<Type> operator/(const Checker<Type>& other) const {
            readCheck();
            return value / other.value;
        }

        virtual Checker<Type> operator%(const Checker<Type>& other) const {
            readCheck();
            return value % other.value;
        }

        virtual Checker<Type> operator<<(const Checker<Type>& other) const {
            readCheck();
            return value << other.value;
        }

        virtual Checker<Type> operator>>(const Checker<Type>& other) const {
            readCheck();
            return value >> other.value;
        }

        virtual Checker<Type> operator&(const Checker<Type>& other) const {
            readCheck();
            return value & other.value;
        }

        virtual Checker<Type> operator^(const Checker<Type>& other) const {
            readCheck();
            return value ^ other.value;
        }

        virtual Checker<Type> operator|(const Checker<Type>& other) const {
            readCheck();
            return value | other.value;
        }

        virtual bool operator==(const Checker<Type>& other) const {
            readCheck();
            return value == other.value;
        }

        virtual bool operator!=(const Checker<Type>& other) const {
            readCheck();
            return value != other.value;
        }

        virtual bool operator>(const Checker<Type>& other) const {
            readCheck();
            return value > other.value;
        }

        virtual bool operator<(const Checker<Type>& other) const {
            readCheck();
            return value < other.value;
        }

        virtual bool operator>=(const Checker<Type>& other) const {
            readCheck();
            return value >= other.value;
        }

        virtual bool operator<=(const Checker<Type>& other) const {
            readCheck();
            return value <= other.value;
        }

        virtual bool operator&&(const Checker<Type>& other) const {
            readCheck();
            return value && other.value;
        }

        virtual bool operator||(const Checker<Type>& other) const {
            readCheck();
            return value || other.value;
        }

        virtual Checker<Type> operator+(const Type& other) const {
            readCheck();
            return value + other;
        }

        virtual Checker<Type> operator-(const Type& other) const {
            readCheck();
            return value - other;
        }

        virtual Checker<Type> operator*(const Type& other) const {
            readCheck();
            return value * other;
        }

        virtual Checker<Type> operator/(const Type& other) const {
            readCheck();
            return value / other;
        }

        virtual Checker<Type> operator%(const Type& other) const {
            readCheck();
            return value % other;
        }

        virtual Checker<Type> operator<<(const Type& other) const {
            readCheck();
            return value << other;
        }

        virtual Checker<Type> operator>>(const Type& other) const {
            readCheck();
            return value >> other;
        }

        virtual Checker<Type> operator&(const Type& other) const {
            readCheck();
            return value & other;
        }

        virtual Checker<Type> operator^(const Type& other) const {
            readCheck();
            return value ^ other;
        }

        virtual Checker<Type> operator|(const Type& other) const {
            readCheck();
            return value | other;
        }

        virtual Checker<Type>& operator++() {
            writeCheck();
            ++value;
            return *this;
        }

        virtual Checker<Type>& operator--() {
            writeCheck();
            --value;
            return *this;
        }

        virtual const Checker<Type> operator++(int) {
            writeCheck();
            return value++;
        }

        virtual const Checker<Type> operator--(int) {
            writeCheck();
            return value--;
        }
/*

        virtual Checker<Type>& operator=(const Checker<Type>& other) {
            if (this == &other) {
                return *this;
            }
            writeCheck();
            value = other.value;
            return *this;
        }
*/

        virtual Checker<Type>& operator+=(const Checker<Type>& other) {
            writeCheck();
            value += other.value;
            return *this;
        }

        virtual Checker<Type>& operator-=(const Checker<Type>& other) {
            writeCheck();
            value -= other.value;
            return *this;
        }

        virtual Checker<Type>& operator*=(const Checker<Type>& other) {
            writeCheck();
            value *= other.value;
            return *this;
        }

        virtual Checker<Type>& operator/=(const Checker<Type>& other) {
            writeCheck();
            value /= other.value;
            return *this;
        }

        virtual Checker<Type>& operator%=(const Checker<Type>& other) {
            writeCheck();
            value %= other.value;
            return *this;
        }

        virtual Checker<Type>& operator<<=(const Checker<Type>& other) {
            writeCheck();
            value <<= other.value;
            return *this;
        }

        virtual Checker<Type>& operator>>=(const Checker<Type>& other) {
            writeCheck();
            value >>= other.value;
            return *this;
        }

        virtual Checker<Type>& operator&=(const Checker<Type>& other) {
            writeCheck();
            value &= other.value;
            return *this;
        }

        virtual Checker<Type>& operator^=(const Checker<Type>& other) {
            writeCheck();
            value ^= other.value;
            return *this;
        }

        virtual Checker<Type>& operator|=(const Checker<Type>& other) {
            writeCheck();
            value |= other.value;
            return *this;
        }

        virtual Checker<Type>& operator=(const Type& other) {
            writeCheck();
            value = other;
            return *this;
        }

        virtual Checker<Type>& operator+=(const Type& other) {
            writeCheck();
            value += other;
            return *this;
        }

        virtual Checker<Type>& operator-=(const Type& other) {
            writeCheck();
            value -= other;
            return *this;
        }

        virtual Checker<Type>& operator*=(const Type& other) {
            writeCheck();
            value *= other;
            return *this;
        }

        virtual Checker<Type>& operator/=(const Type& other) {
            writeCheck();
            value /= other;
            return *this;
        }

        virtual Checker<Type>& operator%=(const Type& other) {
            writeCheck();
            value %= other;
            return *this;
        }

        virtual Checker<Type>& operator<<=(const Type& other) {
            writeCheck();
            value <<= other;
            return *this;
        }

        virtual Checker<Type>& operator>>=(const Type& other) {
            writeCheck();
            value >>= other;
            return *this;
        }

        virtual Checker<Type>& operator&=(const Type& other) {
            writeCheck();
            value &= other;
            return *this;
        }

        virtual Checker<Type>& operator^=(const Type& other) {
            writeCheck();
            value ^= other;
            return *this;
        }

        virtual Checker<Type>& operator|=(const Type& other) {
            writeCheck();
            value |= other;
            return *this;
        }

        virtual bool operator==(const Type& other) const {
            readCheck();
            return value == other;
        }

        virtual bool operator!=(const Type& other) const {
            readCheck();
            return value != other;
        }

        virtual bool operator>(const Type& other) const {
            readCheck();
            return value > other;
        }

        virtual bool operator<(const Type& other) const {
            readCheck();
            return value < other;
        }

        virtual bool operator>=(const Type& other) const {
            readCheck();
            return value >= other;
        }

        virtual bool operator<=(const Type& other) const {
            readCheck();
            return value <= other;
        }

        virtual bool operator&&(const Type& other) const {
            readCheck();
            return value && other;
        }

        virtual bool operator||(const Type& other) const {
            readCheck();
            return value || other;
        }

        operator Type() const {
            readCheck();
            return value;
        }
    };
}

#endif // CXX_LANGUAGE
