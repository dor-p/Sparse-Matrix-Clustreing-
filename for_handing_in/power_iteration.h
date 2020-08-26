/*
 * power_iteration.h
 *
 *  Created on: 1 Jul 2020
 *      Author: computer
 */

#ifndef POWER_ITERATION_H_
#define POWER_ITERATION_H_

#ifndef IS_POSITIVE
#define IS_POSITIVE(X) ((X) > 0.00001)
#endif /* IS_POSITIVE */

#include "b_matrix.h"

/*
 * after running this function:
 * eigen_value = dominant eigenvalue of B
 * s[i] = IS_POSITIVE(b[i]) ? 1 : -1; where b is the dominant eigenvector
 */
int power_iteration(B_matrix* B, double* eigen_value, double* s);

#endif /* POWER_ITERATION_H_ */
