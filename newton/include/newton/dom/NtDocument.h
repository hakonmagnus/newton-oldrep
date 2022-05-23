// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#pragma once

/**
 * \file NtDocument.h
 * \brief HTML document class
 *
 * This file contains the class definition for an HTML document DOM object.
 */

#include "newton/base/NtDefs.h"

namespace newton
{

/**
 * \class NtDocument
 * \brief HTML DOM document object
 *
 * This class implements the DOM's Document object for HTML5.
 */
class NT_EXPORT NtDocument
{
public:
    /**
     * \enum DocumentReadyState
     *
     * Ready state of the document.
     */
    enum class DocumentReadyState
    {
        LOADING,            ///< Document loading
        INTERACTIVE,        ///< Document interactive
        COMPLETE            ///< Document complete
    };

    /**
     * \enum DocumentVisibilityState
     *
     * Visibility state of the document.
     */
    enum class DocumentVisibilityState
    {
        VISIBLE,            ///< Document visible
        HIDDEN              ///< Document hidden
    };

protected:
};

}

