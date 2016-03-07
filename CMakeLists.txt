# © Copyright 2010 - 2016 BlackTopp Studios Inc.
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

####################################################################################################
cmake_minimum_required(VERSION 3.2)
project(StaticFoundation)
message(STATUS "${PROJECT_NAME} - Starting Configuration.")

####################################################################################################
#set(JagatiChecksum "ea5f6ad9531cdcb8e8914d497b1b68d3885d29beceb83c55fdd858\
#2f2827276247869a17b6f8f2cb013a61e3d72540f5ab413f0a53be539c4ae339028acf656c")
#file(DOWNLOAD
#    "https://raw.githubusercontent.com/BlackToppStudios/Jagati/master/Jagati.cmake"
#    "${${PROJECT_NAME}_BINARY_DIR}/Jagati.cmake"
#    EXPECTED_HASH SHA512=${JagatiChecksum}
#)

####################################################################################################
#include("${${PROJECT_NAME}_BINARY_DIR}/Jagati.cmake")
include("Jagati.cmake")
StandardJagatiSetup()
add_subdirectory(CMake)

####################################################################################################
message(STATUS "Determining Source Files.")

set(HeaderFiles
    "${StaticFoundationIncludeDir}crossplatformexport.h"
    "${StaticFoundationIncludeDir}datatypes.h"
    "${StaticFoundationIncludeDir}runtimestatics.h"
    "${StaticFoundationIncludeDir}staticfoundation.h"
    "${StaticFoundationIncludeDir}supresswarnings.h"
)
ShowList("Header Files:" "\t" "${HeaderFiles}")

set(SourceFiles
    "${StaticFoundationSourceDir}runtimestatics.cpp"

)
ShowList("Source Files:" "\t" "${SourceFiles}")

set(TestSourceFiles
    "${StaticFoundationTestDir}tests.h"
    "${StaticFoundationTestDir}tests.cpp"
)

set(SwigFiles
    "${StaticFoundationSwigDir}swigconfig.h"
)

####################################################################################################
# Set up Include Directories

file(MAKE_DIRECTORY ${${PROJECT_NAME}GenHeadersDir})
include_directories(
    ${${PROJECT_NAME}IncludeDir}
    ${${PROJECT_NAME}GenHeadersDir}
)

####################################################################################################
# Set up config file

AddJagatiCompileOption("MEZZ_BuildDoxygen"
    "Create HTML documentation with Doxygen. Requires Doxygen to be install in PATH." ON)
AddJagatiCompileOption("MEZZ_BuildStaticLibraries"
    "If set the Mezzanine will be built as static libraries, shared if unset." ON)

AddJagatiConfig("MEZZ_Linux" "" ${SystemIsLinux})
AddJagatiConfig("MEZZ_Windows" "" ${SystemIsWindows})
AddJagatiConfig("MEZZ_MacOSX" "" ${SystemIsMacOSX})

ChooseLibraryType(${MEZZ_BuildStaticLibraries})
message(STATUS "Libtype: ${MEZZ_LibraryBuildType}")

EmitConfig()

####################################################################################################
# Set up Build targets

AddJagatiLibrary("StaticFoundation")
add_library(${StaticFoundationLib} ${MEZZ_LibraryBuildType} ${HeaderFiles} ${SourceFiles})
add_executable(${PROJECT_NAME}_Tester ${HeaderFiles} ${TestSourceFiles})
target_link_libraries(${PROJECT_NAME}_Tester ${StaticFoundationLib})

# A Project to do nothing but get All the Source files visible in IDEs
add_custom_target(
    ${PROJECT_NAME}_IDE_Visibility
    DEPENDS ${PROJECT_NAME}_Tester
            "${${PROJECT_NAME}BinaryDir}Guidelines.md"
            ExternalProjectDownload
    SOURCES ${HeaderFiles}
            ${SourceFiles}
            ${TestSourceFiles}
            ${SwigFiles}
            ${StaticFoundationConfigFilename}
            README.md
            COPYING.md
)

message(STATUS "${PROJECT_NAME} - Ending Configuration.")
