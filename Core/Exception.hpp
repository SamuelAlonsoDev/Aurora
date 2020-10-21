#pragma once
#include <Core/Types.hpp>

namespace Aurora
{
    enum class Exception : u16
    {
        None,
        MainWindowResize,
        MainWindowRelocate,
        
    };

    Exception GlobalException = Exception::None;
}