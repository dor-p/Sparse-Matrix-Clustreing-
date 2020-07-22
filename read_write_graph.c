/*
 * read_write_graph.c
 *
 *  Created on: 22 Jul 2020
 *      Author: computer
 */
#include "read_write_graph.h"
#include "set_of_sets.h"
#include <stdio.h>


int read_graph(FILE* file, spmat_lists* matrix){
	int k, i;
	int *v;

	if(!(fread(&(matrix->n), 1, file, sizeof(int)))) return 0;

	v = (int*)malloc(matrix->n * sizeof(int));
	if(v == NULL) return 0;

	for(i = 0; i < matrix->n; i++){

		if(!(fread(&k, 1, file, sizeof(int)))){
			free(v);
			return 0;
		}

		if(!(fread(v, k, file, sizeof(int)))){
			free(v);
			return 0;
		}

		if(!(matrix->add_row(matrix, v, k))){
			free(v);
			return 0;
		}
	}
	free(v);
	return 1;
}


int write_sets(FILE* file, set_of_sets* s_of_s){
	int as, i, k;
	int *set;
	linked_list* curr;

	if(!( fwrite(&(s_of_s->N), 1, file, sizeof(int)) )) return 0;

	k = 0;
	for(curr = (s_of_s->sets); curr != NULL; curr = curr->next){
		if(((int_set*)(curr->value))->size > k){
			k = ((int_set*)(curr->value))->size;
		}
	}

	set = (int*)malloc(k * sizeof(int));
	if(set == NULL) return 0;

	for(i = 0; i < s_of_s->N; i++){
		k = s_of_s->sizeof_next;
		as = fwrite(&k, 1, file, sizeof(int));
		if(!as){
			free(set);
			return as;
		}

		as = s_of_s->pop(s_of_s, set);
		if(!as){
			free(set);
			return as;
		}

		if(!( fwrite(set, k, file, sizeof(int)) )){
			free(set);
			return as;
		}

	}
	free(set);
	return 1;
}
