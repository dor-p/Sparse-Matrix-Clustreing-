/*
 * read_write_graph.h
 *
 *  Created on: 30 Jun 2020
 *      Author: computer
 */

#ifndef READ_WRITE_GRAPH_H_
#define READ_WRITE_GRAPH_H_

#include "spmat_lists.h"
#include "set_of_sets.h"
#include <stdio.h>


/*
 * reads the graph from input file, and writes it to a sparse matrix
 * the rows in the resulting sparse matrix should be sorted
 */
int read_graph(FILE* file, spmat_lists* matrix);

/*
 * writes the result of the program into file from s_of_s.
 * number sets, then size of first set, then indices that
 * are in the first set and so on.
 */
int write_sets(FILE* file, set_of_sets* s_of_s);

#endif /* READ_WRITE_GRAPH_H_ */
