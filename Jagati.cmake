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

# This will be the basic package manager for the Mezzanine, the Jagati. This will track and download
# packages from git repositories. This will handle centrally locating Mezzanine packages and provide
# tools for finding and linking against them appropriately.

# This will not be included directly in git repos, but rather a small download snippet with ensure
# this stays up to date.


# Basic Sanity Checks the Jagati enforces
if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(FATAL_ERROR "Prevented in source tree build. Please create a build directory outside of"
                        " the Mezzanine source code and have cmake build from there.")
endif("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")


####################################################################################################
# This is used to determine what the parentmost project is. Whichever project calls this first will
# be the only one that doesn't set all of it's variables in its parent's scope.

# Usage:
#   # Be certain to call project before calling this.
#   # Call this from the main project before calling anything else to insure your project is root.
#   ClaimParentProject()
#
# Result:
#   The following variables will all be set, made available and printed and other Jagati projects
#   will know to pollute your namespace:
#       ParentProject


macro(ClaimParentProject)
    if(ParentProject)
        # It is already set so we must be a child.
        message(STATUS
            "Project '${PROJECT_NAME}' acknowledges '${ParentProject}' as the Parent Project."
        )
    else(ParentProject)
        message(STATUS "Claiming '${PROJECT_NAME}' as the Parent Project.")
        set(ParentProject "${PROJECT_NAME}")
    endif(ParentProject)
endmacro(ClaimParentProject)

####################################################################################################
# This will create a number of variables in the Scope of the calling script that correspond to the
# name of the Project so that they can readily be referenced from other project including the caller
# as a a subproject.

# Usage:
#   # Be certain to call project before calling this.
#   CreateLocations()
#
# Result:
#   The following variables will all be set to some valid folder, made available and printed:
#       ${PROJECT_NAME}RootDir
#       ${PROJECT_NAME}BinaryDir
#
#       ${PROJECT_NAME}GeneratedHeadersDir
#       ${PROJECT_NAME}GeneratedSourceFolder
#
#       ${PROJECT_NAME}DoxDir
#       ${PROJECT_NAME}IncludeDir
#       ${PROJECT_NAME}LibDir
#       ${PROJECT_NAME}SourceDir
#       ${PROJECT_NAME}SwigDir
#       ${PROJECT_NAME}TestDir

