#pragma once

namespace Aurora
{
    namespace Concepts
    {
        template<class T> class IsPointerClass
        {
        public:
            constexpr static bool Value = false;
        };

        template<class T> class IsPointerClass<T*>
        {
        public:
            constexpr static bool Value = true;
        };

        template<class T> concept IsPointer = IsPointerClass<T>::Value;
    }
}