// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#pragma once

/**
 * \file NtJSONObject.h
 * \brief JSON object
 * \author Hákon Hjaltalín
 *
 * This file contains the class definition for a JSON object.
 */

#include "newton/json/NtJSONElement.h"
#include <map>
#include <string>

namespace newton
{

/**
 * \class NtJSONObject
 * \brief JSON object class
 *
 * This class defines a JSON object.
 */
class NT_EXPORT NtJSONObject : public NtJSONElement
{
public:
    /**
     * \brief Constructor
     *
     * Default constructor
     */
    NtJSONObject()
        : NtJSONElement(Type::OBJECT)
    {
    }

    /**
     * \brief Destructor
     */
    ~NtJSONObject() { }

    /**
     * \brief Add element
     *
     * Add an element to this object.
     *
     * \param name Name of element
     * \param value Element value
     */
    void add(const std::string& name, NtJSONElement* value)
    {
        m_members.insert({ name, value });
    }

    /**
     * \brief Remove element
     *
     * Remove an element from this object
     *
     * \param name Name of element
     */
    void remove(const std::string& name)
    {
        auto it = m_members.find(name);
        if (it != m_members.end())
            m_members.erase(it);
    }

    /**
     * \brief Access element
     *
     * Get element by name string
     *
     * \param name Element name
     */
    NtJSONElement* get(const std::string& name)
    {
        return m_members[name];
    }

    /**
     * \brief Member access operator
     *
     * Access member at string index
     *
     * \param name Name to access
     */
    NtJSONElement* operator[](const char* name)
    {
        return m_members[name];
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
     * Members map
     */
    std::map<std::string, NtJSONElement*> m_members;
};

}

