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

namespace ldcpp
{
    template <class T>
    struct differ_delegate
    {
        typedef typename T::item_type item_type;    
        virtual void event_items_inserted(event_list& events) = 0;
        virtual void event_items_removed(event_list& events) = 0;
        virtual void event_items_moved(event_list& events) = 0;
    };
}