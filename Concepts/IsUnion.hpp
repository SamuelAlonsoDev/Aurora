#pragma once

namespace Aurora
{
    namespace Concepts
    {
        template<class T> concept IsUnion = __is_union(T);
    }
}