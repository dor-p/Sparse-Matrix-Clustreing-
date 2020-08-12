#include "power_iteration.h"

#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdio.h>


double* getRandomVector(int length)
{
        int i;
	double* vector = (double*)malloc(length * sizeof(double));
        assert(vector != NULL);
	for (i = 0; i < length; ++i)
	{
		vector[i] = rand();
	}

	return vector;
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

double magnitude(double* vector, int length)
{
	return sqrt(dot(vector, vector, length));
}

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

   while (1)
    {
      multiply_vec(mat, eigenVector, matEigenVector);
      magnitudeMatEigenVector = magnitude(matEigenVector, mat->n);
      ok = 1;
      for (i = 0; i < mat.n; ++i)
      {
        eigenVector2[i] = matEigenVector[i] / magnitudeMatEigenVector;
        if (IS_POSITIVE(fabs(eigenVector2[i] - eigenVector[i])))
        {
          ok = 0;
        }
      }

      if (ok)
      {
        *eigenValue = dot(eigenVector2, eigenVector, mat->n) / dot(eigenVector, eigenVector, mat->n);
        memcpy(s, eigenVector2, mat->n * sizeof(double));
        break;
      }

      memcpy(eigenVector, eigenVector2, mat->n * sizeof(double));
    }
    free(eigenVector);
    free(eigenVector2);
    free(matEigenVector);
    return 1;
}
 

