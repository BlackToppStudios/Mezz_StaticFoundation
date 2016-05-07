# README #

The Mezzanine is a set of multi platform C++ libraries designed to help create high performance
videos games. The Mezzanine is focused on games requiring 3d physics, 3d graphics, 3d sounds and
common facilities that such games need. This is just one component of several.

## About this Library ##

The current Linux/Travis build status is: 
[![Build Status](https://travis-ci.org/BlackToppStudios/Mezz_StaticFoundation.svg?branch=master)](https://travis-ci.org/BlackToppStudios/Mezz_StaticFoundation)

The current Windows/Appveyor build status is:
[![Build Status](https://ci.appveyor.com/api/projects/status/github/BlackToppStudios/Mezz_StaticFoundation?branch=master&svg=true)](https://ci.appveyor.com/project/Sqeaky/mezz-staticfoundation)


This library, the StaticFoundation, is responsible for detecting compilation options, compiler
settings and other platform specific details.

It does this by a mix a of use of preprocessor macros and configuration time/CMake scripting
techniques.
