//
//  listdiffer.h
//  listdiffer-cpp
//
//  Created by Konrad Wieczorek on 13/02/2015.
//  Copyright (c) 2015 kwketh.com. All rights reserved.
//

#pragma once

#include <list>
#include <assert.h>

#include "list_interface.h"
#include "list_differ_delegate.h"

enum list_event_type
{
    ITEM_INSERTED = 0,
    ITEM_REMOVED,
    ITEM_MOVED
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

template <class T> /* Adapter type */
class list_differ
{
    typedef typename T::item_type item_type;
    typedef typename T::container_type container_type;
    typedef list_event_typed<item_type> list_event;
    typedef typename std::list<list_event> list_events;

    public:
        list_differ(const T& list) : m_list(list), m_list_prev(m_container_prev)
        {
            sync();
        }
    
        /*
         * Compare two ordered lists.
         *
         * @notes
         *   complexity O(n) 
         *   where n is number of elements in the larger list.
         */
        void compare_ordered_list(const T& list1, const T& list2, list_events& insertions, list_events& deletions)
        {
            list_index i1 = 0, i2 = 0;
            while (i1 < m_list.size() && i2 < m_list_prev.size())
            {
                item_type value1 = m_list.at(i1);
                item_type value2 = m_list_prev.at(i2);
                if (m_list.less_than(value1, value2)) {
                    insertions.push_back(list_event(ITEM_INSERTED, i1, value1));
                    i1++;
                } else
                    if (m_list.less_than(value2, value1)) {
                        deletions.push_back(list_event(ITEM_INSERTED, i2, value2));
                        i2++;
                    } else
                    {
                        assert(m_list.are_equal(value1, value2));
                        i1++, i2++;
                    }
            }
            while (i1 < m_list.size())
            {
                item_type value1 = m_list.at(i1);
                insertions.push_back(list_event(ITEM_INSERTED, i1, value1));
                i1++;
            }
            while (i2 < m_list_prev.size())
            {
                item_type value2 = m_list_prev.at(i2);
                deletions.push_back(list_event(ITEM_REMOVED, i2, value2));
                i2++;
            }
        }
    
        void flush_events()
        {
            if (m_list.is_ordered())
            {
                list_events insertions;
                list_events deletions;
                compare_ordered_list(m_list_prev, m_list, insertions, deletions);
                for (list_event event : deletions)
                    printf("  %i was removed from index %i!\n", event.value, event.index);
                for (list_event event : insertions)
                    printf("  %i was inserted at index %i!\n", event.value, event.index);
            }
            sync();
        }
    
    private:
    
        /**
         * Synchronises previous list with current state.
         * via copy operator.
         */
        void sync()
        {
            m_container_prev = m_list.get_container();
        }
    
        const T& m_list;
        const T m_list_prev;
        container_type m_container_prev;
        list_differ_delegate<item_type>* m_delegate;
};

template <typename AdapterType>
list_differ<AdapterType> create_list_differ(AdapterType& adapter) {
    return list_differ<AdapterType>(adapter);
}
