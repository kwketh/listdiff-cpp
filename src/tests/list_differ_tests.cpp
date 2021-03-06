//
//  list_differ_tests.cpp
//  listdiff-cpp
//
//  Created by Konrad Wieczorek on 13/02/2015.
//  Copyright (c) 2015 kwketh.com. All rights reserved.
//

#include <set>
#include "list_differ_tests.h"
#include "list_differ.h"
#include "list_adapter.h"
#include <adapters/list_adapter_stdset.h>

using namespace ldcpp;

void differ_tests::run_tests()
{
    run_test_simple();
    run_test_demo();
}

void differ_tests::run_test_demo()
{
    std::set<int> v;
    v.insert(1);
    v.insert(4);
    v.insert(5);
    
    auto adapter = create_list_adapter(v);
    auto differ = create_differ(adapter);
    
    v.insert(0);
    v.erase(4);
    v.erase(5);
    v.insert(9);
    v.insert(10);

    differ.flush_events();
    
    while (differ.count_events(ITEM_REMOVED) > 0)
    {
        auto event = differ.top_event(ITEM_REMOVED);
        printf("item at index %zu was removed\n", event.index);
        differ.pop_event(ITEM_REMOVED);
    }
    
    while (differ.count_events(ITEM_INSERTED) > 0)
    {
        auto event = differ.top_event(ITEM_INSERTED);
        printf("value of %i was inserted at index %zu!\n", adapter.at(event.index), event.index);
        differ.pop_event(ITEM_INSERTED);
    }
}

void differ_tests::run_test_simple()
{
    std::set<int> v;
    v.insert(1);
    v.insert(4);
    v.insert(5);
    
    auto adapter = create_list_adapter(v);
    assert(adapter.size() == 3);
    assert(adapter.at(0) == 1);
    assert(adapter.at(1) == 4);
    assert(adapter.at(2) == 5);
    assert(adapter.index_of(1) == 0);
    assert(adapter.index_of(4) == 1);
    assert(adapter.index_of(5) == 2);
    assert(adapter.index_of(10) == -1);
    assert(adapter.exists(1) == true);
    assert(adapter.exists(4) == true);
    assert(adapter.exists(5) == true);
    assert(adapter.exists(10) == false);
    
    auto differ(adapter);
    /* TODO: test differ class */
}


