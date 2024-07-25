//
// Created by keenan on 7/17/24.
//
#ifndef COMPUTER_BRAIN2_LINEAR_ALGEBRA_H
#define COMPUTER_BRAIN2_LINEAR_ALGEBRA_H

#include <vector>
#include <stdexcept>
#include <iostream>

/* ----------------------------------------- Vector Class Definitions ----------------------------------------------- */
template<typename T> class Vector {
private:
    std::vector<T> repr;  // the representation of the Vector class is a std::vector
public:
    /* Constructors and Destructor */
    ~Vector();                                      // destructor
    Vector(const Vector& other);                    // copy constructor
    Vector& operator=(const Vector& other);         // copy assignment operator
    Vector(Vector&& other) noexcept;                // move constructor
    Vector& operator=(Vector && other) noexcept;    // move assignment operator
    Vector(int num_elements, T element);
    explicit Vector(std::vector<T> vec);

    /* Member Variables */
    bool is_transposed = false;

    /* Member Functions */
    size_t size();
    auto begin();
    auto end();
    void transpose();
    Vector<T>& t();

    /* Non-Mathematical Operations */
    T& operator[](const size_t& i);

    /* Mathematical Operations */
    Vector operator+(Vector& other);
    Vector operator-(Vector& other);
    T operator*(Vector& other);         // dot product
    Vector& operator*(const T& other);  // scalar multiplication with variable
    Vector& operator*(T&& other);       // scalar multiplication with literal
};


/* ---------------------------------------- Matrix Class Declarations ----------------------------------------------- */


template<typename U> class Matrix {
private:
    std::vector<Vector<U>> repr;  // representation is a std::vector of computer_brain Vectors
public:
    /* Constructors and Destructor */
    ~Matrix();                                           // destructor
    Matrix(const Matrix& other);                         // copy constructor
    Matrix& operator=(const Matrix& other);              // copy assignment operator
    Matrix(Matrix&& other) noexcept;                     // move constructor
    Matrix& operator=(Matrix && other) noexcept;         // move assignment operator
    explicit Matrix(const std::vector<Vector<U>>& mat);  // value constructor (vector)
    Matrix(size_t num_rows, size_t num_cols);            // value constructor (two ints)



    /* Member Variables */
    bool is_transposed = false;

    /* Member Functions */
    size_t rows();
    size_t columns();
    auto begin();
    auto end();
    void t();

    /* Non-Mathematical Operations */
    U& operator[](const size_t& i);

    /* Mathematical Operations */
    Matrix operator+(const Matrix& other);
    Matrix operator-(const Matrix& other);
    Matrix& operator*(const U& other);      // scalar multiplication; with scalar variable
    Matrix& operator*(U&& other);           // scalar multiplication; with scalar literal
};


/* ----------------------------------------- Vector Class Definitions ----------------------------------------------- */


/* Constructors and Destructor */
/// Vector Destructor is just the default constructor.
template<typename T>
Vector<T>::~Vector() = default;  // classic destructor

/**
 * Copy assignment: Used to make a new object by copying an existing object. Copy constructor is used when we pass
 * an object by value or when we make a copy explicitly. Most commonly used to replicate an existing item.
 *
 * Deep copy of another Vector.
 */
template<typename T>
Vector<T>::Vector(const Vector& other){
    repr = other.repr;
    is_transposed = other.is_transposed;
}

/**
 * Copy assignment operator: Assigns data from one object to another object. Used when the assignment operator = is
 * between two Vector objects.
 */
template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T> &other) {
    if (this != &other){  // if: this vector is not the same vector as other, make a deep copy of other
        repr = other.repr;
        is_transposed = other.is_transposed;
    }
    return *this;
}

/// Move constructor: Transfers the ownership of resources from one Vector to another.
template<typename T>
Vector<T>::Vector(Vector<T>&& other) noexcept : repr(std::move(other.repr)), is_transposed(other.is_transposed) { }

