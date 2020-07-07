/*
 * modularity_maximization.h
 *
 *  Created on: 22 Jun 2020
 *      Author: computer
 */

#ifndef MODULARITY_MAXIMIZATION_H_
#define MODULARITY_MAXIMIZATION_H_

#include "set_of_sets.h"
#include "b_matrix.h"

/*
 *
 */
void maximize_modularity(int* s, B_matrix* hatB, int* target);

#endif /* MODULARITY_MAXIMIZATION_H_ */
