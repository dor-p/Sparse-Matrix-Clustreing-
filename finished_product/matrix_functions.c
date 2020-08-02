#include "matrix_functions.h"

#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

#define EPS 0.00001

double* random_vector(int length)
{
	int i;
	double* vector = (double*)malloc(length * sizeof(double));
	if (vector == NULL)
	{
		printf("Error: couldn't allocate memory!\n");
		return NULL;
	}
	for (i = 0; i < length; ++i)
	{
		vector[i] = rand();
	}

	return vector;
}

double magnitude(const double* vector, int length)
{
	double sum = 0.0;
	int i;
	for (i = 0; i < length; ++i)
	{
		sum += vector[i] * vector[i];
	}

	return sqrt(sum);
}

double dot(const double* vector1, const double* vector2, int length)
{
	double result = 0;
	int i;
	for (i = 0; i < length; ++i)
	{
		result += vector1[i] * vector2[i];
	}
	return result;
}

int matrix_set_value(SparseMatrix mat, int row, int col, double value)
{
	Node* previousRowNode = NULL;
	Node* currentRowNode = mat.rows[row];
	Node* previousColNode = NULL;
	Node* currentColNode = mat.cols[col];
	Node* newNode = NULL;

	while (currentRowNode != NULL && currentRowNode->column < col)
	{
		previousRowNode = currentRowNode;
		currentRowNode = currentRowNode->right;
	}

	/* element present */
	if (currentRowNode != NULL && currentRowNode->column == col)
	{
		/* set value of element */
		if (value != 0.0)
		{
			currentRowNode->value = value;
		}
		/* erase element */
		else
		{
			while (currentColNode != NULL && currentColNode->row < row)
			{
				previousColNode = currentColNode;
				currentColNode = currentColNode->down;
			}

			if (previousRowNode != NULL)
			{
				previousRowNode->right = currentRowNode->right;
			}

			if (previousColNode != NULL)
			{
				previousColNode->down = currentColNode->down;
			}

			free(currentRowNode);
		}
	}
	/* element not present, insert it */
	else if (value != 0.0)
	{
		newNode = (Node*)malloc(sizeof(Node));
		if (newNode == NULL)
		{
			return -1;
		}
		newNode->value = value;
		newNode->row = row;
		newNode->column = col;

		while (currentColNode != NULL && currentColNode->row < row)
		{
			previousColNode = currentColNode;
			currentColNode = currentColNode->down;
		}

		if (previousRowNode != NULL)
		{
			previousRowNode->right = newNode;
		}
		else
		{
			mat.rows[row] = newNode;
		}

		if (previousColNode != NULL)
		{
			previousColNode->down = newNode;
		}
		else
		{
			mat.cols[col] = newNode;
		}

		newNode->right = currentRowNode;
		newNode->down = currentColNode;
	}

	return 0;
}

double matrix_get_value(SparseMatrix mat, int row, int col)
{
	Node* currentRowNode = mat.rows[row];

	while (currentRowNode != NULL && currentRowNode->column < col)
	{
		currentRowNode = currentRowNode->right;
	}

	/* element present */
	if (currentRowNode != NULL && currentRowNode->column == col)
	{
		/* return value of element */
		return currentRowNode->value;
	}
	/* element not present, return 0 */
	else
	{
		return 0.0;
	}
}

double matrix_1norm(SparseMatrix mat)
{
	int row;
	int col;
	double sum;
	double largestSum = 0.0;

	for (col = 0; col < mat.n; ++col)
	{
		sum = 0.0;
		for (row = 0; row < mat.n; ++row)
		{
			sum += fabs(matrix_get_value(mat, row, col));
		}
		if (sum > largestSum)
		{
			largestSum = sum;
		}
	}
	return largestSum;
}

int matrix_dominant_eigenpair(SparseMatrix mat, double** eigenVector, double* eigenValue)
{
	double* eigenVector2;
	double* matEigenVector;
	double magnitudeMatEigenVector;
	int i;
	int ok;

	matEigenVector = (double*)malloc(mat.n * sizeof(double));
	if (matEigenVector == NULL)
	{
		printf("Error: couldn't allocate memory!\n");
		return -1;
	}
	eigenVector2 = (double*)malloc(mat.n * sizeof(double));
	if (eigenVector2 == NULL)
	{
		printf("Error: couldn't allocate memory!\n");
		free(matEigenVector);
		return -1;
	}

	while (1)
	{
		matrix_mult_right(mat, *eigenVector, matEigenVector);
		magnitudeMatEigenVector = magnitude(matEigenVector, mat.n);
		ok = 1;
		for (i = 0; i < mat.n; ++i)
		{
			eigenVector2[i] = matEigenVector[i] / magnitudeMatEigenVector;
			if (fabs(eigenVector2[i] - (*eigenVector)[i]) >= EPS)
			{
				ok = 0;
			}
		}

		if (ok)
		{
			*eigenValue = dot(eigenVector2, *eigenVector, mat.n) / dot(*eigenVector, *eigenVector, mat.n);
			memcpy(*eigenVector, eigenVector2, mat.n * sizeof(double));
			break;
		}

		memcpy(*eigenVector, eigenVector2, mat.n * sizeof(double));
	}

	free(matEigenVector);
	free(eigenVector2);

	return 0;
}

