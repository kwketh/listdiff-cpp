//
//  list_event.h
//  listdiff-cpp
//
//  Created by Konrad Wieczorek on 15/02/2015.
//  Copyright (c) 2015 kwketh.com. All rights reserved.
//

#pragma once

enum list_event_type
{
    ITEM_INSERTED = 0,
    ITEM_REMOVED,
    ITEM_MOVED,
    LAST,
};

template <class T> /* Item type */
struct list_event_typed
{
    typedef T list_value_type;
    list_event_typed(list_event_type _type, list_index _index, list_value_type _value)
    : type(_type), index(_index), value(_value) {};
    list_event_type type;
    list_index index;
    list_value_type value;
};

