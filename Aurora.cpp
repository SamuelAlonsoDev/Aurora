#include <iostream>
#include <Concepts/IsSigned.hpp>

class c{};

int main()
{
    std::cout << std::boolalpha << "s8: " <<
    
    Aurora::Concepts::IsSigned<Aurora::s8> <<

    "\nc: " << Aurora::Concepts::IsSigned<c>;
    
    return 0;
}