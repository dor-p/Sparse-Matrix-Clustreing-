/*
 * helper_functions.c
 *
 *  Created on: 24 Jul 2020
 *      Author: computer
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <time.h>
#include <string.h>


int bernuly_test(int p, int q){
	int res;
	assert(0 <= p && p <= q);
	if(p == q) return 1;
	if(p == 0) return 0;
	res = (rand() % q) + 1;
	return res <= p;
}

int string_to_int(char *s){
	int res, len, i;
	len = strlen(s);
	res = 0;
	for(i=0; i < len; i++){
		res = res * 10 + ( s[i] - '0' );
	}
	return res;
}
