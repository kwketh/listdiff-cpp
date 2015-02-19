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
#include "list_compare.h"

namespace ldcpp
{
    template <class T> /* Adapter type */
    class differ
    {
        typedef T adapter_type;
        typedef typename T::item_type item_type;
        typedef typename T::container_type container_type;

        public:
            differ(const T& list) : m_list(list), m_list_prev(m_container_prev)
            {
                sync();
            }
        
            void flush_events()
            {
                if (m_list.is_ordered())
                {
                    event_list& insertions = m_events[event_type::ITEM_INSERTED];
                    event_list& deletions = m_events[event_type::ITEM_REMOVED];
                    compare_ordered(m_list_prev, m_list, insertions, deletions);
                }
                sync();
            }
        
            const event& top_event(event_type type)
            {
                return m_events[type].front();
            }
        
            void pop_event(event_type type)
            {
                return m_events[type].pop_front();
            }
        
            size_t count_events(event_type type)
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
            event_list m_events[event_type::LAST];
    };

    template <typename AdapterType>
    differ<AdapterType> create_differ(AdapterType& adapter) {
        return differ<AdapterType>(adapter);
    }
}
