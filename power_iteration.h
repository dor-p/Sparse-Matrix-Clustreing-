/*
 * power_iteration.h
 *
 *  Created on: 1 Jul 2020
 *      Author: computer
 */

#ifndef POWER_ITERATION_H_
#define POWER_ITERATION_H_

#include "b_matrix.h"

/*
 * after running this function:
 * eigen_value = dominant eigenvalue of B
 * s_i = b_i > 0 ? 1 : -1 where b is the dominant eigenvector
 */
void power_iteration(B_matrix* B, double* eigen_value, double* s);

#endif /* POWER_ITERATION_H_ */
