//
// Created by keenan on 7/17/24.
//
#ifndef COMPUTER_BRAIN2_LINEAR_ALGEBRA_H
#define COMPUTER_BRAIN2_LINEAR_ALGEBRA_H

#include <vector>
#include <stdexcept>
#include <iostream>

/* ----------------------------------------- Vector Class Definitions ----------------------------------------------- */
template<typename T> class Vector{
private:
    std::vector<T> repr;  // the representation of the Vector class is a std::vector
public:
    /* Constructors and Destructor */
    ~Vector();                                      // destructor
    Vector(const Vector& other);                    // copy constructor
    Vector& operator=(const Vector& other);         // copy assignment operator
    Vector(Vector&& other) noexcept;                // move constructor
    Vector& operator=(Vector && other) noexcept;    // move assignment operator
    explicit Vector(std::vector<T> vec);

    /* Member Variables */
    bool is_transposed = false;

    /* Member Functions */
    size_t size();
    auto begin();
    auto end();
    void t();

    /* Non-Mathematical Operations */
    T& operator[](const size_t& i);

    /* Mathematical Operations */
    Vector operator+(Vector<T>& other);
    Vector operator-(Vector<T>& other);
};

/* ----------------------------------------- Vector Class Definitions ----------------------------------------------- */
/* Constructors and Destructor */
template<typename T>
Vector<T>::~Vector() = default;  // classic destructor

template<typename T>
Vector<T>::Vector(const Vector& other){
    /**
     * Copy assignment: Used to make a new object by copying an existing object. Copy constructor is used when we pass
     * an object by value or when we make a copy explicitly. Most commonly used to replicate an existing item.
     *
     * Deep copy of another Vector.
     */
    repr = other.repr;
    is_transposed = other.is_transposed;
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T> &other) {
    /**
     * Copy assignment operator: Assigns data from one object to another object. Used when the assignment operator = is
     * between two Vector objects.
     */
    if (this != &other){  // if: this vector is not the same vector as other, make a deep copy of other
        repr = other.repr;
        is_transposed = other.is_transposed;
    }
    return *this;
}

template<typename T>
Vector<T>::Vector(Vector<T>&& other) noexcept
    : repr(std::move(other.repr)){
    /// Move constructor: Transfers the ownership of resources from one Vector to another.
    is_transposed = other.is_transposed;
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other) noexcept{
    /**
     * Move assignment operator: Used when an existing Vector is assigned the value of an rvalue. It is activated when
     * the assignment operator (=) assigns the data of a temporary Vector to an existing Vector.
     */
    if (this != &other){  // if: this vector and the other are not the same Vector, transfer resources to this vector
        repr(std::move(other.repr));
        is_transposed = other.is_transposed;
    }
    return *this;
}

template<typename T>
Vector<T>::Vector(std::vector<T> vec) : repr(std::move(vec)) {
    /// Create a computer_brain Vector by passing the constructor an std::vector.
}

/* Member Functions */
template<typename T>
size_t Vector<T>::size(){
    /// Vector.size() returns the number of elements that the vector contains.
    return repr.size();
}

template<typename T>
auto Vector<T>::begin() {
    /**
     * Vector.begin() calls the begin function on the representation of a Vector. The begin function, along with the end
     * function, allows us to use the range based for loop on our Vectors.
     */
    return repr.begin();
}

template<typename T>
auto Vector<T>::end(){
    /**
     * Vector.end() calls the end function on the representation of a Vector. The end function, along with the begin
     * function, allows us to use the range based for loop on our Vectors.
     */
    return repr.end();
}

template<typename T>
void Vector<T>::t(){
    /**
     * In linear algebra, the orientation of a Vector is very important. The function t() allows us to transpose the
     * vector when writing a mathematical statement. It is crucial to note that a Vector will NOT remain transposed
     * after any mathematical operation. Importantly, when the value of is_transposed is false (such as at
     * instantiation), the Vector is -conceptually- a row vector.
     */
    is_transposed = !is_transposed;
}

/* Non-Mathematical Operation */
template <typename T>
T& Vector<T>::operator[](const size_t& i){
    /// Indexing a Vector is similar to indexing a std::vector.
    return repr[i];
}

/* Mathematical Operations */
template<typename T>
Vector<T> Vector<T>::operator+(Vector<T>& other){
    if (is_transposed == other.is_transposed && size() == other.size()) { // if: vectors have the same orientation and size
        std::vector<T> result_repr(repr.size(), 0);
        Vector<T> result(result_repr);
        for (size_t i = 0; i < repr.size(); ++i) {
            result[i] = repr[i] + other[i];
        }
        if (is_transposed) {  // if: the vectors are transposed, then un-transpose them
            is_transposed = false;
            other.is_transposed = false;
            result.is_transposed = true;  // result vector takes the orientation of the argument vectors
        }
        return result;
    }
    else if(size() == other.size() == 1){  // else if: the vectors have different orientation, but only one element
        std::vector<T> result_repr(repr.size(), 0);
        Vector<T> result(result_repr);
        result[0] = repr[0] + other[0];
        if (is_transposed)  // if: this vector is transposed, un-transpose it
            is_transposed = false;
        else                // else: other vector must be transposed, un-transpose it
            other.is_transposed = false;
        return result;
    }
    else{  // else: throw an error
        throw std::invalid_argument("Either: (a) The vectors you attempted to add have different orientation\n"
                                    "        (b) The Vectors you attempted to add have different sizes\n"
                                    "        (c) Both\n"
        );
    }
}

template<typename T>
Vector<T> Vector<T>::operator-(Vector<T>& other){
    if (is_transposed == other.is_transposed && size() == other.size()) { // if: vectors have the same orientation and size
        std::vector<T> result_repr(repr.size(), 0);
        Vector<T> result(result_repr);
        for (size_t i = 0; i < repr.size(); ++i) {
            result[i] = repr[i] - other[i];
        }
        if (is_transposed) {  // if: the vectors are transposed, then un-transpose them
            is_transposed = false;
            other.is_transposed = false;
            result.is_transposed = true;  // result vector takes the orientation of the argument vectors
        }
        return result;
    }
    else if(size() == other.size() == 1){  // else if: the vectors have different orientation, but only one element
        std::vector<T> result_repr(repr.size(), 0);
        Vector<T> result(result_repr);
        result[0] = repr[0] - other[0];
        if (is_transposed)  // if: this vector is transposed, un-transpose it
            is_transposed = false;
        else                // else: other vector must be transposed, un-transpose it
            other.is_transposed = false;
        return result;
    }
    else{  // else: throw an error
        throw std::invalid_argument("Either: (a) The vectors you attempted to add have different orientation\n"
                                    "        (b) The Vectors you attempted to add have different sizes\n"
                                    "        (c) Both\n"
        );
    }
}

#endif //COMPUTER_BRAIN2_LINEAR_ALGEBRA_H
