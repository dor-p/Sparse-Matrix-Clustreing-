/*
 * cluster.c
 *
 *  Created on: 1 Jul 2020
 *      Author: computer
 */

#include "spmat_lists.h"
#include "set_of_sets.h"
#include "b_matrix.h"
#include "norm_1.h"
#include "modularity_maximization.h"
#include "power_iteration.h"
#include "sub_graph.h"
#include "read_write_graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>


/*
 * swap the values for two given pointers
 */
void swap_int(int* a, int* b){
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

/*
 * this takes care of matrix shifting
 * after running this function we'll want to run modularity maximization
 */
void split_group(B_matrix* hatB, double *eigen_value, double *s){
	double norm;
	norm = norm_1(hatB);
	hatB->lambda = norm;
	power_iteration(hatB, eigen_value, s);
	hatB->lambda -= norm;
	*eigen_value -= norm;
}

/*
 * given a division into two groups (after modularity maximization)
 * this function puts the values of group into g1, g2 and than
 * puts g1, g2 into P or O depending on size
 */
void groups_to_res(set_of_sets* P, set_of_sets* O, double *s,
										int *group, int size){
	int g1, g2, i;

	g1 = 0;
	g2 = 0;
	for(i = 0; i < size; ){
		if(s[i] > 0.0){
			g1++;
			i++;
		}
		else{
			if(i + g2 >= size) break;
				swap_int(group + i, group + size - 1 - g2);
				g2++;
			}
		}

	if(g1 * g2 == 0) O->add(O, group, size);
	else{
		if(g1 == 1){
			O->add(O, group, 1);
		}
		else{
			P->add(P, group, g1);
		}
		if(g2 == 1){
			O->add(O, group + size - 1, 1);
		}
		else{
			P->add(P, group + size - g2, g2);
		}
	}
}

/*
 * function for initiating resources for parse_clusters
 */
int init_parse(int **curr, double **s1, double **s2, int size,
					spmat_lists* A, B_matrix **B){
	int i, *k, M;
	*curr = (int*)malloc(size * sizeof(int));
	*s1 = (double*)malloc(size * sizeof(double));
	*s2 = (double*)malloc(size * sizeof(double));
	k = (int*)malloc(size * sizeof(int));
	if(*curr == NULL || *s1 == NULL || *s2 == NULL || k == NULL){
		if(*curr != NULL) free(*curr);
		if(*s1 != NULL) free(*s1);
		if(*s2 != NULL) free(*s2);
		if(k != NULL) free(k);
		return 0;
	}

	M = 0;
	for(i = 0; i < size; i++){
		k[i] = A->rows[i]->size;
		M += k[i];
	}

	*B = allocate_B(A, k, M);
	if(*B == NULL){
		free(*curr);
		free(*s1);
		free(*s2);
		return 0;
	}
	return 1;
}

/*
 * this function implements the algorithm
 * given P = {{1,...,n}}, O = {} and A represents the graph
 */
int parse_clusters(set_of_sets* P, set_of_sets* O, spmat_lists* A){
	int size, *curr;
	double eigen_value;
	double *s1, *s2;
	B_matrix *hatB, *B;
	spmat_lists* subA;

	size = A->n;
  /*printf("size = %d", size);*/
	if(!init_parse(&curr, &s1, &s2, size, A, &B)) return 0;
  /*printf("size = %d", size);*/
	while(size > 0){
    /*printf("P = %p, curr = %p", (void*)P, (void*)curr);*/
		if(!P->pop(P, curr)){
			free(curr);
			free(s1);
			free(s2);
			return 0;
		}

		subA = get_subA(A, curr, size);
		if(subA == NULL){
			free(curr);
			free(s1);
			free(s2);
			B->free(B);
			return 0;
		}
		hatB = get_hatB_g(subA, curr, B);
		if(hatB == NULL){
			free(curr);
			free(s1);
			free(s2);
			B->free(B);
			subA->free(subA);
			return 0;
		}

		split_group(hatB, &eigen_value, s1);

		modularity_maximization(hatB, s1);

		hatB->multiply_vec(hatB, s1, s2);

		if(eigen_value <= 0.0) O->add(O, curr, size);

		else if(dot_product(s1, s2, size) <= 0) O->add(O, curr, size);

		else groups_to_res(P, O, s2, curr, size);

		hatB->free(hatB);
		size = P->sizeof_next;
	}
	free(curr);
	free(s1);
	free(s2);
	return 1;
}

/*
 * function for exiting correctly if an error should happen
 */
void main_error(char *s){
	printf("%s\n", s);
	/*TODO free all memory*/
}

/*
 *
 */
int main(int argc, char* argv[]){
	int n, *v;
	set_of_sets *O, *P;
	spmat_lists* A;
	FILE *file;

	if(argc < 3) main_error("Program is missing arguments");
	file = fopen(argv[1], "r");
	if(file == NULL) main_error("Opening file for reading has failed");

	if(!fread(&n, 1, sizeof(int), file)) main_error("Reading from file has failed");

	A = spmat_lists_allocate(n);
	P = allocate_set_of_sets();
	O = allocate_set_of_sets();
	v = (int*)malloc(n * sizeof(int));
	if(P == NULL || O == NULL || A == NULL || v == NULL){
		if(P != NULL) free(P);
		if(O != NULL) free(O);
		if(A != NULL) free(A);
		if(v != NULL) free(v);
		main_error("Memory allocation of P, O, A or v has failed");
	}

	if(!read_graph(file, A)) main_error("Reading A has failed");
	fclose(file);

    if(!P->add(P, v, n)) main_error("Add to P has failed");
    /*printf("P = %p, A = %p", (void*)P, (void*)A);*/

	if(!parse_clusters(P, O, A)) main_error("Main algorithm has failed");

	file = fopen(argv[2], "w");
	if(file == NULL) main_error("Opening file for writing has failed");
	if(!write_sets(file, O)) main_error("Writing O has failed");
	fclose(file);

	free(v);
	P->free(P);
	O->free(O);
	A->free(A);

	return 0;
}
