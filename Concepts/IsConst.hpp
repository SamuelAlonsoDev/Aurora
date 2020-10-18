#pragma once

namespace Aurora
{
    namespace Concepts
    {
        template<class T> class IsConstClass
        {
        public:
            constexpr static bool Value = false;
        };

        template<class T> class IsConstClass<const T>
        {
        public:
            constexpr static bool Value = true;
        };

        template<class T> concept IsConst = IsConstClass<T>::Value;
    }
}