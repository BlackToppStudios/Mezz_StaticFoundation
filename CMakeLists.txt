# © Copyright 2010 - 2018 BlackTopp Studios Inc.
# This file is part of The Mezzanine Engine.
#
#    The Mezzanine Engine is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    The Mezzanine Engine is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with The Mezzanine Engine.  If not, see <http://www.gnu.org/licenses/>.
#
#   The original authors have included a copy of the license specified above in the
#   'Docs' folder. See 'gpl.txt'
#
#   We welcome the use of the Mezzanine engine to anyone, including companies who wish to
#   Build professional software and charge for their product.
#
#   However there are some practical restrictions, so if your project involves
#   any of the following you should contact us and we will try to work something
#   out:
#    - DRM or Copy Protection of any kind(except Copyrights)
#    - Software Patents You Do Not Wish to Freely License
#    - Any Kind of Linking to Non-GPL licensed Works
#    - Are Currently In Violation of Another Copyright Holder's GPL License
#    - If You want to change our code and not add a few hundred MB of stuff to
#        your distribution
#
#   These and other limitations could cause serious legal problems if you ignore
#   them, so it is best to simply contact us or the Free Software Foundation, if
#   you have any questions.
#
#   Joseph Toppi - toppij@gmail.com
#   John Blackwood - makoenergy02@gmail.com

########################################################################################################################
cmake_minimum_required(VERSION 2.8)
project(StaticFoundation)
message(STATUS "${PROJECT_NAME} - Starting Configuration using CMake ${CMAKE_VERSION}.")

##########################################################################|#############################################
# Download, Verify and setup the Jagati
set(JagatiChecksum "48270c82b7c471b8ad025c6b68e6d2fc5e1dc4b69e79d2dcfd9519\
42b7661fcbae3c17a9555274cd7894f1b2e6d8c3b080673b7dfd7589c042e6c94776445bf6")
file(DOWNLOAD
    "https://raw.githubusercontent.com/BlackToppStudios/Jagati/0.20.0/Jagati.cmake"
    "${${PROJECT_NAME}_BINARY_DIR}/Jagati.cmake"
    EXPECTED_HASH SHA512=${JagatiChecksum}
)
include("${${PROJECT_NAME}_BINARY_DIR}/Jagati.cmake")

set(${PROJECT_NAME}BinTarget "${PROJECT_NAME}_Tester")
StandardJagatiSetup()

########################################################################################################################
message(STATUS "Determining Source Files.")

AddHeaderFile("CrossPlatformExport.h")
AddHeaderFile("DataTypes.h")
AddHeaderFile("RuntimeStatics.h")
AddHeaderFile("StaticFoundation.h")
AddHeaderFile("StaticString.h")
AddHeaderFile("SuppressWarnings.h")
ShowList("Header Files:" "\t" "${StaticFoundationHeaderFiles}")

AddSourceFile("RuntimeStatics.cpp")
ShowList("Source Files:" "\t" "${StaticFoundationSourceFiles}")

# Because this can't rely on Mezz_Test we need to do this manually
AddMainSourceFile("${StaticFoundationTestDir}Tests.h")
AddMainSourceFile("${StaticFoundationTestDir}Tests.cpp")
ShowList("Test Source Files:" "\t" "${StaticFoundationMainSourceFiles}")

AddSwigEntryPoint("SwigConfig.h")
ShowList("Swig Input Files:" "\t" "${StaticFoundationSwigFiles}")

AddJagatiDoxInput("Dox.h")
ShowList("Doxygen Input Files:" "\t" "${JagatiDoxArray}")

########################################################################################################################
# Set up config file

AddJagatiCompileOption("MEZZ_BuildDoxygen"
    "Create HTML documentation with Doxygen. Requires Doxygen to be install in PATH." ON)
AddJagatiCompileOption("MEZZ_BuildStaticLibraries"
    "If set the Mezzanine will be built as static libraries, shared if unset." ON)
AddJagatiCompileOption("MEZZ_CodeCoverage"
    "If set compiler flags will be set that gather code coverage data on build results." OFF)

UseStaticLinking(${MEZZ_BuildStaticLibraries})
ChooseCodeCoverage(${MEZZ_CodeCoverage})

AddJagatiConfig("MEZZ_CpuKnown" "" ${CpuIsKnown})
AddJagatiConfig("MEZZ_CpuX86" "" ${CpuIsX86})
AddJagatiConfig("MEZZ_CpuAmd64" "" ${CpuIsAmd64})
AddJagatiConfig("MEZZ_CpuArm" "" ${CpuIsArm})

AddJagatiConfig("MEZZ_Linux" "" ${SystemIsLinux})
AddJagatiConfig("MEZZ_Windows" "" ${SystemIsWindows})
AddJagatiConfig("MEZZ_MacOSX" "" ${SystemIsMacOSX})
AddJagatiConfig("MEZZ_Ios" "" ${SystemIsIOS})

AddJagatiConfig("MEZZ_CompilerDetected" "" ${CompilerDetected})
AddJagatiConfig("MEZZ_CompilerIsClang" "" ${CompilerIsClang})
AddJagatiConfig("MEZZ_CompilerIsEmscripten" "" ${CompilerIsEmscripten})
AddJagatiConfig("MEZZ_CompilerIsGCC" "" ${CompilerIsGCC})
AddJagatiConfig("MEZZ_CompilerIsIntel" "" ${CompilerIsIntel})
AddJagatiConfig("MEZZ_CompilerIsMsvc" "" ${CompilerIsMsvc})

