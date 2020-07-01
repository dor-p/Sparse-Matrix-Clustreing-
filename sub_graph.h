/*
 * sub_graph.h
 *
 *  Created on: 1 Jul 2020
 *      Author: computer
 */

#ifndef SUB_GRAPH_H_
#define SUB_GRAPH_H_

#include "spmat_lists.h"

/*
 * given a graph G (in spmat) and a subset of its indices,
 * return a pointer to the adjacency matrix of the subset
 */
spmat_lists* get_subA(spmat_lists* G, int* subset, int sub_size);

#endif /* SUB_GRAPH_H_ */
