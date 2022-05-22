// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#pragma once

/**
 * \file NtJSONArray.h
 * \brief JSON array
 * \author Hákon Hjaltalín
 *
 * This file contains the class definition for a JSON array.
 */

#include "newton/json/NtJSONElement.h"
#include <vector>
#include <algorithm>

namespace newton
{

/**
 * \class NtJSONArray
 * \brief JSON array class
 *
 * This class defines a JSON array.
 */
class NT_EXPORT NtJSONArray : public NtJSONElement
{
public:
    /**
     * \brief Constructor
     *
     * Default constructor.
     */
    NtJSONArray()
        : NtJSONElement(Type::ARRAY)
    {
    }

    /**
     * \brief Destructor
     */
    ~NtJSONArray() { }

    /**
     * \brief Add element
     *
     * Add an element to this array.
     *
     * \param element Element to add
     */
    void add(NtJSONElement* element)
    {
        m_members.push_back(element);
    }

    /**
     * \brief Remove element
     *
     * Remove an element from this array
     *
     * \param element Element to remove
     */
    void remove(NtJSONElement* element)
    {
        auto it = std::find(m_members.begin(), m_members.end(), element);
        if (it != m_members.end())
            m_members.erase(it);
    }

    /**
     * \brief Access element
     *
     * Get element by index
     *
     * \param idx Index to access
     */
    NtJSONElement* get(const size_t idx)
    {
        return m_members[idx];
    }

    /**
     * \brief Member access operator
     *
     * Access member at index.
     *
     * \param idx Index to access
     */
    NtJSONElement* operator[](const size_t idx)
    {
        return m_members[idx];
    }

    /**
     * \brief Element count
     *
     * Get number of elements.
     *
     * \return Number of elements
     */
    size_t count() const { return m_members.size(); }

private:
    /**
     * Members
     */
    std::vector<NtJSONElement*> m_members;
};

}

