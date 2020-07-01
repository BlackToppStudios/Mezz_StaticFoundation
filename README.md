# README #

The Mezzanine is a set of multi platform C++ libraries designed to help create high performance
videos games. The Mezzanine is focused on games requiring 3d physics, 3d graphics, 3d sounds and
common facilities that such games need. This is just one component of many.

## About this Library ##

This library, the StaticFoundation, is responsible for detecting compilation options, compiler settings, doing work at
compile time (like string manipulation) and handling other platform specific details.

It does this by a mix a of use of preprocessor macros, constexpr C++11/14 and configuration time/CMake scripting
techniques.

## Build Status ##

The current Travis CI (Apple - GCC/Clang) build status is:
[![Build Status](https://travis-ci.org/BlackToppStudios/Mezz_StaticFoundation.svg?branch=master)](https://travis-ci.org/BlackToppStudios/Mezz_StaticFoundation)

The current Appveyor (Windows - MinGW/Msvc) build status is:
[![Build Status](https://ci.appveyor.com/api/projects/status/github/BlackToppStudios/Mezz_StaticFoundation?branch=master&svg=true)](https://ci.appveyor.com/project/Sqeaky/mezz-staticfoundation)

The current code coverage for tests is:
[![codecov](https://codecov.io/gh/BlackToppStudios/Mezz_StaticFoundation/branch/master/graph/badge.svg)](https://codecov.io/gh/BlackToppStudios/Mezz_StaticFoundation)

The current Jenkins, which covers Linux (Emscripten, Rasberry Pi, Ubuntu and Fedora), old Mac OS X (High Sierra) and old windows (7 64 bit msvc and mingw), build status is available on the [BTS Jenkins Instance](http://blacktopp.ddns.net:8080/blue/organizations/jenkins/Mezz_StaticFoundation/activity). The current status is: [![Build Status](http://blacktopp.ddns.net:8080/job/Mezz_StaticFoundation/job/master/badge/icon)](http://blacktopp.ddns.net:8080/blue/organizations/jenkins/Mezz_StaticFoundation/activity)

## How to Build ##

This project is one part of a larger set of libraries and this uses CMake and the Jagati to handle much of that
automatically. This builds like any other CMake style project.

You will need:

 * A modern version of some OS Linux, Windows, or Max OS X (We test on all three),
 * A halfway modern C++ compiler - GCC, Clang, AppleClang, MSVC, MinGW (We test all of these and more),
 * [CMake](https://cmake.org/download/) (`apt install cmake cmake-gui` on Ubuntu Linux),
 * [Git](https://git-scm.com/downloads) (`apt install git` on Ubuntu Linux),
 * Some build system like Make or [Ninja](https://ninja-build.org/) (`apt install ninja-build` on Ubuntu Linux),
 * Optionally [Doxygen](https://www.doxygen.nl/download.html) (`apt install doxygen` on Ubuntu Linux) if you want our officials docs,
 * A working internet Connection.

Building on any platform with a command line works something like this:

    # Clone the code
    $ git clone git@github.com:BlackToppStudios/Mezz_StaticFoundation.git

    # Navigate to source directory and create a build directory
    $ cd Mezz_StaticFoundation
    $ mkdir Build
    $ cd Build

    # Create build scripts for your build, with a line like ONE of these.
    # We use ninja, but select your build system with `-G`, see our Jenkinsfile for examples.
    # All of the `-D` can be set in a way that makes sense to you, we tried to pick sensible defaults.
    $ cmake ..
    $ cmake -G"Ninja" .. -DCMAKE_BUILD_TYPE=DEBUG -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=ON
    $ cmake -G"Visual Studio 16 2019" .. -DCMAKE_BUILD_TYPE=RELEASE -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF

    # Actually build the software, use only one of these and this will build
    $ cmake --build .   # Use CMake to do it.
    $ make -j4          # You used makefile in the previous stepm `-j` indicates the number of build processes
    $ ninja             # You know and understand ninja, and you used it in the previous step
    > ; Do nothing on the cmd line, if you uses MSVC in the previous open visual studion, and click build.

Here are some of the options you can pass to CMake to configure the behaviour of the build.

Cmake provides this by default:

* CMAKE_BUILD_TYPE can be "DEBUG" to enable debugging or "RELEASE" to build optimized programs,

Our tools provide this:

* MEZZ_ForceGcc32Bit - If you are using a 64 OS, CPU, and compiler this can force a 32 bit build,
* MEZZ_BuildStaticLibraries - Static bakes everything into one executable, when disabled this makes DLLs and SOs.
* MEZZ_CodeCoverage - GCC style compilers can easily instrument the output executable, this enables that.
* MEZZ_BuildDoxygen - If you have doxygen installed this will create our official docs but only for our packages.
