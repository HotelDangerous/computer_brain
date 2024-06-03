//
// Created by keenan on 5/29/24.
//

#ifndef PERCEPTRON_BRAIN_MATTER_H
#define PERCEPTRON_BRAIN_MATTER_H

#include <iostream>
#include <utility>
#include <vector>
#include <variant>



namespace cb{  // Computer Brain namespace

    class Matrix{
    public:
        // Constructors and Destructors
        Matrix() = default;                                                                // default constructor(empty)
        explicit Matrix(std::vector<std::vector<float>> mat) : matrix_(std::move(mat)){ }  // value constructor
        explicit Matrix(float mat_from_float) :                                            // Matrix from float (1x1)
            matrix_(std::move(std::vector<std::vector<float>> {{mat_from_float}})){ }

// Matrix Orientation
        bool is_transposed = false;                                                        // matrix is not transposed at initialization
        void transpose();                                                                  // transpose changes the state of is_transposed

        // Matrix Operators
        friend std::ostream& operator << (std::ostream &os, const Matrix& self);           // declaration for the ( << ) operator
        friend std::ostream& operator << (std::ostream &os, const std::variant<float, Matrix>& self);

    private:
        std::vector<std::vector<float>> matrix_;
    };

    class Vector{
    public:
        // Constructors and Destructor
        Vector() = default;                                                                // default constructor (empty)
        explicit Vector(std::vector<float> vec) : vector_(std::move(vec)){ };              // value constructor
        ~Vector() = default;                                                               // let the language handle destruction


        // Vector Class Variables
        bool is_transposed = false;                                                        // vector is not transposed at initialization

        // Vector Class Functions
        void transpose();                                                                  // transpose changes the state of is_transposed
        Vector T();                                                                        // transposes the vector and returns the transposed vector
        int len();                                                                         // get the length of a vector

        // Vector Class Operators
        friend std::ostream& operator << (std::ostream &os, const Vector& self);           // declaration for the ( << ) operator
        Vector operator+ (Vector& other);                                                  // declaration for the ( + ) operator
        Vector operator- (Vector& other);                                                  // declaration for the ( - ) operator
        std::variant<float, Matrix> operator* (Vector other);                              // declaration for the ( * ) operator
    private:
        std::vector<float> vector_;
    };
}
#endif //PERCEPTRON_BRAIN_MATTER_H