int matrix_leading_eigenpair(SparseMatrix mat, double** eigenVector, double* eigenValue)
{
	SparseMatrix mat2;
	double norm;
	int row, col;

	norm = matrix_1norm(mat);

	mat2 = matrix_allocate(mat.n);
	if (mat2.n == 0)
	{
		return -1;
	}

	for (row = 0; row < mat.n; ++row)
	{
		for (col = 0; col < mat.n; ++col)
		{
			if (row == col)
			{
				if (matrix_set_value(mat2, row, col, matrix_get_value(mat, row, col) + norm) == -1)
				{
					printf("Error: couldn't allocate memory!\n");
					matrix_free(&mat2);
					return -1;
				}
			}
			else
			{
				if (matrix_set_value(mat2, row, col, matrix_get_value(mat, row, col)) == -1)
				{
					printf("Error: couldn't allocate memory!\n");
					matrix_free(&mat2);
					return -1;
				}
			}
		}
	}

	if (matrix_dominant_eigenpair(mat2, eigenVector, eigenValue) == -1)
	{
		matrix_free(&mat2);
		return -1;
	}

	matrix_free(&mat2);

	return 0;
}

SparseMatrix matrix_allocate(int size)
{
	SparseMatrix mat;
	int row, col, i;

	mat.n = size;
	mat.M = 0;
	mat.k = (int*)malloc(size * sizeof(int));
	if (mat.k == NULL)
	{
		printf("Error: couldn't allocate memory!\n");
		mat.n = 0;
		mat.M = 0;
		mat.k = NULL;
		mat.rows = NULL;
		mat.cols = NULL;
		return mat;
	}
	for (i = 0; i < size; ++i)
	{
		mat.k[i] = 0;
	}
	mat.rows = (Node**)malloc(size * sizeof(Node*));
	if (mat.rows == NULL)
	{
		printf("Error: couldn't allocate memory!\n");
		free(mat.k);
		mat.n = 0;
		mat.M = 0;
		mat.k = NULL;
		mat.rows = NULL;
		mat.cols = NULL;
		return mat;
	}
	mat.cols = (Node**)malloc(size * sizeof(Node*));
	if (mat.cols == NULL)
	{
		printf("Error: couldn't allocate memory!\n");
		free(mat.rows);
		free(mat.k);
		mat.n = 0;
		mat.M = 0;
		mat.k = NULL;
		mat.rows = NULL;
		mat.cols = NULL;
		return mat;
	}
	for (row = 0; row < size; ++row)
	{
		mat.rows[row] = NULL;
	}
	for (col = 0; col < size; ++col)
	{
		mat.cols[col] = NULL;
	}

	return mat;
}

SparseMatrix matrix_read(const char* filename)
{
	FILE* file;
	SparseMatrix mat;
	int value;
	int as;
	int row;
	int n;
	int k;
	int i;

	file = fopen(filename, "r");
	if (file == NULL)
	{
		printf("Error: cannot open file %s!\n", filename);
		return mat;
	}

	as = fread(&n, sizeof(int), 1, file);
	if (as != 1)
	{
		printf("Error: problem while reading from file %s!\n", filename);
		fclose(file);
		return mat;
	}

	mat = matrix_allocate(n);
	if (mat.n == 0 && n != 0)
	{
		printf("Error: couldn't allocate memory!\n");
		fclose(file);
		return mat;
	}

	for (row = 0; row < n; ++row)
	{
		as = fread(&k, sizeof(int), 1, file);
		if (as != 1)
		{
			printf("Error: problem while reading from file %s!\n", filename);
			matrix_free(&mat);
			fclose(file);
			return mat;
		}
		mat.k[row] = k;
		mat.M += k;

		for (i = 0; i < k; ++i)
		{
			as = fread(&value, sizeof(int), 1, file);
			if (as != 1)
			{
				printf("Error: problem while reading from file %s!\n", filename);
				matrix_free(&mat);
				fclose(file);
				return mat;
			}

			if (matrix_set_value(mat, row, value, 1.0) == -1)
			{
				printf("Error: couldn't allocate memory!\n");
				matrix_free(&mat);
				fclose(file);
				return mat;
			}
		}
	}

	fclose(file);

	return mat;
}

