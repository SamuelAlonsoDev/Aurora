#pragma once
#include <Core/Types.hpp>

namespace Aurora
{
    namespace Concepts
    {
        template<class T> class IsIntegerClass
        {
        public:
            constexpr static bool Value = false;
        };

        template<> class IsIntegerClass<bool>
        {
        public:
            constexpr static bool Value = true;
        };

        template<> class IsIntegerClass<u8>
        {
        public:
            constexpr static bool Value = true;
        };

        template<> class IsIntegerClass<s8>
        {
        public:
            constexpr static bool Value = true;
        };

        template<> class IsIntegerClass<u16>
        {
        public:
            constexpr static bool Value = true;
        };

        template<> class IsIntegerClass<s16>
        {
        public:
            constexpr static bool Value = true;
        };

        template<> class IsIntegerClass<u32>
        {
        public:
            constexpr static bool Value = true;
        };

        template<> class IsIntegerClass<s32>
        {
        public:
            constexpr static bool Value = true;
        };

        template<> class IsIntegerClass<u64>
        {
        public:
            constexpr static bool Value = true;
        };

        template<> class IsIntegerClass<s64>
        {
        public:
            constexpr static bool Value = true;
        };

        template<class T> concept IsInteger = IsIntegerClass<T>::Value;
    }
}