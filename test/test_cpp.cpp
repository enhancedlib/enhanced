/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
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

#include <cstdlib>

#include <iostream>

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/annotations.h"
#include "EnhancedCore/array.h"

#include "EnhancedBasic/core/String.h"

#include "EnhancedBasic/collection/Vector.h"
#include "EnhancedBasic/collection/ArrayList.h"
#include "EnhancedBasic/collection/LinkedList.h"

#include "EnhancedBasic/collection/referenced/ReferencedArrayList.h"
#include "EnhancedBasic/collection/referenced/ReferencedLinkedList.h"

#include "EnhancedBasic/collection/mixed/MixedArrayList.h"
#include "EnhancedBasic/collection/mixed/MixedLinkedList.h"

#include "EnhancedBasic/core/Any.h"

using EnhancedBasic::Core::String;

using EnhancedBasic::Collection::List;
using EnhancedBasic::Collection::Deque;
using EnhancedBasic::Collection::Vector;
using EnhancedBasic::Collection::ArrayList;
using EnhancedBasic::Collection::LinkedList;

using EnhancedBasic::Collection::Referenced::ReferencedList;
using EnhancedBasic::Collection::Referenced::ReferencedDeque;
using EnhancedBasic::Collection::Referenced::ReferencedArrayList;
using EnhancedBasic::Collection::Referenced::ReferencedLinkedList;

using EnhancedBasic::Collection::Mixed::MixedList;
using EnhancedBasic::Collection::Mixed::MixedDeque;
using EnhancedBasic::Collection::Mixed::MixedArrayList;
using EnhancedBasic::Collection::Mixed::MixedLinkedList;

using EnhancedBasic::Core::Any;

int main() {
    List<String> *list = new Vector<String>();

    String a = "world!\n";

    list->add("Hello, ");
    list->add(a);

    std::cout << "[1]" << std::endl;
    for (Size index = 0; index < list->getLength(); ++ index) {
        std::cout << list->get(index);
    }

    std::cout << "[2]" << std::endl;
    for (const auto &item : *list) {
        std::cout << item;
    }

    std::cout << "[3]" << std::endl;
    for (auto it = list->iterator(); it->hasNext(); it->next()) {
        std::cout << it->get();
    }

    std::cout << "[4]" << std::endl;
    {
        auto it = list->iterator();
        while (it->hasNext()) {
            std::cout << it->get();
            it->next();
        }
    }

    std::cout << "[5]" << std::endl;
    {
        auto it = list->iterator();
        while (it->each()) {
            std::cout << it->get();
        }
    }

    std::cout << list->contain("world!\n") << std::endl;
    a = "C++!\n";
    std::cout << list->remove();

    delete list;

    return 0;
}
