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
#ifndef Mezz_StaticFoundation_DataTypes_h
#define Mezz_StaticFoundation_DataTypes_h

///////////////////////////////////////////////////////////////////////////////
// Any Special data types that we need will get declared right here
/// @file
/// @brief All the definitions for datatypes as well as some basic conversion functions are defined here. Additionally,
/// this is where all of the other standard header inclusions go as well.
///////////////////////////////////////

// Standard Headers are not included in SWIG preprocessing. Most std includes are centralized here to make modifying
// this list as simple as possible. Other standard includes that are not included here are in places that they are
// required and conditionally may not be compiled in.

#ifndef SWIG
    #include "CrossPlatformExport.h"
    #include "SuppressWarnings.h"

    SAVE_WARNING_STATE
    SUPPRESS_VC_WARNING(4061)
    // 4548 was added to suppress a warning in MSVC's implementation of malloc.h where
    // they use a comma in an assert.
    SUPPRESS_VC_WARNING(4548)
    // 4582 and 4583 was added to suppress a warning in MSVC's implementation of optional where
    // constructors and destructors were not implicitly called.
    SUPPRESS_VC_WARNING(4582)
    SUPPRESS_VC_WARNING(4583)

    // C-Library Utilities
    #include <stdint.h>
    #include <cstddef>
    #include <cstdlib>
    #include <cassert>
    // Containers
    #include <array>
    #include <initializer_list>
    #include <list>
    #include <map>
    #include <set>
    #include <vector>
    // Strings
    #include <string>
    #include <string_view>
    // Threading
    #include <atomic>
    #include <condition_variable>
    // Streams
    #include <fstream>
    #include <istream>
    #include <ostream>
    #include <sstream>
    // Whatever Else
    #include <algorithm>
    #include <chrono>
    #include <exception>
    #include <functional>
    //#include <filesystem> // When will this work?!
    #include <initializer_list>
    #include <memory>
    #include <new>
    #include <optional>
    #include <type_traits>
    #include <typeindex>
    #include <utility>

    RESTORE_WARNING_STATE
#endif

namespace Mezzanine
{
    ///////////////////////////////////////////////////////////////////////////////
    // Pointer math
    ///////////////////////////////////////

    /// @brief A type that any pointer can be converted to and back from.
    /// @details This ensures after the conversion back it will be identical.
    typedef intptr_t ConvertiblePointer;

    /// @brief A number large enough to hold every integer from 0 to the amount of bytes of addressable space.
    /// @details This is intended to be of use when using buffer/size pairs or otherwise keeping track of data
    /// like that.
    typedef uintptr_t DataSize;

    ///////////////////////////////////////////////////////////////////////////////
    // Efficient and at least this size.
    ///////////////////////////////////////

    /// @brief An 8-bit integer.
    typedef int8_t Int8;
    /// @brief An 8-bit unsigned integer.
    typedef uint8_t UInt8;
    /// @brief A 16-bit integer.
    typedef int16_t Int16;
    /// @brief A 16-bit unsigned integer.
    typedef uint16_t UInt16;
    /// @brief A 32-bit integer.
    typedef int32_t Int32;
    /// @brief A 32-bit unsigned integer.
    typedef uint32_t UInt32;
    /// @brief A 64-bit integer.
    typedef int64_t Int64;
    /// @brief A 64-bit unsigned integer.
    typedef uint64_t UInt64;

    ///////////////////////////////////////////////////////////////////////////////
    // General Purpose
    ///////////////////////////////////////

    /// @brief A Datatype used to represent a common real floating point number of average precision.
    /// @details This Datatype is currently a typedef to a float, This is to match our compilations of Ogre (rendering
    /// subsystem ogre::Real), and Bullet (physics subsystem, btScalar). With a recompilation of all the subsystems and
    /// this there is no theoretical reason why this could not be changed to a double, or even something more extreme
    /// like a GMP datatype. Most likely this switch would require at least some troubleshooting.
    /// @n @n
    /// This type will be word aligned and the fastest type for GPU math and the fastest type for floating point CPU
    /// math.
    typedef float Real;
    /// @brief This is real number that is at least as precise as the Real and could be considerably more-so.
    /// @details Perhaps doubly precise.
    /// @n @n
    /// This type might be poorly aligned and slower on GPUs than the Real.
    typedef double PreciseReal;

