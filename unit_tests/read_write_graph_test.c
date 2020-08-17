/*
 * read_write_graph_test.c
 *
 *  Created on: 24 Jul 2020
 *      Author: computer
 */

#include "read_write_graph.h"
#include "linked_list.h"
#include "spmat_lists.h"
#include "set_of_sets.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void graph_row_to_vec(int k, FILE *file, int* target){
	int i, tmp;
	for(i = 0; i < k; i++){
		fread(&tmp, sizeof(int), 1, file);
		target[tmp] = tmp;
	}
}

void print_graph(spmat_lists *A){
  int i;
  linked_list *curr;

  for(i = 0; i < n; i++){
    curr = A->rows[i];
    while(curr != NULL){
      printf("%d ", *(int*)curr->value);
    }
    printf("\n");
  }
}



/*
int main(int argc, char* argv[]){
	int n, k, i, *row;
	FILE* file;
	spmat_lists *A;
	linked_list *curr;
	set_of_sets* S;

	assert(argc > 2);
	file = fopen(argv[1], "r");
	fread(&n, sizeof(int), 1, file);
	A = spmat_lists_allocate(n);
	row = (int*)malloc(n * sizeof(int));
	read_graph(file, A);
	fclose(file);
	S = allocate_set_of_sets();
	for(i = 0; i < n; i++){
		curr = A->rows[i];
		k = curr->size;
		while(curr != NULL){
			row[k - curr->size] = *(int*)curr->value;
			curr = curr->next;
		}
		S->add(S, row, k);
	}

	file = fopen(argv[2], "w");
	write_sets(file, S);
	fclose(file);

	free(row);
	S->free(S);
	A->free(A);

	return 0;
}*/
