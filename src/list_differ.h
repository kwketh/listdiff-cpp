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
#include "list_event.h"

template <class T> /* Adapter type */
class list_differ
{
    typedef T adapter_type;
    typedef typename T::item_type item_type;
    typedef typename T::container_type container_type;
    
    typedef list_event_typed<item_type> list_event;
    typedef std::list<list_event> list_events;

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
                list_events& insertions = m_events[list_event_type::ITEM_INSERTED];
                list_events& deletions = m_events[list_event_type::ITEM_REMOVED];
                compare_ordered_list(m_list_prev, m_list, insertions, deletions);
            }
            sync();
        }
    
        list_event& top_event(list_event_type type)
        {
            return m_events[type].front();
        }
    
        void pop_event(list_event_type type)
        {
            return m_events[type].pop_front();
        }
    
        size_t count_events(list_event_type type)
        {
            return m_events[type].size();
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
    
        const adapter_type& m_list;
        const adapter_type m_list_prev;
        container_type m_container_prev;
        list_events m_events[list_event_type::LAST];
};

template <typename AdapterType>
list_differ<AdapterType> create_list_differ(AdapterType& adapter) {
    return list_differ<AdapterType>(adapter);
}
