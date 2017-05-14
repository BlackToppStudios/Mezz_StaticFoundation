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
#ifndef Mezz_StaticFoundation_Exception_h
#define Mezz_StaticFoundation_Exception_h

#include "DataTypes.h"

namespace Mezzanine
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief This is the exception thrown by most Mezzanine systems that can throw exceptions.
/// @ingroup ExceptionGen
class MEZZ_LIB ExceptionBase : public std::exception
{
    private:
        /// @brief This stores the Error Message
        const Mezzanine::String ErrorMessage;
        /// @brief This stores the function name where the exception originated.
        const Mezzanine::String Function;
        /// @brief This stores the file where the exception originated.
        const Mezzanine::String File;
        /// @brief This stores the line number where the exception originated.
        const Mezzanine::Whole Line;

    public:
        /// @brief Declaring Constructor.
        /// @param Message A basic description of the error.
        /// @param SrcFunction The name of the function from which this originated.
        /// @param SrcFile The name of the file from which this originated.
        /// @param FileLine The line on the named file from which this originated.
        /// @details Don't call this, use MEZZ_EXCEPTION which captures a bunch of information automatically and is
        /// simpler.
        ExceptionBase(const Mezzanine::String& Message,
                      const Mezzanine::String& SrcFunction,
                      const Mezzanine::String& SrcFile,
                      const Mezzanine::Whole& FileLine);

        /// @brief Class destructor.
        virtual ~ExceptionBase() noexcept;


        ///////////////////////////////////////////////////////////////////////////////
        // Throw actions
        typedef std::function<void(const Mezzanine::String&)> ExpectedActionType;

        /// @brief A valid action that does nothing
        static const ExpectedActionType NullAction;

    private:
        /// @brief This is a function that can be used to do something when an exception is thrown
        /// @details This default to a null lamba and causes no action to occur. If set to any other function it will be
        /// called when an exception is being constructed and passed the results of GetCompleteMessage(). The primary
        /// goal of this is to enable easy logging, but in principle this could be used for anything.
        static ExpectedActionType ExceptionAction;

    public:
        /// @brief Set the exception action.
        /// @param FreshAction Any functionlike thing accepting a Mezzanine::String reference and returning nothing.
        static void SetExceptionCreationAction(ExpectedActionType&& FreshAction);
        /// @brief Remove any previously define exception actions.
        static void EraseExceptionCreationAction();

        ///////////////////////////////////////////////////////////////////////////////
        // Class MetaData
        /// @brief Gets the exception code for this exception.
        /// @return Returns the exception code for this exception.
        virtual Mezzanine::Whole GetExceptionCode() const noexcept = 0;
        /// @brief Gets the name of the exception type.
        /// @return Returns the exception type as a Mezzanine::String.
        virtual const Mezzanine::String& GetExceptionTypeName() const noexcept = 0;

        ///////////////////////////////////////////////////////////////////////////////
        // Error Information
        /// @brief Gets the function of the exception.
        /// @return Returns a const Mezzanine::String reference
        const Mezzanine::String& GetFunction() const noexcept;
        /// @brief Gets the file of the exception.
        /// @return Returns the name of the file this exception is being thrown from.
        const Mezzanine::String& GetFile() const noexcept;
        /// @brief Gets the line number of the exception.
        /// @return Returns the line in the file this exception is being thrown from.
        const Mezzanine::Whole& GetLine() const noexcept;

        ///////////////////////////////////////////////////////////////////////////////
        // Error Messages
        /// @brief Constructs the complete message from all the information provided about the exception.
        /// @return Returns a Mezzanine::String with the complete error.
        Mezzanine::String GetCompleteMessage() const noexcept;
        /// @brief Retrieves the error message.
        /// @return This returns a Mezzanine::String that is the stored error message.
        virtual const char* what() const noexcept;
};//Exception

//#ifndef MEZZ_EXCEPTION
/// @brief An easy way to throw exceptions with rich information.
/// @ingroup ExceptionGen
/// @details An important part of troubleshooting errors from the users perspective is being able to tie a specific
/// 'fix' to a specific error message. An important part of that is catching the right exceptions at the right time. It
/// is also important to not allocate more memory or other resources while creating an exception.
/// @n @n
/// This macro makes doing all of these easy. Every exception thrown by this macro with provide the function name, the
/// file name and the line in the file from which it was thrown. That provides all the information the developer needs
/// to identify the issue. This uses some specific template machinery to generate specifically typed exceptions static
/// instances at compile to insure the behaviors a programmer needs, specifically capturing the line, function, file and
/// class of the exception in the error message. Since these are allocated (optimized out really) when the program
/// is first loaded so there will be no allocations when this is called, and the type is controlled
/// by the error number parameter.
/// @n @n
/// As long as the developer provides a unique string for each failure, then any messages logged or presented to the
/// user or log will uniquely identify that specific problem. This allows the user to perform very specific web searches
/// and potentially allows troubleshooters/technicians to skip lengthy diagnostics steps.
/// @param num A specific code from the @ref ExceptionBase::ExceptionCodes enum will control the
/// type of exception produced.
/// @param desc A message/description to be passed through to the exceptions constructor.
#define MEZZ_EXCEPTION(num, desc) throw Mezzanine::ExceptionFactory<num>::Type(desc, __func__, __FILE__, __LINE__ );
//#endif

}//Mezzanine

#endif
