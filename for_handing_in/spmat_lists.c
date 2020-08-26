/*
 * spmat_lists.c
 *
 *  Created on: 18 Jun 2020
 *      Author: computer
 */

#include "spmat_lists.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

/*
 * adding a row to A
 * row is a binary vector so that
 * A[i][j] = row[j] != 0 ? j : 0;
 */
int add_row_linked_lists(spmat_lists *A, const int *row, int i){
	int j, as;
	int* tmp;
	j = A->n - 1;
	while(j >= 0 && row[j] == 0) j--;
	if(j < 0) return 1;
	tmp = (int*)malloc(sizeof(int));
	if(tmp == NULL){
		A->rows[i]->free(A->rows[i]);
		return 0;
	}
	*tmp = j;
	A->rows[i] = allocate_list(tmp);
	for(j -= 1; j >= 0; j--){
		if(row[j] != 0){
			tmp = (int*)malloc(sizeof(int));
			if(tmp == NULL){
				A->rows[i]->free(A->rows[i]);
				return 0;
			}
			*tmp = j;
			as = A->rows[i]->add(A->rows[i], tmp);
			if(!as) return as;
		}
	}
	return 1;
}

/*
 * free all resources allocated to A
 */
void free_spmat_lists(spmat_lists *A){
	int i;
	for(i = 0; i < A->n; i++){
		if(A->rows[i] != NULL) A->rows[i]->free(A->rows[i]);
	}
	free(A->rows);
	free(A);
}

/*
 * allocate new empty sparse matrix of size n * n 
 */
spmat_lists*  spmat_lists_allocate(int n){
	spmat_lists* res;
	res = (spmat_lists*)malloc(sizeof(spmat_lists));
	if(res == NULL){
		free(res);
		return NULL;
	}

	res->rows = (linked_list**)calloc(n, sizeof(linked_list*));
	if(res->rows == NULL){
		free(res->rows);
		free(res);
		return NULL;
	}

	res->n = n;
	res->add_row = add_row_linked_lists;
	res->free = free_spmat_lists;

	return res;
}
