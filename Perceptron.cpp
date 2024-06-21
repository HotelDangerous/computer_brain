//
// Created by keenan on 6/17/24.
//
#include "Perceptron.h"
#include <random>
#include <vector>
#include <unordered_map>

using namespace cb;

std::unordered_map<std::string, std::function<double(double)>> extern activation_map;  // defined in brain_matter.cpp

/* --------------------------------------------- Perceptron Class ----------------------------------------------------*/

// Constructor and Destructor
Perceptron::Perceptron(int neurons, int features, std::string activation_func, bool random_initialization, bool add_bias) {
    if (random_initialization) { // if elements are initialized with a random distribution
        std::vector<std::vector<double>> temp_mat (neurons, std::vector<double>(features, 0.0));
        for (auto &row : temp_mat){
            std::generate(row.begin(), row.end(), random_double);
            if (add_bias)
                row.push_back(1.0);
        }
        perceptron_matrix_ = Matrix(temp_mat);
    }
    else{  // else elements are initialized to zero
        std::vector<std::vector<double>> temp_mat (neurons, std::vector<double>(features, 0.0));
        if (add_bias) {
            for (auto &row: temp_mat) {
                row.push_back(1.0);
            }
        }
        perceptron_matrix_ = Matrix(temp_mat);
    }
    activation_name = std::move(activation_func);
    num_neurons = neurons;
    num_features = features;
}

Vector Perceptron::operator* (Vector& rhs){
    /* Multiplying a pattern (cb::vector) by a perceptron, has the effect of multiplying the vector by the cb::matrix
     * representation of the perceptron. This gives a vector output vector of net outputs. That vector will have
     * {neurons} elements. Then, each element in the output vector is run through the activation function assigned to
     * this Perceptron. The result is a vector of activations, which is finally returned. */
    Vector activation_vector = perceptron_matrix_ * rhs;
    for (auto& element : activation_vector){
        element = activation_map[activation_name](element);
    }
    return activation_vector;
}