/*
 * int_set.h
 *
 *  Created on: 21 Jun 2020
 *      Author: computer
 */

#ifndef SET_OF_SETS_H_
#define SET_OF_SETS_H_

#include "linked_list.h"

typedef struct _int_set {
	int *values;
	int size;
} int_set;

typedef struct _set_of_sets {

	/*
	 * linked list, each node points to a linked list of integers
	 */
	linked_list* sets;

	/*
	 * number of sets currently in this struct
	 */
	int N;

	/*
	 * the size of the next set to be retrieved by pop.
	 * if there are no sets, returns a non-positive value (say 0)
	 */
	int sizeof_next;

	/*
	 * add this array values as another set
	 * return value indicates successful use
	 */
	int (*add)(struct _set_of_sets*, int *values, int size);

	/*
	 * copies a set into target and deletes it from here.
	 * target must have enough memory allocated to it
	 * the value needed should be retrieved by using get_sizeof_next
	 * return value indicates successful use
	 */
	int (*pop)(struct _set_of_sets*, int *target);

	/*
	 * free all resources allocated to this struct
	 */
	void (*free)(struct _set_of_sets*);

} set_of_sets;

/*allocate a new set of sets*/
set_of_sets* allocate_set_of_sets();

#endif /* SET_OF_SETS_H_ */
