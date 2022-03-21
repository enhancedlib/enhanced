/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 * This software is licensed under Enhanced License.
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

#ifndef ENHANCED_BASIC_CORE_STRING_H
#define ENHANCED_BASIC_CORE_STRING_H

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/annotations.h"

#include "EnhancedBasic/export.h"

#include "EnhancedBasic/collection/List.h"

#if defined(C_LANGUAGE) /* C language */ || defined(ENHANCED_BASIC_C_MODE)

EXTERN_C_START

typedef struct String {
    /*!
     * This variable is used to hold the original string.
     */
    char *value;

    /*!
     * This variable is used to record the count of a string.
     */
    Size length;

    Size (*getLength)(const struct String *self);

    /*!
     * To concatenate the current string with another string.
     *
     * @param self
     * @param str
     * @return String
     */
    struct String (*const add)(struct String *self, struct String str);
} String;

#define ALIAS_String String

ENHANCED_BASIC_API String newEmptyString();

ENHANCED_BASIC_API String toString(char *value);

ENHANCED_BASIC_API String newString(Size length);

ENHANCED_BASIC_API String newStringExt(const char *value, Size length);

EXTERN_C_END

#else // C++ language

namespace EnhancedBasic {
    namespace core {
        class ENHANCED_BASIC_API String {
        private:
            /*!
             * This variable is used to hold the original string.
             */
            char *value;

            /*!
             * This variable is used to record the count of a string.
             */
            Size length;

            bool dynamic;

        public:
            String(const char *value = "");

            String(char *value);

            explicit String(Size length);

            String(const String &other);

            String(String &&other) noexcept;

            ~String();

            $RetNotIgnored()
            Size getLength() const;

            $RetNotIgnored()
            bool isEmpty() const;

            $RetNotIgnored()
            Size indexOf(char ch, Size getN = 0) const;

            $RetNotIgnored()
            Size indexOf(const String &string, Size getN = 0) const;

            $RetRequiresRelease()
            collection::List<Size> *indexOfAll(char ch) const;

            $RetRequiresRelease()
            collection::List<Size> *indexOfAll(const String &string) const;

            $RetNotIgnored()
            char *getCharacters() const;

            char &operator[](Size index) const;

            bool operator==(const String &string) const;

            String operator+(const String &string) const;

            operator char *() const;

            String &operator=(const String &other);

            String &operator=(String &&other) noexcept;

            String append(const String &string);

            String replace(char oldChar, char newChar);

            String replace(const String &oldSubstring, const String &newSubstring);

            String replace(char oldChar, const String &newSubstring);

            String replace(const String &oldSubstring, char newChar);

            String operator+=(const String &string);
        };
    } // namespace core
} // namespace EnhancedBasic

#endif // defined(C_LANGUAGE) || defined(ENHANCED_BASIC_C_MODE)

#endif // !ENHANCED_BASIC_CORE_STRING_H
