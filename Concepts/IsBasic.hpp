#pragma once
#include <Core/Types.hpp>

namespace Aurora
{
    namespace Concepts
    {
        template<class T> class IsBasicClass
        {
        public:
            constexpr static bool Value = false;
        };

        template<> class IsBasicClass<bool>
        {
        public:
            constexpr static bool Value = true;
        };

        template<> class IsBasicClass<u8>
        {
        public:
            constexpr static bool Value = true;
        };

        template<> class IsBasicClass<s8>
        {
        public:
            constexpr static bool Value = true;
        };

        template<> class IsBasicClass<u16>
        {
        public:
            constexpr static bool Value = true;
        };

        template<> class IsBasicClass<s16>
        {
        public:
            constexpr static bool Value = true;
        };

        template<> class IsBasicClass<u32>
        {
        public:
            constexpr static bool Value = true;
        };

        template<> class IsBasicClass<s32>
        {
        public:
            constexpr static bool Value = true;
        };

        template<> class IsBasicClass<f32>
        {
        public:
            constexpr static bool Value = true;
        };

        template<> class IsBasicClass<u64>
        {
        public:
            constexpr static bool Value = true;
        };

        template<> class IsBasicClass<s64>
        {
        public:
            constexpr static bool Value = true;
        };

        template<> class IsBasicClass<f64>
        {
        public:
            constexpr static bool Value = true;
        };

        template<class T> concept IsBasic = IsBasicClass<T>::Value;
    }
}