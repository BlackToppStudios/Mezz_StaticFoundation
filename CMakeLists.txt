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

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "Prevented in source tree build. Please create a "
                        "build directory outside of the Mezzanine source "
                        "code and have cmake build from there.")
endif(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})

###############################################################################
# The name of our project is "MezzanineAndCatch".
cmake_minimum_required(VERSION 3.2)
project (StaticFoundation)
message(STATUS "${PROJECT_NAME} - Starting Configuration.")

message(STATUS "${CMAKE_MODULE_PATH} -asf")

####################################################################################################
message(STATUS "Creating helper variables and functions")

#######################################
message(STATUS "\tRoot Folders")

set(${PROJECT_NAME}RootDir ${${PROJECT_NAME}_SOURCE_DIR}/)
message(STATUS "\t\tUsing Sources From: ${${PROJECT_NAME}RootDir}")

set(${PROJECT_NAME}BinaryDir ${${PROJECT_NAME}_BINARY_DIR}/)
message(STATUS "\t\tPutting all major output in: ${${PROJECT_NAME}BinaryDir}")

#######################################
message(STATUS "\tDerived Output folders")

set(${PROJECT_NAME}GeneratedHeadersDir ${${PROJECT_NAME}BinaryDir}config/)
message(STATUS "\t\tPutting Generated Headers in: ${${PROJECT_NAME}GeneratedHeadersDir}")

set(${PROJECT_NAME}GeneratedSourceFolder ${${PROJECT_NAME}BinaryDir}generated_source/)
message(STATUS "\t\tPutting Generated Source files: ${${PROJECT_NAME}GeneratedSourceFolder}")

#######################################
message(STATUS "\tDerived Input folders")

set(${PROJECT_NAME}DoxDir ${${PROJECT_NAME}RootDir}dox/)
message(STATUS "\t\tUsing supplementary doxygen header files from: ${${PROJECT_NAME}DoxDir}")

set(${PROJECT_NAME}IncludeDir ${${PROJECT_NAME}RootDir}include/)
message(STATUS "\t\tUsing Header files from: ${${PROJECT_NAME}IncludeDir}")

set(${PROJECT_NAME}LibDir ${${PROJECT_NAME}RootDir}lib/)
message(STATUS "\t\tUsing source libraries from: ${${PROJECT_NAME}LibDir}")

set(${PROJECT_NAME}SourceDir ${${PROJECT_NAME}RootDir}src/)
message(STATUS "\t\tUsing Source files from: ${${PROJECT_NAME}SourceDir}")

set(${PROJECT_NAME}SwigDir ${${PROJECT_NAME}RootDir}swig/)
message(STATUS "\t\tUsing supplementary Swig Header files from: ${${PROJECT_NAME}SwigDir}")

set(${PROJECT_NAME}TestDir ${${PROJECT_NAME}RootDir}test/)
message(STATUS "\t\tUsing Test files from: ${${PROJECT_NAME}TestDir}")


####################################################################################################
message(STATUS "Determining Source Files.")

set(HeaderFiles
    "${${PROJECT_NAME}IncludeDir}crossplatformexport.h"
    "${${PROJECT_NAME}IncludeDir}datatypes.h"
    "${${PROJECT_NAME}IncludeDir}staticfoundation.h"
    "${${PROJECT_NAME}IncludeDir}supresswarnings.h"
)

set(SourceFiles
)

set(TestSourceFiles
    "${${PROJECT_NAME}TestDir}tests.h"
    "${${PROJECT_NAME}TestDir}tests.cpp"
)

set(SwigFiles
    "${${PROJECT_NAME}SwigDir}swigconfig.h"
)

####################################################################################################
message(STATUS "Determining platform specific details.")

#######################################
message(STATUS "\tDetecting OS")

set(SystemIsLinux OFF)
set(SystemIsWindows OFF)
set(SystemIsMacOSX OFF)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    message(STATUS "\t\tDetected OS as 'Linux'.")
    set(SystemIsLinux ON)
endif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    message(STATUS "\t\tDetected OS as 'Windows'.")
    set(SystemIsWindows ON)
