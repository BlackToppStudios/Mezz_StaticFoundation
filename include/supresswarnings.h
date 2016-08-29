// © Copyright 2010 - 2016 BlackTopp Studios Inc.
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
#ifndef Mezz_StaticFoundation_supresswarnings_h
#define Mezz_StaticFoundation_supresswarnings_h

/// @file
/// @brief Sets up some macros for cross platform warning supression.

/// @def SAVE_WARNING_STATE
/// @brief Saves thes State in the compiler which detemines what warnings will be captured. Must
/// be used with @ref RESTORE_WARNING_STATE to prevent compilation issues.
/// @sa RESTORE_WARNING_STATE

/// @def SUPPRESS_VC_WARNING
/// @brief If in visual studio this resolves to a pragma that supresses a warning, if not it resolves to nothing.

/// @def SUPPRESS_GCC_WARNING
/// @brief If in GCC or a compatible compiler this resolves to a pragma that supresses a warning, if
/// not it resolves to nothing.

/// @def SUPPRESS_CLANG_WARNING
/// @brief If in CLANG this resolves to a pragma that supresses a warning, if not it resolves to nothing.

/// @def RESTORE_WARNING_STATE
/// @brief Restores the last warning state saved with @ref SAVE_WARNING_STATE. This cleans up after
/// @ref SAVE_WARNING_STATE
/// @note Part of the C++ API only.
/// @sa SAVE_WARNING_STATE

/// @def PRAGMA
/// @internal
/// @brief Used as an abstraction to insure the C++11 _Pragma keyword (or workalike when dealing
/// with visual studio BS) can be called using a single symbol on any platform.
/// @warning There is no reason to use this in client code, ever.

#ifndef SWIG
    #ifdef _MSC_VER // The intel compiler might act up here
        #define SAVE_WARNING_STATE PRAGMA(warning(push))
        #define SUPPRESS_VC_WARNING(suppress) PRAGMA(warning(disable: ## suppress ## ))
        #define SUPPRESS_GCC_WARNING(suppress)
        #define SUPPRESS_CLANG_WARNING(suppress)
        #define RESTORE_WARNING_STATE PRAGMA(warning(pop))
        #define PRAGMA(x) __pragma(x)
    #endif

    #ifdef __clang__
        #define SAVE_WARNING_STATE PRAGMA(GCC diagnostic push)
        #define SUPPRESS_VC_WARNING(X)
        #define SUPPRESS_GCC_WARNING(X) PRAGMA(clang diagnostic ignored X)
        #define SUPPRESS_CLANG_WARNING(X) PRAGMA(clang diagnostic ignored X)
        #define RESTORE_WARNING_STATE PRAGMA(GCC diagnostic pop)
        #define PRAGMA(x) _Pragma(#x)
    #elif __GNUG__
        #define SAVE_WARNING_STATE PRAGMA(GCC diagnostic push)
        #define SUPPRESS_VC_WARNING(X)
        #define SUPPRESS_GCC_WARNING(X) PRAGMA(GCC diagnostic ignored X)
        #define SUPPRESS_CLANG_WARNING(X)
        #define RESTORE_WARNING_STATE PRAGMA(GCC diagnostic pop)
        #define PRAGMA(x) _Pragma(#x)
    #endif

    #ifdef DOXYGEN
        #define SAVE_WARNING_STATE PRAGMA(GCC diagnostic push)
        #define SUPPRESS_VC_WARNING(suppress) PRAGMA(warning(disable: ## suppress ## ))
        #define SUPPRESS_GCC_WARNING(X) PRAGMA(GCC diagnostic ignored X)
        #define SUPPRESS_CLANG_WARNING(X) PRAGMA(GCC diagnostic ignored X)
        #define RESTORE_WARNING_STATE PRAGMA(GCC diagnostic pop)
        #define PRAGMA(x) _Pragma(#x)
    #endif

#endif // \SWIG


#endif
