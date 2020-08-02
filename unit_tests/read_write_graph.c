/*
 * read_write_graph.c
 *
 *  Created on: 22 Jul 2020
 *      Author: computer
 */
#include "read_write_graph.h"
#include "set_of_sets.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int read_graph(FILE* file, spmat_lists* matrix){
	int k, i, j, tmp;
	int *v, *row;

	v = (int*)malloc(matrix->n * sizeof(int));
	row = (int*)malloc(matrix->n * sizeof(int));
	if(v == NULL) return 0;

	for(i = 0; i < matrix->n; i++){

		if(!(fread(&k, sizeof(int), 1, file))){
			free(v);
			return 0;
		}

		if(!(fread(v, sizeof(int), k, file))){
			free(v);
			return 0;
		}

		tmp = 0;
		for(j = 0; j < matrix->n; j++){
			row[j] = (tmp < k && v[tmp] == j) ? 1 : 0;
			if(v[tmp] == j) tmp++;
		}

		if(!(matrix->add_row(matrix, row, i))){
			free(v);
			return 0;
		}
	}
	free(v);
	free(row);
	return 1;
}


int write_sets(FILE* file, set_of_sets* S){
	int as, i, k, N;
	int *set;
	linked_list* curr;

	N = S->N;

	if(!(fwrite(&N, sizeof(int), 1, file))) return 0;

	k = 0;
	for(curr = S->sets; curr != NULL; curr = curr->next){
		if(((int_set*)(curr->value))->size > k){
			k = ((int_set*)(curr->value))->size;
		}
	}

	set = (int*)malloc(k * sizeof(int));
	if(set == NULL) return 0;

	for(i = 0; i < N; i++){
		k = S->sizeof_next;
		as = fwrite(&k, sizeof(int), 1, file);
		if(!as){
			free(set);
			return as;
		}

		as = S->pop(S, set);
		if(!as){
			free(set);
			return as;
		}

		if(!( fwrite(set, sizeof(int), k, file) )){
			free(set);
			return as;
		}

	}
	free(set);
	return 1;
}
