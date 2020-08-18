#ifndef MATRIX_FUNCTIONS_H
#define MATRIX_FUNCTIONS_H

#include "matrix.h"
#include <stdlib.h>

/* returns a random vector of size length */
double* random_vector(int length);

/* returns the magnitude of the given vector */
double magnitude(const double* vector, int length);

/* returns the dot product of the two vectors */
double dot(const double* vector1, const double* vector2, int length);

/* Sets the value at the given row and column */
int matrix_set_value(SparseMatrix mat, int row, int col, double value);

/* Gets the value at the given row and column */
double matrix_get_value(SparseMatrix *mat, int row, int col, int con);

/* returns the 1-norm of the given matrix */
double matrix_1norm(SparseMatrix *mat);

/* computes the dominant eigenpair of given matrix, eigenVector is a preallocated random vector */
int matrix_dominant_eigenpair(SparseMatrix mat, double** eigenVector, double* eigenValue);

/* computes the leading eigenpair of given matrix, eigenVector is a preallocated random vector */
int matrix_leading_eigenpair(SparseMatrix *mat, double** eigenVector, double* eigenValue);

/* Allocates a new matrix of given size */
/*SparseMatrix* matrix_allocate(int size);*/
SparseMatrix* matrix_allocate(int size);

/* Reads a matrix from the given file and creates a new matrix from it */
SparseMatrix* matrix_read(const char* filename);

/* Frees all resources used by mat */
void matrix_free(SparseMatrix* mat);

/* Multiplies mat by vector from the right (mat*vector), into result (result is pre-allocated) */
int matrix_mult_right(SparseMatrix *mat, const double* vector, double* result);

/* Multiplies mat by vector from the left (vector*mat), into result (result is pre-allocated) */
int matrix_mult_left(const double* vector, SparseMatrix *mat, double* result);

/* Converts adjacency matrix into modularity matrix */
int	matrix_to_modularity(SparseMatrix *mat);

/* Converts modularity submatrix into modified modularity submatrix */
int matrix_modify_submodularity(SparseMatrix *mat);

/* Creates a submatrix of mat with only the rows and columns corresponding to the given group of row/column indices */
SparseMatrix* matrix_submatrix(SparseMatrix *mat, const int* indices, int indicesSize);

/* Sums all the values in the given row of the matrix */
double matrix_sum_row(SparseMatrix *mat, int row);

/* Prints the matrix to the screen */
void matrix_print(SparseMatrix *mat);

#endif
