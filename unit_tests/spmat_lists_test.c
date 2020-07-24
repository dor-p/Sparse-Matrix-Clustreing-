/*
 * spmat_lists_test.c
 *
 *  Created on: 24 Jul 2020
 *      Author: computer
 */

#include "spmat_lists.h"
#include <stdio.h>

void get_vector(int n, int *v, int is_random, int (*f)(int)){
	int i;
	for(i = 0; i < n; i++){
		v[i] = is_random ? rand() : f(i);
	}
}

void multiply_matrix(int n, int mtrx[n][n], int *v, int *target){
	int i, j;
	for(i = 0; i < n; i++){
		target[i] = 0;
		for(j = 0; j < n; j++){
			target[i] += mtrx[i][j] * v[j];
		}
	}
}


void create_matrix(int n, int mtrx[n][n]){
	int i, j, ber;
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			ber = bernuly_test(1, n);
			mtrx[i][j] = ber ? rand() % (n*n) : 0;
		}
	}
}


int main(int argc, char *argv[]){
	int i, n, k, *mtrx, *v, t1, t2;
	spmat_lists *smtrx;
	linked_list *r;
	FILE *file;
	file = fopen(argv[1]);
	fread(&n, 1, file, sizeof(int));
	mtrx = (int*)malloc(n * n * sizeof(int));
	smtrx = spmat_lists_allocate(n);
	v = (int*)malloc(n * sizeof(int));
	t1 = (int*)calloc(n, sizeof(int));
	for(i = 0; i < n; i++){
		memcpy(v, t1, n);
		fread(&k, 1, file, sizeof(int));
		graph_row_to_vec(k, file, v);
		memcpy(mtrx + (i * n), v, n);
		smtrx->add_row(v);
	}
	fclose(file);

	t2 = (int*)malloc(n * sizeof(int));
	srand(time(NULL));
	get_vector(n, v, 1, NULL);
	multiply_matrix(n, (int *[n])mtrx, v, t1);

	for(i = 0; i < n; i++){
		r = smtrx->rows[i];
		t2[i] = 0;
		while(r != NULL){
			k = *(int*)(r->value);
			t2[k] += k * v[k];
		}
	}

	for(i = 0; i < n; i++){
		if(t1[i] != t2[i]){
			printf("error at index %d\nt1[%d] = %d, t2[%d] = %d\n", i, i, t1[i], i, t2[i]);
			break;
		}
	}

	smtrx->free(smtrx);
	free(mtrx);
	free(v);
	free(t1);
	free(t2);


	return 0;
}
