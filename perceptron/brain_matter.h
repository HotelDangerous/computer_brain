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
        Matrix() = default;
        explicit Matrix(std::vector<std::vector<double>> mat) : matrix_(std::move(mat)){ }
        explicit Matrix(double mat_from_double) : matrix_(std::move(std::vector<std::vector<double>> {{mat_from_double}})){ }
        ~Matrix() = default;

        // Matrix variables
        bool is_transposed = false;  // matrix is not transposed at initialization

        // Matrix Methods
        size_t rows(){ return matrix_.size(); }                 // number of rows
        size_t columns(){ return matrix_[0].size(); }           // number of columns
        auto begin(){ return matrix_.begin(); };  // necessary for the range for
        auto end(){ return matrix_.end(); }       // necessary for the range for
        void transpose();                                       // transpose the matrix and return nothing
        Matrix& T();                                            // transpose the matrix and return it

        // Matrix Operators
        std::vector<double>& operator[](size_t index);           // index rows from matrix
        Matrix& operator= (const Matrix& rhs);                   // overloading the assignment operator
        Matrix operator+ (Matrix& rhs);                          // overloading the addition operator
        Matrix operator- (Matrix& rhs);
        friend std::ostream& operator<< (std::ostream &os, const Matrix& self);           // declaration for the ( << ) operator
        friend std::ostream& operator<< (std::ostream &os, const std::variant<double, Matrix>& self);

    private:
        std::vector<std::vector<double>> matrix_;
    };

    class Vector{
    public:
        // Constructors and Destructor
        Vector() = default;                                                                // default constructor (empty)
        explicit Vector(std::vector<double> vec) : vector_(std::move(vec)){ };              // value constructor
        ~Vector() = default;                                                               // let the language handle destruction

        // Vector Variables
        bool is_transposed = false;

        // Vector Methods
        size_t size(){ return vector_.size(); }                 // length of the vector
        auto begin(){ return vector_.begin(); };  // necessary for the range for
        auto end(){ return vector_.end(); }       // necessary for the range for
        void transpose();                                       // transpose the vector and return nothing
        Vector& T();                                            // transpose the vector and return it

        // Vector Class Operators
        double operator[] (size_t index);
        Vector& operator= (const Vector& rhs);
        Vector operator+ (Vector& other);                                                  // declaration for the ( + ) operator
        Vector operator- (Vector& other);                                                  // declaration for the ( - ) operator
        std::variant<double, Matrix> operator* (Vector other);                              // declaration for the ( * ) operator
        friend std::ostream& operator << (std::ostream &os, const Vector& self);           // declaration for the ( << ) operator


    private:
        std::vector<double> vector_;
    };
}
#endif //PERCEPTRON_BRAIN_MATTER_H
