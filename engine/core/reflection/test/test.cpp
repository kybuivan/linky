#include "reflection_enum.hpp"
#include <iostream>

using namespace lk::reflection;
enum class Num : int32_t
{
    ONE,
    TWO,
    THREE
};

int main()
{
    std::cout << enum_to_string(Num::ONE) << std::endl;
    std::cout << enum_to_string(Num::TWO) << std::endl;
    std::cout << enum_to_string(Num::THREE) << std::endl;
    return 0;
}