AddJagatiConfig("MEZZ_CompilerDesignNix" "" ${CompilerDesignNix})
AddJagatiConfig("MEZZ_CompilerDesignMS" "" ${CompilerDesignMS})
AddJagatiConfig("MEZZ_Arch64" "" ${Platform64Bit})
AddJagatiConfig("MEZZ_Arch32" "" ${Platform32Bit})

AddJagatiConfig("MEZZ_Debug" "" ${CompilerDebug})

EmitConfig()
ShowList("Config Files made by StaticFoundation:" "\t" "${StaticFoundationConfigFilename}")
AddJagatiDoxInput("${StaticFoundationConfigFilename}")

########################################################################################################################
# Set up Doxygen Targets
if(MEZZ_BuildDoxygen)
    find_program(MEZZ_DoxygenExecutable "doxygen")
    if(MEZZ_DoxygenExecutable)
        set(DoxygenConfigDir "${StaticFoundationDoxDir}doxyfiles/")
        set(DoxygenResultsDir "${StaticFoundationBinaryDir}Doxygen/")
        set(WarningsFile "${DoxygenResultsDir}html/DoxygenWarnings.txt")
        string (REPLACE ";" " " DoxygenInputs "${JagatiDoxArray}")

        configure_file(${DoxygenConfigDir}Doxyfile ${StaticFoundationBinaryDir})

        if(EXISTS ${WarningsFile})
        else(EXISTS ${WarningsFile})
            file(MAKE_DIRECTORY ${DoxygenResultsDir})
            file(WRITE ${WarningsFile} "")
        endif(EXISTS ${WarningsFile})

        message(STATUS "Found doxygen Executable at '${MEZZ_DoxygenExecutable}'")
        add_custom_target(MezzanineDocumentation ALL
            COMMAND ${MEZZ_DoxygenExecutable} ${StaticFoundationBinaryDir}Doxyfile
            COMMAND ${CatCommand} ${DoxygenResultsDir}html/DoxygenWarnings.txt 1>&2
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    ${DoxygenConfigDir}img/closed.png
                    ${DoxygenResultsDir}html/clclosed.png
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    ${DoxygenConfigDir}img/closed.png
                    ${DoxygenResultsDir}html/closed.png
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    ${DoxygenConfigDir}img/open.png
                    ${DoxygenResultsDir}html/clopen.png
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    ${DoxygenConfigDir}img/favicon.ico
                    ${DoxygenResultsDir}html/favicon.ico
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    ${DoxygenConfigDir}img/open.png
                    ${DoxygenResultsDir}html/open.png
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    ${DoxygenConfigDir}img/red_x.png
                    ${DoxygenResultsDir}html/search/close.png
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    ${DoxygenConfigDir}img/Magnifier.png
                    ${DoxygenResultsDir}html/search/mag_sel.png
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    ${DoxygenConfigDir}html/search.css
                    ${DoxygenResultsDir}html/search/search.css

            COMMAND ${CMAKE_COMMAND} -E remove
                    ${DoxygenResultsDir}html/tab_a.png
            COMMAND ${CMAKE_COMMAND} -E remove
                    ${DoxygenResultsDir}html/tab_b.png
            COMMAND ${CMAKE_COMMAND} -E remove
                    ${DoxygenResultsDir}html/tab_h.png
            COMMAND ${CMAKE_COMMAND} -E remove
                    ${DoxygenResultsDir}html/tab_s.png
            COMMAND ${CMAKE_COMMAND} -E remove
                    ${DoxygenResultsDir}html/search/search_m.png
            COMMAND ${CMAKE_COMMAND} -E remove
                    ${DoxygenResultsDir}html/search/search_l.png
            COMMAND ${CMAKE_COMMAND} -E remove
                    ${DoxygenResultsDir}html/search/search_r.png
            COMMAND ${CMAKE_COMMAND} -E remove
                    ${DoxygenResultsDir}html/search_r.png
            WORKING_DIRECTORY ${DoxygenConfigDir}
            COMMENT "Generating API documentation with Doxygen" VERBATIM
            SOURCES ${DoxygenConfigDir}Doxyfile
                    ${DoxygenConfigDir}layout.xml
                    ${DoxygenResultsDir}html/DoxygenWarnings.txt
                    ${DoxygenConfigDir}html/DoxyStyle.css
                    ${DoxygenConfigDir}html/search.css
                    ${DoxygenConfigDir}html/DoxyFooter.html
                    ${DoxygenConfigDir}html/DoxyHeader.html
        )
        # Creation Doxygen target here
    else(MEZZ_DoxygenExecutable)
        message(ERROR
            " Could not find doxygen executable, is it installed and in your system Path?'")
    endif(MEZZ_DoxygenExecutable)
endif(MEZZ_BuildDoxygen)
########################################################################################################################
# Set up Build targets

# Add this as a library to the list of available libraries.
AddJagatiLibrary()
CreateCoverageTarget(${StaticFoundationLib} ${StaticFoundationSourceFiles})

# This makes its own tester as the main exe because this cannot rely on Mezz_Test.
AddJagatiExecutable()

# Some extra creating of targets for other development related tasks
AddIDEVisibility("${StaticFoundationTestSourceFiles}")
SetCodeCoverage()

message(STATUS "${PROJECT_NAME} - Ending Configuration.")
