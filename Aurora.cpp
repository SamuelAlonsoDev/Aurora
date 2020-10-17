#include <iostream>
#include <Concepts/IsUnsigned.hpp>

class c{};

int main()
{
    std::cout << std::boolalpha << "u8: " <<
    
    Aurora::Concepts::IsUnsigned<Aurora::u8> <<

    "\nc: " << Aurora::Concepts::IsUnsigned<c>;
    
    return 0;
}