#include <iostream>
#include <Concepts/IsBasic.hpp>

int main()
{
    std::cout << std::boolalpha <<
    
    "u8: " << Aurora::Concepts::IsBasic<Aurora::u8>
    <<
    "\nc: " << Aurora::Concepts::IsBasic<c>;
    
    return 0;
}