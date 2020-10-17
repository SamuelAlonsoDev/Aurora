#pragma once

namespace Aurora
{
    namespace Concepts
    {
        template<class T> concept IsEnum = __is_enum(T);
    }
}