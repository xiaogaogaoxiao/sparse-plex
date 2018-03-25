/**
Wrapper for BLAS functions

This code is derived from OMPBOX.
Hand coded C routines have been replaced
in many cases with implementations from
BLAS and LAPACK.

Some conventions:
- input arguments are marked with const
- output arguments are non-const
- array values are returned  through output arguments
- scalar values are returned through return values.
- input arrays come first.
- output arrays follow.
- scalars describing dimensions etc. come last.

*/

#ifndef _SPX_BLAS_H_
#define _SPX_BLAS_H_ 1

#include <math.h>
#include "mex.h"

/**
Square of a value
*/
#define SQR(x) ((x) * (x))

/********************************************
* One vector operations
*
*********************************************/

/**
Returns the index of the maximum absolute value in the array
*/
mwIndex abs_max_index(const double x[], mwSize n);



/**
Returns the index of the maximum value in the array
*/
mwIndex max_index(const double x[], mwSize n);

/**
Extracts a vector y = x(indices)
*/
void vec_extract(const double x[], 
    const mwIndex indices[], double y[], mwSize k);

/**
Set same value to all entries in vector
*/
void vec_set_value(double x[], double value, mwSize n);

/********************************************
* One matrix operations
*
*********************************************/

/**
Computes the transpose
Y = X'
*/
void mat_transpose(const double X[], double Y[], mwSize m, mwSize n);


/********************************************
* Vector vector operations
*
*********************************************/

/**
Computes 
y = alpha * x + y 
*/
void sum_vec_vec(double alpha, const double x[], double y[], mwSize n);

/***
Copies a vector y = x
*/
void copy_vec_vec(const double x[], double y[], mwSize n);


/**
Computes inner product of two vectors
*/
double inner_product(const double a[], const double b[], mwSize n);


/********************************************
* Matrix vector operations
*
*********************************************/

/***
Compute y = alpha * A * x
*/
void mult_mat_vec(double alpha, 
    const double A[], 
    const double x[], 
    double y[], mwSize m, mwSize n);

/***
Compute y = alpha * A' * x
*/
void mult_mat_t_vec(double alpha, 
    const double A[], 
    const double x[], 
    double y[], mwSize m, mwSize n);

/***
Compute y = alpha * A * x where x is sparse array
*/
void mult_mat_vec_sp(double alpha, 
    const double A[], 
    const double pr[], const mwIndex ir[], const mwIndex jc[],
    double y[], mwSize m, mwSize n);




/**
Solves a lower triangular system via back substitution

L x  = b

where L is lower triangular.

L can be of a size m x n where 
m is the number of rows and n
is the number of columns.

k is the number of equations to solve.
We require that k <= m, n

Only the  lower triangle of the submatrix L(1:k, 1:k) is used 
for solving the problem.

*/
void lt_back_substitution(const double L[], 
    const double b[], 
    double x[], 
    mwSize m, mwSize k);

/**
Solves an upper triangular system via back substitution

U x  = b

where U is upper triangular.

U can be of a size m x n where 
m is the number of rows and n
is the number of columns.

k is the number of equations to solve.
We require that k <= m, n

Only the upper triangle of the submatrix U(1:k, 1:k) is used 
for solving the problem.

*/
void ut_back_substitution(const double U[], 
    const double b[], 
    double x[], 
    mwSize m, mwSize k);

/**
Solves an upper triangular system via back substitution

L' x  = b

where L is lower triangular.

L can be of a size m x n where 
m is the number of rows and n
is the number of columns.

k is the number of equations to solve.
We require that k <= m, n

Only the upper triangle of the submatrix L'(1:k, 1:k) is used 
for solving the problem.

*/
void lt_t_back_substitution(const double L[], 
    const double b[], 
    double x[], 
    mwSize m, mwSize k);


/**
Solves the linear system 
A x = b

where A is a symmetric positive definite matrix
with the decomposition
A = L L' where L is a lower triangular matrix.

L can be of a size m x n where 
m is the number of rows and n
is the number of columns.

k is the number of equations to solve.
We require that k <= m, n

Only the  lower triangle of the submatrix L(1:k, 1:k) is used 
for solving the problem.
*/
void spd_chol_lt_solve(const double L[], 
    const double b[], 
    double x[], 
    mwSize m, mwSize k);


/********************************************
* Matrix matrix operations
*
*********************************************/





/** 
Matrix matrix multiplication 

Compute X = alpha * A * B

A is m x k,  B is k x n
*/
void mult_mat_mat(double alpha, 
    const double A[], 
    const double B[], 
    double X[], 
    mwSize m, mwSize n, mwSize k);

/** 
Matrix transpose matrix multiplication 

Compute X = alpha * A' * B

A' is m x k,  B is k x n
A is k x m
*/
void mult_mat_t_mat(double alpha, 
    const double A[], 
    const double B[], 
    double X[], 
    mwSize m, mwSize n, mwSize k);






/********************************************
* Debugging functions
*
*********************************************/


/**
Prints the contents of a matrix
*/
void print_matrix(const double A[], int m, int n, char* matrix_name);

/**
Prints the contents of a vector
*/
void print_vector(const double v_x[], int n, char* vec_name);


/**
Prints the contents of a sparse vector
*/
void print_sparse_vector(const mxArray *A, char* vector_name);


#endif 

