/*
 * create_graph.c
 *
 *  Created on: 25 Jun 2020
 *      Author: computer
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <time.h>
#include <string.h>


int string_to_int(char* s){
	int res, i;
	res = 0;
	for(i = 0; i < (int)strlen(s); i++){
		res = res * 10 + (s[i] - '0');
	}
	return res;
}

/*
 * input: size of graph, name of output file, (optional) number of clusters 
 */
int main(int argc, char* argv[]){
	int n, i, zero;
	FILE* file;
	assert(argc > 2);
  srand(time(NULL));
	n = string_to_int(argv[1]);
	file = fopen(argv[2], "w");
  zero = 0;
	fwrite(&n, sizeof(int), 1, file);
    for(i = 0; i < n; i++){
      fwrite(&zero, sizeof(int), 1, file);
    }
	fclose(file);
	return 0;
}

