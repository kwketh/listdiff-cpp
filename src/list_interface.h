//
//  list_interface.h
//  listdiff-cpp
//
//  Created by Konrad Wieczorek on 13/02/2015.
//  Copyright (c) 2015 kwketh.com. All rights reserved.
//

#pragma once

#include <cstddef>
#include "list_differ_consts.h"

template <class ItemType>
struct list_interface
{
    virtual list_index index_of(ItemType it) const = 0;
    virtual ItemType at(list_index index) const = 0;
    virtual bool exists(ItemType it) const = 0;
    virtual size_t size() const = 0;
};
