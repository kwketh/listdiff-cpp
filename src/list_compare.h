//
//  list_compare.h
//  listdiff-cpp
//
//  Created by Konrad Wieczorek on 16/02/2015.
//  Copyright (c) 2015 kwketh.com. All rights reserved.
//

#pragma once

#include "list_interface.h"
#include "list_event.h"

/*
 * Compare two ordered lists.
 *
 * @notes
 *   complexity O(n)
 *   where n is number of elements in the larger list.
 */
template <class T>
void list_compare_ordered(const list_interface<T>& list1, const list_interface<T>& list2, event_list& insertions, event_list& deletions)
{
    list_index i1 = 0, i2 = 0;
    while (i1 < list1.size() && i2 < list2.size())
    {
        T value1 = list1.at(i1);
        T value2 = list2.at(i2);
        if (list1.less_than(value1, value2))
        {
            insertions.push_back(list_event(ITEM_INSERTED, i1));
            i1++;
        } else
        if (list1.less_than(value2, value1))
        {
            deletions.push_back(list_event(ITEM_INSERTED, i2));
            i2++;
        } else
        {
            assert(list1.are_equal(value1, value2));
            i1++, i2++;
        }
    }
    while (i1 < list1.size())
    {
        insertions.push_back(list_event(ITEM_INSERTED, i1));
        i1++;
    }
    while (i2 < list2.size())
    {
        deletions.push_back(list_event(ITEM_REMOVED, i2));
        i2++;
    }
}