    /// @brief Whole is an unsigned integer, it will be at least 32bits in size and suitable for common counting tasks.
    /// @details This is a typedef to unsigned Long. but could be smaller in some situations. In general it will be the
    /// most efficient unsigned type for CPU bound math.
    typedef unsigned long Whole;
    /// @brief A datatype used to represent any integer in an efficient way for general purposes.
    /// @details This is a typedef to int, but could int16 or smaller to improve performance in some situations, in
    /// general it will be the most efficient signed type for CPU Bound math.
    typedef int Integer;
    /// @brief A large integer type suitable for compile time math and long term microsecond time keeping.
    /// @details For reference when this is a 64 bit integer, it can store a number between 9,223,372,036,854,775,808
    /// and 9,223,372,036,854,775,807. That many seconds is approximately 292,277,000,000 years and the universe is
    /// only 14,600,000,000 years old. So this is good for any time between 20x the age of the universe before and
    /// after the beginning of any chosen epoch. Even if used to track nanoseconds it should be good for 292 years.
    typedef intmax_t MaxInt;
    /// @brief An unsigned integral type suitable for storing the sizes and alignments of types.
    /// @details On 64-bit systems this will often be larger than a Whole. For (potentially) very large arrays
    /// this type will be more suitable for massive index values and loops. This is the type returned by many
    /// standard functions, including the return for container sizes such as vector and string.
    typedef size_t SizeType;

    /// @brief A type used to express a run-time series of characters.
    /// @remarks This is a typedef to std::string, but could change particularly if UTF16 or UTF32 support is
    /// desired.  If this is changed, The Character typedef should be adjusted accordingly.
    typedef std::string String;
    /// @brief A type used to express a compile-time range of characters.
    /// @remarks This is a typedef to std::string_view, but could change particularly if UTF16 or UTF32 support
    /// is desired.  If this is changed, The Character typedef should be adjusted accordingly.
    typedef std::string_view StringView;

    // @brief Some compatible with std::filesystem::path to work with filesystem paths.
    //using Path = std::filesystem::path;

    /// @brief A datatype to represent one character.
    /// @details The character type of String
    typedef char Char8;

    /// @brief Generally acts a single bit, true or false
    /// @details Normally just a bool, but on some platform alignment matters more than size for performance, so this
    /// could be as large as one CPU word in size or as small as a single bit.
    typedef bool Boole;

    /// @brief The type that the system expects to be returned from main.
    typedef decltype(EXIT_SUCCESS) ExitCode;

    ///////////////////////////////////////////////////////////////////////////////
    // Complex standardized types.
    ///////////////////////////////////////

    /// @todo See which of these can be gotten rid of. These do not provide strong or particularly use guarantees or
    /// abstractions and cement suboptimal decisions at the basis or


    /// @brief A datatype used for streaming operations with Strings.
    /// @todo See if this can be removed entirely.
    typedef std::stringstream StringStream;

    /// @brief In case we ever replace the stringstream with another class, this will allow us to swap it out.
    /// @details This will always support <<, str() but may lose support for formatting functions like std::hex.
    /// @todo Replace with foundation location
    typedef std::stringstream Logger;

    /// @brief A datatype used to indicate a specific point in time, or a timestamp.
    /// @details This is made into its own datatype for when we want to tweak the possible size for a timestamp.
    typedef UInt32 OldTimeMarker;

    /// @brief A datatype for precision timing with std::chrono.
    /// @details This is a time point with the standard high resolution clock which can be used for frame timings.
    typedef std::chrono::time_point<std::chrono::high_resolution_clock> PrecisionTimeMarker;

    /// @brief A datatype for returning data and whether or not it is safe to use that data.
    /// @details This should replace any and all uses of the std::pair<bool,Datum> idiom.
    /// @tparam OptType Can be any allocatable class.
    template<class OptType>
    using Optional = std::optional<OptType>;

    ///////////////////////////////////////////////////////////////////////////////
    // Compound String types
    ///////////////////////////////////////

    /// @brief This is a pair for the generic storage of a value and its associated name.
    typedef std::pair< String, String > NameValuePair;
    /// @brief This is a datatype mostly used for describing settings or parameters that can't be declared in advance.
    /// @details This datatype uses the std::map container for its storage.
    typedef std::map< String, String > NameValuePairMap;

    /// @brief This is a simple datatype for a vector container of Strings.
    typedef std::vector< String > StringVector;
    /// @brief This is a simple datatype for a vector container of StringViews.
    typedef std::vector< StringView > StringViewVector;

    /// @brief This is a simple datatype for a set container of Strings.
    typedef std::set< String > StringSet;

}//Mezzanine

#endif
