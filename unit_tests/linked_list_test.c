/*
 * linked_list_test.c
 *
 *  Created on: 24 Jul 2020
 *      Author: computer
 */

#include "linked_list.h"
#include <stdio.h>
#include <string.h>
#include "helper_functions.c"

/*
 * return a list containing: n + 1, n,..., 1
 * in int
 */
linked_list* get_lst_int(int n){
	int i;
	linked_list* res;
	int tmp;
	int *val;
	val = (int*)malloc(sizeof(int));
	*val = 1;
	tmp = 1;
	res = allocate_list((void*)val);
	assert(res != NULL);


	for(i = 0; i < n; i++){
		tmp += 1;
		val = (int*)malloc(sizeof(int));
		*val = tmp;
		res->add(res, (void*)val);
	}

	return res;
}


/*
 * return a list containing: n + 1, n,..., 1
 * in doubles
 */
linked_list* get_lst_double(int n){
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

/*
 * prints the elements of the list in order
 * types: 1 - int, 2 - double, 3 - char, 4 - string
 */
void print_list(linked_list* lst, short value_type){
	printf("%d\n", lst->size);
	while(lst != NULL){
		switch(value_type){
		case 1 :
			printf("%d, ", *(int*)(lst->value));
			break;

		case 2:
			printf("%f, ", *(double*)(lst->value));
			break;

		case 3:
			printf("%c, ", *(char*)(lst->value));
			break;

		case 4:
			printf("%s, ", *(char**)(lst->value));
			break;

		default :
			printf("value type must be one of: 1, 2, 3, 4\n");
			return;
		}
		lst = lst->next;
	}
	printf("\n");
}
/*
int main(int argc, char* argv[]){
	linked_list* lst = get_lst_int(string_to_int(argv[1]));
	assert(argc > 1);
	print_list(lst, 1);
	lst->free(lst);
	return 0;
}*/
