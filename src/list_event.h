//
//  list_event.h
//  listdiff-cpp
//
//  Created by Konrad Wieczorek on 15/02/2015.
//  Copyright (c) 2015 kwketh.com. All rights reserved.
//

#pragma once

#include <list>

namespace ldcpp
{
    enum event_type
    {
        ITEM_INSERTED = 0,
        ITEM_REMOVED,
        ITEM_MOVED,
        LAST,
    };

    struct event
    {
        event(event_type _type, list_index _index) : type(_type), index(_index) {};
        event_type type;
        list_index index;
    };

    typedef std::list<event> event_list;
}
