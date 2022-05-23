// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#pragma once

/**
 * \file NtNCLToken.h
 * \brief NCL token definition
 * \author Hákon Hjaltalín
 *
 * This file contains the class definition for a lexical token for the
 * NCL language.
 */

#include "newton/base/NtDefs.h"

namespace newton
{

/**
 * \class NtNCLToken
 * \brief NCL lexical token
 *
 * This class defines a lexical token object for the NCL language.
 */
class NT_EXPORT NtNCLToken
{
public:
    /**
     * \enum Type
     * \brief Token type
     *
     * This enum class specifies the type of token.
     */
    enum class Type
    {
        KEYWORD,        ///< Keyword token
        IDENTIFIER,     ///< Identifier token
        LITERAL,        ///< Literal token
        OPERATOR,       ///< Operator token
        PUNCTUATOR,     ///< Punctuator token
        WHITESPACE,     ///< Whitespace token
        DOM             ///< DOM element token
    };

    /**
     * \brief Constructor
     *
     * Default constructor.
     *
     * \param type Type of token
     * \param value String value of token
     * \param line Source code line for this token
     * \param col Source code column for this token
     */
    NtNCLToken(const Type type, const std::string& value, const size_t line, const size_t col)
        : m_type{ type }, m_value{ value }, m_line{ line }, m_col{ col }

    /**
     * \brief Virtual destructor
     */
    virtual ~NtNCLToken() { }

protected:
    /**
     * Token type
     */
    Type m_type;

    /**
     * Token string value
     */
    std::string m_value;

    /**
     * Token source code line
     */
    size_t m_line;

    /**
     * Token source code column
     */
    size_t m_col;
};

}

