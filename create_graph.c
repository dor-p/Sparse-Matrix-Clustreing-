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
	for(i = 0; i < strlen(s); i++){
		res = res * 10 + (s[i] - '0');
	}
	return res;
}

int bernuly(int p, int q){
	int res;
	assert(0 <= p <= q);
	if(p == q) return 1;
	if(p == 0) return 0;
	res = (rand() % q) + 1;
	return res <= p;
}

/*
 * input: size of graph, name of output file, (optional) number of clusters 
 */
int main(int argc, char* argv[]){
	int n, k, is_out, i, j, deg;
	int *adj;
	FILE* file;
	assert(argc > 2);
    srand(time(NULL));
	n = string_to_int(argv[1]);
	file = fopen(argv[2], "w");
	fwrite(&n, sizeof(int), 1, file);
    adj = (int*)calloc(n * n, sizeof(int));
	if(argc > 3){
		k = string_to_int(argv[3]);
		assert(k <= n);
	}
	else{
		k = (rand() % (n / 2))+ 1;
	}
	
    for(i = 0; i < n; i++){
        for(j = i + 1; j < n; j++){
            if((k * (i / k)) <= j && j <= (k * ((i / k) + 1))){
                is_out = bernuly(n - k, n);
            }
            else{
                is_out = bernuly(1, n);
            }
            if(is_out){
                adj[i * n + j] = 1;
                adj[j * n + i] = 1;
            }
        }
    }
    for(i = 0; i < n; i++){
        deg = 0;
        for(j = 0; j < n; j++){
            if(adj[i * n + j]) deg++;
        }
        fwrite(&deg, sizeof(int), 1, file);
        for(j = 0; j < n; j++){
            if(adj[i * n + j]){
                fwrite(&j, sizeof(int), 1, file);
            }
        }
    }
    free(adj);
	fclose(file);
	return 0;
}

