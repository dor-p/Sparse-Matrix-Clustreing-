
#include "matrix_functions.h"
#include "linked_list.h"
#include "spmat_lists.h"
#include "read_write_graph.h"
#include "sub_graph.h"


#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

#define EPS 0.00001

void print_graph(spmat_lists *A){
  int i;
  linked_list *curr;

  for(i = 0; i < A->n; i++){
    curr = A->rows[i];
    while(curr != NULL){
      printf("%d ", *(int*)curr->value);
      curr = curr->next;
    }
    printf("\n");
  }
}



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

/***
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

	* element present *
	if (currentRowNode != NULL && currentRowNode->column == col)
	{
		* set value of element *
		if (value != 0.0)
		{
			currentRowNode->value = value;
		}
		* erase element *
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
	* element not present, insert it *
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
}***/

double matrix_get_value(SparseMatrix *mat, int row, int col, int val)
{
	if(row == col) return mat->diagonal[row] + mat->lambda;
	return (val ? 1.0 : 0.0) - (double)(mat->k[row] * mat->k[col]) / (double)mat->M;
}

double get_next_b(Row_iterator *I){
  int con;
  double res;
  con = (I->curr != NULL) && I->col == *(int*)I->curr->value;
  res = (I->B)->to_value(I->B, I->row, I->col, con);
  I->col = I->col + 1;
  if(con) I->curr = I->curr->next;
  if(I->col >= I->length){
    free(I);
  }
  return res;
}

Row_iterator* new_iterator(SparseMatrix *B, int row){
  Row_iterator* res;

  res = (Row_iterator*)malloc(sizeof(Row_iterator));
  if(res == NULL) return NULL;

  res->curr = B->A->rows[row];
  res->length = B->n;
  res->row = row;
  res->col = 0;
  res->B = B;
  res->get_next = get_next_b;

  return res;

}

double matrix_1norm(SparseMatrix* mat)
{
	int row, col;
	Row_iterator *I;
	double *sums;
	double largestSum = 0.0;

  sums = (double*)calloc(mat->n, sizeof(double));
  if(sums == NULL) return -1.0;

	for (row = 0; row < mat->n; ++row)
	{
    I = new_iterator(mat, row);
    if(I == NULL){
      free(sums);
      return -1.0;
    }

		for (col = 0; col < mat->n; ++col)
		{
			sums[col] += fabs(I->get_next(I));
		}
	}

  for (col = 0; col < mat->n; ++col)
		{
			if(sums[col] > largestSum) largestSum = sums[col];
		}
	return largestSum;
}

