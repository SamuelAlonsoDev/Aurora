#include <iostream>
#include <Core/Types.hpp>
#include <Concepts/IsConst.hpp>

int main()
{
    const Aurora::s32 a = 4;
    Aurora::s32 b;

    std::cout << std::boolalpha <<
    "\nIs 'a' const? " << Aurora::Concepts::IsConst<decltype(a)> <<
    "\nIs 'b' const? " << Aurora::Concepts::IsConst<decltype(b)>;
    return 0;
}