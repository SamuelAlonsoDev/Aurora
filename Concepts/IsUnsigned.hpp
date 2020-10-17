#pragma once
#include <Core/Types.hpp>

namespace Aurora
{
    namespace Concepts
    {
        template<class T> class IsUnsignedClass
        {
        public:
            constexpr static bool Value = false;
        };

        template<> class IsUnsignedClass<u8>
        {
        public:
            constexpr static bool Value = true;
        };

        template<> class IsUnsignedClass<u16>
        {
        public:
            constexpr static bool Value = true;
        };

        template<> class IsUnsignedClass<u32>
        {
        public:
            constexpr static bool Value = true;
        };

        template<> class IsUnsignedClass<u64>
        {
        public:
            constexpr static bool Value = true;
        };

        template<class T> concept IsUnsigned = IsUnsignedClass<T>::Value;
    }
}