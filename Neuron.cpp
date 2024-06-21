//
// Created by keenan on 6/13/24.
//
#include "Neuron.h"
#include <random>
#include <vector>
#include <unordered_map>

using namespace cb;

std::unordered_map<std::string, std::function<double(double)>> extern activation_map;  // defined in brain matter.cpp

/* ----------------------------------------------- Neuron Class ------------------------------------------------------*/
// Constructor and Destructor
Neuron::Neuron(int features, std::string activation_func, bool random_initialization, bool add_bias) {
    if (random_initialization) { // if elements are initialized with a random distribution
        std::vector<double> temp_vec(features, 0.0);
        std::generate(temp_vec.begin(), temp_vec.end(), random_double);
        if (add_bias)
            temp_vec.push_back(1.0);
        neuron_vector_ = Vector(temp_vec);
    }
    else{  // else elements are initialized to zero
        if (add_bias){
            std::vector temp_vec(features, 0.0);
            temp_vec.push_back(1.0);
            neuron_vector_ = Vector(temp_vec);
        } else {
            neuron_vector_ = Vector(std::vector<double>(features, 0.0));
        }

    }
    activation_name = std::move(activation_func);
    num_features = features;
}

double Neuron::operator* (Vector& rhs){
    return activation_map[activation_name](neuron_vector_ * rhs);
}