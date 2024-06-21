//
// Created by keenan on 6/13/24.
//
#include <iostream>
#include <string>
#include <functional>
#include "brain_matter.h"

#ifndef PERCEPTRON_LAYER_H
#define PERCEPTRON_LAYER_H
namespace cb {

    class Neuron{
    public:
        // Constructors and Destructor
        Neuron(int features, std::string activation, bool random_initialization=true, bool add_bias=true);
        ~Neuron() = default;

        // member variables
        std::string activation_name;  // name of the activation function being used
        int num_features;

        // Operator Overloading
        double operator* (Vector& rhs);

    private:
        cb::Vector neuron_vector_;  // underlying representation is a cb::Vector
    };
}

#endif //PERCEPTRON_LAYER_H
