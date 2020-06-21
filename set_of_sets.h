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
	linked_list* sets;

	/*add this array values as another set
	 * return value indicates if add was successful
	 */
	int (*add)(struct _set_of_sets*, int *values, int size);

	/*the size of the next set to be retrieved
	 * if there are no sets if returns a non-positive value
	 */
	int (*get_sizeof_next)(struct _set_of_sets*);

	/*copies a set into target and deletes it from here
	 * target must have enough memory allocated to it
	 * the value needed should be retrieved by using get_sizeof_next
	 */
	int (*pop)(struct _set_of_sets*, int *target);

	/*free all resources allocated to this struct*/
	void (*free)(struct _set_of_sets*);

} set_of_sets;

/*allocate a new set of sets*/
set_of_sets* allocate_set_of_sets();

#endif /* SET_OF_SETS_H_ */
