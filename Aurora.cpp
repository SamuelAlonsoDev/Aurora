#include <Core/Types.hpp>
#include <Concepts/RemoveConst.hpp>

int main()
{
    const Aurora::s32 a = 4;
    a = 3;
    Aurora::Concepts::RemoveConst<decltype(a)> b = 4;
    b = 3;
    return 0;
}