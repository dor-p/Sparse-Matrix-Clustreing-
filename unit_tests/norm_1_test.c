/*
 * norm_1_test.c
 *
 *  Created on: 24 Jul 2020
 *      Author: computer
 */

#include "norm_1.h"
#include "spmat_lists.h"
#include <stdio.h>
#include <math.h>

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

	return 0.0;
}*/
