#include <iostream>
#include <Concepts/IsClass.hpp>

class i;

class c{};

enum n{};

enum class e{};

int main()
{
    std::cout << std::boolalpha <<
    "\nIs 'i' a class? " << Aurora::Concepts::IsClass<i> <<
    "\nIs 'c' a class? " << Aurora::Concepts::IsClass<c> << 
    "\nIs 'n' a class? " << Aurora::Concepts::IsClass<n> <<
    "\nIs 'e' a class? " << Aurora::Concepts::IsClass<e>;
    return 0;
}