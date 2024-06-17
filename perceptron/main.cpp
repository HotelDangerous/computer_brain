#include <iostream>
#include <vector>
#include "brain_matter.h"
#include "Neuron.h"


int main() {
    cb::Neuron perceptron(10, "linear");
    cb::Vector pattern(std::vector<double>(11, 1));
    std::cout << perceptron * pattern.T();
}