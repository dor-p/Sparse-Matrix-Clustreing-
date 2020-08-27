/*
 * main.c
 *
 *  Created on: 24 Jun 2020
 *      Author: computer
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <time.h>
#include <string.h>

int main(int argc, char* argv[]){
	int curr, i, j, n, k;
    FILE *file;
    file = fopen(argv[1], "r");
    fread(&curr, sizeof(int), 1, file);
    printf("%d\n", curr);
    n = curr;
    for(i = 0; i < n; i++){
        fread(&k, sizeof(int), 1, file);
        for(j = 0; j < k; j++){
            fread(&curr, sizeof(int), 1, file);
            printf("%d ", curr);
        }
        printf("\n");
    }
    fclose(file);
    return 0;
}
