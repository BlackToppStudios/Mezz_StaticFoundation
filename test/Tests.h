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
#ifndef Mezz_StaticFoundation_tests_h
#define Mezz_StaticFoundation_tests_h

#include "StaticFoundation.h"

/// @file
/// @brief Some declarations of functions for the tests Mezz_StaticFoundation.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Dealing with the command line

/// @brief Check if the command line arguments are completely wrong. Can easily miss minor mistakes.
/// @details If this detects a problem this will exit with a failure code and print a message to std::cerr.
/// @param ArgCount The Argument count passed into main.
/// @param ArgVars The argument values passed into main.
void CheckUsage(int ArgCount, char** ArgVars);

/// @brief Get the string describing how to use this.
/// @return A Mezzanine::String containing human readable, thought likely minimal, help.
Mezzanine::String Usage(Mezzanine::String ExecutableName);

/// @brief Accepts command line parameters and creates a NameValuePairMap from them.
/// @details If this detects a problem this will exit with a failure code and print a message to std::cerr.
/// @param ArgCount The Argument count passed into main.
/// @param ArgVars The argument values passed into main.
/// @return A NameValuePairMap With an entry for each of the ArgVars split on a ":"
Mezzanine::NameValuePairMap CreateMapFromArgs(int ArgCount, char** ArgVars);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Test Functions

/// @brief What values where stored at compile time.
/// @return Mezzanine::NameValuePairMap which contains all the compiler flags set during the build.
Mezzanine::NameValuePairMap CheckableValues();

/// @param Mapping A name value pair list to turn into a String.
/// @return A String with each name value pair on its own line seperated by ":" and preceded by two spaces.
Mezzanine::String Stringify(const Mezzanine::NameValuePairMap& Mapping);

/// @param SomeInt Any integer to be converted to a String, defaults to 0.
/// @return A String contained the lexigraphically equivalent String to SomeInt.
Mezzanine::String IntToString(const Mezzanine::Int32 SomeInt);

/// @brief compare two instances Mezzanine::NameValuePairMap and determine if one is a subset of the other.
/// @param Expected The list of correct values that must be entirely contained in the other list for the test to be
/// successful.
/// @param Compiled The list of all values as compiled into the code.
/// @return True on success, false otherwise.
Mezzanine::Boole DoComparisonTest(const Mezzanine::NameValuePairMap& Expected,
                                  const Mezzanine::NameValuePairMap& Compiled);

/// @brief Check the StaticString class.
/// @return True if the class works, false if there was an issue.
Mezzanine::Boole CheckStaticString();

/// @brief Check that tracing works
/// @return True if tracing works, false if there was an issue.
Mezzanine::Boole DoTraceTest();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// XML Results

/// @brief Start Preparing an XML file that is compatible with JUnit.
/// @param Count The amount of tests that will be executed through all tests.
void StartJunitXml(Mezzanine::SizeType Count);

/// @brief Add a passing test result to the output file and display a message to the standard output.
/// @param TestClass The class or group that the test is a member of.
/// @param TestName A unique identifier for a test in a group.
/// @param Message A message that might be emitted or stored in the JUnit file.
void AddPass(Mezzanine::StringView&& TestClass,
             Mezzanine::StringView&& TestName,
             Mezzanine::StringView&& Message);

/// @brief Add a failing test result to the output file and display a message to the standard output.
/// @param TestClass The class or group that the test is a member of.
/// @param TestName A unique identifier for a test in a group.
/// @param Message A message that might be emitted or stored in the JUnit file.
void AddFail(Mezzanine::StringView&& TestClass,
             Mezzanine::StringView&& TestName,
             Mezzanine::StringView&& Message);

/// @brief Close and emit the JUnit file.
void CloseJunitXml();


#endif
