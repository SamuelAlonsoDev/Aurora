#include <iostream>
#include <Concepts/IsInteger.hpp>

class c{};

int main()
{
    std::cout << std::boolalpha << "s8: " <<
    
    Aurora::Concepts::IsInteger<Aurora::s8> <<

    "\nc: " << Aurora::Concepts::IsInteger<c>;
    
    return 0;
}