/**
 * Move assignment operator: Used when an existing Vector is assigned the value of an rvalue. It is activated when
 * the assignment operator (=) assigns the data of a temporary Vector to an existing Vector.
 */
template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other) noexcept{
    if (this != &other){  // if: this vector and the other are not the same Vector, transfer resources to this vector
        repr = std::move(other.repr);
        is_transposed = std::move(other.is_transposed);
    }
    return *this;
}

/// Create a computer_brain Vector by passing an integer and an element to be repeated.
template<typename T>
Vector<T>::Vector(int num_elements, T element){
    std::vector temp_vec(num_elements, element);
    repr = temp_vec;
}

/// Create a computer_brain Vector by passing the constructor an std::vector.
template<typename T>
Vector<T>::Vector(std::vector<T> vec) : repr(std::move(vec)) { }

/* Vector Member Functions */

/// Vector.size() returns the number of elements that the vector contains.
template<typename T>
size_t Vector<T>::size(){ return repr.size(); }

/**
 * Vector.begin() calls the begin function on the representation of a Vector. The begin function, along with the end
 * function, allows us to use the range based for loop on our Vector(s).
 */
template<typename T>
auto Vector<T>::begin() { return repr.begin(); }

/**
 * Vector.end() calls the end function on the representation of a Vector. The end function, along with the begin
 * function, allows us to use the range based for loop on our Vector(s).
 */
template<typename T>
auto Vector<T>::end(){ return repr.end(); }

/**
 * @brief Vector.tronspose() changes the orientation of the Vector from not transposed to transposed, or vice-versa.
 * And returns void.
 *
 * In linear algebra, the orientation of a Vector is very important. The function t() allows us to transpose the
 * vector when writing a mathematical statement. It is crucial to note that a Vector will NOT remain transposed
 * after any mathematical operation. Importantly, when the value of is_transposed is false (such as at
 * instantiation), the Vector is -conceptually- a column vector.
 */
template<typename T>
void Vector<T>::transpose(){

}

/**
 * @brief Vector.t() changes the orientation of the Vector from not transposed to transposed, or vice-versa. And returns
 * the Vector in a transposed state.
 *
 * In linear algebra, the orientation of a Vector is very important. The function t() allows us to transpose the
 * vector when writing a mathematical statement. It is crucial to note that a Vector will NOT remain transposed
 * after any mathematical operation. Importantly, when the value of is_transposed is false (such as at
 * instantiation), the Vector is -conceptually- a column vector.
 */
template<typename T>
Vector<T>& Vector<T>::t(){
    is_transposed = !is_transposed;
    return *this;
}

/* Non-Mathematical Operation */

/// Indexing a Vector is similar to indexing a std::vector.
template <typename T>
T& Vector<T>::operator[](const size_t& i) { return repr[i]; }

/* Mathematical Operations */
/**
 * Addition between two Vectors is defined by elementwise addition. In other words, given two Vectors of the same
 * size, regardless of orientation, the sum of two matrices is equal to a Vector of the same size whose element i is
 * equal to the sum of the elements i in each of the Vectors; for all i.
 */
template<typename T>
Vector<T> Vector<T>::operator+(Vector& other){
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
        throw std::invalid_argument("\nEither: (a) The vectors you attempted to add have different orientation\n"
                                    "        (b) The Vectors you attempted to add have different sizes\n"
                                    "        (c) Both\n"
        );
    }
}

/**
 * Subtraction between two Vectors is defined by elementwise subtraction. In other words, given two Vectors of the
 * same size, regardless of orientation, the difference of two matrices is equal to a Vector of the same size whose
 * element i is equal to the difference of the elements i in each of the Vectors; for all i.
 */
template<typename T>
Vector<T> Vector<T>::operator-(Vector& other){
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
        throw std::invalid_argument("\nEither: (a) The vectors you attempted to subtract have different orientation\n"
                                    "        (b) The Vectors you attempted to subtract have different sizes\n"
                                    "        (c) Both\n"
        );
    }
}

