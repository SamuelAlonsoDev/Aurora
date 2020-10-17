#pragma once
#include <Core/Types.hpp>

namespace Aurora
{
    namespace Concepts
    {
        template<class T> class IsFloatingPointClass
        {
        public:
            constexpr static bool Value = false;
        };

        template<> class IsFloatingPointClass<f32>
        {
        public:
            constexpr static bool Value = true;
        };

        template<> class IsFloatingPointClass<f64>
        {
        public:
            constexpr static bool Value = true;
        };

        template<class T> concept IsFloatingPoint = IsFloatingPointClass<T>::Value;
    }
}