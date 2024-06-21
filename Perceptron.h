//
// Created by keenan on 6/17/24.
//
#include <iostream>
#include <string>
#include <functional>
#include "brain_matter.h"

#ifndef PERCEPTRON_PERCEPTRON_H
#define PERCEPTRON_PERCEPTRON_H

namespace cb {

    class Perceptron{
    public:
        // Constructors and Destructor
        Perceptron(int neurons, int features, std::string activation, bool random_initialization=true, bool add_bias=true);
        ~Perceptron() = default;

        // Member Variables
        std::string activation_name;  // name of the activation function being used
        int num_neurons;              // number of rows in the matrix representation
        int num_features;             // number of columns in the matrix representation

        // Operator Overloading
        Vector operator* (Vector& rhs);

    private:
        Matrix perceptron_matrix_;  // underlying representation is a cb::Matrix
    };
}

#endif //PERCEPTRON_PERCEPTRON_H
