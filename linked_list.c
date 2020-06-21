/*
 * linked_list.c
 *
 *  Created on: 16 Jun 2020
 *      Author: computer
 */

#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

/*
 * we assume that the argument lst is not NULL
 */
int add_LL(linked_list *lst, void *val){

	linked_list *new_next = (linked_list*)malloc(sizeof(linked_list));
	new_next->value = malloc(sizeof(void));
	new_next->next = (linked_list*)malloc(sizeof(linked_list));
	if(new_next == NULL || new_next->value == NULL || new_next->next == NULL){
		free(new_next);
		free(new_next->value);
		free(new_next->next);
		return 0;
	}

	new_next->value = lst->value;
	new_next->next = lst->next;
	lst->next = new_next;
	lst->value = val;

	return 1;
}

/*
 * note that there is more than one reason to get NULL:
 * 1. *lst == NULL
 * 2. (*lst)->value == NULL
 */
void* ecxtract_first(linked_list **lst){
	void* res;
	linked_list *tmp;
	if((*lst) == NULL) return NULL;

	res = (*lst)->value;
	tmp = *lst;
	*lst = (*lst)->next;
	free(tmp->next);
	free(tmp->value);
	return res;
}

/*
 * we assume that the argument lst is not NULL
 */
int for_each_list(linked_list *lst, int (*func)(void* , void* ), void* vd){
	int as;
	as = func(lst->value, vd);
	if(!as) return as;
	if(lst->next != NULL){
		return for_each_list(lst->next, func, vd);
	}
	return as;
}

/*
 * we assume that the argument lst is not NULL
 */
void free_LL(linked_list *lst){
	free(lst->value);
	if(lst->next != NULL) free_LL(lst->next);
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

	res->add = add_LL;
	res->for_each = for_each_list;
	res->free = free_LL;

	return res;
}
