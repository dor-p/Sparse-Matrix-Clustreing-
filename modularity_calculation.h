/*
 * modularity_calculation.h
 *
 *  Created on: 22 Jun 2020
 *      Author: computer
 */

#ifndef MODULARITY_CALCULATION_H_
#define MODULARITY_CALCULATION_H_

#include "spmat_lists.h"
#include "set_of_sets.h"

/*
 * function assumes that the disjoint union of O in {0,...,n - 1}
 * meaning the sets in O are mutually disjoint, and the union
 * of them all is the integers from 0 to n - 1
 * (n can be found as a field of B)
 */
double get_modularity(spmat_lists* B, set_of_sets* O);


#endif /* MODULARITY_CALCULATION_H_ */
