/*
 * b_matrix_test.c
 *
 *  Created on: 28 Jul 2020
 *      Author: computer
 */


#include "linked_list.h"
#include "spmat_lists.h"
#include "b_matrix.h"
#include "read_write_graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

void print_double_vec(double *v, int n, int print_as_int){
	int i;
	for(i = 0; i < n; i++){
		if(print_as_int) printf("%d", (int)v[i]);
		else printf("%f", v[i]);
		if(i < n - 1) printf(", ");
	}
	printf("\n");
}

void sparse_to_full(B_matrix *B, double b[B->n][B->n]){
	int n, i, j, con;
	linked_list *curr;
	n = B->n;
	for(i = 0; i < n; i++){
			curr = B->A->rows[i];
			for(j = 0; j < n; j++){
				con = (curr != NULL && j == *(int*)curr->value);
				b[i][j] = B->to_value(B, i, j, con);
				if(con) curr = curr->next;
			}
		}
}

void multiply_full_vec(int n, double b[n][n], double *v, double *target){

}
/*
int main(int argc, char* argv[]){
	FILE *file;
	int n, M, *k, i, j;
	double d, *v, *bk, dk, *u, *b;
	spmat_lists *A;
	B_matrix *B;

	file = fopen(argv[1], "r");
	fread(&n, sizeof(int), 1, file);
	A = spmat_lists_allocate(n);
	read_graph(file, A);
	fclose(file);
	k = (int*)malloc(n * sizeof(int));
	M = 0;
	u = (double*)malloc(n * sizeof(double));
	for(i = 0; i < n; i++){
		k[i] = A->rows[i] != NULL ? A->rows[i]->size : 0;
		u[i] = (double)k[i];
		M += k[i];
	}
	B = allocate_B(A, k, M);
	b = (double*)malloc(n * n * sizeof(double));
	sparse_to_full(B, (double (*)[n])b);
	bk = (double*)malloc(n * sizeof(double));
	for(i = 0; i < n; i++){
		bk[i] = 0.0;
		for(j = 0; j < n; j++){
			bk[i] += b[i * n + j] * (double)k[j];
		}
	}
	v = (double*)malloc(n * sizeof(double));
	B->multiply_vec(B, u, v);
	d = dot_product(u, v, n);
	dk = dot_product(u, bk, n);

	print_graph(A);
	print_double_vec(u, n, 1);
	print_double_vec(v, n, 0);
	printf("%f\n", d);

	print_double_vec(bk, n, 0);
	printf("%f\n", dk);

	free(u);
	free(v);
	B->free(B);

	return 0;
}*/
