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
#ifndef Mezz_StaticFoundation_staticstring_h
#define Mezz_StaticFoundation_staticstring_h

/// @file
/// @brief Provide a simple compile time way to concatenate and manipulate strings.

#include "DataTypes.h"
#include "SuppressWarnings.h"

namespace Mezzanine
{
    /// @brief A class for simple manipulation of strings at compile time.
    /// @details if used with constexpr values everything this class does can be evaluated at compile time, except those
    /// methods marked with warnings and labeled otherwise.
    /// @tparam ByteCount The size of string in question.
    template <DataSize ByteCount>
    class StaticString
    {
    public:
        /// @brief the type used for sizes in this class
        typedef DataSize size_t;

    private:
        /// @brief The data in the string, except its null terminator
        std::array<Char8, ByteCount> StringData;

    public:

        /// @brief Initializing Constructor
        /// @param OtherString an std::array of chars, which can implicitly be constructed from a string literal.
        constexpr StaticString(const std::array<Char8, ByteCount>& OtherString)
            : StringData(OtherString)
            { }

        /// @brief How big is the contained string, including the null terminator
        /// @return A DataSize with this size of the important data+1, so 'foo'.size() would be 4.
        constexpr DataSize size() const
            { return ByteCount; }

        /// @brief Indexing operator, get a Char8 from a specific place
        /// @param Index indicates the char to get, does compile times bounds checking.
        /// @return If with the bounds of the string get the requested Char8, otherwise get a null terminator.
        constexpr Char8 operator[](DataSize Index) const
            { return (Index < ByteCount-1 ? StringData[Index] : '\0'); }

    private:

        /// @brief Compare equality of two strings recursively
        /// @tparam OtherByteCount The size of the other character array, because it is part of the type.
        /// @param OtherString The char array to compare this too.
        /// @param Index The first/current index to compare. Default to 0 so the calls itself with the index +1.
        /// @return True if they match and false if they don't.
        /// @warning This does no length checking on the other string so check the length before calling this.
        template <DataSize OtherByteCount>
        constexpr bool CompareEqualityContents(const Char8(&OtherString)[OtherByteCount], DataSize Index = 0) const
        {
            return  operator[](Index) == OtherString[Index] &&
                    ( ByteCount>Index || CompareEqualityContents(OtherString, Index+1) );
        }

        /// @brief Compare equality of two StaticString instances recursively
        /// @tparam OtherByteCount The size of the other StaticString, because it is part of the type.
        /// @param OtherString The StaticString to compare this too.
        /// @param Index The first/current index to compare. Default to 0 so the calls itself with the index +1.
        /// @return True if they match and false if they don't.
        /// @warning This does no length checking on the other string so check the length before calling this.
        template <DataSize OtherByteCount>
        constexpr bool CompareEqualityContents(const StaticString<OtherByteCount>& OtherString,
                                               DataSize Index = 0) const
        {
            return  operator[](Index) == OtherString[Index] &&
                    ( ByteCount>Index || CompareEqualityContents(OtherString, Index+1) );
        }

    public:

        SAVE_WARNING_STATE
        SUPPRESS_VC_WARNING(4100) // Incorrect warning OtherString is referenced and msvc missed that somehow.

        /// @brief Compare equality of two strings.
        /// @tparam OtherByteCount The size of the other character array, because it is part of the type.
        /// @param OtherString The char array to compare this too.
        /// @return True if they match and false if they don't.
        /// @note This does not stop at internal null terminators so beware of strings that attempt to internally
        /// terminate prematurely.
        template <DataSize OtherByteCount>
        constexpr bool operator==(const Char8(&OtherString)[OtherByteCount]) const
        {
            return  ByteCount == OtherByteCount &&
                    ( 0==ByteCount || CompareEqualityContents(OtherString) );
        }

        /// @brief Compare equality of two StaticString instances.
        /// @tparam OtherByteCount The size of the other StaticString instance, because it is part of the type.
        /// @param OtherString The StaticString instance to compare this too.
        /// @return True if they match and false if they don't.
        /// @note This does not stop at internal null terminators so beware of strings that attempt to internally
        /// terminate prematurely.
        template <DataSize OtherByteCount>
        constexpr bool operator==(const StaticString<OtherByteCount>& OtherString) const
        {
            return  ByteCount == OtherByteCount &&
                    ( 0==ByteCount || CompareEqualityContents(OtherString) );
        }

        RESTORE_WARNING_STATE

