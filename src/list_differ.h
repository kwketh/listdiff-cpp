//
//  listdiffer.h
//  listdiffer-cpp
//
//  Created by Konrad Wieczorek on 13/02/2015.
//  Copyright (c) 2015 kwketh.com. All rights reserved.
//

#pragma once

#include "list_interface.h"
#include "list_differ_delegate.h"

template <class ItemType>
class list_differ
{
    public:
        list_differ(const list_interface<ItemType>& list) : m_list(list)
        {
            m_list_prev = list;
        };
    
        void flush_events()
        {
            /* TODO: compare lists and flush events to delegate */
            m_list_prev = m_list;
        }
    
    private:
        const list_interface<ItemType>& m_list;
        const list_interface<ItemType> m_list_prev;
        list_differ_delegate<ItemType>* m_delegate;
};