void matrix_free(SparseMatrix* mat)
{
	Node* currentNode = NULL;
	Node* tempNode = NULL;
	int row;

	for (row = 0; row < mat->n; ++row)
	{
		currentNode = mat->rows[row];
		while (currentNode != NULL)
		{
			tempNode = currentNode->right;
			free(currentNode);
			currentNode = tempNode;
		}
	}

	free(mat->rows);
	free(mat->cols);
	free(mat->k);

	mat->rows = NULL;
	mat->cols = NULL;
	mat->n = 0;
	mat->M = 0;
	mat->k = NULL;
}

void matrix_mult_right(SparseMatrix mat, const double* vector, double* result)
{
	int row;
	int col;

	for (row = 0; row < mat.n; ++row)
	{
		result[row] = 0.0;
		for (col = 0; col < mat.n; ++col)
		{
			result[row] += matrix_get_value(mat, row, col) * vector[col];
		}
	}
}

void matrix_mult_left(const double* vector, SparseMatrix mat, double* result)
{
	int row;
	int col;

	for (col = 0; col < mat.n; ++col)
	{
		result[col] = 0.0;
		for (row = 0; row < mat.n; ++row)
		{
			result[col] += matrix_get_value(mat, row, col) * vector[row];
		}
	}
}

int matrix_to_modularity(SparseMatrix mat)
{
	int row;
	int col;
	double v;

	if (mat.M == 0)
	{
		printf("Error: division by zero!\n");
		return -1;
	}

	for (row = 0; row < mat.n; ++row)
	{
		for (col = 0; col < mat.n; ++col)
		{
			v = (double)(mat.k[row] * mat.k[col]) / (double)mat.M;
			if (matrix_set_value(mat, row, col, matrix_get_value(mat, row, col) - v) == -1)
			{
				printf("Error: couldn't allocate memory!\n");
				return -1;
			}
		}
	}

	return 0;
}

int matrix_modify_submodularity(SparseMatrix mat)
{
	int row;
	double rowSum;

	for (row = 0; row < mat.n; ++row)
	{
		rowSum = matrix_sum_row(mat, row);
		if (matrix_set_value(mat, row, row, matrix_get_value(mat, row, row) - rowSum) == -1)
		{
			printf("Error: couldn't allocate memory!\n");
			return -1;
		}
	}

	return 0;
}

SparseMatrix matrix_submatrix(SparseMatrix mat, const int* indices, int indicesSize)
{
	SparseMatrix result;
	int row;
	int col;
	int rowSub = 0;
	int colSub = 0;
	int i;
	int found;
	double v;

	result = matrix_allocate(indicesSize);
	if (result.n == 0)
	{
		printf("Error: couldn't allocate memory!\n");
		return result;
	}

	result.k[0] = 0;
	for (row = 0; row < mat.n; ++row)
	{
		found = 0;
		for (i = 0; i < indicesSize; ++i)
		{
			if (indices[i] == row)
			{
				found = 1;
				break;
			}
			else if (indices[i] > row)
			{
				break;
			}
		}
		if (!found)
		{
			continue;
		}
		for (col = 0; col < mat.n; ++col)
		{
			found = 0;
			for (i = 0; i < indicesSize; ++i)
			{
				if (indices[i] == col)
				{
					found = 1;
					break;
				}
				else if (indices[i] > col)
				{
					break;
				}
			}
			if (found)
			{
				v = matrix_get_value(mat, row, col);
				if (matrix_set_value(result, rowSub, colSub, v) == -1)
				{
					printf("Error: couldn't allocate memory!\n");
					matrix_free(&result);
					return result;
				}
				result.k[rowSub] += v;
				result.M += v;
				colSub++;
				if (colSub >= indicesSize)
				{
					rowSub++;
					if (rowSub < indicesSize) result.k[rowSub] = 0;
					colSub = 0;
				}
			}
		}
	}

	return result;
}

double matrix_sum_row(SparseMatrix mat, int row)
{
	double sum = 0.0;
	int col;

	for (col = 0; col < mat.n; ++col)
	{
		sum += matrix_get_value(mat, row, col);
	}

	return sum;
}

void matrix_print(SparseMatrix mat)
{
	int row;
	int col;

	for (row = 0; row < mat.n; ++row)
	{
		for (col = 0; col < mat.n; ++col)
		{
			printf("%1.1f ", matrix_get_value(mat, row, col));
		}
		printf("\n");
	}
}
