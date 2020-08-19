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


spmat_lists*  get_subA(spmat_lists* G, const int* subset, int sub_size){
	spmat_lists* res;
	linked_list* curr;
	int i, j, *row;

	row = (int*)malloc(sub_size * sizeof(int));
	if(row == NULL) return NULL;

	res = spmat_lists_allocate(sub_size);
	if(res == NULL){
		free(row);
		return NULL;
	}
	/*
	 * Goal:
	 * we need to check for all i,j in subset, what is A[i][j]
	 * Problem: how do we do this eficiantly?
	 * We want to iterate over A once!
	 * we'll have two values to look at in every point in time:
	 * 1. curr - the next neighbor in A of i
	 * 2. j the next elemnt in subset.
	 *
	 * compare curr->value to j
	 * if curr->value = j: sub_A = 1
	 * if curr->value > j: sub_A = 0 and indent j
	 * if curr->value < j: indent curr
	 */

	for(i = 0; i < sub_size; i++){
		curr = G->rows[subset[i]];
		memset(row, 0, sub_size * sizeof(int));
		for(j = 0; j < sub_size; j++){
			if(curr == NULL) break;
			while(curr != NULL && *(int*)curr->value < subset[j]) curr = curr->next;
			if(curr != NULL && *(int*)curr->value == subset[j]){
				row[j] = 1;
				curr = curr->next;
			}
		}
		res->add_row(res, row, i);
	}

	free(row);
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
