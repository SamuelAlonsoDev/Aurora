#pragma once
#include <Concepts/IsSame.hpp>
#include <Concepts/RemoveConst.hpp>
#include <Concepts/RemoveVolatile.hpp>

namespace Aurora
{
    namespace Concepts
    {
        template<class T> concept IsVoid = IsSame<RemoveConst<RemoveVolatile<T>>, void>;
    }
}