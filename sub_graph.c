/*
 * sub_graph.c
 *
 *  Created on: 10 Aug 2020
 *      Author: computer
 */
#include "sub_graph.h"
#include "b_matrix.h"
#include <string.h>
#include <stdlib.h>


spmat_lists*  get_subA(spmat_lists* G, int* subset, int sub_size){
	spmat_lists* res;

	return res;
}


B_matrix* get_hatB_g(spmat_lists* subA, int* subset, B_matrix *B){
	B_matrix* res;
	int i, *k;
	k = (int*)malloc(subA->n * sizeof(int));
	if(k == NULL) return NULL;

	for(i = 0; i < subA->n; i++){
		k[i] = B->k[subset[i]];
	}

	res = allocate_B(subA, k, B->M);
	if(res == NULL) free(k);

	return res;
}

