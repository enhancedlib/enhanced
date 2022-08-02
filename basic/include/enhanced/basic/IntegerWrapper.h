/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 *
 * This software is licensed under Enhanced License.
 * You may not use this file except in compliance with the License.
 * You should see a copy of Enhanced License in this software, if not, visit
 * <https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt>
 *
 * The Software is always provided "AS IS",
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#pragma once

#include "enhanced/core/defines.h"
#include "enhanced/core/types.h"
#include "enhanced/core/annotations.h"

#ifdef CXX_LANGUAGE

namespace enhanced::basic {
    template <typename Type>
    class IntegerWrapper {
    protected:
        Type& value;

    public:
        IntegerWrapper(const Type& value) : value((Type&) value) {}

        IntegerWrapper(Type&& value) : value(value) {}

        virtual IntegerWrapper<Type> operator+() const {
            return +value;
        }

        virtual IntegerWrapper<Type> operator-() const {
            return -value;
        }

        virtual IntegerWrapper<Type>& operator++() {
            ++value;
            return *this;
        }

        virtual IntegerWrapper<Type>& operator--() {
            --value;
            return *this;
        }

        virtual const IntegerWrapper<Type> operator++(int) {
            return value++;
        }

        virtual const IntegerWrapper<Type> operator--(int) {
            return value--;
        }

        virtual IntegerWrapper<Type> operator!() const {
            return !value;
        }

        virtual IntegerWrapper<Type> operator~() const {
            return ~value;
        }

        virtual IntegerWrapper<Type> operator+(const IntegerWrapper<Type>& other) const {
            return value + other.value;
        }

        virtual IntegerWrapper<Type> operator-(const IntegerWrapper<Type>& other) const {
            return value - other.value;
        }

        virtual IntegerWrapper<Type> operator*(const IntegerWrapper<Type>& other) const {
            return value * other.value;
        }

        virtual IntegerWrapper<Type> operator/(const IntegerWrapper<Type>& other) const {
            return value / other.value;
        }

        virtual IntegerWrapper<Type> operator%(const IntegerWrapper<Type>& other) const {
            return value % other.value;
        }

        virtual IntegerWrapper<Type> operator<<(const IntegerWrapper<Type>& other) const {
            return value << other.value;
        }

        virtual IntegerWrapper<Type> operator>>(const IntegerWrapper<Type>& other) const {
            return value >> other.value;
        }

        virtual IntegerWrapper<Type> operator&(const IntegerWrapper<Type>& other) const {
            return value & other.value;
        }

        virtual IntegerWrapper<Type> operator^(const IntegerWrapper<Type>& other) const {
            return value ^ other.value;
        }

        virtual IntegerWrapper<Type> operator|(const IntegerWrapper<Type>& other) const {
            return value | other.value;
        }

        virtual IntegerWrapper<Type>& operator=(const IntegerWrapper<Type>& other) {
            value = other.value;
            return *this;
        }

        virtual IntegerWrapper<Type>& operator+=(const IntegerWrapper<Type>& other) {
            value += other.value;
            return *this;
        }

        virtual IntegerWrapper<Type>& operator-=(const IntegerWrapper<Type>& other) {
            value -= other.value;
            return *this;
        }

        virtual IntegerWrapper<Type>& operator*=(const IntegerWrapper<Type>& other) {
            value *= other.value;
            return *this;
        }

        virtual IntegerWrapper<Type>& operator/=(const IntegerWrapper<Type>& other) {
            value /= other.value;
            return *this;
        }

        virtual IntegerWrapper<Type>& operator%=(const IntegerWrapper<Type>& other) {
            value %= other.value;
            return *this;
        }

        virtual IntegerWrapper<Type>& operator<<=(const IntegerWrapper<Type>& other) {
            value <<= other.value;
            return *this;
        }

        virtual IntegerWrapper<Type>& operator>>=(const IntegerWrapper<Type>& other) {
            value >>= other.value;
            return *this;
        }

        virtual IntegerWrapper<Type>& operator&=(const IntegerWrapper<Type>& other) {
            value &= other.value;
            return *this;
        }

