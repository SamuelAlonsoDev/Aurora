#pragma once

namespace Aurora
{
    namespace Concepts
    {
        template<class T> concept IsClass = __is_class(T);
    }
}