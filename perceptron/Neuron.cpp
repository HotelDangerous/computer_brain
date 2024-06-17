//
// Created by keenan on 6/13/24.
//
#include "Neuron.h"
#include <random>
#include <vector>
#include <unordered_map>

using namespace cb;

/* ------------------------------------------ Random Number Generator ----------------------------------------------- */

double random_double(){
    std::random_device rd;
    std::mt19937 engine(rd());
    std::normal_distribution<double> dist(0, .5);  // normal distribution: mean 0.0, std deviation 0.5
    return dist(engine);
}

/* ----------------------------------------Supported Activation Functions-------------------------------------------- */

double identity(double net_input){
    return net_input;
}

double hardlim(double net_input){
    if (net_input > 0.0){ return 1.0; }
    else { return 0.0; }
}

double hardlims(double net_input){
    if (net_input > 0.0){ return 1.0; }
    else { return -1.0; }
}

double relu(double net_input){
    if (net_input > 0.0){ return net_input; }
    else { return 0.0; }
}

std::unordered_map<std::string, std::function<double(double)>> activation_map = {
        {"identity",  identity},
        {"linear", identity},
        {"hardlim",  hardlim},
        {"hard_lim", hardlim},
        {"hardlims", hardlims},
        {"hard_lims", hardlims},
        {"relu",      relu},
        {"ReLU", relu}
};

/* ------------------------------------------------ Layer Class ------------------------------------------------------*/

// Constructor and Destructor
Neuron::Neuron(int units, std::string activation_func, bool random_initialization, bool add_bias) {
    if (random_initialization) { // if elements are initialized with a random distribution
        std::vector<double> temp_vec(units, 0.0);
        std::generate(temp_vec.begin(), temp_vec.end(), random_double);
        if (add_bias)
            temp_vec.push_back(1.0);
        layer_vector_ = Vector(temp_vec);
    }
    else{  // else elements are initialized to zero
        if (add_bias){
            std::vector temp_vec(units, 0.0);
            temp_vec.push_back(1.0);
            layer_vector_ = Vector(temp_vec);
        } else {
            layer_vector_ = Vector(std::vector<double>(units, 0.0));
        }

    }
    activation_name = std::move(activation_func);
}

double Neuron::operator* (Vector& rhs){
    return activation_map[activation_name](layer_vector_ * rhs);
}