template <typename T>
T Vector<T>::operator*(Vector& other){
    if(is_transposed && !other.is_transposed && (size() == other.size())) {
        T sum = 0;
        for (int i = 0; i < size(); ++i) {
            sum += (repr[i] + other[i]);
        }
        return sum;
    } else {
        throw std::invalid_argument("\nEither: (a) The dot product cannot be computed due to incompatible orientation of vectors\n"
                                    "        (b) The dot product cannot be computed due to incompatible vector length\n"
                                    "        (c) Both\n"
        );
    }
}

template<typename T>
/**
 * @brief Multiply each element by a scalar number.
 *
 * @tparam T a scalar number type (int, float, double, etc..)
 * @param other a scalar number held in a variable
 * @return Vector<T> where T is the same as the vector which we are operating on
 */
Vector<T>& Vector<T>::operator*(const T& other){
    for(size_t i = 0; i < size(); ++i){
        repr[i] *= other;
    }
    return *this;
}

template <typename T>
/**
 * @brief Multiply each element by a scalar number.
 *
 * @tparam T a scalar number type (int, float, double, etc..)
 * @param other a scalar literal
 * @return Vector<T> where T is the same as the vector which we are operating on
 */
Vector<T>& Vector<T>::operator*(T&& other){
    std::cout << other << ' ';
    for(size_t i = 0; i < size(); ++i){
        repr[i] *= other;
    }
    return *this;
}


/* ----------------------------------------- Matrix Class Definitions ----------------------------------------------- */

/* Constructors and Destructor */
/// Matrix Destructor is just the default constructor.
template<typename U>
Matrix<U>::~Matrix() = default;  // classic destructor

/**
 * Copy assignment: Used to make a new object by copying an existing object. Copy constructor is used when we pass
 * an object by value or when we make a copy explicitly. Most commonly used to replicate an existing item.
 *
 * Deep copy of another Matrix.
 */
template<typename U>
Matrix<U>::Matrix(const Matrix& other){
    repr = other.repr;
    is_transposed = other.is_transposed;
}

/**
 * Copy assignment operator: Assigns data from one object to another object. Used when the assignment operator = is
 * between two Matrix objects.
 */
template<typename U>
Matrix<U>& Matrix<U>::operator=(const Matrix &other) {
    if (this != &other){  // if: this Matrix is not the same vector as other, make a deep copy of other
        repr = other.repr;
        is_transposed = other.is_transposed;
    }
    return *this;
}

/// Move constructor: Transfers the ownership of resources from one Matrix to another.
template<typename U>
Matrix<U>::Matrix(Matrix&& other) noexcept : repr(std::move(other.repr)), is_transposed(other.is_transposed) { }

/**
 * Move assignment operator: Used when an existing Matrix is assigned the value of an rvalue. It is activated when
 * the assignment operator (=) assigns the data of a temporary Vector to an existing Matrix.
 */
template<typename U>
Matrix<U>& Matrix<U>::operator=(Matrix<U>&& other) noexcept{
    if (this != &other){  // if: this vector and the other are not the same Matrix, transfer resources to this vector
        repr(std::move(other.repr));
        is_transposed = other.is_transposed;
    }
    return *this;
}

/**
 * @brief Value Constructor: Takes an std::vector<Vector<U>> and returns a Matrix<U> with the same elements.
 *
 * This value constructor takes one parameter: @param mat a std::vector<Vector<U>>, a standard vector full of Vectors
 * with elements of type U. This is useful when we want to transform a vector into a Matrix or when we want to define
 * a Matrix with particular values.
 *
 * @tparam U should be a numerical type
 */
template <typename U>
Matrix<U>::Matrix(const std::vector<Vector<U>>& mat) : repr(std::move(mat)) { }

/**
 * @brief Value constructor. Takes two integer values and returns a Matrix of zeros.
 *
 * This value constructor takes two parameters: @param num_cols, num_rows these parameters are both of type size_t.
 * Calling this value constructor will return a Matrix full of zeros with num_rows rows and num_cols columns.
 *
 * @tparam U should be a numerical type.
 */
 template <typename U>
