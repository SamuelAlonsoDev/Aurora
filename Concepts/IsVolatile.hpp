#pragma once

namespace Aurora
{
    namespace Concepts
    {
        template<class T> class IsVolatileClass
        {
        public:
            constexpr static bool Value = false;
        };

        template<class T> class IsVolatileClass<volatile T>
        {
        public:
            constexpr static bool Value = true;
        };

        template<class T> concept IsVolatile = IsVolatileClass<T>::Value;
    }
}