// © Copyright 2010 - 2020 BlackTopp Studios Inc.
/* This file is part of The Mezzanine Engine.

    The Mezzanine Engine is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    The Mezzanine Engine is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with The Mezzanine Engine.  If not, see <http://www.gnu.org/licenses/>.
*/
/* The original authors have included a copy of the license specified above in the
   'Docs' folder. See 'gpl.txt'
*/
/* We welcome the use of the Mezzanine engine to anyone, including companies who wish to
   Build professional software and charge for their product.

   However there are some practical restrictions, so if your project involves
   any of the following you should contact us and we will try to work something
   out:
    - DRM or Copy Protection of any kind(except Copyrights)
    - Software Patents You Do Not Wish to Freely License
    - Any Kind of Linking to Non-GPL licensed Works
    - Are Currently In Violation of Another Copyright Holder's GPL License
    - If You want to change our code and not add a few hundred MB of stuff to
        your distribution

   These and other limitations could cause serious legal problems if you ignore
   them, so it is best to simply contact us or the Free Software Foundation, if
   you have any questions.

   Joseph Toppi - toppij@gmail.com
   John Blackwood - makoenergy02@gmail.com
*/
#ifndef Mezz_StaticFoundation_trace_h
#define Mezz_StaticFoundation_trace_h

/// @file
/// @brief Some basic tools for troubleshooting the test suite when a debugger might not work

#include "DataTypes.h"

#ifndef MEZZ_TRACE // The user macro

    /// @def MEZZ_Trace
    /// @brief This is a compiler flag to enable or disable the trace messages.

    /// @def MEZZ_TRACE
    /// @brief This is a better alternative to littering prints in code when troubleshooting without a debugger.
    /// @details When MEZZ_Trace (Lower case) is disabled this is nothing, When enabled this emits a message, file name,
    /// line number, and function name it is called from.
    /// @param Message A message to be emitted

    #ifdef MEZZ_Trace // The compiler option
        #ifdef __FUNCTION__
            #define MEZZ_TRACE(Message)                                                                                \
                Mezzanine::StaticFoundation::Trace((Message), __FUNCTION__, __FILE__, __LINE__ );
        #else
            #define MEZZ_TRACE(Message)                                                                                \
                Mezzanine::StaticFoundation::Trace((Message), __func__, __FILE__, __LINE__ );
        #endif
    #else
        #define MEZZ_TRACE(Message);
    #endif
#endif


namespace Mezzanine
{
namespace StaticFoundation
{

    /// @brief A simple function that sends the provided information to the standard log.
    /// @note This shouldn't be used directly in most cases. Instead game devs should use MEZZ_TRACE.
    /// @param Message Any text to be emitted when tracing is enabled.
    /// @param FuncName The function name this is called from, emitted when tracing is enabled.
    /// @param File The file name this is called from, emitted when tracing is enabled.
    /// @param Line The line number this was called from, emitted when tracing is enabled.
    void MEZZ_LIB Trace(String&& Message,
                        String&& FuncName = "",
                        String&& File = "",
                        Whole Line = 0);

}// Testing
}// Mezzanine

#endif
