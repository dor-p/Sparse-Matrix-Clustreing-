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
	linked_list* curr;
	int i, j, *row;

	row = (int*)malloc(sub_size * sizeof(int));
	if(row == NULL) return NULL;

	res = spmat_lists_allocate(sub_size);
	if(res == NULL){
		free(row);
		return NULL;
	}

	for(i = 0; i < sub_size; i++){
		curr = G->rows[subset[i]];
		memset(row, 0, sub_size * sizeof(int));
		for(j = 0; j < sub_size; j++){
			row[j] = (curr != NULL && *(int*)curr->value == j) ? 1 : 0;
			if(curr == NULL) continue;
			if(*(int*)curr->value == j) curr = curr->next;
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

