#include <vector>
#include <stdexcept>
#include "brain_matter.h"


using namespace cb;

// ------------------------------------------COMPUTER BRAIN MATRIX------------------------------------------------------

// Matrix Class Operators
std::vector<double>& Matrix::operator[](size_t index){
    /* when using cb::Matrix, we want it to feel like we are interacting with std::vector<std::vector<double>>, thus
     * indexing the cb::Matrix indexes its representation which is a std::vector<std::vector<double>>. notice that the
     * object being returned is the actual row of the matrix. */
    return (*this).matrix_[index];
}
Matrix& Matrix::operator= (const Matrix& rhs){
    /* when we assign one cb::Matrix to another cb::Matrix, we are essentially doing a deep copy we make sure to copy
     * both the representation of the right-hand-side and the orientation of that cb::Matrix. Some may complain that
     * this is slow. I want linear algebra with these matrices to work as if you were writing the equations on paper.*/
    matrix_ = rhs.matrix_;
    (*this).is_transposed = rhs.is_transposed;
    return *this;
}

Matrix Matrix::operator+ (Matrix& rhs) {
    /* when adding two matrices, they must have the same shape. Therefore, we check the shape, and if they are the same,
     * then we add the matrices elementwise. We also check the orientations of each matrix before adding. This insures
     * that we are adding the matrices in the way that the user intended.*/

    if (is_transposed){
        if (rhs.is_transposed and rows() == rhs.rows() and columns() == rhs.columns()){
            /* both matrices are transposed and are the same size */
            size_t num_rows = columns(), num_cols = rhs.rows();
            std::vector<std::vector<double>> result (num_rows, std::vector<double>(num_cols, 0.0));
            for (size_t i = 0; i < num_rows; ++i){
                for (size_t j = 0; j < num_cols; ++j){
                    result[i][j] = matrix_[j][i] + rhs[j][i];
                }
            }
            (*this).transpose(); rhs.transpose();  // return matrices back to their regular state (not transposed)
            return Matrix(result);
        }
        else if(not rhs.is_transposed and columns() == rhs.rows() and rows() == rhs.columns()){
            /* lhs (this) matrix is transposed and rhs is not transposed, in this orientation they are the same size */
            size_t num_rows = columns(), num_cols = rows();
            std::vector<std::vector<double>> result (num_rows, std::vector<double>(num_cols, 0.0));
            for (size_t i = 0; i < num_rows; ++i){
                for (size_t j = 0; j < num_cols; ++j){
                    result[i][j] = matrix_[j][i] + rhs[i][j];
                }
            }
            (*this).transpose();  // return matrix back to its regular state (not transposed)
            return Matrix(result);
        }
        else {
            throw std::invalid_argument("The matrices you are attempting to add do not have the same size. Or they have"
                                        " been passed in an incompatible orientation.");
        }
    }
    else{
        if (not rhs.is_transposed and rows() == rhs.rows() and columns() == rhs.columns()){
            /* both matrices are not transposed and are the same size */
            size_t num_rows = rows(), num_cols = columns();
            std::vector<std::vector<double>> result (num_rows, std::vector<double>(num_cols, 0.0));
            for (size_t i = 0; i < num_rows; ++i){
                for (size_t j = 0; j < num_cols; ++j){
                    result[i][j] = matrix_[i][j] + rhs[i][j];
                }
            }
            return Matrix(result);
        }
        else if(rhs.is_transposed and rows() == rhs.columns() and columns() == rhs.rows()){
            /* the rhs matrix is transposed and the matrices have the same size when in this orientation */
            size_t num_rows = rows(), num_cols = columns();
            std::vector<std::vector<double>> result (num_rows, std::vector<double>(num_cols, 0.0));
            for (size_t i = 0; i < num_rows; ++i){
                for (size_t j = 0; j < num_cols; ++j){
                    result[i][j] = matrix_[i][j] + rhs[j][i];
                }
            }
            rhs.transpose();  // return the rhs to its regular state (not transposed)
            return Matrix(result);
        }
        else{
            throw std::invalid_argument("The matrices you are attempting to add do not have the same size. Or they have"
                                        " been passed in an incompatible orientation.");
        }
    }
}

