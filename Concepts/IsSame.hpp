#pragma once

namespace Aurora
{
    namespace Concepts
    {
        template<class T, class U> class IsSameClass
        {
        public:
            constexpr static bool Value = false;
        };

        template<class T> class IsSameClass<T, T>
        {
        public:
            constexpr static bool Value = true;
        };

        template<class T, class U> concept IsSame = IsSameClass<T, U>::Value;
    }
}