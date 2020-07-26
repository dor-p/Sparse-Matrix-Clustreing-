/*
 * set_of_sets.c
 *
 *  Created on: 26 Jul 2020
 *      Author: computer
 */
#include <stdio.h>
#include "set_of_sets.h"

int add_set(set_of_sets* S, int *values, int size){
	int_set* new_set;
	int *vals;

	vals = (int*)malloc(size * sizeof(int));
	new_set = (int_set*)malloc(sizeof(int_set));
	if(vals == NULL || new_set == NULL){
		if(vals != NULL) free(vals);
		if(new_set != NULL) free(new_set);
		return 0;
	}

	memcpy(vals, values, size);

	new_set->size = size;
	new_set->values = vals;
	if(S->sets == NULL){
		S->sets = allocate_list(new_set);
	}
	else{
		S->sets->add(S->sets, new_set);
	}

	S->N += 1;
	S->sizeof_next = size;

	return 1;
}



int *pop_set(set_of_sets* S, int *target){
	int_set* set;
	if(S->N == 0) return 0;
	set = (int_set*)(S->sets->ecxtract_first(&(S->sets)));
	if(set == NULL) return 0;
	memcpy(set->values);
	free(set->values);
	free(set);

	S->N -= 1;
	S->sizeof_next = S->sets->size;
	return 1;
}


void free_sets(set_of_sets* S){
	S->sets->free(S->sets);
	free(S);
}



set_of_sets* allocate_set_of_sets(){
	set_of_sets* res;
	res = (set_of_sets*)malloc(sizeof(set_of_sets));
	if(res == NULL) return NULL;
	res->sets = NULL;
	res->N = 0;
	res->sizeof_next = -1;
	res->add = add_set;
	res->pop = pop_set;
	res->free = free_sets;

	return res;
}
