/*
 * linked_list.h
 *
 *  Created on: 16 Jun 2020
 *      Author: computer
 */

#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

typedef struct _linked_list {
	/*
	 * the value of the current node
	 */
	void *value;

	/*number of elements in this list*/
	int size;

	/*pointer to next node*/
	struct _linked_list *next;

	/*
	 * Add a new element at the start of the list
	 * return value represents a successful add
	 */
	int (*add)(struct _linked_list *lst, void *val);

	/*
	 * removes the first element and returns its value
	 */
	void* (*ecxtract_first)(struct _linked_list **lst);

	/*
	 * Free all nodes from this one to the end
	 */
	void	(*free)(struct _linked_list *lst);

} linked_list;

/*
 * Allocates a new linked-lists
 */
linked_list* allocate_list(void *val);


#endif /* LINKED_LIST_H_ */
