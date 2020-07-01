/*
 * cluster.c
 *
 *  Created on: 1 Jul 2020
 *      Author: computer
 */

#include "linked_list.h"
#include "spmat_lists.h"
#include "set_of_sets.h"
#include "b_matrix.h"
#include "norm_1.h"
#include "modularity_maximization.h"
#include "power_iteration.h"
#include "sub_graph.h"
#include "read_write_graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


#define IS_POSITIVE(X) ((X) > 0.00001)


/*
 *
 */
void swap(int* a, int* b){
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

/*
 *
 */
void parse_clusters(set_of_sets* P, set_of_sets* O, spmat_lists* A){
	int size, i, g1, g2;
	int *curr;
	double eigen_value, norm;
	double *s1, *s2;
	B_matrix* hatB;
	spmat_lists* subA;

	subA = A;
	size = A->n;
	curr = (int*)malloc(size * sizeof(int));
	s1 = (double*)malloc(size * sizeof(double));
	s2 = (double*)malloc(size * sizeof(double));

	while(size > 0){
		P->pop(P, curr);
		subA = get_subA(A, curr, size);
		hatB = allocate_B(subA);
		norm = norm_1(hatB);
		hatB->lambda = norm;
		power_iteration(hatB, &eigen_value, s1);
		hatB->lambda -= norm;
		eigen_value -= norm;
		hatB->multiply_vec(hatB, s1, s2);

		if(eigen_value <= 0.0) O->add(O, curr, size);

		else if(dot_product(s1, s2) <= 0.0) O->add(O, curr, size);

		else{
			modularity_maximization(curr, size, s1);
			g1 = 0;
			g2 = 0;
			for(i = 0; i < size; ){
				if(s1[i] > 0.0){
					g1++;
					i++;
				}
				else{
					if(i + g2 >= size) break;
					swap(curr + i, curr + size - 1 - g2);
					g2++;
				}
			}

			if(g1 * g2 == 0) O->add(O, curr, size);
			else{
				if(g1 == 1){
					O->add(O, curr, 1);
				}
				else{
					P->add(P, curr, g1);
				}
				if(g2 == 1){
					O->add(O, curr + size - 1, 1);
				}
				else{
					P->add(P, curr + size - g2, g2);
				}
			}
		}
		subA->free(subA);
		hatB->free(hatB);
		size = P->sizeof_next;
	}
	free(curr);
	free(s1);
	free(s2);
}


