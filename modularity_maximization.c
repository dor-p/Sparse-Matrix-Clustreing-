

#include "modularity_maximization.h"
#include "b_matrix.h"
#include "linked_list.h"
#include "power_iteration.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*helper function for allocating resources for modularity maximization*/
int allocate_MM_vectors(double **bestS, double **delta,
									double **stag, int **hasMoved, int n){
	*bestS = (double*)malloc(n * sizeof(double));
	if(*bestS == NULL) return 0;

	*stag = (double*)malloc(n * sizeof(double));
	if(*stag == NULL){
		free(*bestS);
	    return 0;
	}

	*delta = (double*)malloc(n * sizeof(double));
	if(*delta == NULL){
	    free(*bestS);
	    free(*stag);
	    return 0;
	}

	*hasMoved = (int*)malloc(n * sizeof(int));
	if(delta == NULL){
	    free(bestS);
	    free(stag);
	    free(delta);
	    return 0;
	}

	return 1;
}


int modularity_maximization(B_matrix* hatB, double *s){
  double M, bestM, *bestS, *delta, *stag;
  int i, j, k, con, changed, moved, *hasMoved;
  linked_list *currentNode;

  if(!allocate_MM_vectors(&bestS, &delta, &stag, &hasMoved, hatB->n)) return 0;

  memcpy(bestS, s, hatB->n);
  hatB->multiply_vec(hatB, bestS, s);
  bestM = 0.5 * dot_product(s, bestS, hatB->n);

  do{
    memcpy(s, bestS, hatB->n * sizeof(double));
    M = bestM;
    memset(hasMoved, 0, hatB->n * sizeof(int));
    moved = 0;
    memcpy(stag, bestS, hatB->n * sizeof(double));

    while(moved < hatB->n){

      for(i = 0; i < hatB->n; i++){
        delta[i] = 2 * hatB->diagonal[i];
      }

      for(i = 0; i < hatB->n; i++){
        currentNode = hatB->A->rows[i];
        for(j = 0; j < hatB->n; j++){
          con = currentNode != NULL && *(int*)currentNode->value == j;
          delta[i] -= 2 * stag[i] * stag[j] * hatB->to_value(hatB, i, j, con);
          if(con) currentNode = currentNode->next;
        }
      }

      for(i = 0; i < hatB->n; i++){
         if(!hasMoved[i]){
        	 k = i;
        	 break;
         }
       }
      for(; i < hatB->n; i++){
        if(delta[i] > delta[k] && !hasMoved[i]) k = i;
      }
      M += delta[k];
      stag[k] *= -1;

      moved++;
      hasMoved[k] = 1;

      if(IS_POSITIVE(M - bestM)){
        bestM = M;
        memcpy(bestS, stag, hatB->n * sizeof(double));
      }

    }

    changed = memcmp(bestS, s, hatB->n * sizeof(double));

  } while(changed);
  
  memcpy(s, bestS, hatB->n * sizeof(double));

  free(bestS);
  free(stag);
  free(delta);
  free(hasMoved);
  return 1;
}
