#include <iostream>
#include <vector>
#include "brain_matter.h"

int main(){
    cb::Vector vec{std::vector<float>{1, 2, 3, 4, 5}};
    cb::Vector vec2{std::vector<float>{1, 2, 3, 4, 5}};
    cb::Vector vec3{std::vector<float>{1, 2, 3, 4, 5}};


    std::cout << vec + vec2 + vec3 << '\n';

    auto mat = vec.T() * vec2;

    cb::Matrix mat2{std::vector<std::vector<float>>{{2, 1, 3},{2, 3, 4}}};
    std::cout << mat;
    std::cout << mat2;
}