Matrix Matrix::operator- (Matrix& rhs) {
    /* when subtracting two matrices, they must have the same shape. Therefore, we check the shape, and if they are the
     * same, then we subtract the matrices elementwise. We also check the orientations of each matrix before subtraction.
     * This insures that we are subtracting the matrices in the way that the user intended.*/

    if (is_transposed){
        if (rhs.is_transposed and rows() == rhs.rows() and columns() == rhs.columns()){
            /* both matrices are transposed and are the same size */
            size_t num_rows = columns(), num_cols = rhs.rows();
            std::vector<std::vector<double>> result (num_rows, std::vector<double>(num_cols, 0.0));
            for (size_t i = 0; i < num_rows; ++i){
                for (size_t j = 0; j < num_cols; ++j){
                    result[i][j] = matrix_[j][i] - rhs[j][i];
                }
            }
            (*this).transpose(); rhs.transpose();  // return matrices back to their regular state (not transposed)
            return Matrix(result);
        }
        else if(not rhs.is_transposed and columns() == rhs.rows() and rows() == rhs.columns()){
            /* lhs (this) matrix is transposed and rhs is not transposed, in this orientation they are the same size */
            size_t num_rows = columns(), num_cols = rows();
            std::vector<std::vector<double>> result (num_rows, std::vector<double>(num_cols, 0.0));
            for (size_t i = 0; i < num_rows; ++i){
                for (size_t j = 0; j < num_cols; ++j){
                    result[i][j] = matrix_[j][i] - rhs[i][j];
                }
            }
            (*this).transpose();  // return matrix back to its regular state (not transposed)
            return Matrix(result);
        }
        else {
            throw std::invalid_argument("The matrices you are attempting to add do not have the same size. Or they have"
                                        " been passed in an incompatible orientation.");
        }
    }
    else{
        if (not rhs.is_transposed and rows() == rhs.rows() and columns() == rhs.columns()){
            /* both matrices are not transposed and are the same size */
            size_t num_rows = rows(), num_cols = columns();
            std::vector<std::vector<double>> result (num_rows, std::vector<double>(num_cols, 0.0));
            for (size_t i = 0; i < num_rows; ++i){
                for (size_t j = 0; j < num_cols; ++j){
                    result[i][j] = matrix_[i][j] - rhs[i][j];
                }
            }
            return Matrix(result);
        }
        else if(rhs.is_transposed and rows() == rhs.columns() and columns() == rhs.rows()){
            /* the rhs matrix is transposed and the matrices have the same size when in this orientation */
            size_t num_rows = rows(), num_cols = columns();
            std::vector<std::vector<double>> result (num_rows, std::vector<double>(num_cols, 0.0));
            for (size_t i = 0; i < num_rows; ++i){
                for (size_t j = 0; j < num_cols; ++j){
                    result[i][j] = matrix_[i][j] - rhs[j][i];
                }
            }
            rhs.transpose();  // return the rhs to its regular state (not transposed)
            return Matrix(result);
        }
        else{
            throw std::invalid_argument("The matrices you are attempting to add do not have the same size. Or they have"
                                        " been passed in an incompatible orientation.");
        }
    }
}

void Matrix::transpose() {
    /* the orientation of a matrix is important. Calling transpose() on a cb::Matrix will (logically) change its
     * orientation. This function returns void. If you want to use a transposed matrix within an operation, you should
     * use the cb::Matrix::T() function, which returns the matrix in its new orientation (logically). */
    (*this).is_transposed = not this->is_transposed;
}

Matrix& Matrix::T() {
    /* the orientation of a matrix is important. Calling T() on a cb::Matrix will (logically) change its
     * orientation. This function should be used within mathematical statements. */
    (*this).is_transposed = not this->is_transposed;
    return *this;
}


// -------------------------------------COMPUTER BRAIN VECTOR-----------------------------------------------------------

// Vector class operators
double Vector::operator[] (size_t index){
    /* we want our cb::Vector(s) to act like the std::vector, hence we can index the underlying std::vector simply by
     * using the operator []. */
    return (*this).vector_[index];
}
Vector& Vector::operator= (const Vector& rhs){
    /* when we assign one cb::Vector to another cb::Vector, we are essentially doing a deep copy we make sure to copy
     * both representation of the right-hand-side (which is a std::vector) and the orientation of that vector. */
    (*this).vector_ = rhs.vector_;
    (*this).is_transposed = rhs.is_transposed;
    return *this;
}

