/*
 * spmat_lists.h
 *
 *  Created on: 16 Jun 2020
 *      Author: computer
 */

#ifndef SPMAT_LISTS_H_
#define SPMAT_LISTS_H_

#include "linked_list.h"

typedef struct _spmat_lists{
	/* Matrix size (n*n) */
		int		n;

		/* Adds row i the matrix. Called before any other call,
		 * exactly n times in order (i = 0 to n-1) */
		int	(*add_row)(struct _spmat_lists *A, const int *row, int i);

		/* Frees all resources used by A */
		void	(*free)(struct _spmat_lists *A);

		/*Array of matrix rows*/
		linked_list	**rows;

} spmat_lists;

/* Allocates a new linked-lists sparse matrix of size n */
spmat_lists*  spmat_lists_allocate(int n);

#endif /* SPMAT_LISTS_H_ */
