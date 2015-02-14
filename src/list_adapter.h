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

// Partial template specialization

template <typename ValueType>
class list_adapter {};

template <>
class list_adapter<void> {};

/** 
 * List adapter for 'std::set'
 */
template <class ItemType>
class list_adapter<std::set<ItemType>> : public list_interface<ItemType>
{
    typedef std::set<ItemType> Container;
    typedef typename Container::const_iterator ConstIter;
    public:
        list_adapter(const Container& container) : m_container(container) {};
    
        inline list_index index_of(ItemType it) const
        {
            ConstIter i = m_container.find(it);
            if (i == m_container.end())
                return -1;
            return std::distance(m_container.begin(), i);
        }
    
        inline ItemType at(list_index index) const
        {
            assert(index < size());
            ConstIter it = m_container.begin();
            std::advance(it, index);
            return *it;
        }
    
        inline bool exists(ItemType value) const
        {
            return m_container.find(value) != m_container.end();
        }
    
        inline size_t size() const
        {
            return m_container.size();
        }
        
    private:
        const Container& m_container;
};

template <typename ContainerType>
list_adapter<ContainerType> create_list_adapter(ContainerType& container) {
    return list_adapter<ContainerType>(container);
}
