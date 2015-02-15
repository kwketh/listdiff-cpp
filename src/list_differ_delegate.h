//
//  list_differ_delegate.h
//  listdiff-cpp
//
//  Created by Konrad Wieczorek on 13/02/2015.
//  Copyright (c) 2015 kwketh.com. All rights reserved.
//

#pragma once

#include "list_differ_consts.h"
#include "list_event.h"

template <class T>
struct list_differ_delegate
{
    typedef typename T::item_type item_type;
    typedef list_event_typed<item_type> list_event;
    typedef std::list<list_event> list_events;
    
    virtual void event_items_inserted(list_events& events) = 0;
    virtual void event_items_removed(list_events& events) = 0;
    virtual void event_items_moved(list_events& events) = 0;
};