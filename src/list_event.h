//
//  list_event.h
//  listdiff-cpp
//
//  Created by Konrad Wieczorek on 15/02/2015.
//  Copyright (c) 2015 kwketh.com. All rights reserved.
//

#pragma once

#include <list>

enum list_event_type
{
    ITEM_INSERTED = 0,
    ITEM_REMOVED,
    ITEM_MOVED,
    LAST,
};

struct list_event
{
    list_event(list_event_type _type, list_index _index) : type(_type), index(_index) {};
    list_event_type type;
    list_index index;
};

typedef std::list<list_event> event_list;

/* --- TODO ---
 *
 * add namespacing. to avoid confusion between 
 * 'event_list' and 'list_event', 'ldcpp' 
 * namespace would seem reasonable.
 *
 * ldcpp::event
 * ldcpp::event_list 
 *
 * --- --- --- --- --- --- --- --- --- --- --- */