macro(CreateLocations)
    message(STATUS "Creating Location Variables for '${PROJECT_NAME}'")
    set(PROJECT_NAME "${PROJECT_NAME}")

    if("${ParentProject}" STREQUAL "${PROJECT_NAME}")
        #######################################
        # Root
        set(${PROJECT_NAME}RootDir ${${PROJECT_NAME}_SOURCE_DIR}/)
        set(${PROJECT_NAME}BinaryDir ${${PROJECT_NAME}_BINARY_DIR}/)

        #######################################
        # Derived Output Folders
        set(${PROJECT_NAME}GeneratedHeadersDir ${${PROJECT_NAME}BinaryDir}config/)
        set(${PROJECT_NAME}GeneratedSourceFolder ${${PROJECT_NAME}BinaryDir}generated_source/)

        #######################################
        # Derived Input Folders
        set(${PROJECT_NAME}DoxDir ${${PROJECT_NAME}RootDir}dox/)
        set(${PROJECT_NAME}IncludeDir ${${PROJECT_NAME}RootDir}include/)
        set(${PROJECT_NAME}LibDir ${${PROJECT_NAME}RootDir}lib/)
        set(${PROJECT_NAME}SourceDir ${${PROJECT_NAME}RootDir}src/)
        set(${PROJECT_NAME}SwigDir ${${PROJECT_NAME}RootDir}swig/)
        set(${PROJECT_NAME}TestDir ${${PROJECT_NAME}RootDir}test/)
    else("${ParentProject}" STREQUAL "${PROJECT_NAME}")
        #######################################
        # Root as child
        set(${PROJECT_NAME}RootDir ${${ParentProject}_SOURCE_DIR}/ PARENT_SCOPE)
        set(${PROJECT_NAME}BinaryDir ${${ParentProject}_BINARY_DIR}/ PARENT_SCOPE)

        #######################################
        # Derived Output Folders  as child
        set(${PROJECT_NAME}GeneratedHeadersDir ${${PROJECT_NAME}BinaryDir}config/ PARENT_SCOPE)
        set(${PROJECT_NAME}GeneratedSourceFolder ${${PROJECT_NAME}BinaryDir}generated_source/
            PARENT_SCOPE)

        #######################################
        # Derived Input Folders  as child
        set(${PROJECT_NAME}DoxDir ${${PROJECT_NAME}RootDir}dox/ PARENT_SCOPE)
        set(${PROJECT_NAME}IncludeDir ${${PROJECT_NAME}RootDir}include/ PARENT_SCOPE)
        set(${PROJECT_NAME}LibDir ${${PROJECT_NAME}RootDir}lib/ PARENT_SCOPE)
        set(${PROJECT_NAME}SourceDir ${${PROJECT_NAME}RootDir}src/ PARENT_SCOPE)
        set(${PROJECT_NAME}SwigDir ${${PROJECT_NAME}RootDir}swig/ PARENT_SCOPE)
        set(${PROJECT_NAME}TestDir ${${PROJECT_NAME}RootDir}test/ PARENT_SCOPE)
    endif("${ParentProject}" STREQUAL "${PROJECT_NAME}")

    #######################################
    message(STATUS "\tVariables for '${PROJECT_NAME}'")

    #######################################
    message(STATUS "\tRoot Folders")

    message(STATUS "\t\tIn '${PROJECT_NAME}RootDir' Using Sources From: ${${PROJECT_NAME}RootDir}")
    message(STATUS "\t\tPutting all major output in: ${${PROJECT_NAME}BinaryDir}")

    #######################################
    message(STATUS "\tDerived Output folders")

    message(STATUS "\t\tPutting Generated Headers in: ${${PROJECT_NAME}GeneratedHeadersDir}")
    message(STATUS "\t\tPutting Generated Source files: ${${PROJECT_NAME}GeneratedSourceFolder}")

    #######################################
    message(STATUS "\tDerived Input folders")

    message(STATUS "\t\tUsing supplementary doxygen header files from: ${${PROJECT_NAME}DoxDir}")
    message(STATUS "\t\tUsing Header files from: ${${PROJECT_NAME}IncludeDir}")
    message(STATUS "\t\tUsing source libraries from: ${${PROJECT_NAME}LibDir}")
    message(STATUS "\t\tUsing Source files from: ${${PROJECT_NAME}SourceDir}")
    message(STATUS "\t\tUsing supplementary Swig Header files from: ${${PROJECT_NAME}SwigDir}")
    message(STATUS "\t\tUsing Test files from: ${${PROJECT_NAME}TestDir}")
endmacro(CreateLocations)

####################################################################################################
# Clearly CMake knows how to ID the OS without our help, but there are tricks to it and builtin
# tools are not as well identified as the could be. Hopefully this overcomes these minor shortfalls.

# Usage:
#   IdentifyOS()
#
# Result:
#   Details about OS are displayed and the following variables are set:
#
#       SystemIsLinux   - ON/OFF
#       SystemIsWindows - ON/OFF
#       SystemIsMacOSX  - ON/OFF
#
#       CatCommand - Some command that can print files when supplied a filename as only argument.
#       PlatformDefinition - LINUX/WINDOWS/MACOSX

