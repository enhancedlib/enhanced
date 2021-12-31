/*
 * Copyright (C) 2021 Liu Baihao.
 * This product is licensed under Enhanced License.
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

/*!
 * This file is used to test function and debug code of this library.
 * This file will only be compiled in configuration "Debug".
 */

#include <stdio.h>
#include <stdlib.h>

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/array.h"

#include "EnhancedBasic/core/exception/Exception.h"

int main() {
    char *str = "Hello!\n";
    printf(str);

    TRY {
        RAISE(1, "error!\n");
        str = "Hi!\n";
    } CATCH (1, exception) {
        printf(exception->message);
    } PASS {
        printf("pass!\n");
    } FINALLY {
        printf("finally!\n");
    } END_TRY;

    printf(str);

    return 0;
}
