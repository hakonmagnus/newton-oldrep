// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#pragma once

/**
 * \file NtJSONNumber.h
 * \brief JSON number element
 *
 * This file contains the class definition for a JSON number.
 */

#include "newton/json/NtJSONElement.h"
#include <string>
#include <sstream>
#include <utility>
#include <cstdlib>

namespace newton
{
/**
 * \class NtJSONNumber
 * \brief JSON number class
 *
 * This class defines a JSON number element.
 */
class NT_EXPORT NtJSONNumber : public NtJSONElement
{
  public:
  /**
   * \brief Default constructor
   *
   * Default constructor. Takes a double type value.
   *
   * \param value Value to set
   */
  NtJSONNumber(const double value = 0.0) :
    NtJSONElement(Type::NUMBER), m_value{value}
  {
  }

  /**
   * \brief Copy constructor
   * \param other Other NtJSONNumber
   */
  NtJSONNumber(const NtJSONNumber& other) :
    NtJSONElement(Type::NUMBER), m_value{other.m_value}
  {
  }

  /**
   * \brief Move constructor
   * \param other Other NtJSONNumber
   */
  NtJSONNumber(NtJSONNumber&& other) :
    NtJSONElement(Type::NUMBER), m_value{std::move(other.m_value)}
  {
  }

  /**
   * \brief Virtual destructor
   */
  virtual ~NtJSONNumber() {}

  /**
   * \brief Copy assignment
   * \param other Other NtJSONNumber
   * \return Reference to this
   */
  NtJSONNumber& operator=(const NtJSONNumber& other)
  {
    m_type = other.m_type;
    m_value = other.m_value;
    return *this;
  }

  /**
   * \brief Move assignment
   * \param other Other NtJSONNumber
   * \return Reference to this
   */
  NtJSONNumber& operator=(NtJSONNumber&& other)
  {
    m_type = std::move(other.m_type);
    m_value = std::move(other.m_value);
    return *this;
  }

  /**
   * \brief Assignment from double
   *
   * Assigns a value to this class using a double
   *
   * \param num Number to set
   * \return Reference to this
   */
  NtJSONNumber& operator=(const double num)
  {
    m_value = num;
    return *this;
  }

  /**
   * \brief Get value
   *
   * Get the value associated with this class.
   *
   * \return Numeric value
   */
  double value() const { return m_value; }

  /**
   * \brief Set value
   *
   * Set the value associated with this class.
   *
   * \param value Value to set
   */
  void setValue(const double value) { m_value = value; }

  /**
   * \brief Convert to string
   *
   * Convert this number to an std::string
   *
   * \return This number as a string
   */
  std::string toString() const
  {
    std::ostringstream strs;
    strs << m_value;
    return strs.str();
  }

  /**
   * \brief Set value from string
   *
   * Convert an std::string into a double and store in this class
   *
   * \param str String to set
   */
  void fromString(const std::string& str) { m_value = atof(str.c_str()); }

  /**
   * \brief Comparison operator
   *
   * Compare if this class is equal to another
   *
   * \param num This object
   * \param other Other NtJSONNumber
   * \return True if equal
   */
  friend bool operator==(const NtJSONNumber& num, const NtJSONNumber& other);

  /**
   * \brief Comparison operator
   *
   * Compare if this class is not equal to another
   *
   * \param num This object
   * \param other Other NtJSONNumber
   * \return False if equal
   */
  friend bool operator!=(const NtJSONNumber& num, const NtJSONNumber& other);

  /**
   * \brief Comparison operator
   *
   * Compare if this class is equal to a double
   *
   * \param num This object
   * \param d Double to compare
   * \return True if equal
   */
  friend bool operator==(const NtJSONNumber& num, const double d);

  /**
   * \brief Comparison operator
   *
   * Compare if this class is not equal to a double
   *
   * \param num This object
   * \param d Double to compare
   * \return False if equal
   */
  friend bool operator!=(const NtJSONNumber& num, const double d);

  private:
  /**
   * Number value
   */
  double m_value;
};

inline bool operator==(const NtJSONNumber& num, const NtJSONNumber& other)
{
    return num.m_value == other.m_value;
}

inline bool operator!=(const NtJSONNumber& num, const NtJSONNumber& other)
{
    return num.m_value != other.m_value;
}

inline bool operator==(const NtJSONNumber& num, const double d)
{
    return num.m_value == d;
}

inline bool operator!=(const NtJSONNumber& num, const double d)
{
    return num.m_value != d;
}

}  // namespace newton
