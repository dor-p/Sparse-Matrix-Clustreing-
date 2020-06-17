/*
 * matrix_row.c
 *
 *  Created on: 16 Jun 2020
 *      Author: computer
 */

#include "matrix_row.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>


/*
 *row can't be NULL, but row->lst can be
 */
int add_to_row(matrix_row *row, double val, int column){
	int as;
	matrix_element* new_elem = (matrix_element*)malloc(sizeof(matrix_element));
	if(new_elem == NULL) return -1;
	new_elem->value = val;
	new_elem->column = column;

	if(row->lst == NULL){
		row->lst = allocate_list((void*)new_elem); /*do we need (void*)?*/
		if(row->lst == NULL){
			free(new_elem);
			return -1;
		}
		return 1;
	}
	as = row->lst->add(row->lst, (void*)new_elem);
	if(!as){
		 free(new_elem);
		return -1;
	}

	return as;
}


/*
 * Assuming row != NULL
 */
int for_each_row(const matrix_row *row,
		int (*func)(matrix_element* , void* ), void* vd){

	return row->lst->for_each(row->lst, func, vd);
}

/*
 *
 */
void free_row(matrix_row *row){
	row->lst->free(row->lst);
	free(row);
}

/*
 *
 */
matrix_row* allocate_row(){
	matrix_row *res = (matrix_row*)malloc(sizeof(matrix_row));
	if(res == NULL){
		free(res);
		return NULL;
	}
	res->lst = NULL;
	res->add = add_to_row;
	res->for_each = for_each_row;
	res->free = free_row;
	return res;
}

