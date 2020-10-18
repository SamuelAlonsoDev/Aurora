#include <iostream>
#include <Concepts/IsUnion.hpp>

class c{};

union u{};

int main()
{
    std::cout << std::boolalpha <<
    "\nIs 'c' a union? " << Aurora::Concepts::IsUnion<c> <<
    "\nIs 'u' a union? " << Aurora::Concepts::IsUnion<u>;
    return 0;
}