        /// @brief Check two string for inequality.
        /// @tparam OtherByteCount The size of the other character array, because it is part of the type.
        /// @param OtherString The char array to compare this too.
        /// @return True if they are different and false if they match.
        /// @note This does not stop at internal null terminators so beware of strings that attempt to internally
        /// terminate prematurely.
        template <DataSize OtherByteCount>
        constexpr bool operator!=(const Char8(&OtherString)[OtherByteCount]) const
            { return !( *this==OtherString ); }
        /// @brief Check two StatocString instances for inequality.
        /// @tparam OtherByteCount The size of the other StatocString instance, because it is part of the type.
        /// @param OtherString The StatocString instance to compare this too.
        /// @return True if they are different and false if they match.
        /// @note This does not stop at internal null terminators so beware of strings that attempt to internally
        /// terminate prematurely.
        template <DataSize OtherByteCount>
        constexpr bool operator!=(const StaticString<OtherByteCount>& OtherString) const
            { return !( *this==OtherString ); }

        /// @brief Get the raw data backing this string in its native form
        /// @return A std::array of Char8.
        constexpr const std::array<Char8, ByteCount>& GetData() const
            { return StringData; }

        /// @brief Convert this to a const char* for runtime use.
        /// @return A c-string with this the same contents as this.
        /// @warning This method executes at run time.
        const Char8* c_str() const
            { return StringData.data(); }
        /// @brief Convert this to a Mezzanine::String for runtime use
        /// @return A string with this the same contents as this.
        /// @warning This method executes at run time.
        String str() const
            { return std::string(StringData.data()); }
    }; //StaticString

    /// @brief Check for equality of strings when the character array is on the left.
    /// @tparam CharSize The size of the char array
    /// @tparam StringSize The size of the StaticString
    /// @param Left the character array
    /// @param Right the Static string
    /// @return True if they match and false if they differ
    template <DataSize CharSize, DataSize StringSize>
    constexpr bool operator==(const Char8(&Left)[CharSize], const StaticString<StringSize>& Right)
        { return Right == Left; }

    /// @brief Check for inequality of strings when the character array is on the left.
    /// @tparam CharSize The size of the char array
    /// @tparam StringSize The size of the StaticString
    /// @param Left the character array
    /// @param Right the Static string
    /// @return True if they match and false if they differ
    template <DataSize CharSize, DataSize StringSize>
    constexpr bool operator!=(const Char8(&Left)[CharSize], const StaticString<StringSize>& Right)
        { return Right != Left; }

    /// @brief A macro to simplify some of the boilerplate required by the type system.
    #define MakeStaticString(StringLiteral) Mezzanine::StaticString<sizeof(StringLiteral)>\
                                            { std::array<Mezzanine::Char8,sizeof(StringLiteral)> {StringLiteral} }

    /// @brief A namespace for implementation details
    namespace internal
    {
        namespace
        {
            // A series of templates that create the space needed for concatenating two string literals.
            // Used with permissions from Stack Overflow Per Creative Commons Attribution license:
            // http://stackoverflow.com/questions/13292237/c-concat-two-const-char-string-literals

            template <DataSize...>
            struct IndiceSequence { };

            // A type recursively define in terms of itself to get one item off a parameter pack.
            template <DataSize OneId, DataSize... Pack>
            struct GenerateIndiceSequence : GenerateIndiceSequence<OneId-1, OneId-1, Pack...> { };

            // 0 case to end recursion actually has a type so other templates are ignore because SFINAE, I think?!
            template <DataSize... Pack>
            struct GenerateIndiceSequence<0, Pack...>
            {
                typedef IndiceSequence<Pack...> type;
            };

            template <DataSize LeftSize, DataSize... LeftIndice,
                      DataSize RightSize, DataSize... RightIndice>
            constexpr StaticString<LeftSize+RightSize-1> ConcatenateCharArrayImpl(
                const std::array<Char8, LeftSize>& LeftString, internal::IndiceSequence<LeftIndice...>,
                const std::array<Char8, RightSize>& RightString, internal::IndiceSequence<RightIndice...>)
            {
                return StaticString<LeftSize+RightSize-1> // 1 less because there is only 1 null terminator
                    { std::array<Char8, LeftSize+RightSize-1>{{ LeftString[LeftIndice]...,
                                                                RightString[RightIndice]...,
                                                                '\0' }} };
            }
        }
    }//Internal

    /// @brief Concatenate two StaticString instances
    /// @tparam LeftSize The size of the left hand string
    /// @tparam RightSize The size of the right hand string
    /// @param LeftString The StaticString on the Left of the +.
    /// @param RightString The StaticString on the Right of the +.
    /// @return A new StaticString with the data of both strings and a null terminator at the end.
    template <DataSize LeftSize, DataSize RightSize>
    constexpr StaticString<LeftSize+RightSize-1> operator+(const StaticString<LeftSize>& LeftString,
                                                           const StaticString<RightSize>& RightString)
    {
        typedef typename internal::GenerateIndiceSequence<LeftSize-1>::type LeftIndices;
        typedef typename internal::GenerateIndiceSequence<RightSize-1>::type RightIndices;
        return internal::ConcatenateCharArrayImpl(LeftString.GetData(), LeftIndices(),
                                                  RightString.GetData(), RightIndices());
    }
}//Mezzanine

#endif
