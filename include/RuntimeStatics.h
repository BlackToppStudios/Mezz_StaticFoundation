// © Copyright 2010 - 2017 BlackTopp Studios Inc.
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
#ifndef Mezz_StaticFoundation_runtime_statics_h
#define Mezz_StaticFoundation_runtime_statics_h

/// @file
/// @brief This file is deeply confused, it tries to provide runtime versions of various compile
/// time constants.
/// @details This might seem useless, but languages like Lua and Ruby have no concept of compile
/// time at all and languages like Like Java and C# do not have a robust equivelant to the C
/// preprocessor. These and languages like these could use the Mezzanine via SWIG bindings.
/// @n @n
/// This might also be useful in situations where the absence of a preprocessor value needs to
/// stored in a C++ container.

#include "DataTypes.h"

namespace Mezzanine
{
    /// @brief A class for aggregating all the methods related to the Mezzanine preprocessor
    /// directives
    /// @details This is required because some SWIG languages cannot handle free functions.
    class RuntimeStatic
    {
        public:
            /// @return If MEZZ_BuildDoxygen is defined true, false otherwise.
            static Boole BuildDoxygen();

            /// @return If MEZZ_BuildStaticLibraries is defined true, false otherwise.
            static Boole BuildStaticLibraries();

            /// @return If MEZZ_CodeCoverage is defined true, false otherwise.
            static Boole CodeCoverage();

            /// @return If MEZZ_Linux is defined true, false otherwise.
            static Boole Linux();

            /// @return If MEZZ_Windows is defined true, false otherwise.
            static Boole Windows();

            /// @return If MEZZ_MacOSX is defined true, false otherwise.
            static Boole MacOSX();

            /// @return If MEZZ_CompilerIsClang is defined true, false otherwise.
            static Boole CompilerIsClang();

            /// @return If MEZZ_CompilerIsEmscripten is defined true, false otherwise.
            static Boole CompilerIsEmscripten();

            /// @return If MEZZ_CompilerIsGCC is defined true, false otherwise.
            static Boole CompilerIsGCC();

            /// @return If MEZZ_CompilerIsIntel is definde true, false otherwise.
            static Boole CompilerIsIntel();

            /// @return If MEZZ_CompilerIsMsvc is defined true, false otherwise.
            static Boole CompilerIsMsvc();

            /// @return If MEZZ_CompilerDesignNix is defined true, false otherwise.
            static Boole CompilerDesignNix();

            /// @return If MEZZ_CompilerDesignMS is defined true, false otherwise.
            static Boole CompilerDesignMS();

            /// @return If MEZZ_Arch64 is defined true, false otherwise.
            static Boole Arch64();

            /// @return If MEZZ_Arch32 is defined true, false otherwise.
            static Boole Arch32();

            /// @return If MEZZ_Debug is defined true, false otherwise.
            static Boole Debug();
    };

}



#endif
