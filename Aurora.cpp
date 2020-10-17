#include <iostream>
#include <Concepts/IsSize.hpp>

class c{};

int main()
{
    std::cout << std::boolalpha <<
    
    "Is the size of u8 of 1 byte? " << 
    Aurora::Concepts::IsSize<Aurora::u8, 1u> <<

    "\nIs the size of u8 of 2 bytes? " << 
    Aurora::Concepts::IsSize<Aurora::u8, 2u>;
    
    return 0;
}