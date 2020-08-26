#include "power_iteration.h"

#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <time.h>


/*returns a pointer to double represnting a random vector*/
double* getRandomVector(int length)
{
        int i;
	double* vector = (double*)malloc(length * sizeof(double));
        if(vector == NULL) return NULL;
  srand(0);
	for (i = 0; i < length; ++i)
	{
		vector[i] = rand();
    while(vector[i] == 0) vector[i] = rand();
	}

	return vector;
}

/*returns the dot product between vector1 and vector 2*/
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

/*returns the euclaidian norm of vector*/
double magnitude(double* vector, int length)
{
	return sqrt(dot(vector, vector, length));
}

/*
 * finding the dominating eigen pair of mat
 * writes the sign vector of the eigen vector
 * in s and the eigen value in eigenValue
 */
int power_iteration(B_matrix *mat,double *eigenValue ,double *s){
  double *eigenVector, *matEigenVector, *eigenVector2;
  double magnitudeMatEigenVector;
  int i, ok;

  eigenVector = getRandomVector(mat->n);
  matEigenVector = (double*)malloc(mat->n * sizeof(double));
  eigenVector2 = (double*)malloc(mat->n * sizeof(double));
  if(eigenVector == NULL || matEigenVector == NULL || eigenVector2 == NULL){
    if(matEigenVector != NULL) free(matEigenVector);
    if(eigenVector != NULL) free(eigenVector);
    if(eigenVector2 != NULL) free(eigenVector);
    return 0;
  }

  ok = 1;
  while(ok){
    mat->multiply_vec(mat, eigenVector, matEigenVector);
    for(i = 0; i < mat->n; i++){
      if(matEigenVector[i]){
        ok = 0;
        break;
        }
      }
    }

  while (1)
    {
      mat->multiply_vec(mat, eigenVector, matEigenVector);
      magnitudeMatEigenVector = magnitude(matEigenVector, mat->n);
      ok = 1;
      for (i = 0; i < mat->n; ++i)
      {
        eigenVector2[i] = matEigenVector[i] / magnitudeMatEigenVector;
        if (IS_POSITIVE(fabs(eigenVector2[i] - eigenVector[i])))
        {
          ok = 0;
        }
      }

      if (ok)
      {
        *eigenValue = dot(eigenVector, matEigenVector, mat->n) / dot(eigenVector, eigenVector, mat->n);
        for(i = 0; i < mat->n; i++){
        	s[i] = IS_POSITIVE(eigenVector2[i]) ? 1.0 : -1.0;
        }
        break;
      }

      memcpy(eigenVector, eigenVector2, mat->n * sizeof(double));
    }
    free(eigenVector);
    free(eigenVector2);
    free(matEigenVector);
    return 1;
}
 

