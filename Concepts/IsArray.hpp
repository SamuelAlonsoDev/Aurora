#pragma once

namespace Aurora
{
    namespace Concepts
    {
        template<class T> class IsArrayClass
        {
        public:
            constexpr static bool Value = false;
        };

        template<class T> class IsArrayClass<T[]>
        {
        public:
            constexpr static bool Value = true;
        };

        template<class T> concept IsArray = IsArrayClass<T>::Value;
    }
}