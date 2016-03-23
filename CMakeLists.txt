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
cmake_minimum_required(VERSION 2.8)
project(StaticFoundation)
message(STATUS "${PROJECT_NAME} - Starting Configuration.")

##########################################################################|#########################
set(JagatiChecksum "10b36fe75fd14bc6505c2baa8e24edc0f8fc1c38b14720ee0ab3ba\
cc8523f15c9a13820d1d1c267fac9156a512300ae0840ad816cb34613f32b761b7684183d7")
file(DOWNLOAD
    "https://raw.githubusercontent.com/BlackToppStudios/Jagati/master/Jagati.cmake"
    "${${PROJECT_NAME}_BINARY_DIR}/Jagati.cmake"
    EXPECTED_HASH SHA512=${JagatiChecksum}
)
include("${${PROJECT_NAME}_BINARY_DIR}/Jagati.cmake")

StandardJagatiSetup()

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

AddJagatiConfig("MEZZ_CompilerIsGCC" "" ${CompilerIsGCC})
AddJagatiConfig("MEZZ_CompilerIsClang" "" ${CompilerIsClang})
AddJagatiConfig("MEZZ_CompilerIsIntel" "" ${CompilerIsIntel})
AddJagatiConfig("MEZZ_CompilerIsMsvc" "" ${CompilerIsMsvc})

AddJagatiConfig("MEZZ_CompilerDesignNix" "" ${CompilerDesignNix})
AddJagatiConfig("MEZZ_CompilerDesignMS" "" ${CompilerDesignMS})

ChooseLibraryType(${MEZZ_BuildStaticLibraries})
EmitConfig()

####################################################################################################
# Set up Doxygen Targets
if(MEZZ_BuildDoxygen)
    find_program(MEZZ_DoxygenExecutable "doxygen")
    if(MEZZ_DoxygenExecutable)
        set(DoxygenConfigDir "${StaticFoundationDoxDir}doxyfiles/")
        set(DoxygenResultsDir "${StaticFoundationBinaryDir}Doxygen/")

        set(WarningsFile "${DoxygenResultsDir}html/DoxygenWarnings.txt")

        configure_file(${DoxygenConfigDir}Doxyfile ${StaticFoundationBinaryDir})

        if(EXISTS ${WarningsFile})
        else(EXISTS ${WarningsFile})
            file(MAKE_DIRECTORY ${DoxygenResultsDir})
            file(WRITE ${WarningsFile} "")
        endif(EXISTS ${WarningsFile})

        # create output folder
        # Touch this file ${DoxygenResultsDir}html/DoxygenWarnings.txt


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
            .travis.yml
)

message(STATUS "${PROJECT_NAME} - Ending Configuration.")
