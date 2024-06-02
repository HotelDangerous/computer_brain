#include <iostream>
#include <vector>
#include "brain_matter.h"

int main(){
    cb::Vector vec{std::vector<float>{1, 2, 3, 4, 5}};
    cb::Vector vec2{std::vector<float>{1, 2, 3, 4, 5}};
    cb::Vector vec3{std::vector<float>{1, 2, 3, 4, 5}};

    std::cout << vec + vec2 + vec3 << '\n';
    cb::Matrix mat = vec.T() * vec2;
    std::cout << mat;
}

