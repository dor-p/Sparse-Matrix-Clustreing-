/*
 * sub_graph.h
 *
 *  Created on: 1 Jul 2020
 *      Author: computer
 */

#ifndef SUB_GRAPH_H_
#define SUB_GRAPH_H_

#include "spmat_lists.h"
#include "b_matrix.h"

/*
 * given a graph G (in spmat) and a subset of its indices,
 * return a pointer to the adjacency matrix of the subset
 */
spmat_lists*  get_subA(spmat_lists* G, int* subset, int sub_size);

/*
 * get B_marix of sub_graph
 * hatB[i][j] = B[i][j] - delta[i][j]*fg[i]
 * i' because the number i vertex in this subset corresponds
 * to the number i' vertex of the entire graph 
 * (check project instructions page 4 for clarification)
 */
B_matrix* get_hatB_g(spmat_lists* subA, int* subset, B_matrix *B);

#endif /* SUB_GRAPH_H_ */
