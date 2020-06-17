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

int print_elem(void* elem, void *vd){
	printf("%f ", *((double*)elem));
	*(int*)vd += 1;
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
}

int main(){
	linked_list *lst;
	int num;
	lst = get_lst(5);
	/*tmp = lst->next;*/

	num = 0;
	lst->for_each(lst, print_elem, &num);
	/*while(tmp != NULL){
		printf("%f ", *((double*)(tmp->value)));
		tmp = tmp->next;
	}*/
	printf("%d", num);
	lst->free(lst);
	return 0;
}