macro(IdentifyOS)
    message(STATUS "\tDetecting OS:")

    set(SystemIsLinux OFF)
    set(SystemIsWindows OFF)
    set(SystemIsMacOSX OFF)

    if("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
        message(STATUS "\t\tDetected OS as 'Linux'.")
        set(SystemIsLinux ON)
    endif("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")

    if("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
        message(STATUS "\t\tDetected OS as 'Windows'.")
        set(SystemIsWindows ON)
    endif("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")

    if("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
        message(STATUS "\t\tDetected OS as 'Mac OS X'.")
        set(SystemIsMacOSX ON)
    endif("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")

    message(STATUS "\t\tLinux: ${SystemIsLinux}")
    message(STATUS "\t\tWindows: ${SystemIsWindows}")
    message(STATUS "\t\tMacOSX: ${SystemIsMacOSX}")

    if(SystemIsLinux)
        message(STATUS "\t\tSetting specific variables for 'Linux'.")
        set(CatCommand "cat")
        set(PlatformDefinition "LINUX")
    endif(SystemIsLinux)

    if(SystemIsWindows)
        message(STATUS "\t\tSetting specific variables for 'Windows'.")
        set(CatCommand "type")
        set(PlatformDefinition "WINDOWS")
    endif(SystemIsWindows)

    if(SystemIsMacOSX)
        message(STATUS "\t\tSetting specific variables for 'Mac OS X'.")
        set(CatCommand "cat")
        set(PlatformDefinition "MACOSX")
    endif(SystemIsMacOSX)
endmacro(IdentifyOS)

####################################################################################################
# Again, CMake knows how to detect the compiler. It does this in hyper precise detail. For purposes
# of the mezzanine there are really two categories of compiler: visual studio and good compilers.
# this can roughly identify those.

# Usage:
#   IdentifyOS()
#
# Result:
#   Details about compiler are displayed and the following variables are set:
#
#       CompilerIsGCC   - ON/OFF
#       CompilerIsClang - ON/OFF
#       CompilerIsIntel - ON/OFF
#       CompilerIsMsvc  - ON/OFF
#
#       CompilerDesignNix   - ON/OFF
#       CompilerDesignMS    - ON/OFF

macro(IdentifyCompiler)
    message(STATUS "\tDetecting Compiler:")

    set(CompilerIsGCC OFF)
    set(CompilerIsClang OFF)
    set(CompilerIsIntel OFF)
    set(CompilerIsMsvc OFF)

    set(CompilerDesignNix OFF)
    set(CompilerDesignMS OFF)

    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        message(STATUS "\t\tDetected compiler as 'GCC'.")
        set(CompilerIsGCC ON)
        set(CompilerDesignNix ON)
    endif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")

    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        message(STATUS "\t\tDetected compiler as 'Clang'.")
        set(CompilerIsClang ON)
        set(CompilerDesignNix ON)
    endif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")

    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
        message(STATUS "\t\tDetected compiler as 'Intel'.")
        set(CompilerIsIntel ON)
        set(CompilerDesignNix ON)
    endif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")

    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
        message(STATUS "\t\tDetected compiler as 'MSVC'.")
        set(CompilerIsMsvc ON)
        set(CompilerDesignMS ON)
    endif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")

    if(CompilerDesignNix)
        message(STATUS "\t\tPresuming *nix style compiler.")
    endif(CompilerDesignNix)

    if(CompilerDesignMS)
        message(STATUS "\t\tPresuming ms style compiler.")
    endif(CompilerDesignMS)
endmacro(IdentifyCompiler)

####################################################################################################
# This is one of those things that CMake is simultaneously great and terrible at. It provides like
# a trillion ways to do this and about a billion of them are wrong. Here is one way that seems to
# work most of the time when we do it:

#   Usage:
#       # Be sure the variable CompilerDesignNix is set to "ON" or "OFF"
#       SetCommonCompilerFlags()
#
#   Results:
#       Compiler flags are set that:
#           Enable a ton of warnings.
#           Treat warnings as errors are set.
#           Turn off compiler logos.
#           Enable Position independent code or otherwise fix linker issues.
#           Turn on C++11.

macro(SetCommonCompilerFlags)
    if(CompilerDesignNix)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
        -std=c++11 -fno-strict-aliasing -pthread -m64 -fPIC\
        -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy \
        -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations \
        -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Wredundant-decls -Wshadow \
        -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wundef \
        -Wno-unused -Wparentheses -Werror")

        # Removed -Winline it did not seem useful
        # He are some flags suggested for use an why they were not used:
        # -Werror - this is used to force others to resolve errors, when they wouldn't normally, I
        #           am resolving them as I go, but I want to option to run unit tests with warnings
        #           in place.
        # -Woverloaded-virtual - What did the author of this think virtual methods were for if not
        #                      - to be overloaded. This disagrees with explicit design decisions.
        # -Wmisleading-indentation - Help find errors revolving around tabs and control flow. I
        #                            want to enable this, but not until GCC 6.
        # -DDEBUG_DIRECTOR_EXCEPTION  # Used to make swig emit more
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
        # C4514 - An unused function was optimized out. Why is the optimizer doing its job a
        # warning?!
        # C4251 - Is safe to ignore per STL
# http://stackoverflow.com/questions/24511376/how-to-dllexport-a-class-derived-from-stdruntime-error
        # C4820 - When padding is added for performance reasons.
    endif(CompilerDesignNix)

    message(STATUS "\tC++ compiler and linker flags: ${CMAKE_CXX_FLAGS}")
endmacro(SetCommonCompilerFlags)


####################################################################################################
# This does what the above macros do, but this does it all together.

# Usage:
#   # Be certain to call project before calling this.
#   StandardJagatiSetup()
#
# Result:
#       Many variables for compiler, OS and locations will be set, see above.
#       Compiler Flags will be set.

macro(StandardJagatiSetup)
    ClaimParentProject()
    CreateLocations()
    message(STATUS "Determining platform specific details.")
    IdentifyOS()
    IdentifyCompiler()
    SetCommonCompilerFlags()
endmacro(StandardJagatiSetup)









####################################################################################################
# Basic Display Functionality

function(ShowList Header Tabbing ToPrint)
    message(STATUS "${Tabbing}${Header}")
    foreach(ListItem ${ToPrint})
        message(STATUS "${Tabbing}\t${ListItem}")
    endforeach(ListItem ${ToPrint})
endfunction(ShowList)




###############################################################################
# Direct Download Experiments.

# These should be usable instead of hunters



set(JagatiPackageNameArray)

macro(AddJagatiPackage)
    list(append JagatiPackageNameArray ${PROJECT_NAME})
endmacro(AddJagatiPackage)




####################################################################################################
#message(STATUS "Determining Jagati Package Manager Details.")

set(vara "zxcv")

#include(CMake/CMakeLists.txt) # PARENT_SCOPE causes this to blow up.
#add_subdirectory(CMake)
#include(ExternalProject)
#ExternalProject_Add (CmakeFolder SOURCE_DIR "Cmake/" DOWNLOAD_COMMAND ""
#                        BUILD_COMMAND "" UPDATE_COMMAND "" INSTALL_COMMAND "")

                                            # Include   | subdir    | extern
message(STATUS "var1: '${var1}'")           # set       | empty     | empty
message(STATUS "var2: '${var2}'")           # error     | set       | empty
message(STATUS "Name: '${PROJECT_NAME}'")   # overwrite | in file   | in file



#set(MezzPackageDir $ENV{MEZZ_PACKAGE_DIR})

#if(MezzPackageDir)
#    message(STATUS "Using Mezzanine Packages from ${MezzPackageDir}")
#else(MezzPackageDir)
#    message(ERROR "\tCould not determine directory to look for or save Mezzanine Packages. \
#            Set Environment Variable 'MezzPackageDir' to directory to place files or select \
#            location from CMake-gui.")
#endif(MezzPackageDir)


#set(ExpectedIndexHash "ffa5f2df93913e7d168021631a3564605b87dd2126afda779ba17\
#27ccf2be05e9c31882a42a731a7bb985cc1f265f98e5714ac4f791a3f8a0113fe6d86b1c476")

#file(DOWNLOAD
#    https://raw.githubusercontent.com/isocpp/CppCoreGuidelines/master/CONTRIBUTING.md
#    "${${PROJECT_NAME}BinaryDir}Guidelines.md"
#    EXPECTED_HASH SHA512=${ExpectedIndexHash}
#)

#include(ExternalProject)

#ExternalProject_Add(
#  ExternalProjectDownload
#  GIT_REPOSITORY git@github.com:isocpp/CppCoreGuidelines.git
#  GIT_TAG master
#  DOWNLOAD_COMMAND git clone git@github.com:isocpp/CppCoreGuidelines.git
#  UPDATE_COMMAND git pull
#  BUILD_COMMAND ""
#  TEST_COMMAND ""
#  INSTALL_COMMAND ""
#)
