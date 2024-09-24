#include <iostream>

#include "linear_algebra.h"

int main() {
    Vector<double> rows(10, 12);
    std::vector proto_mat(12, rows);
    Matrix<double> matrix(proto_mat);


    double x = 12.0;

    Matrix<u_long> mat_1(2, 3);
    Matrix<double> mat_2(3, 2);

    std::cout << matrix << '\n';
    std::cout << mat_1 << '\n';
    std::cout << mat_2;
    return 0;
}
