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

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[]){
  double *Mat, *s, ev;
  int *k;
  spmat_lists *A;
  B_matrix *B;
  FILE *file;
  assert(argc > 2);
  file = fopen(argv[1], "r");

  read_graph(file, A);
  fclose(file);

  k = (int*)calloc(B->n, sizeof(int));
  B = allocate_B(A, k, 1);
  memset(B->diagonal, 0, B->n * sizeof(double));

  s = (double*)malloc(B->n * sizeof(double));
  power_iteration(B, &ev, s);

file = fopen(argv[2], "w");
fwrite(s, sizeof(double), B->n, file);
fclose(file);
free(s);
B->free(B);
return 0;

}