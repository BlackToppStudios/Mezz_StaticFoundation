// © Copyright 2010 - 2018 BlackTopp Studios Inc.
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

/// @file
/// @brief The

#include "RuntimeStatics.h"
#include "StaticFoundationConfig.h"

namespace Mezzanine
{
    Boole RuntimeStatic::BuildDoxygen()
    {
        #ifdef MEZZ_BuildDoxygen
            return true;
        #else
            return false;
        #endif
    }

    Boole RuntimeStatic::BuildStaticLibraries()
    {
        #ifdef MEZZ_BuildStaticLibraries
            return true;
        #else
            return false;
        #endif
    }


    Boole RuntimeStatic::CodeCoverage()
    {
        #ifdef MEZZ_CodeCoverage
            return true;
        #else
            return false;
        #endif
    }

    Boole RuntimeStatic::CpuKnown()
    {
        #ifdef MEZZ_CpuKnown
            return true;
        #else
            return false;
        #endif
    }

    Boole RuntimeStatic::CpuX86()
    {
        #ifdef MEZZ_CpuX86
            return true;
        #else
            return false;
        #endif
    }

    Boole RuntimeStatic::CpuAmd64()
    {
        #ifdef MEZZ_CpuAmd64
            return true;
        #else
            return false;
        #endif
    }

    Boole RuntimeStatic::CpuArm()
    {
        #ifdef MEZZ_CpuArm
            return true;
        #else
            return false;
        #endif
    }

    Boole RuntimeStatic::Linux()
    {
        #ifdef MEZZ_Linux
            return true;
        #else
            return false;
        #endif
    }

    Boole RuntimeStatic::Windows()
    {
        #ifdef MEZZ_Windows
            return true;
        #else
            return false;
        #endif
    }

    Boole RuntimeStatic::MacOSX()
    {
        #ifdef MEZZ_MacOSX
            return true;
        #else
            return false;
        #endif
    }

    Boole RuntimeStatic::Ios()
    {
        #ifdef MEZZ_Ios
            return true;
        #else
            return false;
        #endif
    }

    Boole RuntimeStatic::CompilerDetected()
    {
        #ifdef MEZZ_CompilerDetected
            return true;
        #else
            return false;
        #endif
    }

    Boole RuntimeStatic::CompilerIsClang()
    {
        #ifdef MEZZ_CompilerIsClang
            return true;
        #else
            return false;
        #endif
    }

    Boole RuntimeStatic::CompilerIsGCC()
    {
        #ifdef MEZZ_CompilerIsGCC
            return true;
        #else
            return false;
        #endif
    }

    Boole RuntimeStatic::CompilerIsEmscripten()
    {
        #ifdef MEZZ_CompilerIsEmscripten
            return true;
        #else
            return false;
        #endif
    }

    Boole RuntimeStatic::CompilerIsIntel()
    {
        #ifdef MEZZ_CompilerIsIntel
            return true;
        #else
            return false;
        #endif
    }

    Boole RuntimeStatic::CompilerIsMsvc()
    {
        #ifdef MEZZ_CompilerIsMsvc
            return true;
        #else
            return false;
        #endif
    }

    Boole RuntimeStatic::CompilerDesignNix()
    {
        #ifdef MEZZ_CompilerDesignNix
            return true;
        #else
            return false;
        #endif
    }

    Boole RuntimeStatic::CompilerDesignMS()
    {
        #ifdef MEZZ_CompilerDesignMS
            return true;
        #else
            return false;
        #endif
    }

    Boole RuntimeStatic::Arch64()
    {
        #ifdef MEZZ_Arch64
            return true;
        #else
            return false;
        #endif
    }

    Boole RuntimeStatic::Arch32()
    {
        #ifdef MEZZ_Arch32
            return true;
        #else
            return false;
        #endif
    }

    Boole RuntimeStatic::Debug()
    {
        #ifdef MEZZ_Debug
            return true;
        #else
            return false;
        #endif
    }

}