Matrix<U>::Matrix(size_t num_rows, size_t num_cols){
    Vector<U> temp_vec(std::vector(num_cols, 0));
    repr = std::vector(num_rows, temp_vec);
}

/* Matrix Member Functions */

/// Matrix.rows() returns the number of elements -rows- that the Matrix contains.
template<typename U>
size_t Matrix<U>::rows(){
    return repr.size();
}

/**
 * @brief Returns the number of elements in the first row of the matrix.
 *
 * Matrix.columns() returns the number of elements in the [FIRST] row of the Matrix. If there are no elements -no
 * rows- in the Matrix, you will receive an error. This is because we cannot count the number of columns in a non-
 * existent object.
 *
 * WARNING: Because the representation of a Matrix is an std::vector, it is possible to create a Matrix with uneven
 * rows. This Matrix class was built to reflect the matrices used in mathematics, which cannot have uneven rows.
 * If you create a Matrix with uneven rows, the behavior will be undefined. Do not create a Matrix with uneven rows.
 */
template<typename U>
size_t Matrix<U>::columns() {
    if (!repr.empty()){ return repr[0].size(); }
    throw std::logic_error("The matrix, on which Matrix.columns() was called, is empty and thus does not contain any "
                           "elements. Therefore, Matrix cannot report a column count.");
}

/**
 * Matrix.begin() calls the begin function on the representation of a Matrix. The begin function, along with the end
 * function, allows us to use the range based for loop on our Matrix(s).
 */
template<typename U>
auto Matrix<U>::begin(){ return repr.begin(); }

/**
 * Matrix.end() calls the end function on the representation of a Matrix. The end function, along with the begin
 * function, allows us to use the range based for loop on our Matrix(s).
 */
template<typename U>
auto Matrix<U>::end(){ return repr.end(); }

/**
 * @brief Matrix.t() changes the orientation of the Matrix from not transposed to transposed, or vice-versa.
 *
 * In linear algebra, the orientation of a Matrix is very important. The function t() allows us to transpose the
 * Matrix when writing a mathematical statement. It is crucial to note that a Vector will NOT remain transposed
 * after any mathematical operation.
 */

template<typename U>
void Matrix<U>::t(){ is_transposed = !is_transposed; }

/* Non-Mathematical Operation */
/// Indexing a Vector is similar to indexing a std::vector.
template <typename U>
U& Matrix<U>::operator[](const size_t& i) { return repr[i]; }

/* Mathematical Operations */
/**
 * @brief Elementwise addition between two Matrix.
 *
 * Given two Matrix the (+) operator performs elementwise addition between matrices. Matrix addition is performed as
 * learned in linear algebra. If the matrices are both NxM, then addition is legal. If matrices have shape MxN and NxM,
 * then addition is only legal if one of the matrices is transposed.
 *
 * The resulting Matrix will have shape corresponding to the input. If both matrices are, MxN and transposed, then the
 * result matrix will have shape NxM. Just as you would expect in linear algebra
 *
 * @tparam U should be a numerical type
 * @param other should be a Matrix with compatible dimensions for addition
 * @return a Matrix<U> with dimension defined by the input
 */
