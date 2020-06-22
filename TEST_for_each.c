/*
 * for_each_test.c
 *
 *  Created on: 17 Jun 2020
 *      Author: computer
 */

#include "norm_1.h"
#include "linked_list.h"
#include "matrix_row.h"
#include "spmat_lists.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

/*
int print_elem(matrix_element* elem, void *vd){
	printf("%f ", elem->value);
	*(int*)vd += 1;
	return 1;
}

int add_to_norm_t(matrix_element *elem, void *column_sums){
	double *double_sums = (double*)column_sums;
	double_sums[elem->column] += abs(elem->value);
	return 1;
}

linked_list* get_lst(int n){
	int i;
	linked_list* res;
	double tmp;
	double *val;
	val = (double*)malloc(sizeof(double));
	*val = 1.0;
	tmp = 1.0;
	res = allocate_list((void*)val);
	assert(res != NULL);


	for(i = 0; i < n; i++){
		tmp += 1.0;
		val = (double*)malloc(sizeof(double));
		*val = tmp;
		res->add(res, (void*)val);
	}

	return res;
}*


int main(){
	*
	int i, j;
	double *column_sums;
	matrix_row** mtrx;
	mtrx = (matrix_row**)malloc(5 * sizeof(matrix_row*));
	assert(mtrx != NULL);
	for(i = 0; i < 5; i++){
		mtrx[i] = allocate_row();
		for(j = 0; j < 5; j++){
			mtrx[i]->add(mtrx[i], pow(-1, (double)(i + j)) * (double)(i + j), j);
		}
	}
	column_sums = (double*)malloc(5 * sizeof(double));
	for(i = 0; i < 5; i++){
		mtrx[i]->for_each(mtrx[i], add_to_norm_t, column_sums);
	}
	printf("matrix:\n");
	for(i = 0; i < 5; i++){
		mtrx[i]->for_each(mtrx[i], print_elem, NULL);
		printf("\n");
	}
	printf("column sums:\n");
	for(i = 0; i < 5; i++){
		printf("%f ", column_sums[i]);
	}*


	return 0;
}*/