        virtual IntegerWrapper<Type>& operator^=(const IntegerWrapper<Type>& other) {
            value ^= other.value;
            return *this;
        }

        virtual IntegerWrapper<Type>& operator|=(const IntegerWrapper<Type>& other) {
            value |= other.value;
            return *this;
        }

        virtual bool operator==(const IntegerWrapper<Type>& other) const {
            return value == other.value;
        }

        virtual bool operator!=(const IntegerWrapper<Type>& other) const {
            return value != other.value;
        }

        virtual bool operator>(const IntegerWrapper<Type>& other) const {
            return value > other.value;
        }

        virtual bool operator<(const IntegerWrapper<Type>& other) const {
            return value < other.value;
        }

        virtual bool operator>=(const IntegerWrapper<Type>& other) const {
            return value >= other.value;
        }

        virtual bool operator<=(const IntegerWrapper<Type>& other) const {
            return value <= other.value;
        }

        virtual bool operator&&(const IntegerWrapper<Type>& other) const {
            return value && other.value;
        }

        virtual bool operator||(const IntegerWrapper<Type>& other) const {
            return value || other.value;
        }

        virtual IntegerWrapper<Type> operator+(const Type& other) const {
            return value + other;
        }

        virtual IntegerWrapper<Type> operator-(const Type& other) const {
            return value - other;
        }

        virtual IntegerWrapper<Type> operator*(const Type& other) const {
            return value * other;
        }

        virtual IntegerWrapper<Type> operator/(const Type& other) const {
            return value / other;
        }

        virtual IntegerWrapper<Type> operator%(const Type& other) const {
            return value % other;
        }

        virtual IntegerWrapper<Type> operator<<(const Type& other) const {
            return value << other;
        }

        virtual IntegerWrapper<Type> operator>>(const Type& other) const {
            return value >> other;
        }

        virtual IntegerWrapper<Type> operator&(const Type& other) const {
            return value & other;
        }

        virtual IntegerWrapper<Type> operator^(const Type& other) const {
            return value ^ other;
        }

        virtual IntegerWrapper<Type> operator|(const Type& other) const {
            return value | other;
        }

        virtual IntegerWrapper<Type>& operator=(const Type& other) {
            value = other;
            return *this;
        }

        virtual IntegerWrapper<Type>& operator+=(const Type& other) {
            value += other;
            return *this;
        }

        virtual IntegerWrapper<Type>& operator-=(const Type& other) {
            value -= other;
            return *this;
        }

        virtual IntegerWrapper<Type>& operator*=(const Type& other) {
            value *= other;
            return *this;
        }

        virtual IntegerWrapper<Type>& operator/=(const Type& other) {
            value /= other;
            return *this;
        }

        virtual IntegerWrapper<Type>& operator%=(const Type& other) {
            value %= other;
            return *this;
        }

        virtual IntegerWrapper<Type>& operator<<=(const Type& other) {
            value <<= other;
            return *this;
        }

        virtual IntegerWrapper<Type>& operator>>=(const Type& other) {
            value >>= other;
            return *this;
        }

        virtual IntegerWrapper<Type>& operator&=(const Type& other) {
            value &= other;
            return *this;
        }

        virtual IntegerWrapper<Type>& operator^=(const Type& other) {
            value ^= other;
            return *this;
        }

        virtual IntegerWrapper<Type>& operator|=(const Type& other) {
            value |= other;
            return *this;
        }

        virtual bool operator==(const Type& other) const {
            return value == other;
        }

        virtual bool operator!=(const Type& other) const {
            return value != other;
        }

        virtual bool operator>(const Type& other) const {
            return value > other;
        }

        virtual bool operator<(const Type& other) const {
            return value < other;
        }

        virtual bool operator>=(const Type& other) const {
            return value >= other;
        }

        virtual bool operator<=(const Type& other) const {
            return value <= other;
        }

        virtual bool operator&&(const Type& other) const {
            return value && other;
        }

        virtual bool operator||(const Type& other) const {
            return value || other;
        }

        operator Type() const {
            return value;
        }
    };
}

#endif // CXX_LANGUAGE