int matrix_dominant_eigenpair(SparseMatrix mat, double** eigenVector, double* eigenValue)
{
	double* eigenVector2;
	double* matEigenVector;
	double magnitudeMatEigenVector;
	int i, iter;
	int ok;

	/*print_graph(mat.A);*/
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
	iter = 0;
	while (1)
	{
		iter++;
		matrix_mult_right(&mat, *eigenVector, matEigenVector);
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

int matrix_leading_eigenpair(SparseMatrix* mat, double** eigenVector, double* eigenValue)
{
  double norm;
  norm = matrix_1norm(mat);
  mat->lambda += norm;
  if(!matrix_dominant_eigenpair(*mat, eigenVector, eigenValue)) return 0;
  mat->lambda -= norm;
  *eigenValue = *eigenValue - norm;
	return 1;
}



SparseMatrix* matrix_read(const char* filename)
{
	FILE* file;
	SparseMatrix *mat;
	int as, n, i;

	file = fopen(filename, "r");
	if (file == NULL)
	{
		printf("Error: cannot open file %s!\n", filename);
		return NULL;
	}

	as = fread(&n, sizeof(int), 1, file);
	if (as != 1)
	{
		printf("Error: problem while reading from file %s!\n", filename);
		fclose(file);
		return NULL;
	}

	mat = matrix_allocate(n);
	if (mat == NULL)
	{
		printf("Error: couldn't allocate memory!\n");
		fclose(file);
		return NULL;
	}
  
  as = read_graph(file, mat->A);
  if (as != 1)
		{
			printf("Error: problem while writing from file to mat.A %s!\n", filename);
			fclose(file);
      matrix_free(mat);
			return NULL;
		}

  mat->M = 0;
  for(i = 0; i < n; i++){
    mat->k[i] = mat->A->rows[i]->size;
    mat->M += mat->k[i];
  }

	fclose(file);

	return mat;
}

void matrix_free(SparseMatrix* mat)
{
  if(mat == NULL) return;
  
  if(mat->A != NULL) mat->A->free(mat->A);
  if(mat->k != NULL) free(mat->k);
  if(mat->diagonal != NULL) free(mat->diagonal);
  free(mat);
/*
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
	mat->k = NULL;*/
}

int matrix_mult_right(SparseMatrix *mat, const double* vector, double* result)
{
	int row, j;
  Row_iterator *I;

	for (row = 0; row < mat->n; ++row)
	{
		result[row] = 0.0;
    I = new_iterator(mat, row);
    if(I == NULL) return 0;
    while(I->col < mat->n){
    	j = I->col;
    	result[row] += I->get_next(I) * vector[j];
    }
	}
  
  return 1;
}

int matrix_mult_left(const double* vector, SparseMatrix *mat, double* result)
{
  int row;
  Row_iterator *I;

  memset(result, 0, mat->n * sizeof(double));
	for (row = 0; row < mat->n; ++row)
	{
		I = new_iterator(mat, row);
		if(I == NULL) return 0;
		while(I->col < mat->n){
			result[I->col] += I->get_next(I) * vector[row];
		}
	}
  return 1;
}

/*
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
    curr = B->A->rows[i];
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
}*/

int matrix_modify_submodularity(SparseMatrix* mat)
{
	int row;

  mat->M = 0;
  
  for(row = 0; row < mat->n; row++){
	  mat->k[row] = (mat->A->rows[row] != NULL) ? mat->A->rows[row]->size : 0;
	  mat->M += mat->k[row];
  }
 
	for (row = 0; row < mat->n; ++row)
	{
		mat->diagonal[row] = matrix_sum_row(mat, row);
	}

	return 0;
}

SparseMatrix* matrix_submatrix(SparseMatrix* mat, const int* indices, int indicesSize)
{
	SparseMatrix *result;

	result = matrix_allocate(indicesSize);
	if (result == NULL)
	{
		printf("Error: couldn't allocate memory!\n");
		return result;
	}

  result->A = get_subA(mat->A, indices, indicesSize);
  matrix_modify_submodularity(result);

	return result;
}

SparseMatrix* matrix_allocate(int size)
{
	SparseMatrix* mat;

  mat = (SparseMatrix*)malloc(sizeof(SparseMatrix));
  if(mat == NULL) return NULL;

	mat->A = spmat_lists_allocate(size);
  mat->n = size;
	mat->M = 0;
	mat->k = (int*)malloc(size * sizeof(int));
  mat->diagonal = (double*)calloc(size, sizeof(double));
  mat->lambda = 0.0;
  mat->to_value = matrix_get_value;
	if (mat->A == NULL || mat->k == NULL || mat->diagonal == NULL)
	{
		printf("Error: couldn't allocate memory!\n");
    if(mat->A != NULL) mat->A->free(mat->A);
    if(mat->k != NULL) free(mat->k);
    if(mat->diagonal != NULL) free(mat->diagonal);
    free(mat);
		return NULL;
	}


  /*
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
	for (col = 0; col < size; ++col)
	{
		mat.cols[col] = NULL;
	}*/

	return mat;
}

double matrix_sum_row(SparseMatrix *mat, int row)
{
	double sum = 0.0;
	Row_iterator *I;
  if(row == 15) printf("15");
  I = new_iterator(mat, row);
  if(I == NULL) printf("???");

	for (; I->col < mat->n;)
	{
		sum += I->get_next(I);
	}

	return sum;
}

void matrix_print(SparseMatrix* mat)
{
	int row;
  Row_iterator *I;

	for (row = 0; row < mat->n; ++row)
	{
    I = new_iterator(mat, row);
		for (; I->col < mat->n;)
		{
			printf("%1.1f ", I->get_next(I));
		}
		printf("\n");
	}
}