Vector Vector::operator+ (Vector& rhs){
    /* Vector addition. Before the addition takes place, we check that the two cb::Vectors have the same size and
     * orientation. If not, we throw an error and remind the user that the vectors must have these qualities.  If we
     * perform the addition, we return the result in the orientation that the input vectors were in. */
    if ((*this).is_transposed == rhs.is_transposed and size() == rhs.size()){
        std::vector<double> result((*this).size(), 0.00);
        for (size_t i = 0; i < (*this).size(); ++i){
            result[i] = vector_[i] + rhs[i];
        }
        if ((*this).is_transposed){
            (*this).transpose();  // return to regular orientation
            rhs.transpose();      // return to regular orientation
            return Vector(result).T();
        }
        else{ return Vector(result); }
    }
    else{
        throw std::invalid_argument("The vectors that you are attempting to add (a) are not the same length or (b) do "
                                    "not have the same orientation.");
    }
}

Vector Vector::operator- (Vector& rhs){
    /* Vector addition. Before the addition takes place, we check that the two cb::Vectors have the same size and
     * orientation. If not, we throw an error and remind the user that the vectors must have these qualities. If we
     * perform the subtraction, we return the result in the orientation that the input vectors were in. */
    if ((*this).is_transposed == rhs.is_transposed and size() == rhs.size()){
        std::vector<double> result((*this).size(), 0.00);
        for (size_t i = 0; i < (*this).size(); ++i){
            result[i] = vector_[i] - rhs[i];
        }

        if ((*this).is_transposed){
            (*this).transpose();  // return to regular orientation
            rhs.transpose();      // return to regular orientation
            return Vector(result).T();
        }
        else{ return Vector(result); }
    }
    else{
        throw std::invalid_argument("The vectors that you are attempting to add (a) are not the same length or (b) do "
                                    "not have the same orientation.");
    }
}

double Vector::operator* (Vector& rhs){
    /* Compute the dot product. If you wish to compute the outer product, you must use the outer() class function or the
     * symbol (^) rather than (*). Once again, we check that the vectors have the correct orientation before computing
     * the dot product and return the input vectors to their standard positions before returning the dot product. */
    if (!(*this).is_transposed and rhs.is_transposed and size() == rhs.size()){
        double result = 0.0;
        for (size_t i = 0; i < (*this).size(); ++i){
            result += (vector_[i] * rhs[i]);
        }
        rhs.transpose();  // return to regular orientation
        return result;
    }
    else{
        throw std::invalid_argument("The dot product could not be computed because either (a) the vectors were not in"
                                    "the correct orientation or (b) the vectors are different sizes.");
    }
}

Matrix Vector::operator^ (Vector& rhs){
    /* Compute the outer product. If you wish to compute the dot product, you must use the symbol (*). Once again, we
     * check that the vectors have the correct orientation before computing the outer product and return the input
     * vectors to their standard positions before returning the dot product. */
    if ((*this).is_transposed and !rhs.is_transposed){
        std::vector<std::vector<double>> result((*this).size(), std::vector(rhs.size(), 0.0));
        for (size_t i = 0; i < (*this).size(); ++i){
            for (size_t j = 0; j < rhs.size(); ++j){
                result[i][j] = vector_[i]*rhs[j];
            }
        }
        (*this).transpose();  // return to regular orientation
        return Matrix(result);
    }
    else{
        throw std::invalid_argument( "The dot product could not be computed because either the vectors were not in the "
                                     "correct orientation.");
    }
}

void Vector::transpose(){
    /* the orientation of a vector is important. Calling transpose() on a cb::Vector will (logically) change its
     * orientation. This function returns void. If you want to use a transposed vector within an operation, you should
     * use the cb::Vector::T() function, which returns the vector in its new orientation (logically). */
    (*this).is_transposed = not this->is_transposed;
}

Vector& Vector::T(){
    
    (*this).is_transposed = not this->is_transposed;
    return *this;
}