#pragma once

namespace Aurora
{
    namespace Concepts
    {
        template<class T> class RemovePointerClass
        {
        public:
            using Type = T;
        };

        template<class T> class RemovePointerClass<T*>
        {
        public:
            using Type = T;
        };

        template<class T> using RemovePointer = typename RemovePointerClass<T>::Type;
    }
}