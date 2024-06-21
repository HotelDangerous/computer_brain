#include <iostream>
#include <vector>
#include <cassert>

#include "brain_matter.h"
#include "Perceptron.h"


int main() {
    static_assert(std::is_default_constructible_v<cb::Matrix>);
    static_assert(std::is_destructible_v<cb::Matrix>);
    static_assert(!std::is_copy_constructible_v<cb::Matrix>);  // matrix and vector are not copy constructible
    static_assert(std::is_copy_assignable_v<cb::Matrix>);
    static_assert(std::is_move_constructible_v<cb::Matrix>);
    static_assert(std::is_move_assignable_v<cb::Matrix>);
    static_assert(!std::has_virtual_destructor_v<cb::Matrix>);
    return 0;
}