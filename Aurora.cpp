#include <iostream>
#include <Core/Types.hpp>
#include <Concepts/IsArray.hpp>

int main()
{
    std::cout << std::boolalpha <<
    "\nIs 'Aurora::s32' an array? " << 
    Aurora::Concepts::IsArray<Aurora::s32> <<
    "\nIs 'Aurora::s32[]' an array? " << 
    Aurora::Concepts::IsArray<Aurora::s32[]>;
    return 0;
}