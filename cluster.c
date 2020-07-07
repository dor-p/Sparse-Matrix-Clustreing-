/*
 * cluster.c
 *
 *  Created on: 1 Jul 2020
 *      Author: computer
 */

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
#include <string.h>


#define IS_POSITIVE(X) ((X) > 0.00001)


/*
 *
 */
void swap_int(int* a, int* b){
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

/*
 *
 */
void split_group(B_matrix* hatB, double *eigen_value, double *s){
	double norm;
	norm = norm_1(hatB);
	hatB->lambda = norm;
	power_iteration(hatB, eigen_value, s);
	hatB->lambda -= norm;
	eigen_value -= norm;
}

/*
 *
 */
void groups_to_res(set_of_sets* P, set_of_sets* O, double *s,
										int *group, int size){
	int g1, g2, i;

	g1 = 0;
	g2 = 0;
	for(i = 0; i < size; ){
		if(s[i] > 0.0){
			g1++;
			i++;
		}
		else{
			if(i + g2 >= size) break;
				swap_int(group + i, group + size - 1 - g2);
				g2++;
			}
		}

	if(g1 * g2 == 0) O->add(O, group, size);
	else{
		if(g1 == 1){
			O->add(O, group, 1);
		}
		else{
			P->add(P, group, g1);
		}
		if(g2 == 1){
			O->add(O, group + size - 1, 1);
		}
		else{
			P->add(P, group + size - g2, g2);
		}
	}
}

/*
 *
 */
void parse_clusters(set_of_sets* P, set_of_sets* O, spmat_lists* A){
	int size;
	int *curr;
	double eigen_value, norm;
	double *s1, *s2;
	B_matrix* hatB;
	spmat_lists* subA;

	size = A->n;
	curr = (int*)malloc(size * sizeof(int));
	s1 = (double*)malloc(size * sizeof(double));
	s2 = (double*)malloc(size * sizeof(double));

	while(size > 0){
		P->pop(P, curr);
		subA = get_subA(A, curr, size);
		hatB = allocate_B(subA);
		split_group(hatB, &eigen_value, s1);
		hatB->multiply_vec(hatB, s1, s2);

		if(eigen_value <= 0.0) O->add(O, curr, size);

		else if(dot_product(s1, s2) <= 0) O->add(O, curr, size);

		else{
			maximize_modularity(s1, hatB, s2);
			groups_to_res(P, O, s2, curr, size);
		}
		subA->free(subA);
		hatB->free(hatB);
		size = P->sizeof_next;
	}
	free(curr);
	free(s1);
	free(s2);
}


/*
 *
 */
int main(int argc, char* argv[]){

	return 0;
}
