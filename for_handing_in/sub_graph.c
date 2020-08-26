/*
 * sub_graph.c
 *
 *  Created on: 10 Aug 2020
 *      Author: computer
 */
#include "sub_graph.h"
#include <string.h>
#include <stdlib.h>

/* given G that represents the whole graph and a subset, 
 * returns a sparse matrix of the subgraph
 */
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
			while(curr != NULL && *(int*)curr->value < subset[j]) curr = curr->next;
			if(curr == NULL) break;
			if(*(int*)curr->value == subset[j]){
				row[j] = 1;
				curr = curr->next;
			}
		}
		res->add_row(res, row, i);
	}

	free(row);
	return res;
}

/* given a newly created B_matrix, this function 
 * computes its diagonal
 */
int modify_diagonal(B_matrix *B){
	int i, j;
	double new_d;
	Row_iterator *I;
	for(i = 0; i < B->n; i++){
		new_d = 0.0;
		I = new_iterator(B, i);
		for(j = 0; j < B->n; j++){
			new_d += I->get_next(I);
		}
		B->diagonal[i] = B->diagonal[i] - new_d;
	}
	return 1;
}

/* given a matrix A and the subset that A
 * is its sub-adjecency matrix computes k and M for B*/
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
