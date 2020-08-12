/*
 * power_iteration_test.c
 *
 *  Created on: 24 Jul 2020
 *      Author: computer
 */

#include "power_iteration.h"
#include "read_write_graph.h"
#include "b_matrix.h"
#include "spmat_lists.h"
#include "linked_list.h"

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[]){
  double *s, ev, Mat;
  int *k, M, n, i, j;
  spmat_lists *A;
  B_matrix *B;
  FILE *file;
  linked_list *currentNode;
  assert(argc > 2);
  file = fopen(argv[1], "r");

  fread(&n, sizeof(int), 1, file);
  A = spmat_lists_allocate(n);
  read_graph(file, A);
  fclose(file);

  M = 0;
  k = (int*)calloc(n, sizeof(int));
  for(i = 0; i < n ;i++){
    k[i] = A->rows[i] != NULL ? A->rows[i]->size : 0;
    M += k[i];
  }
  B = allocate_B(A, k, M);
  Mat = (double*)malloc(n * n * sizeof(double));
  for(i = 0; i < hatB->n; i++){
      currentNode = hatB->A->rows[i];
      for(j = 0; j < hatB->n; j++){
        con = currentNode != NULL && *(int*)currentNode->value == j;
          Mat[i * n + j] = hatB->to_value(hatB, i, j, con);
          if(con) currentNode = currentNode->next;
        }
      }


  s = (double*)malloc(B->n * sizeof(double));
  power_iteration(B, &ev, s);

file = fopen(argv[2], "w");
fwrite(s, sizeof(double), B->n, file);
fclose(file);
free(s);
B->free(B);
return 0;

}