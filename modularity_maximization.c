
#include "modularity_maximization.h"
#include "b_matrix.h"
#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int modularity_maximization(b_matrix* hatB, double *s){
  double bk, M, bestM, *bestS, *delta, *stag;
  int i, j, k, con, changed, moved, *hasMoved;
  linked_list *currentNode;

  bestS = (double*)malloc(hatB->n * sizeof(double));
  if(bestS == NULL){
    free(bestS);
    return 0;
  }

  stag = (double*)malloc(hatB->n * sizeof(double));
  if(stag == NULL){
    free(bestS);
    free(stag);
    return 0;
  }

  delta = (double*)malloc(hatB->n * sizeof(double));
  if(delta == NULL){
    free(bestS);
    free(stag);
    free(delta);
    return 0;
  }

  hasMoved = (int*)malloc(hatB->n*sizeof(int));
  if(delta == NULL){
    free(bestS);
    free(stag);
    free(delta);
    free(hasMoved);
    return 0;
  }

  memcpy(bestS, s, hatB->n);
  matrix_mult_left(s, subModularity, s);
  bestM = dot_product(s, bestS, hatB->n);

  do{
    memcpy(s, bestS, hatB->n);
    M = bestM;
    for(i = 0; i < hatB->n; i++){
      hasMoved[i] = 0;
    }
    moved = 0;

    while(moved < hatB->n){
      hatB->multiply_vec(hatB, s, stag);

      for(i = 0; i < hatB->n; i++){
        bk = hatB->diagonal[i] * s[i];
        delta[i] = s[i] * (2 * bk - stag[i]); 
      }

      for(i = 0; i < hatB->n; i++){
        currentNode = hatB->A->rows[i];
        for(j = 0; j < hatB->n; j++){
          con = currentNode != NULL && *(int*)currentNode->value == j;
          dleta[j] -= s[i] * s[j] * hatB->to_value(hatB, i, j, con);
          if(con) currentNode = currentNode->next;
        }
      }

      k = 0;
      for(i = 0; i < hatB->n; i++){
        if(delta[i] > delta[k]) k = i;
      }
      M += delta[k];
      memcpy(stag, s, hatB->n);
      stag[k] *= -1;

      moved++;
      hasMoved[k] = 1;

      if(M > bestM){
        bestM = M;
        memcpy(bestS, stag, hatB->n);
      }

    }

    changed = 0;
    for(i = 0; i < hatB->n; i++){
      if(bestS[i] != s[i]){
        changed = 1;
        break;
    }

  } while(changed);
  
  memcpy(s, bestS, hatB->n);

  free(bestS);
  free(stag);
  free(delta);
  free(hasMoved);
  return 1;
}