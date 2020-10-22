#pragma once

namespace Aurora
{
    namespace Concepts
    {
        template<class T> class RemoveVolatileClass
        {
        public:
            using Type = T;
        };

        template<class T> class RemoveVolatileClass<volatile T>
        {
        public:
            using Type = T;
        };

        template<class T> using RemoveVolatile = typename RemoveVolatileClass<T>::Type;
    }
}