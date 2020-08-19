/*
 * linked_list.c
 *
 *  Created on: 16 Jun 2020
 *      Author: computer
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "linked_list.h"

/*
 * we assume that the argument lst is not NULL
 */
int add_LL(linked_list *lst, void *val){
	linked_list *new_next;

	if(lst == NULL) return 0;

	new_next = allocate_list(lst->value);
	if(new_next == NULL){
		free(new_next);
		return 0;
	}

	new_next->next = lst->next;
	new_next->size = lst->size;
	lst->next = new_next;
	lst->value = val;
	lst->size = new_next->size + 1;

	return 1;
}

/*
 * note that there is more than one reason to get NULL:
 * 1. *lst == NULL
 * 2. (*lst)->value == NULL
 */
void* ecxtract_first_LL(linked_list **lst){
	void* res;
	linked_list *tmp;
	if((*lst) == NULL) return NULL;

	res = (*lst)->value;
	tmp = *lst;
	*lst = (*lst)->next;
	free(tmp);

	return res;
}

/*
 * we assume that the argument lst is not NULL
 */
void free_LL(linked_list *lst){
	free(lst->value);
	if(lst->next != NULL) free_LL(lst->next);
	lst->value = NULL;
	lst->next = NULL;
	free(lst);
}


/*
 * Allocates a new linked-lists
 */
linked_list* allocate_list(void *val){
	linked_list *res = (linked_list*)malloc(sizeof(linked_list));
	if(res == NULL){
		 free(res);
		return NULL;
	}
	res->value = val;
	res->next = NULL;
	res->size = 1;

	res->add = add_LL;
	res->ecxtract_first = ecxtract_first_LL;
	res->free = free_LL;

	return res;
}
