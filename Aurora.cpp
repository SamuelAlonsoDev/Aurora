#include <iostream>
#include <Core/Types.hpp>
#include <Concepts/IsPointer.hpp>

int main()
{
    Aurora::s32 c = 4;

    Aurora::s32* a = &c;
    Aurora::s32 b = c;

    std::cout << std::boolalpha <<
    "\nIs 'a' a pointer? " << 
    Aurora::Concepts::IsPointer<decltype(a)> <<
    "\nIs 'b' a pointer? " << 
    Aurora::Concepts::IsPointer<decltype(b)>;
    return 0;
}