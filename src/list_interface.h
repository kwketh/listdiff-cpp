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

namespace ldcpp
{
    template <class ItemType>
    struct list_interface
    {
        /* List operations */
        virtual list_index index_of(ItemType value) const = 0;
        virtual ItemType at(list_index index) const = 0;
        virtual bool exists(ItemType value) const = 0;
        virtual size_t size() const = 0;
        
        /* List properties */
        virtual bool is_ordered() const = 0;
        
        /* Implement if list has non-default comparators */
        virtual int compare(ItemType value1, ItemType value2) const = 0;        
    };
}