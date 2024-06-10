#include <iostream>
#include <vector>
#include "brain_matter.h"

int main(){
    cb::Matrix mat{std::vector<std::vector<double>>(5, std::vector<double>(4, 1.0))};
    cb::Matrix mat2{std::vector<std::vector<double>>(4, std::vector<double>(5, 2.0))};

    cb::Matrix mat3 = mat2 + mat.T() + mat2;

    for (auto const &row : mat3){
        for (auto const &element : row){
            std::cout << element << " ";
        }
        std::cout << '\n';
    }
    std::cout << mat.is_transposed;
}
