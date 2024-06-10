#include <iostream>
#include <vector>
#include "brain_matter.h"

int main(){
    cb::Vector vec (std::vector<double>(5, 1.0));
    cb::Vector vec2 (std::vector<double>(5, 2.0));

    cb::Vector vec3 = vec + vec2;

    std::cout << vec2 * vec3.T() << '\n';

    cb::Matrix mat = vec2.T()^vec3;


    for (const auto &row : mat){
        for (const auto &element : row){
            std::cout << element << " ";
        }
        std::cout << '\n';
    }
}
