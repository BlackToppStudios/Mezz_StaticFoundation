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

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>

#include "Tests.h"
#include "RuntimeStatics.h"

using std::cout;
using std::stringstream;
using std::cerr;
using std::endl;
using Mezzanine::String;
using Mezzanine::NameValuePairMap;
using Mezzanine::Boole;

int main(int ArgCount, char** ArgVars)
{
    CheckUsage(ArgCount, ArgVars);
    if(false==CheckStaticString())
        { return EXIT_FAILURE; }
    NameValuePairMap FromCommandLine{CreateMapFromArgs(ArgCount, ArgVars)};
    DoComparisonTest(FromCommandLine, CheckableValues());
    return EXIT_SUCCESS;
}

void CheckUsage(int ArgCount, char** ArgVars)
{
    if(ArgCount==1)
    {
        cerr << Usage(ArgVars[0]);
        std::exit(EXIT_FAILURE);
    }
    if(ArgCount<1)
    {
        cerr << Usage("StaticFoundation_Tester");
        std::exit(EXIT_FAILURE);
    }
}

String Usage(String ExecutableName)
{
    return String("Usage:\n  ") + ExecutableName +
           " Name:Value [Name2:Value2 [Name3:Value3 [...]]\n\n" +
           "Currently Known Names and Values:\n" +
           Stringify(CheckableValues())+ "\n";
}

SAVE_WARNING_STATE
SUPPRESS_VC_WARNING(5045)
Mezzanine::NameValuePairMap CreateMapFromArgs(int ArgCount, char** ArgVars)
{
    NameValuePairMap Results;
    for(int Counter=1; Counter<ArgCount; Counter++)
    {
        String Current{ArgVars[Counter]};
        String::size_type ColonAt{Current.find(':')};
        if(0==ColonAt || String::npos==ColonAt)
        {
            cerr << "Colon not in expected place for '" << Current << "'" << endl;
            std::exit(EXIT_FAILURE);
        }
        String Name{Current.substr(0,ColonAt)};
        String Value{Current.substr(ColonAt+1,Current.size()-Name.size()-1)};
        Results[Name] = Value;
    }
    return Results;
}
RESTORE_WARNING_STATE

NameValuePairMap CheckableValues()
{
    NameValuePairMap Results;
    Results["MEZZ_BuildDoxygen"] = IntToString(Mezzanine::RuntimeStatic::BuildDoxygen());
    Results["MEZZ_BuildStaticLibraries"] = IntToString(Mezzanine::RuntimeStatic::BuildStaticLibraries());
    Results["MEZZ_CodeCoverage"] = IntToString(Mezzanine::RuntimeStatic::CodeCoverage());
    Results["MEZZ_CpuKnown"] = IntToString(Mezzanine::RuntimeStatic::CpuKnown());
    Results["MEZZ_CpuX86"] = IntToString(Mezzanine::RuntimeStatic::CpuX86());
    Results["MEZZ_CpuAmd64"] = IntToString(Mezzanine::RuntimeStatic::CpuAmd64());
    Results["MEZZ_CpuArm"] = IntToString(Mezzanine::RuntimeStatic::CpuArm());
    Results["MEZZ_Linux"] = IntToString(Mezzanine::RuntimeStatic::Linux());
    Results["MEZZ_Windows"] = IntToString(Mezzanine::RuntimeStatic::Windows());
    Results["MEZZ_MacOSX"] = IntToString(Mezzanine::RuntimeStatic::MacOSX());
    Results["MEZZ_Ios"] = IntToString(Mezzanine::RuntimeStatic::Ios());
    Results["MEZZ_CompilerDetected"] = IntToString(Mezzanine::RuntimeStatic::CompilerDetected());
    Results["MEZZ_CompilerIsClang"] = IntToString(Mezzanine::RuntimeStatic::CompilerIsClang());
    Results["MEZZ_CompilerIsGCC"] = IntToString(Mezzanine::RuntimeStatic::CompilerIsGCC());
    Results["MEZZ_CompilerIsEmscripten"] = IntToString(Mezzanine::RuntimeStatic::CompilerIsEmscripten());
    Results["MEZZ_CompilerIsIntel"] = IntToString(Mezzanine::RuntimeStatic::CompilerIsIntel());
    Results["MEZZ_CompilerIsMsvc"] = IntToString(Mezzanine::RuntimeStatic::CompilerIsMsvc());
    Results["MEZZ_CompilerDesignNix"] = IntToString(Mezzanine::RuntimeStatic::CompilerDesignNix());
    Results["MEZZ_CompilerDesignMS"] = IntToString(Mezzanine::RuntimeStatic::CompilerDesignMS());
    Results["MEZZ_Arch64"] = IntToString(Mezzanine::RuntimeStatic::Arch64());
    Results["MEZZ_Arch32"] = IntToString(Mezzanine::RuntimeStatic::Arch32());
    Results["MEZZ_Debug"] = IntToString(Mezzanine::RuntimeStatic::Debug());
    return Results;
}

