#ifndef LINEARALGEBRA_H
#define LINEARALGEBRA_H

/*!
 * \file
 * This module contains routine for doing linear algebra in C. There are six types of data here:
 * - Vectors whose length are 3 elements (a simple array). "vector3"
 * - Vectors whose length is arbitrary. "Vector_t"
 * - Matrices whose row and column dimensions are arbitrary. "Matrix_t"
 * - And single precision versions of the above.
 * To avoid unnecessary dynamic memory allocation special macros are used to
 * declare and initialize the Vector_t and Matrix_t types.
 */

#include "Types.h"

// C++ compilers: don't mangle us
#ifdef __cplusplus
extern "C" {
#endif

//! Enumeration for a three dimensional vector
enum
{
    VECTOR3X,
    VECTOR3Y,
    VECTOR3Z,
    NVECTOR3
};

//! Set all elements of a vector3 to a specific value
double* vector3Set(double vector[NVECTOR3], double value);

//! Copy one vector to another
const double* vector3Copy(const double source[NVECTOR3], double dest[NVECTOR3]);

//! Multiply and accumulate two vectors as result = a + b*scale.
const double* vector3MultiplyAccumulate(const double a[NVECTOR3], const double b[NVECTOR3], double scale, double result[NVECTOR3]);

//! Sum two three dimensional vectors together.
const double* vector3Sum(const double a[NVECTOR3], const double b[NVECTOR3], double result[NVECTOR3]);

//! Subtract one three dimensional vector from another.
const double* vector3Difference(const double left[NVECTOR3], const double right[NVECTOR3], double result[NVECTOR3]);

//! Multiply two vectors together element-wise
const double* vector3Multiply(const double a[NVECTOR3], const double b[NVECTOR3], double result[NVECTOR3]);

//! Compute the dot product of two three dimensional vectors
double vector3Dot(const double a[NVECTOR3], const double b[NVECTOR3]);

//! Compute the angle between two three dimensional vectors
double vector3AngleBetween(const double a[NVECTOR3], const double b[NVECTOR3]);

//! Cross one three dimensional vector against another.
const double* vector3Cross(const double left[NVECTOR3], const double right[NVECTOR3], double result[NVECTOR3]);

//! Compute the square of the length of a three dimensional vector
double vector3LengthSquared(const double vector[NVECTOR3]);

//! Compute the length of a three dimensional vector
double vector3Length(const double vector[NVECTOR3]);

//! Change the length of a vector. This is faster than making a unit vector and then scaling.
const double* vector3ChangeLength(const double vector[NVECTOR3], double result[NVECTOR3], double newlength);

//! Scale a three dimensional vector
const double* vector3Scale(const double vector[NVECTOR3], double result[NVECTOR3], double scale);

//! Scale a three dimensional vector to unit length.
const double* vector3Unit(const double vector[NVECTOR3], double result[NVECTOR3]);

//! Convert a double-precision vector to single precision
const float *vector3Convert(const double vector[NVECTOR3], float result[NVECTOR3]);

//! Compute the absolute value of all three elements in a vector
const double *vector3Abs(const double vector[NVECTOR3], double result[NVECTOR3]);

//! Get the largest element in a vector
#define vector3Max(vector)  MAX(vector[VECTOR3X], MAX(vector[VECTOR3Y], vector[VECTOR3Z]))

//! Get the smallest element in a vector
#define vector3Min(vector)  MIN(vector[VECTOR3X], MIN(vector[VECTOR3Y], vector[VECTOR3Z]))


//! The vector structure
typedef struct
{
    uint32_t num;   //!< number of elements of the vector
    double* data;   //!< pointer to the vector data

}Vector_t;


/*! Macro to allocate a vector statically. The vector elements are not initialized.
 * \param V is the name used to refer to the vector.
 * \param num is the number of elements.
 */
#define staticAllocateVector(V, num) static double V##data[(num)]; static Vector_t V = {(num), V##data}

/*! Macro to allocate a vector on the stack. The vector elements are not initialized.
 * \param V is the name used to refer to the vector.
 * \param num is the number of elements.
 */
#define stackAllocateVector(V, num) double V##data[(num)]; Vector_t V = {(num), V##data}

/*! Macro to allocate a vector as part of a structure. The vector MUST be setup with structInitVector()
 * \param V is the name used to refer to the vector.
 * \param num is the number of elements.
 */
#define structAllocateVector(V, num) double V##data[(num)]; Vector_t V

/*! Macro to setup a vector that was previously named in a struct using structAllocateVector()
 * \param V is the name used to refer to the vector.
 * \param num is the number of elements.
 */
#define structInitVector(V, num) V.data = V##data; V.num = (num)

//! Get a specific element of a vector
double vectorGet(const Vector_t* V, uint32_t index);

//! Set a specific element of a vector
Vector_t* vectorSet(Vector_t* V, uint32_t index, double value);

//! Add a scalar to a specific element of the vector
Vector_t* vectorAddToElement(Vector_t* V, uint32_t index, double value);

//! Set the contents of a vector
Vector_t* vectorSetAll(Vector_t* V, double value);

//! Allocate a vector, initializing its memory
Vector_t* vectorAllocate(uint32_t num);

//! Change the size of a dynamically allocated vector
Vector_t* vectorChangeAllocateSize(Vector_t* v, uint32_t num, double initial);

//! Change the size of a vector
void vectorChangeSize(Vector_t* v, uint32_t num, double initial);

//! Set all elements of a vector to zero
Vector_t* vectorZero(Vector_t* V);

//! Copy a vector
Vector_t* vectorCopy(const Vector_t* A, Vector_t* B);

//! Multiply and accumulate two vectors as result = a + b*scale.
Vector_t* vectorMultiplyAccumulate(const Vector_t* a, const Vector_t* b, double scale, Vector_t* result);

//! Sum two three dimensional vectors together.
Vector_t* vectorSum(const Vector_t* a, const Vector_t* b, Vector_t* result);

//! Subtract one three dimensional vector from another.
Vector_t* vectorDifference(const Vector_t* left, const Vector_t* right, Vector_t* result);

//! Multiply two vectors together element-wise
Vector_t* vectorMultiply(const Vector_t* a, const Vector_t* b, Vector_t* result);

//! Compute the dot product of two three dimensional vectors
double vectorDot(const Vector_t* a, const Vector_t* b);

//! Compute the square of the length of a three dimensional vector
double vectorLengthSquared(const Vector_t* v);

//! Compute the length of a three dimensional vector
double vectorLength(const Vector_t* v);

//! Change the length of a vector. This is faster than making a unit vector and then scaling.
Vector_t* vectorChangeLength(const Vector_t* v, Vector_t* result, double newlength);

//! Scale a three dimensional vector
Vector_t* vectorScale(const Vector_t* v, Vector_t* result, double scale);

//! Scale a three dimensional vector to unit length.
Vector_t* vectorUnit(const Vector_t* v, Vector_t* result);

//! Compute the absolute value of all three elements in a vector
Vector_t* vectorAbs(const Vector_t* v, Vector_t* result);

//! Get the largest element in a vector
double vectorMax(const Vector_t* v);

//! Get the smallest element in a vector
double vectorMin(const Vector_t* v);

//! The matrix structure which holds data in row major format
typedef struct
{
    uint32_t numRows;   //!< number of rows of the matrix
    uint32_t numCols;   //!< number of columns of the matrix
    double* data;       //!< pointer to the matrix data in row major format

}Matrix_t;


/*! Macro to allocate a matrix statically. The matrix elements are not initialized.
 * \param M is the name used to refer to the matrix.
 * \param rows is the number of rows.
 * \param cols is the number of columns.
 */
#define staticAllocateMatrix(M, rows, cols) static double M##data[(rows)*(cols)]; static Matrix_t M = {(rows), (cols), M##data}

/*! Macro to allocate a matrix on the stack. The matrix elements are not initialized.
 * \param M is the name used to refer to the matrix.
 * \param rows is the number of rows.
 * \param cols is the number of columns.
 */
#define stackAllocateMatrix(M, rows, cols) double M##data[(rows)*(cols)]; Matrix_t M = {(rows), (cols), M##data}

/*! Macro to allocate a matrix as part of a structure. The matrix MUST be setup with structInitMatrix()
 * \param M is the name used to refer to the DCM.
 * \param rows is the number of rows.
 * \param cols is the number of columns.
 */
#define structAllocateMatrix(M, rows, cols) double M##data[(rows)*(cols)]; Matrix_t M

/*! Macro to setup a DCM that was previously named in a struct using structAllocateDCM()
 * \param M is the name used to refer to the DCM.
 * \param rows is the number of rows.
 * \param cols is the number of columns.
 */
#define structInitMatrix(M, rows, cols) M.data = M##data; M.numRows = (rows); M.numCols = (cols)

//! Get a specific element of a matrix
double matrixGet(const Matrix_t* M, uint32_t row, uint32_t col);

//! Set a specific element of a matrix
void matrixSet(Matrix_t* M, uint32_t row, uint32_t col, double value);

//! Add a scalar to a specific element of the matrix
void matrixAddToElement(Matrix_t* M, uint32_t row, uint32_t col, double value);

//! Set an entire row of a matrix
void matrixSetRow(Matrix_t* M, uint32_t row, double value);

//! Set an entire column of a matrix
void matrixSetColumn(Matrix_t* M, uint32_t col, double value);

//! Allocate a matrix, initializing its memory
Matrix_t* matrixAllocate(uint32_t rows, uint32_t cols);

//! Change the size of a matrix
Matrix_t* matrixChangeAllocateSize(Matrix_t* M, uint32_t rows, uint32_t cols, double initial);

//! Change the size of a matrix
void matrixChangeSize(Matrix_t* M, uint32_t rows, uint32_t cols, double initial);

//! Set all elements of a matrix to zero
void matrixZero(Matrix_t* M);

//! Set this matrix to be identity
void matrixSetIdentity(Matrix_t* M);

//! Copy a matrix
BOOL matrixCopy(const Matrix_t* A, Matrix_t* B);

//! Multiply two matrices together
BOOL matrixMultiply(const Matrix_t* A, const Matrix_t* B, Matrix_t* C);

//! Multiply the transpose of the left matrix against the right matrix
BOOL matrixMultiplyTransA(const Matrix_t* A, const Matrix_t* B, Matrix_t* C);

//! Multiply the left matrix against the transpose of the right matrix
BOOL matrixMultiplyTransB(const Matrix_t* A, const Matrix_t* B, Matrix_t* C);

//! Multiply a vector against a matrix
BOOL matrixVectorMultiply(const Matrix_t* A, const Vector_t* B, Vector_t* C);

//! Multiply a vector against the transpose of a matrix
BOOL matrixVectorMultiplyTransA(const Matrix_t* A, const Vector_t* B, Vector_t* C);

//! Add two matrices together
BOOL matrixAdd(const Matrix_t* A, const Matrix_t* B, Matrix_t* C);

//! Add two matrices together, placing the result back into the first matrix.
BOOL matrixAddEquals(Matrix_t* A, const Matrix_t* B);

//! Scale a matrix
void matrixScale(Matrix_t* A, double scalar);

//! Add two matrices together and multiply each element by 0.5.
BOOL matrixAverage(const Matrix_t* A, const Matrix_t* B, Matrix_t* C);

//! Add identity to a matrix
void matrixAddIdentity(Matrix_t* A);

//! Subtract identity from a matrix
void matrixMinusIdentity(Matrix_t* A);

//! Subtract a matrix from the identity matrix
void matrixIdentityMinus(Matrix_t* A);

//! Compute the dot product of two rows of a matrix
double matrixDotRows(const Matrix_t *A, uint32_t rowA, uint32_t rowB);

//! Compute the transpose of a matrix
BOOL matrixTranspose(const Matrix_t* A, Matrix_t* B);

//! Calculate the inverse of a square matrix A, for dimensions 1x2, 2x2, 3x3
BOOL matrixInverse(const Matrix_t* A, Matrix_t* B);

//! Test a matrix for its error to identity
double testForIdentity(const Matrix_t* M);

//! Test a matrix for its error to null
double testForZeroMatrix(const Matrix_t* M);

//! Evaluate the derivative of quadratic equation at x
double quadraticDerivativeEvaluation(const double cba[3], double x);

//! Evaluate a quadratic equation with 3 coefficients at x
double quadraticEvaluation(const double cba[3], double x);

//! Solve a quadratic regression to determine the coefficients c, b, and a.
BOOL quadraticRegression(const double x[], const double y[], int num, double cba[3]);

//! Set all elements of a vector3 to a specific value
float* vector3Setf(float vector[NVECTOR3], float value);

//! Copy one vector to another
const float* vector3Copyf(const float source[NVECTOR3], float dest[NVECTOR3]);

//! Multiply and accumulate two vectors as result = a + b*scale.
const float* vector3MultiplyAccumulatef(const float a[NVECTOR3], const float b[NVECTOR3], float scale, float result[NVECTOR3]);

//! Sum two three dimensional vectors together.
const float* vector3Sumf(const float a[NVECTOR3], const float b[NVECTOR3], float result[NVECTOR3]);

//! Subtract one three dimensional vector from another.
const float* vector3Differencef(const float left[NVECTOR3], const float right[NVECTOR3], float result[NVECTOR3]);

//! Multiply two vectors together element-wise
const float* vector3Multiplyf(const float a[NVECTOR3], const float b[NVECTOR3], float result[NVECTOR3]);

//! Compute the dot product of two three dimensional vectors
float vector3Dotf(const float a[NVECTOR3], const float b[NVECTOR3]);

//! Compute the angle between two three dimensional vectors
float vector3AngleBetweenf(const float a[NVECTOR3], const float b[NVECTOR3]);

//! Cross one three dimensional vector against another.
const float* vector3Crossf(const float left[NVECTOR3], const float right[NVECTOR3], float result[NVECTOR3]);

//! Compute the square of the length of a three dimensional vector
float vector3LengthSquaredf(const float vector[NVECTOR3]);

//! Compute the length of a three dimensional vector
float vector3Lengthf(const float vector[NVECTOR3]);

//! Change the length of a vector. This is faster than making a unit vector and then scaling.
const float* vector3ChangeLengthf(const float vector[NVECTOR3], float result[NVECTOR3], float newlength);

//! Scale a three dimensional vector
const float* vector3Scalef(const float vector[NVECTOR3], float result[NVECTOR3], float scale);

//! Scale a three dimensional vector to unit length.
const float* vector3Unitf(const float vector[NVECTOR3], float result[NVECTOR3]);

//! Convert a double-precision vector to single precision
const double *vector3Convertf(const float vector[NVECTOR3], double result[NVECTOR3]);

//! Compute the absolute value of all three elements in a vector
const float *vector3Absf(const float vector[NVECTOR3], float result[NVECTOR3]);

//! Get the largest element in a vector
#define vector3Maxf(vector) MAX(vector[VECTOR3X], MAX(vector[VECTOR3Y], vector[VECTOR3Z]))

//! Get the smallest element in a vector
#define vector3Minf(vector) MIN(vector[VECTOR3X], MIN(vector[VECTOR3Y], vector[VECTOR3Z]))


//! The vector structure
typedef struct
{
    uint32_t num;   //!< number of elements of the vector
    float* data;   //!< pointer to the vector data

}Vectorf_t;


/*! Macro to allocate a vector statically. The vector elements are not initialized.
 * \param V is the name used to refer to the vector.
 * \param num is the number of elements.
 */
#define staticAllocateVectorf(V, num) static float V##data[(num)]; static Vectorf_t V = {(num), V##data}

/*! Macro to allocate a vector on the stack. The vector elements are not initialized.
 * \param V is the name used to refer to the vector.
 * \param num is the number of elements.
 */
#define stackAllocateVectorf(V, num) float V##data[(num)]; Vectorf_t V = {(num), V##data}

/*! Macro to allocate a vector as part of a structure. The vector MUST be setup with structInitVector()
 * \param V is the name used to refer to the vector.
 * \param num is the number of elements.
 */
#define structAllocateVectorf(V, num) float V##data[(num)]; Vectorf_t V

//! Get a specific element of a vector
float vectorGetf(const Vectorf_t* V, uint32_t index);

//! Set a specific element of a vector
Vectorf_t* vectorSetf(Vectorf_t* V, uint32_t index, float value);

//! Add a scalar to a specific element of the vector
Vectorf_t* vectorAddToElementf(Vectorf_t* V, uint32_t index, float value);

//! Set the contents of a vector
Vectorf_t* vectorSetAllf(Vectorf_t* V, float value);

//! Allocate a vector, initializing its memory
Vectorf_t* vectorAllocatef(uint32_t num);

//! Set all elements of a vector to zero
Vectorf_t* vectorZerof(Vectorf_t* V);

//! Copy a vector
Vectorf_t* vectorCopyf(const Vectorf_t* A, Vectorf_t* B);

//! Multiply and accumulate two vectors as result = a + b*scale.
Vectorf_t* vectorMultiplyAccumulatef(const Vectorf_t* a, const Vectorf_t* b, float scale, Vectorf_t* result);

//! Sum two three dimensional vectors together.
Vectorf_t* vectorSumf(const Vectorf_t* a, const Vectorf_t* b, Vectorf_t* result);

//! Subtract one three dimensional vector from another.
Vectorf_t* vectorDifferencef(const Vectorf_t* left, const Vectorf_t* right, Vectorf_t* result);

//! Multiply two vectors together element-wise
Vectorf_t* vectorMultiplyf(const Vectorf_t* a, const Vectorf_t* b, Vectorf_t* result);

//! Compute the dot product of two three dimensional vectors
float vectorDotf(const Vectorf_t* a, const Vectorf_t* b);

//! Compute the square of the length of a three dimensional vector
float vectorLengthSquaredf(const Vectorf_t* v);

//! Compute the length of a three dimensional vector
float vectorLengthf(const Vectorf_t* v);

//! Change the length of a vector. This is faster than making a unit vector and then scaling.
Vectorf_t* vectorChangeLengthf(const Vectorf_t* v, Vectorf_t* result, float newlength);

//! Scale a three dimensional vector
Vectorf_t* vectorScalef(const Vectorf_t* v, Vectorf_t* result, float scale);

//! Scale a three dimensional vector to unit length.
Vectorf_t* vectorUnitf(const Vectorf_t* v, Vectorf_t* result);

//! Compute the absolute value of all three elements in a vector
Vectorf_t* vectorAbsf(const Vectorf_t* v, Vectorf_t* result);

//! Get the largest element in a vector
float vectorMaxf(const Vectorf_t* v);

//! Get the smallest element in a vector
float vectorMinf(const Vectorf_t* v);

//! Change the size of a dynamically allocated vector
Vectorf_t* vectorChangeAllocateSizef(Vectorf_t* v, uint32_t num, float initial);

//! Change the size of a vector
void vectorChangeSizef(Vectorf_t* v, uint32_t num, float initial);


//! The matrix structure which holds data in row major format
typedef struct
{
    uint32_t numRows;   //!< number of rows of the matrix
    uint32_t numCols;   //!< number of columns of the matrix
    float* data;        //!< pointer to the matrix data in row major format

}Matrixf_t;

/*! Macro to allocate a matrix statically. The matrix elements are not initialized.
 * \param M is the name used to refer to the matrix.
 * \param rows is the number of rows.
 * \param cols is the number of columns.
 */
#define staticAllocateMatrixf(M, rows, cols) static float M##data[(rows)*(cols)]; static Matrixf_t M = {(rows), (cols), M##data}

/*! Macro to allocate a matrix on the stack. The matrix elements are not initialized.
 * \param M is the name used to refer to the matrix.
 * \param rows is the number of rows.
 * \param cols is the number of columns.
 */
#define stackAllocateMatrixf(M, rows, cols) float M##data[(rows)*(cols)]; Matrixf_t M = {(rows), (cols), M##data}

/*! Macro to allocate a matrix as part of a structure. The matrix MUST be setup with structInitMatrix()
 * \param M is the name used to refer to the DCM.
 * \param rows is the number of rows.
 * \param cols is the number of columns.
 */
#define structAllocateMatrixf(M, rows, cols) float M##data[(rows)*(cols)]; Matrixf_t M

//! Get a specific element of a matrix
float matrixGetf(const Matrixf_t* M, uint32_t row, uint32_t col);

//! Set a specific element of a matrix
void matrixSetf(Matrixf_t* M, uint32_t row, uint32_t col, float value);

//! Add a scalar to a specific element of the matrix
void matrixAddToElementf(Matrixf_t* M, uint32_t row, uint32_t col, float value);

//! Set an entire row of a matrix
void matrixSetRowf(Matrixf_t* M, uint32_t row, float value);

//! Set an entire column of a matrix
void matrixSetColumnf(Matrixf_t* M, uint32_t col, float value);

//! Allocate a matrix, initializing its memory
Matrixf_t* matrixAllocatef(uint32_t rows, uint32_t cols);

//! Change the size of a matrix
Matrixf_t* matrixChangeAllocateSizef(Matrixf_t* M, uint32_t rows, uint32_t cols, float initial);

//! Change the size of a matrix
void matrixChangeSizef(Matrixf_t* M, uint32_t rows, uint32_t cols, float initial);

//! Set all elements of a matrix to zero
void matrixZerof(Matrixf_t* M);

//! Set this matrix to be identity
void matrixSetIdentityf(Matrixf_t* M);

//! Copy a matrix
BOOL matrixCopyf(const Matrixf_t* A, Matrixf_t* B);

//! Multiply two matrices together
BOOL matrixMultiplyf(const Matrixf_t* A, const Matrixf_t* B, Matrixf_t* C);

//! Multiply the transpose of the left matrix against the right matrix
BOOL matrixMultiplyTransAf(const Matrixf_t* A, const Matrixf_t* B, Matrixf_t* C);

//! Multiply the left matrix against the transpose of the right matrix
BOOL matrixMultiplyTransBf(const Matrixf_t* A, const Matrixf_t* B, Matrixf_t* C);

//! Multiply a vector against a matrix
BOOL matrixVectorMultiplyf(const Matrixf_t* A, const Vectorf_t* B, Vectorf_t* C);

//! Multiply a vector against the transpose of a matrix
BOOL matrixVectorMultiplyTransAf(const Matrixf_t* A, const Vectorf_t* B, Vectorf_t* C);

//! Add two matrices together
BOOL matrixAddf(const Matrixf_t* A, const Matrixf_t* B, Matrixf_t* C);

//! Add two matrices together, placing the result back into the first matrix.
BOOL matrixAddEqualsf(Matrixf_t* A, const Matrixf_t* B);

//! Scale a matrix
void matrixScalef(Matrixf_t* A, float scalar);

//! Add two matrices together and multiply each element by 0.5.
BOOL matrixAveragef(const Matrixf_t* A, const Matrixf_t* B, Matrixf_t* C);

//! Add identity to a matrix
void matrixAddIdentityf(Matrixf_t* A);

//! Subtract identity from a matrix
void matrixMinusIdentityf(Matrixf_t* A);

//! Subtract a matrix from the identity matrix
void matrixIdentityMinusf(Matrixf_t* A);

//! Compute the dot product of two rows of a matrix
float matrixDotRowsf(const Matrixf_t *A, uint32_t rowA, uint32_t rowB);

//! Compute the transpose of a matrix
BOOL matrixTransposef(const Matrixf_t* A, Matrixf_t* B);

//! Calculate the inverse of a square matrix A, for dimensions 1x2, 2x2, 3x3
BOOL matrixInversef(const Matrixf_t* A, Matrixf_t* B);

//! Test a matrix for its error to identity
float testForIdentityf(const Matrixf_t* M);

//! Test a matrix for its error to null
float testForZeroMatrixf(const Matrixf_t* M);

//! Compute the transpose of a matrix, copying from Matrixf_t to Matrix_t
BOOL matrixTranspose_ftod(const Matrixf_t* A, Matrix_t* B);

//! Compute the transpose of a matrix, copying from Matrix_t to Matrixf_t
BOOL matrixTranspose_dtof(const Matrix_t* A, Matrixf_t* B);

//! Copy a matrix, copying from Matrixf_t to Matrix_t
BOOL matrixCopy_ftod(const Matrixf_t* A, Matrix_t* B);

//! Copy a matrix, copying from Matrix_t to Matrixf_t
BOOL matrixCopy_dtof(const Matrix_t* A, Matrixf_t* B);

//! Evaluate the derivative of quadratic equation at x
float quadraticDerivativeEvaluationf(const float cba[3], float x);

//! Evaluate a quadratic equation with 3 coefficients at x
float quadraticEvaluationf(const float cba[3], float x);

//! Solve a quadratic regression to determine the coefficients c, b, and a.
BOOL quadraticRegressionf(const float x[], const float y[], int num, float cba[3]);

// C++ compilers: don't mangle us
#ifdef __cplusplus
}
#endif

#endif // LINEARALGEBRA_H
