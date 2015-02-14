//
//  list_differ_delegate.h
//  listdiff-cpp
//
//  Created by Konrad Wieczorek on 13/02/2015.
//  Copyright (c) 2015 kwketh.com. All rights reserved.
//

#pragma once

#include "list_differ_consts.h"

template <class ItemType>
struct list_differ_delegate
{
    virtual void event_item_added(ItemType it, list_index index) = 0;
    virtual void event_item_moved(ItemType it, list_index old_index, list_index index) = 0;
    virtual void event_item_removed(ItemType it, list_index index) = 0;
};