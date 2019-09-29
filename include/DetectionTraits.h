// © Copyright 2010 - 2019 BlackTopp Studios Inc.
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
#ifndef Mezz_StaticFoundation_DetectionTraits_h
#define Mezz_StaticFoundation_DetectionTraits_h

/// @file
/// @brief This file pulls experimental C++20 detection functionality into the main std namespace so they we
/// may use it in the Mezzanine without having to make edits when we do update to C++20. Except for MSVC,
/// which still lacks this basic functionality at the time of this writing. So we implement it ourselves. As
/// a bonus, this code will exclude itself (via ifdef) if we build with any C++ version older than C++17.

#if __cplusplus <= 201703L
#if defined(_MSC_VER) && !defined(__INTEL_COMPILER)
namespace std
{
    // "MSVC is a good compiler" they said.
    // "No reason to use any other" they said.
    // I fart in their general direction.
    struct nonesuch
    {
        nonesuch() = delete;
        ~nonesuch() = delete;
        nonesuch(nonesuch const&) = delete;
        void operator=(nonesuch const&) = delete;
    };

    namespace detail
    {
        template <class Default, class AlwaysVoid, template<class...> class Op, class... Args>
        struct detector
        {
            using value_t = std::false_type;
            using type = Default;
        };

        template <class Default, template<class...> class Op, class... Args>
        struct detector<Default, std::void_t<Op<Args...>>, Op, Args...>
        {
            // Note that std::void_t is a C++17 feature
            using value_t = std::true_type;
            using type = Op<Args...>;
        };
    } // namespace detail

    template <template<class...> class Op, class... Args>
    using is_detected = typename detail::detector<nonesuch, void, Op, Args...>::value_t;

    template <template<class...> class Op, class... Args>
    using detected_t = typename detail::detector<nonesuch, void, Op, Args...>::type;

    template <class Default, template<class...> class Op, class... Args>
    using detected_or = detail::detector<Default, void, Op, Args...>;
}
#else // defined(_MSC_VER) && !defined(__INTEL_COMPILER)
#ifndef SWIG
    #include <experimental/type_traits>
#endif
namespace std
{
    /// @brief Alias is_detected in the std namespace on systems where it is experimental.
    template<template<typename...> class Op, typename... Args>
    using is_detected = std::experimental::is_detected<Op,Args...>;

    /// @brief Alias is_detected_v in the std namespace on systems where it is experimental.
    template<template<typename...> class Op, typename... Args>
    constexpr bool is_detected_v = std::experimental::is_detected_v<Op,Args...>;
}
#endif // defined(_MSC_VER) && !defined(__INTEL_COMPILER)
#endif // __cplusplus <= 201703L

#endif
