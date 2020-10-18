#pragma once

namespace Aurora
{
    namespace Concepts
    {
        template<class T> class RemoveConstClass
        {
        public:
            using Type = T;
        };

        template<class T> class RemoveConstClass<const T>
        {
        public:
            using Type = T;
        };

        template<class T> using RemoveConst = typename RemoveConstClass<T>::Type;
    }
}