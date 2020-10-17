#pragma once
#include <Core/Types.hpp>

namespace Aurora
{
    namespace Concepts
    {
        template<class T, const u64 Size> concept IsSize = sizeof(T) == Size;
    }
}