//
// Created by keenan on 5/29/24.
//
#include "brain_matter.h"
#include <stdexcept>
#include <variant>


namespace cb{

    void Matrix::transpose(){
        is_transposed = !is_transposed;  // if is_transposed was true, now it is false and vice versa
    }

    std::ostream &operator<<(std::ostream &os, const Matrix &self) {                                                     // DEFINING OPERATOR ( << ) for cb::Vector
        if (self.matrix_.empty()){                                                                                       // if the cb::Vector contains no elements
            os << "[]";                                                                                                  // print empty square brackets: "[]"
        }
        else {                                                                                                           // otherwise
            for (auto vec: self.matrix_) {
                os << '[';                                                                                               // print the opening bracket

                for (auto beg = vec.begin(), end = vec.end(); beg + 1 != end; ++beg) {
                    os << *beg
                       << ", ";                                                                                          // print the first n-1 elements seperated by ", "
                }
                os << *(vec.end() - 1) << ']' << '\n';                                                                   // print the nth element followed by the closing bracket
            }
            if (self.is_transposed)                                                                                      // if the vector is transposed
                os << "TRANSPOSED";                                                                                      // print ".T" immediately after the closing bracket
        }
        return os;
    }

    std::ostream &operator<<(std::ostream &os, const std::variant<float, Matrix> &self){
        if (typeid(self) == typeid(float)){
            return os << std::get<float>(self);
        }
        else {
            auto mat = std::get<Matrix>(self);
            return os << mat;
        }
    }

    void Vector::transpose() {
        is_transposed = !is_transposed;  // if is_transposed was true, now it is false and vice versa
    }

    Vector Vector::T(){
        is_transposed = !is_transposed;  // if is_transposed was true, now it is false and vice versa
        return *this;                    // return the vector in its new state
    }

    int Vector::len() {                                                             // defining len for cb::Vector
        int count = 0;                                                              // define a variable to keep count
        for(auto element : Vector::vector_){                                  // iterate through the elements
            count++;                                                                // increment the count for each iteration
        }
        return count;                                                               // return the count
    }

    std::ostream &operator<<(std::ostream &os, const Vector &self) {                // DEFINING OPERATOR ( << ) for cb::Vector
        if (self.vector_.empty()){                                                  // if the cb::Vector contains no elements
            os << "[]";                                                             // print empty square brackets: "[]"
        }
        else {                                                                      // otherwise
            os << '[';                                                              // print the opening bracket
            for (auto beg = self.vector_.begin(), end = self.vector_.end(); beg + 1 != end; ++beg) {
                os << *beg << ", ";                                                 // print the first n-1 elements seperated by ", "
            }
            os << self.vector_.back() << ']';                                 // print the nth element followed by the closing bracket
        }
        if (self.is_transposed)                                                     // if the vector is transposed
            os << ".T";                                                             // print ".T" immediately after the closing bracket
        return os;
    }

    Vector Vector::operator+ (Vector& other){                                       // DEFINING OPERATOR ( + ) for cb::Vector
        int num_elements = (*this).len();                                           // getting the number of elements in the cb::Vector on lhs of ( + )
        std::vector<float> result(num_elements, 0.0);                       // creating a vector of zeros, of the same length, for the result
        if (other.is_transposed == (*this).is_transposed && other.len() == num_elements){  // if the cb::Vectors are the same length and orientation, then
            for (size_t i = 0; i < num_elements; ++i){                               // we iterate through the vectors
                result[i] = (*this).vector_[i] + other.vector_[i];                   // adding them elementwise and storing the result to our result cb::Vector
            }
        }
        else{                                                                        // if the cb::Vectors are of different lengths, or orientations, then
            throw std::invalid_argument(                                             // we throw an error which will terminate the program and notify us
                    "Vectors are not the same length or "                            // with this error message
                    "Vectors are in different orientations"
                    );
        }
        return Vector{result};                                                  // return the result of our addition
    }

    Vector Vector::operator- (Vector& other){                                       // DEFINING OPERATOR ( - ) for cb::Vector
        int num_elements = (*this).len();                                           // getting the number of elements in the cb::Vector on lhs of ( - )
        std::vector<float> result(num_elements, 0.0);                       // creating a vector of zeros, of the same length, for the result
        if (other.is_transposed == (*this).is_transposed && other.len() == num_elements){  // if the cb::Vectors are the same length and orientation, then
            for (size_t i = 0; i < num_elements; ++i){                               // we iterate through the vectors
                result[i] = (*this).vector_[i] - other.vector_[i];                   // subtracting elementwise and storing the result to our result cb::Vector
            }
        }
        else{                                                                        // if the cb::Vectors are of different lengths, or orientations, then
            throw std::invalid_argument(                                             // we throw an error which will terminate the program and notify us
                    "Vectors are not the same length or "                            // with this error message
                    "Vectors are in different orientation."
            );
        }
        return Vector{result};                                                   // return the result of our subtraction
    }

    std::variant<float, Matrix> Vector::operator*(Vector other){
        int num_elements = (*this).len();
        if (!(*this).is_transposed && other.is_transposed && num_elements == other.len()){
            float result{0.0};
            for (size_t i = 0; i < num_elements; ++i){
                result += ((*this).vector_[i] * other.vector_[i]);
            }
            other.transpose();
            return result;
        }
        else if((*this).is_transposed && !other.is_transposed){
            std::vector<std::vector<float>> result((*this).len(), std::vector<float>(other.len(), 0.0));
            size_t i = 0, j;
            for (auto s : other.vector_){
                j = 0;
                for (auto r : (*this).vector_){
                    result[i][j] = s * r;
                    ++j;
                }
                ++i;
            }
            (*this).transpose();
            return Matrix(result);
        }
        else{
            throw std::invalid_argument(
                    "Vectors are not same length (dot product only) or "
                    "Vectors are in the same orientation."
            );
        }
    }
}
