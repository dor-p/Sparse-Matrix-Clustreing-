/*
 * matrix_row.h
 *
 *  Created on: 16 Jun 2020
 *      Author: computer
 */

#ifndef MATRIX_ROW_H_
#define MATRIX_ROW_H_

#include "linked_list.h"

/*
 * node for matrix_row
 */
typedef struct _matrix_element {
	double value;
	int column;

} matrix_element;


typedef struct _matrix_row {
	/*
	 * the value of the current node
	 */
	linked_list* lst;

	/*
	 * Add a new element at the start of the list
	 * return value represents a successful add
	 */
	int (*add)(struct _matrix_row *row, double val, int column);

	/*
	 * Iterates over the row and and performs func on each value
	 */
	int (*for_each)(const struct _matrix_row *row, int (*func)(), void*);


	/*
	 * Free row and resources
	 */
	void	(*free)(struct _matrix_row *row);

} matrix_row;

/*
 * Allocates a new matrix row
 */
matrix_row* allocate_row();

#endif /* MATRIX_ROW_H_ */
