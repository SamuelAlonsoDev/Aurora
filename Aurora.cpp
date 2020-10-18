#include <iostream>
#include <Core/Types.hpp>
#include <Concepts/IsArray.hpp>

int main()
{
    Aurora::s32 a;
    Aurora::s32 b[2];
    
    std::cout << std::boolalpha <<
    "\nIs 'a' an array? " << 
    Aurora::Concepts::IsArray<decltype(a)> <<
    "\nIs 'b' an array? " << 
    Aurora::Concepts::IsArray<decltype(b)>;
    return 0;
}