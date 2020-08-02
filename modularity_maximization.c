
#include "modularity_maximization.h"
#include "b_matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int modularity_maximization(SparseMatrix* hatB, double *s){
  double bk, M, bestM, *bestS, *delta, *stag;
  int i, k, changed,moved, *hasMoved;
  Node *currentNode;

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
  bestM = dot(s, bestS, hatB->n);

  do{
    memcpy(s, bestS, hatB->n);
    M = bestM;
    for(i = 0; i < hatB->n; i++){
      hasMoved[i] = 0;
    }
    moved = 0;

    while(moved < hatB->n){
      matrix_mult_left(s, subModularity, stag);
      for(i = 0; i < hatB->n; i++){
        currentNode = hatB->rows[i];
        while(currentNode != NULL && currentNode->column < i){
          currentNode = currentNode->right;
        }
        bk = (currentNode != NULL && currentNode->column == i) ? currentNode->value : 0;
        delta[i] = s[i] * (2 * bk - stag[i]); 
      }

      for(i = 0; i < hatB->n; i++){
        currentNode = hatB->rows[i];
        while(currentNode != NULL){
          delta[currentNode->column] -= s[i] * s[currentNode->column] * currentNode->value;
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