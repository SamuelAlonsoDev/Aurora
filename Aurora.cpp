#include <iostream>
#include <Concepts/IsEnum.hpp>

class c{};

//btw, you should use 'enum class'
enum n{};

enum class e{};

int main()
{
    std::cout << std::boolalpha <<
    "\nIs 'c' an enum? " << Aurora::Concepts::IsEnum<c> << 
    "\nIs 'n' an enum? " << Aurora::Concepts::IsEnum<n> <<
    "\nIs 'e' an enum? " << Aurora::Concepts::IsEnum<e>;
    return 0;
}