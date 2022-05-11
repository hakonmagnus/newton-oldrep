// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#pragma once

/**
 * \file NtJSONElement.h
 * \brief JSON element
 *
 * This file contains the class definition for a JSON element.
 */

#include "newton/base/NtDefs.h"

namespace newton
{
/**
 * \class NtJSONElement
 * \brief JSON element
 *
 * This is the base class for a JSON element.
 */
class NT_EXPORT NtJSONElement
{
  public:
  /**
   * \enum Type
   * \brief Type of element
   *
   * This enum class defines the element type.
   */
  enum class Type { OBJECT, ARRAY, STRING, NUMBER, BOOLEAN, NUL };

  /**
   * \brief Default constructor
   *
   * Default constructor taking a type of element.
   *
   * \param type Element type
   */
  explicit NtJSONElement(const Type type) : m_type{type} {}

  /**
   * \brief Virtual destructor
   */
  virtual ~NtJSONElement() {}

  /**
   * \brief Get the type of element
   *
   * Get the JSON element type.
   *
   * \return Element type
   */
  Type type() const { return m_type; }

  protected:
  /**
   * Element type
   */
  Type m_type;
};

}  // namespace newton
