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

/// @file
/// @brief This defines what is inside the base exception class.

#include "ExceptionBase.h"

namespace Mezzanine
{
    ExceptionBase::ExceptionBase(const String& Message,
                                 const String& SrcFunction,
                                 const String& SrcFile,
                                 const Whole& FileLine)
        : ErrorMessage(Message),
          Function(SrcFunction),
          File(SrcFile),
          Line(FileLine)
        {  ExceptionAction(GetCompleteMessage()); }

    ExceptionBase::~ExceptionBase() noexcept
        { }

    ///////////////////////////////////////////////////////////////////////////////
    // Throw actions
    // Duplicated to avoid static ordering fiasco
    const ExceptionBase::ExpectedActionType ExceptionBase::NullAction = [](const Mezzanine::String&){};
    ExceptionBase::ExpectedActionType ExceptionBase::ExceptionAction = [](const Mezzanine::String&){};
    
    void ExceptionBase::SetExceptionCreationAction(ExpectedActionType&& FreshAction)
        { ExceptionAction = FreshAction; }

    static void ExceptionBase::EraseExceptionCreationAction()
        { ExceptionAction = NullAction; }

    ///////////////////////////////////////////////////////////////////////////////
    // Error Information

    const String& ExceptionBase::GetFunction() const noexcept
        { return Function; }

    const String& ExceptionBase::GetFile() const noexcept
        { return File; }

    const Whole& ExceptionBase::GetLine() const noexcept
        { return Line; }

    String ExceptionBase::GetCompleteMessage() const noexcept
    {
        try
        {
            // This will probably not work in low memory conditions.
            StringStream ErrorStream;            
            //ErrorStream << "MEZZANINE EXCEPTION(" << ExceptionTypeName << "): "
                        //<< ErrorMessage << " In " << Function << ". "
                        //<< (Line?StringTools::ConvertToString(Line):"Unknown") << " of "
                        //<< File << ".";
            return ErrorStream.str();
        } catch(...) {
            return "Error details unknown. Error caught while generating exception message. :(";
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    // Error Messages
    const char* ExceptionBase::what() const noexcept
        { return GetCompleteMessage().c_str(); }
}
