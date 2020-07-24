/*
 * read_write_graph_test.c
 *
 *  Created on: 24 Jul 2020
 *      Author: computer
 */

#include "read_write_graph.h"


void graph_row_to_vec(int k, FILE *file, int* target){
	int i, tmp;
	for(i = 0; i < k; i++){
		fread(&tmp, 1, file, sizeof(int));
		target[tmp] = tmp;
	}
}
