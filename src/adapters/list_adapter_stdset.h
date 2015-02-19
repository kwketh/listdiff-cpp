//
//  list_adapter_stdset.h
//  listdiff-cpp
//
//  Created by Konrad Wieczorek on 15/02/2015.
//  Copyright (c) 2015 kwketh.com. All rights reserved.
//

#pragma once

namespace ldcpp
{
    /**
     * List adapter implementation for std::set
     *
     * @properties
     *   associative
     *   ordered
     *   unique
     */
    template <class ItemType>
    class list_adapter<std::set<ItemType>> : public list_interface<ItemType>
    {
        public:
            typedef std::set<ItemType> container_type;
            typedef typename container_type::const_iterator const_iter;
            typedef ItemType item_type;
            
            list_adapter(const container_type& container) : m_container(container) {};
            
            inline list_index index_of(ItemType value) const
            {
                const_iter iter = m_container.find(value);
                if (iter == m_container.end())
                    return -1;
                return std::distance(m_container.begin(), iter);
            }
            
            inline bool less_than(ItemType value1, ItemType value2) const
            {
                return m_container.value_comp()(value1, value2);
            }
            
            inline bool are_equal(ItemType value1, ItemType value2) const
            {
                return !(less_than(value1, value2)) && !(less_than(value2, value1));
            }
            
            inline ItemType at(list_index index) const
            {
                assert(index < size());
                const_iter iter = m_container.begin();
                std::advance(iter, index);
                return *iter;
            }
            
            inline bool exists(ItemType value) const
            {
                return m_container.find(value) != m_container.end();
            }
            
            inline size_t size() const
            {
                return m_container.size();
            }
            
            inline bool is_ordered() const
            {
                return true;
            }
            
            const container_type& get_container() const
            {
                return m_container;
            }
            
            
        private:
            const container_type& m_container;
    };
}
