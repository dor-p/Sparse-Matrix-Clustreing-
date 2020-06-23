/*
 * norm_1.c
 *
 *  Created on: 16 Jun 2020
 *      Author: computer
 */

#include "norm_1.h"
#include "spmat_lists.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>

double norm_1_arrays(int n, double A[][n]){
	int i,j;
	double res, col;
	res = 0.0;
	for(j = 0; j < n; j++){
		col = 0.0;
		for(i = 0; i < n; i++){
			col += fabs(A[i][j]);
		}
		if(col > res) res = col;
	}
	return res;
}
/*
double norm_1_test(int n, double A[][n]){
	int i;
	spmat_lists* A;
	A = spmat_lists_allocate(n);
	assert(A != NULL);

	for(i = 0; i < n; i++){
		A->add_row(A, A[i], i);
	}
	return norm_1(B);
}*/

int string_to_int(char *s){
	int res, len, i;
	len = strlen(s);
	for(i=0; i < len; i++){
		res = res * 10 + ( s[i] - '0' );
	}
	return res;
}

int main(){
	/*
	int i, j, n;
	assert(argc >= 0 );
	n = string_to_int(argv[1]);
	double A[n][n];

	srand(time(NULL));

	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			*A[i][j] = pow(-1, (double)(i + j)) * (i + j);*
			A[i][j] = (double)rand();
		}
	}

	printf("%d\n", n);

	if(norm_1_arrays(n, A) != norm_1_test(n, A)){
		printf("you have a problem with this matrix");
	}
	else{
		printf("all good here");
	}*/
	return 0;
}
