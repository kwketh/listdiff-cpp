//
//  list_adapter.h
//  listdiff-cpp
//
//  Created by Konrad Wieczorek on 13/02/2015.
//  Copyright (c) 2015 kwketh.com. All rights reserved.
//

#pragma once

#include <set>
#include <vector>
#include <assert.h>
#include "list_interface.h"

namespace ldcpp
{
    /* Partial template specialization */
    
    template <typename ValueType>
    class list_adapter {};

    template <>
    class list_adapter<void> {};

    /* @see list_adapter_stdset.h for sample adapter implementation */

    template <typename ContainerType>
    list_adapter<ContainerType> create_list_adapter(ContainerType& container) {
        return list_adapter<ContainerType>(container);
    }
}