template<typename U>
Matrix<U> Matrix<U>::operator+(const Matrix<U> &other) {
    // if matrices have the same orientation and dimensions
    if (is_transposed == other.is_transposed and rows() == other.rows() and columns() == other.columns()){
        if (!is_transposed) {  // and if the matrices are not transposed
            Matrix<U> result(rows(), columns());
            for (size_t i; i < rows(); ++i) {
                for (size_t j; j < columns(); ++j) {
                    result[i][j] = this[i][j] + other[i][j];
                }
            }
            return result;
        } else {  // and if the matrices are transposed
            Matrix<U> result(columns(), rows());
            for (size_t i; i < rows(); ++i) {
                for (size_t j; j < columns(); ++j) {
                    result[j][i] = this[i][j] + other[i][j];
                }
            }
            return result;
        }
    }
    // else if the matrices dont have the same orientation, but are compatible for addition in their current orientation
    else if(rows()==other.columns() and columns() == other.rows()) {
        if(!is_transposed){  // if this matrix is not transposed
            Matrix<U> result(rows(), columns());
            for (size_t i; i < rows(); ++i) {
                for (size_t j; j < columns(); ++j) {
                    result[i][j] = this[i][j] + other[j][i];
                }
            }
            return result;
        } else {  // this matrix is transposed
            Matrix<U> result(columns(), rows());
            for (size_t i; i < rows(); ++i) {
                for (size_t j; j < columns(); ++j) {
                    result[j][i] = this[i][j] + other[j][i];
                }
            }
        }
    }
    else {  // else the matrices are not compatible for addition
        throw std::invalid_argument("\nEither: (a) The matrices you attempted to add have different orientation\n"
                                    "        (b) The matrices you attempted to add have different sizes\n"
                                    "        (c) Both\n");
    }
}

/**
 * @brief Elementwise subtraction between two Matrix.
 *
 * Given two Matrix the (-) operator performs elementwise subtraction between matrices. Matrix subtraction is performed
 * as learned in linear algebra. If the matrices are both NxM, then subtraction is legal. If matrices have shape MxN and
 * NxM, then subtraction is legal only if one of the matrices is transposed.
 *
 * The resulting Matrix will have shape corresponding to the input. If both matrices are, MxN and transposed, then the
 * result matrix will have shape NxM. Just as you would expect in linear algebra
 *
 * @tparam U should be a numerical type
 * @param other should be a Matrix with compatible dimensions for subtraction
 * @return a Matrix<U> with dimension defined by the input
 */
template<typename U>
Matrix<U> Matrix<U>::operator-(const Matrix<U> &other) {
    // if matrices have the same orientation and dimensions
    if (is_transposed == other.is_transposed and rows() == other.rows() and columns() == other.columns()){
        if (!is_transposed) {  // and if the matrices are not transposed
            Matrix<U> result(rows(), columns());
            for (size_t i; i < rows(); ++i) {
                for (size_t j; j < columns(); ++j) {
                    result[i][j] = this[i][j] - other[i][j];
                }
            }
            return result;
        } else {  // and if the matrices are transposed
            Matrix<U> result(columns(), rows());
            for (size_t i; i < rows(); ++i) {
                for (size_t j; j < columns(); ++j) {
                    result[j][i] = this[i][j] - other[i][j];
                }
            }
            return result;
        }
    }
        // else if the matrices dont have the same orientation, but are compatible for addition in their current orientation
    else if(rows()==other.columns() and columns() == other.rows()) {
        if(!is_transposed){  // if this matrix is not transposed
            Matrix<U> result(rows(), columns());
            for (size_t i; i < rows(); ++i) {
                for (size_t j; j < columns(); ++j) {
                    result[i][j] = this[i][j] - other[j][i];
                }
            }
            return result;
        } else {  // this matrix is transposed
            Matrix<U> result(columns(), rows());
            for (size_t i; i < rows(); ++i) {
                for (size_t j; j < columns(); ++j) {
                    result[j][i] = this[i][j] - other[j][i];
                }
            }
        }
    }
    else {  // else the matrices are not compatible for addition
        throw std::invalid_argument("\nEither: (a) The matrices you attempted to subtract have different orientation\n"
                                    "        (b) The matrices you attempted to subtract have different sizes\n"
                                    "        (c) Both\n");
    }
}

template<typename U>
/**
 * @brief Multiply each element by a scalar number. In the case of this function, that scalar number is held in a
 * variable.
 *
 * @tparam U a scalar number type (int, float, double, etc..)
 * @param other a scalar number held in a variable
 * @return Matrix<U> where U is the same as the vector which we are operating on
 */
