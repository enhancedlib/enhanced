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

#include <cstdlib>

#include <iostream>

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/annotations.h"
#include "EnhancedCore/array.h"

#include "EnhancedBasic/core/String.h"

#include "EnhancedContainer/collection/ArrayList.h"
#include "EnhancedContainer/collection/LinkedList.h"

#include "EnhancedContainer/collection/referenced/ReferencedArrayList.h"
#include "EnhancedContainer/collection/referenced/ReferencedLinkedList.h"

#include "EnhancedContainer/collection/mixed/MixedArrayList.h"
#include "EnhancedContainer/collection/mixed/MixedLinkedList.h"

using EnhancedBasic::Core::String;

using EnhancedContainer::Collection::List;
using EnhancedContainer::Collection::Deque;
using EnhancedContainer::Collection::ArrayList;
using EnhancedContainer::Collection::LinkedList;

using EnhancedContainer::Collection::Referenced::ReferencedList;
using EnhancedContainer::Collection::Referenced::ReferencedDeque;
using EnhancedContainer::Collection::Referenced::ReferencedArrayList;
using EnhancedContainer::Collection::Referenced::ReferencedLinkedList;

using EnhancedContainer::Collection::Mixed::MixedList;
using EnhancedContainer::Collection::Mixed::MixedDeque;
using EnhancedContainer::Collection::Mixed::MixedArrayList;
using EnhancedContainer::Collection::Mixed::MixedLinkedList;

int main() {
    List<String> *list = new ReferencedArrayList<String>();

    String a = "world!\n";

    list->add("Hello, ");
    list->add(a);

    for (Size index = 0; index < list->getLength(); ++ index) {
        std::cout << list->get(index);
    }

    for (auto item : *list) {
        std::cout << item;
    }

    for (auto it = list->iterator(); it->hasNext(); it->next()) {
        std::cout << it->get();
    }

    {
        auto it = list->iterator();
        while (it->hasNext()) {
            std::cout << it->get();
            it->next();
        }
    }

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
