#pragma once

namespace Aurora
{
    namespace Concepts
    {
        template<class T> class RemoveReferencesClass
        {
        public:
            using Type = T;
        };

        template<class T> class RemoveReferencesClass<T&>
        {
        public:
            using Type = T;
        };

        template<class T> class RemoveReferencesClass<T&&>
        {
        public:
            using Type = T;
        };

        template<class T> using RemoveReferences = typename RemoveReferencesClass<T>::Type;
    }
}