void DoComparisonTest(const Mezzanine::NameValuePairMap& Expected, const Mezzanine::NameValuePairMap& Compiled)
{
    cout << "Expected:\n" << Stringify(Expected)
         << "\nCompiled in:\n" << Stringify(Compiled);

    stringstream XmlContents;
    XmlContents << "<testsuite tests=\"" << Expected.size() << "\">\n";

    Boole failed = false;
    String Other;
    for(Mezzanine::NameValuePair pair : Expected)
    {
        SAVE_WARNING_STATE
        SUPPRESS_VC_WARNING(4571)
        try
            { Other = Compiled.at(pair.first); }
        catch(...)
            { Other = "Not set"; failed=true; }
        RESTORE_WARNING_STATE

        cout << "\n" << pair.first << ": " << Other << " == " << pair.second;
        if(Other == pair.second)
        {
            cout <<  " \t[PASS]";
            XmlContents << "    <testcase classname=\"RuntimeStatic\" name=\"" << pair.first << "\"/>\n";
        }
        else
        {
            cout <<  " \t[FAIL]";
            XmlContents << "    <testcase classname=\"RuntimeStatic\" name=\"" << pair.first << "\">\n"
                        << "        <failure type=\"Mismatch\">"
                            << "Expected " << Other << " actually " << pair.second  << "</failure>\n"
                        << "    </testcase>\n";

            failed=true;

        }
    }
    XmlContents << "</testsuite>";
    cout << endl;

    std::ofstream JunitCompatibleXML("Mezz_StaticFoundationTests.xml");
    JunitCompatibleXML << XmlContents.str() << endl;

    if(failed)
        { std::exit(EXIT_FAILURE); }
}

Mezzanine::String Stringify(const Mezzanine::NameValuePairMap& Mapping)
{
    String Results;
    for(Mezzanine::NameValuePair pair : Mapping)
        { Results += "  " + pair.first + ": " + pair.second + "\n"; }
    return Results;
}

String IntToString(Mezzanine::Int32 SomeInt)
{
    stringstream Results;
    Results << SomeInt;
    return Results.str();
}

bool CheckStaticString()
{
    constexpr auto foo = MakeStaticString("foo");

    static_assert(foo.size() == 4,  "Size of constant string incorrect, 'foo' != 4.");

    static_assert(foo == "foo",     "Equality Comparison operator failed to find equality. [Literal]");
    static_assert(!(foo == "fooo"), "Equality Comparison operator failed to find inequal length. [Literal]");
    static_assert(!(foo == "bar"),  "Equality Comparison operator failed to find inqeual content. [Literal]");
    static_assert("foo" == foo,     "Equality Comparison operator failed to find equality. [Literal]");
    static_assert(!("fooo" == foo), "Equality Comparison operator failed to find inequal length. [Literal]");
    static_assert(!("bar" == foo),  "Equality Comparison operator failed to find inqeual content. [Literal]");

    static_assert(foo != "bar",     "Inequality Comparison operator failed to find inequality. [Literal]");
    static_assert(foo != "fooo",    "Inequality Comparison operator failed to find inequal length. [Literal]");
    static_assert(!(foo != "foo"),  "Inequality Comparison operator failed to find equal content. [Literal]");
    static_assert("bar" != foo,     "Inequality Comparison operator failed to find inequality. [Literal]");
    static_assert("fooo" != foo,    "Inequality Comparison operator failed to find inequal length. [Literal]");
    static_assert(!("foo" != foo),  "Inequality Comparison operator failed to find equal content. [Literal]");

    constexpr auto lorem = MakeStaticString("lorem");
    constexpr auto bar = MakeStaticString("bar");
    constexpr auto foo2 = MakeStaticString("foo");

    static_assert(foo == foo2,     "Equality Comparison operator failed to find equality. [StaticString]");
    static_assert(foo == foo,      "Equality Comparison operator failed to find equality. [Identity]");
    static_assert(!(foo == lorem), "Equality Comparison operator failed to find inequal length. [StaticString]");
    static_assert(!(foo == bar),   "Equality Comparison operator failed to find inqeual content. [StaticString]");

    static_assert(!(foo != foo2),  "Inequality Comparison operator failed to find equality. [StaticString]");
    static_assert(!(foo != foo),   "Inequality Comparison operator failed to find equality. [Identity]");
    static_assert(foo != lorem,    "Inequality Comparison operator failed to find inequal length. [StaticString]");
    static_assert(foo != bar,      "Inequality Comparison operator failed to find inqeual content. [StaticString]");

    if(Mezzanine::String("foo") != foo.str())
        { return false; }
    if(Mezzanine::String("foo") != foo.c_str())
        { return false; }

    static_assert( foo+bar == "foobar", "Concatenation doesn't work as expected with just StaticString instances.");

    // Perhaps someday.
    //static_assert( foo+"bar" == "foobar", "Concatenation doesn't work as expected with StaticStrings and literals.");

    return true;
}