Matrix<U>& Matrix<U>::operator*(const U &other){
    for (size_t i = 0; i < rows(); ++i){
        for (size_t j = 0; j < columns(); ++j){
            repr[i][j] *= other;
        }
    }
    return *this;
}

template<typename U>
/**
 * Multiply each element by a scalar number. In the case of this function, that scalar number is in the form of a
 * literal.
 *
 * @tparam U a scalar number type (int, float, double, etc..)
 * @param other a scalar number held in a variable
 * @return Matrix<U> where U is the same as the vector which we are operating on
 */
Matrix<U>& Matrix<U>::operator*(U&& other){
    for (size_t i = 0; i < rows(); ++i){
        for (size_t j = 0; j < columns(); ++j){
            repr[i][j] *= other;
        }
    }
    return *this;
}


/* ------------------------------------------ Non-Member Operators -------------------------------------------------- */


template <typename T>
/**
 * @brief Multiply each element by a scalar number.
 *
 * Because we are multiplying the scalar number on the right, we cannot write a member function of the Vector class to
 * achieve this. Instead we write a non-member function that tells the (*) operator what to do when it encounters a
 * Vector to its left and a scalar to its right.
 *
 * Because scalar multiplication is commutative, the thing it should do is multiplicate the scalar on the right side of
 * the Vector. And we have defined this operation already
 *
 * @tparam T a scalar number type (int, float, double, etc..)
 * @param scalar, vec a scalar number and a Vector; respectively
 * @return Vector<T> where T is the same as the Vector which we are operating on
 */
 Vector<T>& operator*(const T& scalar, Vector<T>& vec){
    return vec * scalar;
 }

template <typename T>
/**
 * @brief Multiply each element by a scalar number.
 *
 * Because we are multiplying the scalar number on the right, we cannot write a member function of the Vector class to
 * achieve this. Instead we write a non-member function that tells the (*) operator what to do when it encounters a
 * Vector to its left and a scalar to its right.
 *
 * Because scalar multiplication is commutative, the thing it should do is multiplicate the scalar on the right side of
 * the Vector. And we have defined this operation already
 *
 * @tparam T a scalar number type (int, float, double, etc..)
 * @param scalar, vec a scalar number and a Vector; respectively
 * @return Vector<T> where T is the same as the Vector which we are operating on
 */
Vector<T>& operator*(T&& scalar, Vector<T>& vec){
    return vec * scalar;
}

template <typename U>
/**
 * @brief Multiply each element by a scalar number.
 *
 * Because we are multiplying the scalar number on the right, we cannot write a member function of the Matrix class to
 * achieve this. Instead we write a non-member function that tells the (*) operator what to do when it encounters a
 * Matrix to its left and a scalar to its right.
 *
 * Because scalar multiplication is commutative, the thing it should do is multiplicate the scalar on the right side of
 * the Matrix. And we have defined this operation already
 *
 * @tparam T a scalar number type (int, float, double, etc..)
 * @param scalar, mat a scalar number and a Matrix; respectively
 * @return Vector<T> where T is the same as the Matrix which we are operating on
 */
Matrix<U>& operator*(const U& scalar, Matrix<U>& mat){
    return mat * scalar;
}

template <typename U>
/**
 * @brief Multiply each element by a scalar number.
 *
 * Because we are multiplying the scalar number on the right, we cannot write a member function of the Matrix class to
 * achieve this. Instead we write a non-member function that tells the (*) operator what to do when it encounters a
 * Matrix to its left and a scalar to its right.
 *
 * Because scalar multiplication is commutative, the thing it should do is multiplicate the scalar on the right side of
 * the Matrix. And we have defined this operation already
 *
 * @tparam T a scalar number type (int, float, double, etc..)
 * @param scalar, vec a scalar number and a Matrix; respectively
 * @return Vector<T> where T is the same as the Matrix which we are operating on
 */
Matrix<U>& operator*(U&& scalar, Matrix<U>& mat){
    return mat * scalar;
}

#endif //COMPUTER_BRAIN2_LINEAR_ALGEBRA_H