endif(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")

if(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    message(STATUS "\t\tDetected OS as 'Mac OS X'.")
    set(SystemIsMacOSX ON)
endif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")

message(STATUS "\t\tLinux: ${SystemIsLinux}")
message(STATUS "\t\tWindows: ${SystemIsWindows}")
message(STATUS "\t\tMacOSX: ${SystemIsMacOSX}")

if(SystemIsLinux)
    message(STATUS "\tSetting specific variables for 'Linux'.")
    set(CatCommand "cat")
    set(PlatformDefinition "LINUX")
endif(SystemIsLinux)

if(SystemIsWindows)
    message(STATUS "\tSetting specific variables for 'Windows'.")
    set(CatCommand "type")
    set(PlatformDefinition "WINDOWS")
endif(SystemIsWindows)

if(SystemIsMacOSX)
    message(STATUS "\tSetting specific variables for 'Mac OS X'.")
    set(CatCommand "cat")
    set(PlatformDefinition "MACOSX")
endif(SystemIsMacOSX)

####################################################################################################
message(STATUS "Determining Jagati Package Manager Details.")

#set(MezzPackageDir $ENV{MEZZ_PACKAGE_DIR})
#if(MezzPackageDir)
#    set(ENV{HUNTER_ROOT} ${MezzPackageDir})
#else(MezzPackageDir)
#    set(MezzPackageDir $ENV{HUNTER_ROOT})
#endif(MezzPackageDir)

#if(MezzPackageDir)
#    message(STATUS "Using Mezzanine Packages from ${MezzPackageDir}")
#else(MezzPackageDir)
#    message(ERROR "\tCould not determine directory to look for or save Mezzanine Packages. \
#            Set Environment Variable 'MezzPackageDir' to directory to place files or select \
#            location from CMake-gui.")
#endif(MezzPackageDir)

####################################################################################################
# Detect Compiler

set(CompilerIsGCC OFF)
set(CompilerIsClang OFF)
set(CompilerIsIntel OFF)
set(CompilerIsMsvc OFF)

set(CompilerDesignNix OFF)
set(CompilerDesignMS OFF)

if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    message(STATUS "\tDetected compiler as 'GCC'.")
    set(CompilerIsGCC ON)
    set(CompilerDesignNix ON)
endif(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")

if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    message(STATUS "\tDetected compiler as 'Clang'.")
    set(CompilerIsClang ON)
    set(CompilerDesignNix ON)
endif(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")

if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Intel")
    message(STATUS "\tDetected compiler as 'Intel'.")
    set(CompilerIsIntel ON)
    set(CompilerDesignNix ON)
endif(${CMAKE_CXX_COMPILER_ID} STREQUAL "Intel")

if(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    message(STATUS "\tDetected compiler as 'MSVC'.")
    set(CompilerIsMsvc ON)
    set(CompilerDesignMS ON)
endif(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")


###############################################################################
# Set up compiler flags

if(CompilerDesignNix)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
    -std=c++11 -fno-strict-aliasing -pthread -m64 -fPIC\
    -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization \
    -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept \
    -Wold-style-cast -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo \
    -Wstrict-null-sentinel -Wstrict-overflow=2 -Wundef -Wno-unused -Wparentheses")

    # Removed -Winline it did not seem useful
    # He are some flags suggested for use an why they were not used:
    # -Werror - this is used to force others to resolve errors, when they wouldn't normally, I am
    #         - resolving them as I go, but I want to option to run unit tests with warnings in
    #           place.
    # -Woverloaded-virtual - What did the author of this think virtual methods were for if not to be
    #                      - overloaded. This disagrees with explicit design decisions.
    # -Wmisleading-indentation - Help find errors revolving around tabs and control flow.
    # -DDEBUG_DIRECTOR_EXCEPTION  # Used to make swig emit more
    message(STATUS "\tC++ compiler and linker flags: ${CMAKE_CXX_FLAGS}")
else(CompilerDesignNix)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /nologo /Wall /WX /MT \
        /wd4710 /wd4514 /wd4251 /wd4820"
    )

    # Used:
    # /nologo - Skips a few lines of microsoft branding.
    # /Wall - Enable all warnings.
    # /WX - treat warnings as errors.
    # /MT - Statically link against the threading capable standard library.

    # Ignoring:
    # C4710 - Failing to inline things in std::string, well that is STL's fault, not mine.
    # C4514 - An unused function was optimized out. Why is the optimizer doing its job a warning?!
    # C4251 - Is safe to ignore per STL
# http://stackoverflow.com/questions/24511376/how-to-dllexport-a-class-derived-from-stdruntime-error
    # C4820 - When padding is added for performance reasons.
endif(CompilerDesignNix)
message(STATUS "\tC++ compiler and linker flags: ${CMAKE_CXX_FLAGS}")

include_directories(
    ${${PROJECT_NAME}IncludeDir}
    ${${PROJECT_NAME}GeneratedHeadersDir}
)

###############################################################################
# Set up Build targets

add_executable(${PROJECT_NAME}_Tester ${HeaderFiles} ${TestSourceFiles})

# A Project to do nothing but get All the Source files visible in IDEs
add_custom_target(
    ${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}_Tester
    SOURCES ${HeaderFiles}
            ${SourceFiles}
            ${TestSourceFiles}
            ${SwigFiles}
)

message ("${PROJECT_NAME} - Ending Configuration.")
