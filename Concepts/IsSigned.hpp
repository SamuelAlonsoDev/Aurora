#pragma once
#include <Core/Types.hpp>

namespace Aurora
{
    namespace Concepts
    {
        template<class T> class IsSignedClass
        {
        public:
            constexpr static bool Value = false;
        };

        template<> class IsSignedClass<s8>
        {
        public:
            constexpr static bool Value = true;
        };

        template<> class IsSignedClass<s16>
        {
        public:
            constexpr static bool Value = true;
        };

        template<> class IsSignedClass<s32>
        {
        public:
            constexpr static bool Value = true;
        };

        template<> class IsSignedClass<f32>
        {
        public:
            constexpr static bool Value = true;
        };

        template<> class IsSignedClass<s64>
        {
        public:
            constexpr static bool Value = true;
        };

        template<> class IsSignedClass<f64>
        {
        public:
            constexpr static bool Value = true;
        };

        template<class T> concept IsSigned = IsSignedClass<T>::Value;
    }
}