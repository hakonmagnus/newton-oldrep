// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#pragma once

/**
 * \file NtJSONArray.h
 * \brief JSON array element
 *
 * This file contains the class definition for a JSON array.
 */

#include "newton/json/NtJSONElement.h"
#include "newton/base/NtException.h"
#include <vector>
#include <utility>

namespace newton
{

/**
 * \class NtJSONArray
 * \brief JSON array class
 *
 * This class defines a JSON array element.
 */
class NT_EXPORT NtJSONArray : public NtJSONElement
{
private:
    using iterator = std::vector<NtJSONElement*>::iterator;

public:
    /**
     * \brief Default constructor
     *
     * Default constructor. Takes a vector of elements.
     *
     * \param elements Elements to set
     */
    NtJSONArray(const std::vector<NtJSONElement*>& elements = std::vector<NtJSONElement*>())
        : NtJSONElement(Type::ARRAY), m_elements{ elements }
    {
    }

    /**
     * \brief Constructor from initializer list
     *
     * Constructs an NtJSONArray from an initializer list.
     *
     * \param list Initializer list
     */
    NtJSONArray(std::initializer_list<NtJSONElement*> list)
        : NtJSONElement(Type::ARRAY), m_elements{ list }
    {
    }

    /**
     * \brief Copy constructor
     * \param other Other NtJSONArray
     */
    NtJSONArray(const NtJSONArray& other) :
        NtJSONElement(Type::ARRAY), m_elements{ other.m_elements }
    {
    }

    /**
     * \brief Move constructor
     * \param other Other NtJSONArray
     */
    NtJSONArray(NtJSONArray&& other) :
        NtJSONElement(Type::ARRAY), m_elements{ std::move(other.m_elements) }
    {
    }

    /**
     * \brief Virtual destructor
     */
    virtual ~NtJSONArray() {}

    /**
     * \brief Copy assignment
     * \param other Other NtJSONArray
     * \return Reference to this
     */
    NtJSONArray& operator=(const NtJSONArray& other)
    {
        m_elements = other.m_elements;
        return *this;
    }

    /**
     * \brief Move assignment
     * \param other Other NtJSONArray
     * \return Reference to this
     */
    NtJSONArray& operator=(NtJSONArray&& other)
    {
        m_elements = std::move(other.m_elements);
        return *this;
    }

    /**
     * \brief Get array size
     * 
     * Get the number of elements in the array.
     *
     * \return Array size
     */
    size_t size() const { return m_elements.size(); }

    /**
     * \brief Element access
     *
     * Array subscript operator for element access.
     *
     * \param idx Index of element
     * \return Element at index idx
     */
    NtJSONElement* operator[](const size_t idx)
    {
        if (idx >= m_elements.size())
            throw NtOutOfRange("Array subscript out of range.");

        return m_elements[idx];
    }

    /**
     * \brief Get element
     *
     * Get element at index
     *
     * \param idx Index of element
     * \return Element at index idx
     */
    NtJSONElement* at(const size_t idx)
    {
        if (idx >= m_elements.size())
            throw NtOutOfRange("Array subscript out of range.");

        return m_elements[idx];
    }

    /**
     * \brief Push element
     *
     * Add an element to the back of the array.
     *
     * \param element Element to add
     */
    void pushElement(NtJSONElement* element)
    {
        m_elements.push_back(element);
    }

    /**
     * \brief Insert element
     *
     * Insert an element into the array.
     *
     * \param pos Position to insert
     * \param element Element to insert at position
     * \return Iterator pointing to inserted element
     */
    iterator insert(iterator pos, NtJSONElement* element)
    {
        return m_elements.insert(pos, element);
    }

    /**
     * \brief Erase element
     *
     * Erase an element from the array.
     *
     * \param pos Position to erase
     */
    iterator erase(iterator pos)
    {
        return m_elements.erase(pos);
    }

    /**
     * \brief Erase element
     *
     * Erase multiple elements from the array.
     *
     * \param first First element to erase
     * \param last Last element to erase
     */
    iterator erase(iterator first, iterator last)
    {
        return m_elements.erase(first, last);
    }

    /**
     * \brief Clear array
     *
     * Clear all array elements.
     */
    void clear() { m_elements.clear(); }

private:
    /**
     * List of elements
     */
    std::vector<NtJSONElement*> m_elements;
};

}

