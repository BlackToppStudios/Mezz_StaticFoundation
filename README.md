# README #

The Mezzanine is a set of multi platform C++ libraries designed to help create high performance
videos games. The Mezzanine is focused on games requiring 3d physics, 3d graphics, 3d sounds and
common facilities that such games need. This is just one component of many.

## About this Library ##

The current Linux/Travis build status is: 
[![Build Status](https://travis-ci.org/BlackToppStudios/Mezz_StaticFoundation.svg?branch=master)](https://travis-ci.org/BlackToppStudios/Mezz_StaticFoundation)

The current Windows/Appveyor build status is:
[![Build Status](https://ci.appveyor.com/api/projects/status/github/BlackToppStudios/Mezz_StaticFoundation?branch=master&svg=true)](https://ci.appveyor.com/project/Sqeaky/mezz-staticfoundation)

The current code coverage for tests is:
[![codecov](https://codecov.io/gh/BlackToppStudios/Mezz_StaticFoundation/branch/master/graph/badge.svg)](https://codecov.io/gh/BlackToppStudios/Mezz_StaticFoundation)

This library, the StaticFoundation, is responsible for providing common data types as well as 
detecting compilation options, compiler settings and other platform specific details.

It does this by a mix a of use of preprocessor macros and configuration time/CMake scripting
techniques.
